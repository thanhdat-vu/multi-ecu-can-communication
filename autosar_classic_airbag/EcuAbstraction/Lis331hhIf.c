#include "Lis331hhIf.h"
#include "I2c.h"
#include "OsIf.h"
static uint8 who_am_i;
uint8 Lis331hhIf_GetWhoAmI(void){
    return who_am_i;
}
Std_ReturnType Lis331hhIf_Init(void){
    uint8 id=0U;
    if(I2c_ReadReg(LIS331HH_I2C_ADDR,LIS331HH_WHO_AM_I_REG,&id)!=E_OK){
        return E_NOT_OK;
    }
    who_am_i=id;
    if(who_am_i!=LIS331HH_WHO_AM_I_VALUE){
        return E_NOT_OK;
    }
    if(I2c_WriteReg(LIS331HH_I2C_ADDR,LIS331HH_CTRL_REG1,LIS331HH_CTRL1_VALUE)!=E_OK){
        return E_NOT_OK;
    }
    if(I2c_WriteReg(LIS331HH_I2C_ADDR,LIS331HH_CTRL_REG4,LIS331HH_CTRL4_VALUE)!=E_OK){
        return E_NOT_OK;
    }
    OsIf_DelayMs(10U);
    return E_OK;
}
Std_ReturnType Lis331hhIf_ReadAxes(Lis331hhIf_AxesType *axes){
    uint8 buf[6];
    sint16 raw_x,raw_y,raw_z;
    if(axes==NULL_PTR) return E_NOT_OK;
    if(I2c_ReadRegMulti(LIS331HH_I2C_ADDR,(LIS331HH_OUT_X_L|0x80U),buf,6U)!=E_OK){
        return E_NOT_OK;
    }
    raw_x=(sint16)(((uint16)buf[1]<<8)|buf[0]);
    raw_y=(sint16)(((uint16)buf[3]<<8)|buf[2]);
    raw_z=(sint16)(((uint16)buf[5]<<8)|buf[4]);
    axes->x=(sint16)(raw_x>>4);
    axes->y=(sint16)(raw_y>>4);
    axes->z=(sint16)(raw_z>>4);
    return E_OK;
}
uint8 LIS331HHIF_Init(void){
    return (Lis331hhIf_Init()==E_OK)?1U:0U;
}
uint8 LIS331HHIF_ReadAxes(LIS331HH_Axes_t *axes){
    return (Lis331hhIf_ReadAxes(axes)==E_OK)?1U:0U;
}
uint8 LIS331HHIF_GetWhoAmI(void){
    return Lis331hhIf_GetWhoAmI();
}
