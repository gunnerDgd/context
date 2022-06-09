%include "x64_context_load.asm"
%include "x64_context_store.asm"
%include "x64_context_stack.asm"

%define REFERENCE_EXTENDED		  add rcx, 0x30 ; Size of general_field  : 0x30
%define REFERENCE_SIMD			  add rcx, 0x40 ; Size of extended_field : 0x40
%define REFERENCE_STACK			  add rcx, 0x100
%define REFERENCE_INST_PTR		  add rcx, 0x10
%define REFERENCE_ALLOCATED_STACK add rcx, 0x08

%define CREATE_SHADOW_STACK		  sub rsp, 0x28
%define DELETE_SHADOW_STACK		  add rsp, 0x28

%macro STORE_RIP 1
	mov rax, qword[rsp]
	mov %1 , rax
%endmacro

global store_and_execute
global store_and_switch

;	+---------------------------+
;	|							|
;	|	Shadow Stack (Caller)	|
;	|							|
;	+---------------------------+ <-- 0x28A
;	|							|
;	|		Caller RIP			|
;	|							|
;	+---------------------------+ <-- 0x30

section .text
; Store Previous Context, and Start New Context.
; void store_and_execute(register_field& prev  : RCX,
;						 register_field& next  : RDX,
;						 void(*exec_fp)(void*) : R8 ,
;						 void* exec_arg		   : R9 ) 
store_and_execute:
	call store_general_register
	
	REFERENCE_EXTENDED
	call store_extended_register
	
	REFERENCE_SIMD
	call store_simd_register
	
	REFERENCE_STACK
	call store_current_stack

	REFERENCE_INST_PTR
	STORE_RIP qword[rcx]
	
	mov  rcx, rdx   ; "prev" is totally useless...
	add  rcx, 0x170 ; next->r_stack

	SWITCH_STACK_SPACE  ; Create Shadow Stack.
	CREATE_SHADOW_STACK ; And Switch Stack Space.
	
	mov  rcx	   , r9   ; exec_arg is Main Argument.
	mov  qword[rsp], rcx
	call r8


; Store Previous Context, and Start New Context.
; void store_and_execute(register_field& prev  : RCX,
;						 register_field& next  : RDX)
store_and_switch:
	call store_general_register
	
	REFERENCE_EXTENDED
	call store_extended_register
	
	REFERENCE_SIMD
	call store_simd_register
	
	REFERENCE_STACK
	call store_current_stack

	REFERENCE_INST_PTR
	STORE_RIP qword[rcx]
	
	mov  rcx, rdx  ; "prev" is totally useless...
	call load_general_register

	REFERENCE_EXTENDED
	call load_extended_register

	REFERENCE_SIMD
	call load_simd_register

	REFERENCE_STACK
	SWITCH_STACK_SPACE

	REFERENCE_INST_PTR
	jmp  qword[rcx]