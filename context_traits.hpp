#pragma once
#include <context/asm_export/export.hpp>
#include <context/stack/stack.hpp>

namespace context {

	template <typename ContextType, typename AllocatorType>
	class basic_context;

	typedef basic_context<asm_export::types::context_entity, stack<>> context;

	template <typename... AnyContext>
	struct is_context { static constexpr bool value = false; };

	template <typename AnyContext, typename AnyAllocator>
	struct is_context <basic_context<AnyContext, AnyAllocator>> { static constexpr bool value = true; };
}