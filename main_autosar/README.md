# STM32F407 Main ECU 
Main ECU cho hệ thống đa ECU CAN:

- MCU: STM32F407, Cortex-M4.
- CAN: bxCAN register-level, 500 kbps, CAN1 PD0/PD1.
- LCD: HD44780 qua PCF8574 I2C.
- Input: ADC + brake/direction switches.

## CAN Matrix

| Direction | CAN ID | DLC | Payload |
|---|---:|---:|---|
| Main -> ABS | `0x121` | 5 | `ADC_L, ADC_H, Brake, Direction, Seq` |
| ABS -> Main | `0x122` | 4 | `Wheel1, Wheel2, MotorState, Seq` |
| Airbag -> Main | `0x111` | 2 | `Deploy, Seq` |
| Main diagnostic | `0x211` | 8 | `LEC, TEC, REC, EWGF, EPVF, BOFF, ErrorState, ControllerMode` |

## Layering

Luồng TX Main -> ABS:

```text
Swc/MainNodeS -> Rte/Rte_Main -> EcuAbstraction/ComIf -> Bsw/PduR -> Bsw/CanIf -> Mcal/Can -> bxCAN
```

Luồng RX ABS/Airbag -> Main:

```text
bxCAN IRQ/Poll -> Mcal/Can -> Bsw/CanIf -> Bsw/PduR -> EcuAbstraction/ComIf -> Rte/Rte_Main -> Swc/MainNodeS
```

## Folder structure

```text
App/              Main entry
Base/             AUTOSAR-like basic types/compiler/memmap
Config/           Project CAN IDs and timing constants
Bsw/              EcuM, BswM, CanIf, PduR
EcuAbstraction/   ComIf, LcdIf
Mcal/             Mcu, Dio, Adc, I2c, Uart, Can register drivers
Rte/              RTE facade for Main SWC
Services/         Det, OsIf, SchM
Swc/              MainNodeS runnable logic and SWC data
````

## Notes

Đây là AUTOSAR Classic thu gọn, không dùng ARXML/generated RTE/toolchain thương mại. 
