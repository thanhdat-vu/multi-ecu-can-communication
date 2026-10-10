#include "EcuM.h"
#include "OsIf.h"
#include "AbsNodeS.h"
#include "Project_Cfg.h"

int main(void)
{
    EcuM_Init();
    EcuM_StartupTwo();
    AbsNodeS_Init();

    while (1) {
        EcuM_MainFunction();
        AbsNodeS_MainFunction();
        OsIf_DelayMs(ABS_MAIN_PERIOD_MS);
    }
}

void NMI_Handler(void){
    while(1){}
}
void HardFault_Handler(void){
    while(1){}
}
void MemManage_Handler(void){
    while(1){}
}
void BusFault_Handler(void){
    while(1){}
}
void UsageFault_Handler(void){
    while(1){}
}
void SVC_Handler(void){}
void DebugMon_Handler(void){}
void PendSV_Handler(void){}
