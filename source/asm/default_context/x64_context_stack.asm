
%macro GET_CALLER_RSP 0
	mov rax				 , rsp  
	add rax				 , 0x10 
	mov qword[rcx + 0x08], rax 
%endmacro

%macro SWITCH_STACK_SPACE 0
	mov rbp, qword[rcx]		  
	mov rsp, qword[rcx + 0x08]
%endmacro

section .text

;					Stack Layout

; +-------------------------------------------------+
; |													|
; |		Shadow Stack Area (store_and_XXX Function)	|
; |													|
; +-------------------------------------------------+ <-- 0x28 (Dec : 40) : Must Be Preserved in Storing Progress.
; |													|
; |				Previous RIP Area					|
; |													|
; +-------------------------------------------------+ <-- 0x30 (Dec : 48)
; |													|
; |			Store_and_XXX Function RIP				|
; |													|
; +-------------------------------------------------+ <-- 0x38 (Dec : 56)
;

store_current_stack:
	GET_CALLER_RSP
	mov qword[rcx], rbp

	ret