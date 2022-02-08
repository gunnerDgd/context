#pragma once
#include <context/stack/basic_stack.hpp>

namespace context {

	template <typename ContextType, typename AllocatorType>
	class basic_context;

	template <typename... AnyContext>
	struct is_context											{ static constexpr bool value = false; };

	template <typename AnyContext, typename AnyAllocator>
	struct is_context <basic_context<AnyContext, AnyAllocator>> { static constexpr bool value = true; };
}