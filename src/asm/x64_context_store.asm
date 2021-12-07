%define STORE(mem, reg)		 mov    mem, reg
%define SIMD_STORE(mem, reg) movdqu mem, reg

section .text

; Save General Perposed Register
; In C-Type Expression : void store_general_register(context::types::general_field& : RCX)
store_general_register:
	STORE(qword[rcx]	   , rax)
	STORE(qword[rcx + 0x08], rbx)
	STORE(qword[rcx + 0x18], rdx)
	
	STORE(qword[rcx + 0x20], rsi)
	STORE(qword[rcx + 0x28], rdi)

	ret

; Store Extended - General Perposed Register.
; In C-Type Expression : void store_extended_register(context::types::extended_field& : RCX)
store_extended_register:
	STORE(qword[rcx]	   , r8)
	STORE(qword[rcx + 0x08], r9)
	STORE(qword[rcx + 0x10], r10)
	STORE(qword[rcx + 0x18], r11)
	STORE(qword[rcx + 0x20], r12)
	STORE(qword[rcx + 0x28], r13)
	STORE(qword[rcx + 0x30], r14)
	STORE(qword[rcx + 0x38], r15)

	ret

; Store SIMD Register
; In C-Type Expression : void store_simd_register(context::types::extended_field& : RCX)
store_simd_register:
	SIMD_STORE([rcx]	   , xmm0)
	SIMD_STORE([rcx + 0x20], xmm1)
	SIMD_STORE([rcx + 0x40], xmm2)
	SIMD_STORE([rcx + 0x60], xmm3)
	SIMD_STORE([rcx + 0x80], xmm4)
	SIMD_STORE([rcx + 0xA0], xmm5)
	SIMD_STORE([rcx + 0xC0], xmm6)
	SIMD_STORE([rcx + 0xE0], xmm7)