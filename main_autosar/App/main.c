#include "EcuM.h"
#include "MainNodeS.h"
#include "OsIf.h"
#include "Det.h"

int main(void)
{
    EcuM_Init();
    EcuM_StartupTwo();
    MainNodeS_Init();

    Det_Printf("MAIN READY | TX_ABS:0x121 | RX_AIRBAG:0x111 | RX_ABS:0x122 | CAN_DIAG:0x211\r\n");
    Det_Printf("=============================\r\n\r\n");

    while (1) {
        EcuM_MainFunction();
        MainNodeS_MainFunction();
        OsIf_DelayMs(20U);
    }
}
