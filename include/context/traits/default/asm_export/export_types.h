#pragma once
#include <stdint.h>
#include <stdalign.h>

#define SYNAPSE_CONTEXT_DEFAULT_ALIGNED_STRUCT(name) typedef struct name
#define SYNAPSE_CONTEXT_DEFAULT_ALIGNED_REGISTER _Alignas(8) uint64_t

typedef union
{
	double simd_128_pd[2];
	float  simd_128_ps[4];

	uint8_t  simd_128_u8 [16];
	uint16_t simd_128_u16[8] ;
	uint32_t simd_128_u32[4] ;
	uint64_t simd_128_u64[2] ;
} synapse_context_default_register_simd128;

typedef union
{
	double simd_256_pd[4];
	float  simd_256_ps[8];

	uint8_t  simd_256_u8 [32];
	uint16_t simd_256_u16[16];
	uint32_t simd_256_u32[8] ;
	uint64_t simd_256_u64[4] ;
} synapse_context_default_register_simd256;

typedef union
{
	synapse_context_default_register_simd256 simd256_register;
	synapse_context_default_register_simd128 simd_register   ;
} synapse_context_default_register_simd;

SYNAPSE_CONTEXT_DEFAULT_ALIGNED_STRUCT(synapse_context_default_register_field_general)
{
	SYNAPSE_CONTEXT_DEFAULT_ALIGNED_REGISTER
		rax, rbx, rcx, rdx,
		rsi, rdi;
} synapse_context_default_register_field_general;  // 48 (0x30 Byte)

SYNAPSE_CONTEXT_DEFAULT_ALIGNED_STRUCT(synapse_context_default_register_field_extended)
{
	SYNAPSE_CONTEXT_DEFAULT_ALIGNED_REGISTER
		r8, r9, r10, r11, r12, r13, r14, r15;
} synapse_context_default_register_field_extended; // 64 (0x40 Byte)

SYNAPSE_CONTEXT_DEFAULT_ALIGNED_STRUCT(synapse_context_default_register_field_stack)
{
	SYNAPSE_CONTEXT_DEFAULT_ALIGNED_REGISTER rbp, rsp;
} synapse_context_default_register_field_stack; // 16 (0x10 Byte)

SYNAPSE_CONTEXT_DEFAULT_ALIGNED_STRUCT(synapse_context_default_register_field_simd)
{
	synapse_context_default_register_simd rsimd[8];
} synapse_context_default_register_field_simd; // 32 * 8 = 256 (0x100)

SYNAPSE_CONTEXT_DEFAULT_ALIGNED_STRUCT(synapse_context_default_register_field)
{
	synapse_context_default_register_field_general
		r_general;
	synapse_context_default_register_field_extended
		r_extended;
	synapse_context_default_register_field_simd
		r_simd;
	synapse_context_default_register_field_stack
		r_stack;
	SYNAPSE_CONTEXT_DEFAULT_ALIGNED_REGISTER
		r_inst_ptr;
} synapse_context_default_register_field;