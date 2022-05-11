#pragma once
#include <utility>
#include <type_traits>

namespace context::execution {
	template <typename Context, typename Executable, typename... Args>
	auto execute_at			  (Context&&, Executable&&, Args&&...);
}