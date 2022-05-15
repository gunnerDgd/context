#pragma once
#include <context/declare.hpp>

#include <context/basic_context.hpp>
#include <context/stack/default_stack/default_stack.hpp>
#include <context/traits/default_traits.hpp>

namespace context {
	using default_context = basic_context<default_traits>;
}