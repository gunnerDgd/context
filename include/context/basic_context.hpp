#pragma once
#include <context/declare.hpp>

namespace context {
	template <typename ContextTraits> 
	class basic_context
	{
	public:
		using traits_type =					ContextTraits;
		using native_handle_type = typename ContextTraits::entity_type;

	public:
		template <typename Stack> 
		basic_context(Stack&&); // Attaches Stack.
		basic_context()		; // Just Create Control Block

		basic_context(basic_context&)  = default;
		basic_context(basic_context&&) = default;

	public:
		const native_handle_type& native_handle() { return __M_context_entity; }

	private:
		native_handle_type __M_context_entity;
	};
}

template <typename ContextTraits>
template <typename Stack> 
context::basic_context<ContextTraits>::basic_context(Stack&& at_stack)
{
	traits_type::attach_stack(at_stack);
}