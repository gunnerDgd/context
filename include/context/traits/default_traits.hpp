#pragma once
#include <context/asm_export/export.hpp>
#include <context/asm_export/export_types.hpp>

#include <tuple>
#include <type_traits>

#include <cstring>

namespace context {
	class default_traits
	{
	public:
		typedef asm_export::types::context_entity native_handle_type;
	public:
		template <typename Stack>	   static void attach_stack(native_handle_type*, Stack&&);
									   static void switch_to   (native_handle_type*, native_handle_type*);
		
		template <typename Fn, typename... Args> 
		static void								   execute_from(native_handle_type*, native_handle_type*, Fn&&, Args&&...);
		template <typename Fn, typename... Args>
		static native_handle_type*				   execute_from(native_handle_type*, Fn&&, Args&&...);
	};
}

template <typename Stack>
void context::default_traits::attach_stack(native_handle_type* at_block, Stack&& at_stack)
{
	at_block->r_allocated_stack = (std::uint64_t)at_stack.get_pointer(); // Requires PointerBasedStack Requirement.
	at_block->r_allocated_size  =				 at_stack.size	     ();

	at_block->r_stack.rbp	    = at_block->r_allocated_stack + at_block->r_allocated_size - 0x20;
	at_block->r_stack.rsp	    = at_block->r_allocated_stack + at_block->r_allocated_size - 0x20;
}

template <typename Fn, typename... Args>
void context::default_traits::execute_from(native_handle_type* hnd_curr, 
										   native_handle_type* hnd_exec, Fn&& fn, Args&&... args)
{
	struct __exec_helper
	{
		__exec_helper(Fn& _fn, std::tuple<Args&&...>&& _args)
			: __hlp_func(_fn),
			  __hlp_args(std::move(_args)) {  }

		std::tuple<Args&&...> __hlp_args;
		Fn&					  __hlp_func;

		native_handle_type   *__hlp_hnd_curr, 
							 *__hlp_hnd_exec;

		void(*__hlp_exec)(void*) = [](void* ptr_hlp_void)
		{
			__exec_helper*				  ptr_hlp = reinterpret_cast<__exec_helper*>(ptr_hlp_void);
			asm_export::store_and_switch(*ptr_hlp->__hlp_hnd_exec, *ptr_hlp->__hlp_hnd_curr);
			std::apply					( ptr_hlp->__hlp_func	 ,  ptr_hlp->__hlp_args);
			
			native_handle_type* hnd_ret		= ptr_hlp->__hlp_hnd_curr,
							   *hnd_cleanup = ptr_hlp->__hlp_hnd_exec;
			
			delete ptr_hlp;
			asm_export::store_and_switch(*hnd_cleanup, *hnd_ret);
			
		};
	}; 
	
	__exec_helper *__hlp_exec = new __exec_helper(fn, std::forward_as_tuple(args...));
				   __hlp_exec->__hlp_hnd_curr = hnd_curr;
				   __hlp_exec->__hlp_hnd_exec = hnd_exec;

	context::asm_export::store_and_execute(*hnd_curr, *hnd_exec, __hlp_exec->__hlp_exec,
										  (void*)			     __hlp_exec);
}

template <typename Fn, typename... Args>
typename context::default_traits::native_handle_type* 
		 context::default_traits::execute_from(native_handle_type* hnd_exec, Fn&& fn, Args&&... args)
{
	native_handle_type* hnd_curr = new native_handle_type;
	execute_from	   (hnd_curr, hnd_exec, std::forward<Fn>(fn), std::forward<Args>(args)...);

	return				hnd_curr;
}