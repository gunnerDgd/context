#pragma once
#include <context/context_traits.hpp>

#include <context/stack/basic_stack.hpp>
#include <context/stack/forward.hpp>

#include <tuple>
#include <functional>

#include <iostream>

namespace context {
	template <stack_type AllocStack>
	class basic_context<asm_export::types::context_entity, AllocStack>
	{
	public:
		typedef basic_context<asm_export::types::context_entity, stack<>> context_type;
		typedef stack<>													  allocator_type;
		typedef allocator_type::size_type								  alloc_size;

		static constexpr alloc_size default_allocate = allocator_type::default_stack;
		static constexpr alloc_size capture_current  = allocator_type::capture_stack;

		typedef asm_export::types::context_entity		  context_entity;
		typedef std::add_pointer_t<context_type>		  context_pointer;
		typedef std::add_lvalue_reference_t<context_type> context_reference;

	};
}