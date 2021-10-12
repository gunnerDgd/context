#pragma once
#include <context/include/execute/types.hpp>
#include <context/include/asm/export.hpp>

namespace context {
namespace execute {

	template <typename FuncType, typename... FuncArgs>
	using packT	     = context::execute::types::pack<FuncType, FuncArgs...>;
	using contextT   = context::asm_export::types::register_field;

	template <typename FuncType, typename... FuncArgs>
	void execute(contextT&, contextT&, FuncType&&, std::tuple<FuncArgs...>&& args);
	void execute(contextT&, contextT&);

}
}

using namespace context::execute;
template <typename FuncType, typename... FuncArgs>
void context::execute::execute(contextT& prev, contextT& next, FuncType&& func, std::tuple<FuncArgs...>&& args)
{
	packT<FuncType, FuncArgs...>      pack(func, args);
	context::asm_export::store_and_execute(prev, next, 
										  &context::execute::types::pack_executor<FuncType, FuncArgs...>, &pack);
}

void context::execute::execute(contextT& prev, contextT& next) 
{ 
	context::asm_export::store_and_switch(prev, next);
}