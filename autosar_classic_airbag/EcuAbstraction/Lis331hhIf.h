#ifndef LIS331HHIF_H
#define LIS331HHIF_H
#include "Std_Types.h"
#include "Lis331hhIf_Types.h"
#include "Lis331hhIf_Cfg.h"
Std_ReturnType Lis331hhIf_Init(void);
Std_ReturnType Lis331hhIf_ReadAxes(Lis331hhIf_AxesType *axes);
uint8 Lis331hhIf_GetWhoAmI(void);
uint8 LIS331HHIF_Init(void);
uint8 LIS331HHIF_ReadAxes(LIS331HH_Axes_t *axes);
uint8 LIS331HHIF_GetWhoAmI(void);
#endif
