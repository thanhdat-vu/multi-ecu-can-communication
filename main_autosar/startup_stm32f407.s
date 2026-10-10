.syntax unified
.cpu cortex-m4
.thumb

.global g_pfnVectors
.global Reset_Handler

.section .text.Reset_Handler,"ax",%progbits
.weak Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
  ldr sp, =_estack

  ldr r0, =_sidata
  ldr r1, =_sdata
  ldr r2, =_edata

copy_data:
  cmp r1, r2
  bcc copy_data_loop
  b zero_bss

copy_data_loop:
  ldr r3, [r0], #4
  str r3, [r1], #4
  b copy_data

zero_bss:
  ldr r1, =_sbss
  ldr r2, =_ebss
  movs r3, #0

zero_bss_loop:
  cmp r1, r2
  bcc zero_bss_store
  b call_main

zero_bss_store:
  str r3, [r1], #4
  b zero_bss_loop

call_main:
  bl main

hang:
  b hang

.size Reset_Handler, .-Reset_Handler

.weak NMI_Handler
.weak HardFault_Handler
.weak MemManage_Handler
.weak BusFault_Handler
.weak UsageFault_Handler
.weak SVC_Handler
.weak DebugMon_Handler
.weak PendSV_Handler
.weak SysTick_Handler
.weak CAN1_RX1_IRQHandler

.thumb_set NMI_Handler, Default_Handler
.thumb_set HardFault_Handler, Default_Handler
.thumb_set MemManage_Handler, Default_Handler
.thumb_set BusFault_Handler, Default_Handler
.thumb_set UsageFault_Handler, Default_Handler
.thumb_set SVC_Handler, Default_Handler
.thumb_set DebugMon_Handler, Default_Handler
.thumb_set PendSV_Handler, Default_Handler
.thumb_set SysTick_Handler, Default_Handler
.thumb_set CAN1_RX1_IRQHandler, Default_Handler

.section .text.Default_Handler,"ax",%progbits
Default_Handler:
  b Default_Handler

.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object

g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler

  .word Default_Handler /* WWDG */
  .word Default_Handler /* PVD */
  .word Default_Handler /* TAMP_STAMP */
  .word Default_Handler /* RTC_WKUP */
  .word Default_Handler /* FLASH */
  .word Default_Handler /* RCC */
  .word Default_Handler /* EXTI0 */
  .word Default_Handler /* EXTI1 */
  .word Default_Handler /* EXTI2 */
  .word Default_Handler /* EXTI3 */
  .word Default_Handler /* EXTI4 */
  .word Default_Handler /* DMA1_Stream0 */
  .word Default_Handler /* DMA1_Stream1 */
  .word Default_Handler /* DMA1_Stream2 */
  .word Default_Handler /* DMA1_Stream3 */
  .word Default_Handler /* DMA1_Stream4 */
  .word Default_Handler /* DMA1_Stream5 */
  .word Default_Handler /* DMA1_Stream6 */
  .word Default_Handler /* ADC */
  .word Default_Handler /* CAN1_TX */
  .word Default_Handler /* CAN1_RX0 */
  .word CAN1_RX1_IRQHandler /* CAN1_RX1 */

.size g_pfnVectors, .-g_pfnVectors