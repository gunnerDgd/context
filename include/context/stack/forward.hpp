#pragma once
#include <context/stack/stack_page.hpp>
#include <context/stack/basic_stack.hpp>

namespace context {
	using page_backed_stack = basic_stack<stack_page>;

	template <typename T>
	struct is_stack_type				 { static constexpr bool value = false; };

	template <typename T>
	struct is_stack_type<basic_stack<T>> { static constexpr value = true; };

	template <typename T>
	concept stack_type = is_stack_type<T>::value;
}