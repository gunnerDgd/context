#pragma once
#include <context/context_traits.hpp>

#include <context/stack/basic_stack.hpp>
#include <context/stack/forward.hpp>

#include <tuple>
#include <functional>

#include <iostream>

namespace context {
	template <typename ContextTraits, typename StackType>
	class basic_context
	{
		
	public:
		typedef			 ContextTraits							 traits_type;
		typedef typename ContextTraits::entity_type				 entity_type;
		typedef			 basic_context<ContextTraits, StackType> this_type;
		
		typedef typename traits_type::executable_type entity_executable;
		typedef typename traits_type::argument_type	  entity_argument  ;

		typedef			 StackType					  stack_type  ;
		typedef	typename StackType::size_type		  stack_size  ;

	public:
		basic_context (stack_size) requires std::is_constructible_v<stack_type, stack_size>;
		basic_context ();
		~basic_context();

	public:
		static void switch_to (this_type&, this_type&);
		static void execute_at(this_type&, this_type&, entity_executable, entity_argument);

	private:
		entity_type __M_context_entity;
		stack_type  __M_context_stack ;
	};
}

template <typename ContextTraits, typename StackType>
context::basic_context<ContextTraits, StackType>::basic_context(stack_size size) requires std::is_constructible_v<stack_type, stack_size>
	: __M_context_stack(size)
{
	traits_type::attach_stack(__M_context_entity, __M_context_stack);
}

template <typename ContextTraits, typename StackType>
context::basic_context<ContextTraits, StackType>::basic_context() : __M_context_stack(0)
{
	traits_type::attach_stack(__M_context_entity, __M_context_stack);
}


template <typename ContextTraits, typename StackType>
context::basic_context<ContextTraits, StackType>::~basic_context()
{
	traits_type::detach_stack(__M_context_entity);
}

template <typename ContextTraits, typename StackType>
void context::basic_context<ContextTraits, StackType>::switch_to(this_type& prev, this_type& curr)
{
	traits_type::switch_to(prev.__M_context_entity, curr.__M_context_entity);
}

template <typename ContextTraits, typename StackType>
void context::basic_context<ContextTraits, StackType>::execute_at(this_type& prev, this_type& curr, entity_executable exec, entity_argument args)
{
	traits_type::execute_at(prev.__M_context_entity, curr.__M_context_entity, exec, args);
}