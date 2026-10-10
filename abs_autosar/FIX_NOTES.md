# ABS AUTOSAR register F103 - fix notes

Fixed against `autosar_classic_airbag` style:

- Removed stale `MainNodeS_Internal.h` dependency from `Services/Det.c` and `Services/OsIf.c`.
- Reworked `Det` like Airbag project: `Det_Init`, `Det_Start`, `Det_Print`, `Det_Printf`, `Det_ReportError`, `Det_ReportRuntimeError`.
- Reworked `OsIf` like Airbag project: time source comes from `Mcu_GetTick()`; no duplicate `SysTick_Handler`.
- Fixed `EcuM.c`: removed missing `Adc.h`/`I2c.h`, removed invalid `Mcu_InitClock()`/`Mcu_InitSysTick()` calls, and initialized only modules actually present in ABS.
- Added `Uart_SendByte()` and `Uart_SendBuffer()` wrappers so Services layer can print like the Airbag stack.
- Changed `App/main.c` to use AUTOSAR-like startup flow: `EcuM_Init()`, `EcuM_StartupTwo()`, `AbsNodeS_Init()`, then cyclic `EcuM_MainFunction()` + `AbsNodeS_MainFunction()`.
- Added `.vscode/c_cpp_properties.json` and `-I.` in Makefile include path.

Functional pins are kept aligned with the original F103 ABS HAL project:

- CAN1: PA11 RX, PA12 TX, 500 kbps, FIFO1, RX ID 0x121, TX ID 0x122, diag ID 0x212.
- USART2: PA2 TX, PA3 RX, 115200 baud.
- TIM1 PWM: PA8 CH1, PA9 CH2.
- TIM2 encoder: PA0/PA1.
- TIM3 encoder: PA6/PA7.
- Motor direction: PB0/PB1 and PA5/PA4.

Syntax check was run with host GCC using project include paths. Cross-build still requires `arm-none-eabi-gcc` installed locally.

Current update:
- Updated safety-priority CAN IDs: Main -> ABS = 0x121, ABS -> Main = 0x122, ABS diag = 0x212.
- Added sequence counter in ABS -> Main payload at Byte3.
- Added RX/TX counters and lost-frame statistics for UART test logs.
