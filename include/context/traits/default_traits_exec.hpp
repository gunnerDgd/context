#pragma once
#include <tuple>

#include <context/asm_export/export.hpp>
#include <context/traits/default_traits.hpp>

namespace context {
	class default_traits::executable
	{
		friend class default_traits;
	public:
		template <typename Fn, typename... Args>
		executable(Fn&&, Args&&...);

	private:
		void (*__M_exec_func)(void*);
		void*  __M_exec_args;
	};
}

template <typename Fn, typename... Args>
context::default_traits::executable::executable(Fn&& fn, Args&&... args)
{
	struct __helper
	{
		std::tuple<Args...>		    __args;
		std::remove_reference_t<Fn> __fn  ;
	};

	__M_exec_args =   (void*)new __helper(fn, std::forward_as_tuple(args...));
	__M_exec_func = [](void* exec)
					{
						__helper*  ptr_hlp = reinterpret_cast<__helper*>(exec);
						std::apply(ptr_hlp->__fn, ptr_hlp->__args);
						
						delete     ptr_hlp;
					};
}