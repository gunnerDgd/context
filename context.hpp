#pragma once
#include <context/context_traits.hpp>

#include <tuple>
#include <functional>

#include <iostream>

namespace context {
	template <>
	class basic_context<asm_export::types::context_entity, stack<>>
	{
	public:
		typedef basic_context<asm_export::types::context_entity, stack<>> context_type;
		typedef stack<>													  allocator_type;
		typedef allocator_type::size_type								  alloc_size;

		static constexpr alloc_size default_allocate = allocator_type::default_stack;
		static constexpr alloc_size capture_current  = allocator_type::capture_stack;

		typedef asm_export::types::context_entity		  context_entity;
		typedef std::add_pointer_t<context_type>		  context_pointer;
		typedef std::add_lvalue_reference_t<context_type> context_reference;

	private:
		context_entity* __M_context_entity;
	private:
		template <typename In_Func, typename... In_Args>
		struct __execution_pack
		{
			typedef std::remove_cvref_t<In_Func> exec_type;
			
			static void __M_execute_entry(void* __pa_void_pack)
			{
				typedef __execution_pack<In_Func, In_Args...>* pack_pointer;
				
				pack_pointer				  pack = (pack_pointer)__pa_void_pack;
				asm_export::store_and_switch(*pack->__M_pack_curr.__M_context_entity, 
											 *pack->__M_pack_prev.__M_context_entity);

				std::apply					 (pack->__M_pack_exec, pack->__M_pack_args);
				delete						  pack;
			}

			__execution_pack(In_Func __pa_exec, std::tuple<In_Args...>&& __pa_args,
							 context_type& __pa_prev, context_type& __pa_curr) 
				: __M_pack_exec(__pa_exec),
				  __M_pack_args(__pa_args),
				  __M_pack_prev(__pa_prev),
				  __M_pack_curr(__pa_curr) {  }

			exec_type* 			   __M_pack_exec;
			std::tuple<In_Args...> __M_pack_args;
			context_type		  &__M_pack_prev, &__M_pack_curr;
		};

	public:
		template <typename In_Func, typename... In_Args>
		static void execute_at(context_type& __pa_context, In_Func&& __pa_exec, In_Args&&... __pa_args)
		{
			typedef __execution_pack<In_Func, context&, In_Args...> exec_pack_type;
			typedef std::tuple<context&, In_Args...>				exec_args_type;

			if (__pa_context.__M_context_entity->r_allocated_size == capture_current)
				return;

			__pa_context.__M_context_entity->r_stack.rbp = __pa_context.__M_context_entity->r_allocated_stack 
														 + __pa_context.__M_context_entity->r_allocated_size;
			__pa_context.__M_context_entity->r_stack.rsp = __pa_context.__M_context_entity->r_stack.rbp;
			
			context_type    exec_context;
			exec_pack_type* exec_pack = new exec_pack_type(__pa_exec, exec_args_type(__pa_context, __pa_args...), exec_context, __pa_context);

			asm_export::store_and_execute(*exec_context.__M_context_entity,
										  *__pa_context.__M_context_entity,
										  &exec_pack_type::__M_execute_entry,
										   exec_pack);
				
		}
		static void switch_to(context_type& __pa_curr, context_type& __pa_next)
		{
			asm_export::store_and_switch(*__pa_curr.__M_context_entity, *__pa_next.__M_context_entity);
		}
	
	
	public:
		basic_context (alloc_size __pa_size = allocator_type::capture_stack) : __M_context_entity(new context_entity)
		{
			if (__pa_size == allocator_type::capture_stack)
			{
				__M_context_entity->r_allocated_size  = allocator_type::capture_stack;
				__M_context_entity->r_allocated_stack = 0;
			}
			else
			{
				__M_context_entity->r_allocated_size  = (__pa_size > allocator_type::default_stack) 
													  ?  __pa_size
													  :  allocator_type::default_stack;
				__M_context_entity->r_allocated_stack = (uint64_t)allocator_type::allocate(__M_context_entity->r_allocated_size);
			}
		}

		~basic_context()
		{
			if (__M_context_entity->r_allocated_size != allocator_type::capture_stack)
				allocator_type::deallocate((void*)__M_context_entity->r_allocated_stack);

			delete __M_context_entity;
		}

	
	};
}