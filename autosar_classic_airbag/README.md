Dự án này là bản tái cấu trúc thủ công theo hướng AUTOSAR Classic cho demo túi khí chạy bare-metal trên STM32F103. Dự án **không tuyên bố tuân thủ AUTOSAR đầy đủ** vì không sử dụng ARXML, RTE tự sinh hoặc công cụ cấu hình BSW.

## Các lớp kiến trúc

* `Base`: các kiểu dữ liệu nền tảng, kiểu dữ liệu chuẩn và compiler abstraction theo phong cách AUTOSAR.
* `Mcal`: các driver mức thanh ghi cho MCU, DIO, UART, I2C, CAN.
* `EcuAbstraction`: lớp trừu tượng cho cảm biến LIS331HH, buzzer và thông điệp kích hoạt túi khí.
* `Services`: logging kiểu DET và các hàm hỗ trợ thời gian kiểu OS interface.
* `Rte`: RTE facade được viết thủ công cho SWC túi khí.
* `Swc`: software component ứng dụng `AirbagS`.
* `App`: tích hợp khởi động và vòng lặp lập lịch chính.

## Giới hạn

Mô tả phù hợp nhất: **triển khai thủ công theo hướng AUTOSAR Classic-like, không sử dụng công cụ thương mại**. Đây không phải là hệ thống tuân thủ AUTOSAR đầy đủ. Các thành phần AUTOSAR đầy đủ còn thiếu gồm ARXML, RTE tự sinh, EcuM/BswM/SchM hoàn chỉnh, MemMap sections, stack Com/PduR/CanIf đầy đủ, hành vi DEM/DET đúng chuẩn đặc tả và cơ chế sinh task từ OS.

## Nâng cấp Level 3-lite AUTOSAR Classic-like

Phiên bản này vẫn giữ hướng triển khai thủ công và bare-metal, nhưng đẩy kiến trúc đến gần hơn với phân lớp AUTOSAR Classic:

* `Base/MemMap.h`: mẫu include memory mapping nhẹ theo phong cách AUTOSAR.
* `Services/SchM.*`: API Scheduler Manager cho exclusive area.
* `Bsw/EcuM.*`: quản lý quá trình khởi động ECU và điều phối các BSW main-function theo chu kỳ.
* `Bsw/BswM.*`: bộ quản lý mode/state BSW tối giản.
* `Bsw/CanIf.*`: lớp CAN Interface nằm trên MCAL CAN.
* `Bsw/PduR.*`: lớp PDU Router tối giản cho tín hiệu kích hoạt túi khí.
* `EcuAbstraction/ComIf.*`: truyền dữ liệu thông qua chuỗi `PduR -> CanIf -> Can` thay vì gọi trực tiếp MCAL CAN.
* `App/main.c`: quá trình khởi động được chuyển qua `EcuM_Init()` / `EcuM_StartupTwo()`, và khi chạy chương trình sẽ gọi `EcuM_MainFunction()` trước runnable của SWC.

Phiên bản này vẫn chưa phải là một stack AUTOSAR tuân thủ chuẩn trong môi trường sản xuất vì được viết thủ công và không sử dụng công cụ sinh ARXML/RTE/BSW.