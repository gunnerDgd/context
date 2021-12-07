%define LOAD(reg, mem)		mov    reg, mem
%define SIMD_LOAD(reg, mem) movdqu reg, mem

section .text

; Load General Perposed Register
; In C-Type Expression : void load_general_register(context::types::general_field& : RCX)
load_general_register:
	LOAD(rax, qword[rcx])
	LOAD(rbx, qword[rcx + 0x08])
	LOAD(rdx, qword[rcx + 0x18])
	
	LOAD(rsi, qword[rcx + 0x20])
	LOAD(rdi, qword[rcx + 0x28]) 

	ret

; Load Extended - General Perposed Register.
; In C-Type Expression : void load_extended_register(context::types::extended_field& : RCX)
load_extended_register:
	LOAD(r8 , qword[rcx])
	LOAD(r9 , qword[rcx + 0x08])
	LOAD(r10, qword[rcx + 0x10])
	LOAD(r11, qword[rcx + 0x18])
	LOAD(r12, qword[rcx + 0x20])
	LOAD(r13, qword[rcx + 0x28])
	LOAD(r14, qword[rcx + 0x30])
	LOAD(r15, qword[rcx + 0x38])

	ret

; Load SIMD Register
; In C-Type Expression : void load_simd_register(context::types::extended_field& : RCX)
load_simd_register:
	SIMD_LOAD(xmm0, [rcx])
	SIMD_LOAD(xmm1, [rcx + 0x20])
	SIMD_LOAD(xmm2, [rcx + 0x40])
	SIMD_LOAD(xmm3, [rcx + 0x60])
	SIMD_LOAD(xmm4, [rcx + 0x80])
	SIMD_LOAD(xmm5, [rcx + 0xA0])
	SIMD_LOAD(xmm6, [rcx + 0xC0])
	SIMD_LOAD(xmm7, [rcx + 0xE0])

	ret