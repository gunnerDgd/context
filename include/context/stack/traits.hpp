#pragma once
#include <context/stack/backend/stack_page.hpp>
#include <context/stack/basic_stack.hpp>

namespace context {
	template <typename... T>
	struct is_stack					   { static constexpr bool value = false; };

	template <typename T, typename U>
	struct is_stack<basic_stack<T, U>> { static constexpr bool value = true ; };

	template <typename... T>
	struct is_pointer_based_stack								 { static constexpr bool value = false; };

	template <typename T>
	struct is_pointer_based_stack<basic_stack<T, pointer_based>> { static constexpr bool value = true ; };

	template <typename... T>
	struct is_external_stack								     { static constexpr bool value = false; };

	template <typename T>
	struct is_external_stack<basic_stack<T, external_memory>>    { static constexpr bool value = true ; };

	
	template <typename T>
	constexpr bool is_stack_v		   = is_stack<T>::value;

	template <typename T>
	constexpr bool is_pointer_based_v  = is_pointer_based_stack<T>::value;

	template <typename T>
	constexpr bool is_external_stack_v = is_external_stack<T>::value;

	template <typename T>
	concept stack_type = is_stack_v<T>;

	template <typename T>
	concept pointer_based_stack = is_pointer_based_v<T> && requires(T & PointerStack) 
	{ 
		PointerStack.allocated_pointer();
		PointerStack.allocated_size   ();
	};

	template <typename T>
	concept external_stack      = is_external_stack_v<T>;
}