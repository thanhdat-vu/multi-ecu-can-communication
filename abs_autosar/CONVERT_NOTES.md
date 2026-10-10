# ABS AUTOSAR-lite conversion notes
## Final target
- MCU: STM32F103
- CAN bitrate: 500 kbps
- Main -> ABS command: 0x121
- ABS -> Main feedback: 0x122
- ABS diagnostic: 0x212

## New/updated layers
- `Config/Project_Cfg.h`: shared IDs, timing and clock configuration.
- `Rte/Rte_Abs.*`: SWC access ports for COM, CAN diagnostic, OS time, DET log and motor interface.
- `EcuAbstraction/ComIf.*`: COM abstraction for ABS feedback, diagnostic TX and Main command RX buffer.
- `EcuAbstraction/MotorIf.*`: motor/encoder abstraction over Dio and Pwm_Encoder.
- `Bsw/CanIf.*`: CAN Interface layer.
- `Bsw/PduR.*`: PDU routing for CAN TX and RX.
- `Bsw/BswM.*`: basic state manager hook.
- `Services/SchM.*`: exclusive-area hooks.
- `Mcal/Can.*`: AUTOSAR-like Can driver API with bxCAN register-level implementation.

## Data path
TX:
`AbsNodeS -> Rte_Abs -> ComIf -> PduR -> CanIf -> Can -> bxCAN`

RX:
`bxCAN -> Can -> CanIf -> PduR -> ComIf -> Rte_Abs -> AbsNodeS`

## Validation in sandbox
- Host C syntax check passed with GCC using all project include paths.
- Full ARM build could not be executed in this sandbox because `arm-none-eabi-gcc` is not installed here.
