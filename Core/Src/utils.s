.syntax unified

.global Delay_Handler
.global Delay


    .section  .text.Delay_Handler
    .type Delay_Handler, %function
Delay_Handler:
  @ push {r10, fp, lr}
  @ mov r10, r0
  @ add r0, r10, r10
  @ pop {r10, fp, pc}
  bx lr
  .size  Delay_Handler, .-Delay_Handler


    .section  .text.Delay
    .type Delay, %function
Delay:
  ldr r1, =2600
  mul r0, r0, r1
  _LOOP_:
    subs r0, r0, 1
    bpl _LOOP_
  bx lr
  .size  Delay, .-Delay



