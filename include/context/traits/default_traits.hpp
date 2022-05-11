#pragma once
#include <context/asm_export/export_types.hpp>
#include <cstring>

namespace context {
	class default_traits
	{
	public:
		typedef asm_export::types::context_entity control_block;
		class   executable;
	public:
		template <typename Stack> static void attach_stack(control_block&, Stack&&);
								  static void switch_to   (control_block&, control_block&);
								  static void execute_from(control_block&, control_block&, executable&);
	};
}

template <typename Stack>
void context::default_traits::attach_stack(control_block& at_block, Stack&& at_stack)
{
	at_block.r_allocated_stack = at_stack.get_pointer(); // Requires PointerBasedStack Requirement.
	at_block.r_allocated_size  = at_stack.size	     ();

	at_block.r_stack.rbp	   = at_stack.r_allocated_stack + at_stack.r_allocated_size;
	at_block.r_stack.rsp	   = at_stack.r_allocated_stack + at_stack.r_allocated_size;
}