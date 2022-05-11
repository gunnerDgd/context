#pragma once
#include <context/stack/forward.hpp>

#include <context/basic_context.hpp>
#include <context/traits/basic_context_traits.hpp>

namespace context {
	typedef basic_context<context_traits<stack::memory_page>, stack::page> context;
}