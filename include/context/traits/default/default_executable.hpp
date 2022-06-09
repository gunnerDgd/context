#pragma once
#include <tuple>
#include <context/traits/default/default.hpp>

namespace context {
	template <typename ExecType, typename... ExecArgs>
	class default_context::executable
	{
		friend class default_context;

		std::tuple<ExecArgs...>			  __M_exec_args;
		std::remove_reference_t<ExecType> __M_exec;
		static void						  __execute(void*);
	
	public:
		template <typename InExecType, typename... InExecArgs>
		executable(InExecType&&, InExecArgs&&...);
	};
}

template <typename ExecType, typename... ExecArgs>
template <typename InExecType, typename... InExecArgs>
context::default_context::executable<ExecType, ExecArgs...>::executable(InExecType&& pExec, InExecArgs&&... pExecArgs)
	: __M_exec_args(std::forward_as_tuple(pExecArgs...)),
	  __M_exec	   (pExec)								{  }

template <typename ExecType, typename... ExecArgs>
void context::default_context::executable<ExecType, ExecArgs...>::__execute(void* pArgs)
{
	executable* ptr_exec 
		= reinterpret_cast<executable*>(pArgs);

	std::apply(ptr_exec->__M_exec, ptr_exec->__M_exec_args);
	
}