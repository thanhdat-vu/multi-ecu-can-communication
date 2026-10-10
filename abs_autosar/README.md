ABS AUTOSAR Classic Lite - STM32F103 register-level

- Luồng truyền CAN TX: AbsNodeS -> Rte_Abs -> ComIf -> PduR -> CanIf -> Can -> bxCAN.
- Luồng nhận CAN RX: bxCAN -> Can -> CanIf -> PduR -> ComIf -> Rte_Abs -> AbsNodeS.
- Giữ nguyên chức năng điều khiển motor/encoder/PWM và giữ frame CAN cũ.

Cấu trúc layer:
- App: main loop, gọi EcuM và SWC.
- Swc: AbsNodeS, xử lý logic ABS.
- Rte: Rte_Abs, cổng gọi giữa SWC và BSW/EcuAbstraction.
- EcuAbstraction: ComIf, MotorIf.
- Bsw: EcuM, BswM, CanIf, PduR.
- Mcal: Mcu, Dio, Uart, Pwm_Encoder, Can register-level bxCAN.
- Services: Det, OsIf, SchM.
- Config: Project_Cfg.h.

CAN frame chuẩn:
- RX CAN ID 0x121 từ Main: ADC low/high nibble, brake, direction, sequence.
- TX CAN ID 0x122 về Main: wheel1_speed, wheel2_speed, motor_state, sequence.
- TX diagnostic ID 0x212: LEC, TEC, REC, EWGF, EPVF, BOFF, errorState, controllerMode.
- CAN bitrate: 500 kbps.

UART:
- USART2 PA2/PA3, 115200 bps.

Build:
mingw32-make clean
mingw32-make

Flash:
mingw32-make flash
hoặc:
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program abs_autosar_reg_f103.elf verify reset exit"

Ghi chú:
- Đây là AUTOSAR Classic-like/manual, không dùng ARXML hay generator.
