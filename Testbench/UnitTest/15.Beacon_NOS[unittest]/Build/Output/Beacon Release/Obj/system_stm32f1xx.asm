	.cpu cortex-m3
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"system_stm32f1xx.c"
	.text
	.section	.text.SystemInit,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SystemInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	SystemInit, %function
SystemInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r4, r5}
	mov	r5, #10420224
	mov	r4, #134217728
	ldr	r3, .L4
	ldr	r2, .L4+4
	ldr	r1, [r3]
	ldr	r0, .L4+8
	orr	r1, r1, #1
	str	r1, [r3]
	ldr	r1, [r3, #4]
	ands	r2, r2, r1
	str	r2, [r3, #4]
	ldr	r2, [r3]
	bic	r2, r2, #17301504
	bic	r2, r2, #65536
	str	r2, [r3]
	ldr	r2, [r3]
	bic	r2, r2, #262144
	str	r2, [r3]
	ldr	r2, [r3, #4]
	bic	r2, r2, #8323072
	str	r2, [r3, #4]
	str	r5, [r3, #8]
	str	r4, [r0, #8]
	pop	{r4, r5}
	bx	lr
.L5:
	.align	2
.L4:
	.word	1073876992
	.word	-117506048
	.word	-536810240
	.size	SystemInit, .-SystemInit
	.section	.text.SystemCoreClockUpdate,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	SystemCoreClockUpdate
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	SystemCoreClockUpdate, %function
SystemCoreClockUpdate:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L13
	ldr	r3, [r2, #4]
	and	r3, r3, #12
	cmp	r3, #8
	beq	.L12
	ldr	r3, .L13+4
.L7:
	ldr	r2, .L13
	ldr	r0, .L13+8
	ldr	r2, [r2, #4]
	ldr	r1, .L13+12
	ubfx	r2, r2, #4, #4
	ldrb	r2, [r0, r2]	@ zero_extendqisi2
	lsrs	r3, r3, r2
	str	r3, [r1]
	bx	lr
.L12:
	ldr	r3, [r2, #4]
	ldr	r1, [r2, #4]
	ubfx	r3, r3, #18, #4
	lsls	r1, r1, #15
	add	r3, r3, #2
	bpl	.L11
	ldr	r2, [r2, #4]
	lsls	r2, r2, #14
	bmi	.L11
	ldr	r2, .L13+4
	mul	r3, r2, r3
	b	.L7
.L11:
	ldr	r2, .L13+16
	mul	r3, r2, r3
	b	.L7
.L14:
	.align	2
.L13:
	.word	1073876992
	.word	8000000
	.word	.LANCHOR1
	.word	.LANCHOR0
	.word	4000000
	.size	SystemCoreClockUpdate, .-SystemCoreClockUpdate
	.global	APBPrescTable
	.global	AHBPrescTable
	.global	SystemCoreClock
	.section	.data.SystemCoreClock,"aw"
	.align	2
	.set	.LANCHOR0,. + 0
	.type	SystemCoreClock, %object
	.size	SystemCoreClock, 4
SystemCoreClock:
	.word	72000000
	.section	.rodata.AHBPrescTable,"a"
	.align	2
	.set	.LANCHOR1,. + 0
	.type	AHBPrescTable, %object
	.size	AHBPrescTable, 16
AHBPrescTable:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	4
	.byte	6
	.byte	7
	.byte	8
	.byte	9
	.section	.rodata.APBPrescTable,"a"
	.align	2
	.type	APBPrescTable, %object
	.size	APBPrescTable, 8
APBPrescTable:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	4
	.ident	"GCC: (GNU) 8.2.1 20181213 (release) [gcc-8-branch revision 267074]"
