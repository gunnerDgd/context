#pragma once
#include <context/asm_export/export.hpp>
#include <context/asm_export/export_types.hpp>

#include <context/stack/forward.hpp>
#include <cstring>

namespace context {
	template <typename StackType>
	class context_traits
	{
		template <typename T, typename U>
		friend class basic_context;
	public:
		typedef asm_export::types::context_entity entity_type;
		typedef			 StackType				  stack_type ;
		typedef typename StackType::pointer_type  stack_pointer_type;
		typedef typename StackType::size_type	  stack_size_type	;

		typedef void(*executable_type)(void*);
		typedef void* argument_type;

		template <typename T>
		struct is_supported_entity				{ static constexpr bool value = false; };

		template <>
		struct is_supported_entity<entity_type> { static constexpr bool value = true ; };
				
	public:
		static void attach_stack (entity_type&, stack_type&);
		static void detach_stack (entity_type&);
		static void migrate_stack(entity_type&, stack_type&); // Experimental.

	public:
		static void execute_at   (entity_type&, entity_type&, executable_type, argument_type);
		static void switch_to    (entity_type&, entity_type&);
	};
}

template <typename StackType>
void context::context_traits<StackType>::attach_stack(entity_type& entity, stack_type& stack)
{
	entity.r_allocated_stack = (std::uint64_t)stack.allocated_pointer();
	entity.r_allocated_size  =				  stack.allocated_size   ();

	entity.r_stack.rbp		 = entity.r_allocated_stack + entity.r_allocated_size;
	entity.r_stack.rsp		 = entity.r_stack.rbp;
}

template <typename StackType>
void context::context_traits<StackType>::detach_stack(entity_type& entity)
{
	entity.r_allocated_stack = 0;
	entity.r_allocated_size  = 0;

	entity.r_stack.rbp		 = 0;
	entity.r_stack.rsp		 = 0;
}

template <typename StackType>
void context::context_traits<StackType>::migrate_stack(entity_type& entity, stack_type& new_stack)
{
	stack_pointer_type old_stack = reinterpret_cast<stack_pointer_type>(entity.r_allocated_stack);
	stack_size_type    old_size = entity.r_allocated_size;

	std::memcpy(new_stack.allocated_pointer(), old_stack, old_size);
	entity.r_allocated_stack = new_stack.allocated_pointer();
	entity.r_allocated_size	 = new_stack.allocated_size   ();
}

template <typename StackType>
void context::context_traits<StackType>::execute_at(entity_type& prev, entity_type& curr, executable_type exec, argument_type args)
{
	asm_export::store_and_execute(prev, curr, exec, args);
}

template <typename StackType>
void context::context_traits<StackType>::switch_to(entity_type& prev, entity_type& curr)
{
	asm_export::store_and_switch(prev, curr);
}