#pragma once
#include <context/stack/backend/stack_page.hpp>
#include <context/stack/traits.hpp>

namespace context::stack {
	typedef context::basic_stack<context::stack_page, pointer_based> memory_page;
}