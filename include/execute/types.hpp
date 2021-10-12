#pragma once
#include <context/include/asm/types.hpp>
#include <tuple>

namespace context {
namespace execute {
namespace types	  {

	template <typename FuncType, typename... FuncArgs> requires (sizeof...(FuncArgs) > 0)
	class pack
	{
	public:
		template <typename In_FuncType, typename... In_FuncArgs>
		pack(In_FuncType&& in_fp, std::tuple<In_FuncArgs...>& in_args)
			: pack_args(in_args),
			  pack_exec(in_fp)	{ }

	public:
		std::tuple<FuncArgs...> pack_args;
		FuncType				pack_exec;
	};

	template <typename FuncType, typename... FuncArgs>
	void pack_executor(void*);

}
}
}

template <typename FuncType, typename... FuncArgs>
void context::execute::types::pack_executor(void* void_pack)
{
	using packT = pack<FuncType, FuncArgs...>;
	
	packT*	   pack = reinterpret_cast<packT*>(void_pack);
	std::apply(pack->pack_exec, pack->pack_args);	
}