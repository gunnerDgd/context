#pragma once
#include <cstdint>

#define ALIGNED_STRUCT(name) struct alignas(16) name

namespace context::asm_export::types {
	typedef std::uint64_t register_type;
	typedef union alignas(16)
	{
		double simd_128_pd[2];
		float  simd_128_ps[4];

		std::uint8_t  simd_128_u8 [16];
		std::uint16_t simd_128_u16[8];
		std::uint32_t simd_128_u32[4];
		std::uint64_t simd_128_u64[2];
	}				  simd_type;

	typedef union alignas(16)
	{
		double simd_256_pd[4];
		float  simd_256_ps[8];

		std::uint8_t  simd_256_u8 [32];
		std::uint16_t simd_256_u16[16];
		std::uint32_t simd_256_u32[8];
		std::uint64_t simd_256_u64[4];
	}	   simd256_type;

	typedef union alignas(16)
	{
		simd256_type simd256_register;
		simd_type	 simd_register;
	}				 simd_register_type;

	ALIGNED_STRUCT(general_field)
	{
		register_type rax, rbx, rcx, rdx,
					  rsi, rdi;
	};  // 48 (0x30 Byte)

	ALIGNED_STRUCT(extended_field)
	{
		register_type r8, r9, r10, r11, r12, r13, r14, r15;
	}; // 64 (0x40 Byte)

	ALIGNED_STRUCT(stack_field)
	{
		register_type rbp, rsp;
	}; // 16 (0x10 Byte)

	ALIGNED_STRUCT(simd_field)
	{
		simd_register_type rsimd[8];
	}; // 32 * 8 = 256 (0x100)

	ALIGNED_STRUCT(register_field)
	{
		general_field  r_general;
		extended_field r_extended;

		simd_field	   r_simd;
		stack_field	   r_stack;
		
		register_type  r_inst_ptr,
					   r_allocated_stack = 0,
					   r_allocated_size  = 0;
	};

	typedef register_field context_entity;
}