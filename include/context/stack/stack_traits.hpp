#pragma once

namespace context::stack {
	template <typename StackType>
	class stack_traits
	{
	public:
		using stack_type	  = StackType;
		using pointer		  = typename StackType::pointer  ;
		
		using size_type		  = typename StackType::size_type;
		using difference_type = typename StackType::difference_type;

	public:
		static pointer    get_pointer(stack_type&);
		static size_type  size		 (stack_type&);
		
		static stack_type resize	 (stack_type&, size_type);
		static stack_type migrate    (stack_type&);
	};
}

template <typename StackType>
typename context::stack::stack_traits<StackType>::pointer
		 context::stack::stack_traits<StackType>::get_pointer(stack_type& pStack) { return pStack.get_pointer(); }

template <typename StackType>
typename context::stack::stack_traits<StackType>::size_type  
		 context::stack::stack_traits<StackType>::size(stack_type& pStack)		  { return pStack.size(); }

template <typename StackType>
typename context::stack::stack_traits<StackType>::stack_type 
		 context::stack::stack_traits<StackType>::resize(stack_type& pStack, size_type pStackSize) { return stack_type::resize(pStack, pStackSize); }

template <typename StackType>
typename context::stack::stack_traits<StackType>::stack_type 
		 context::stack::stack_traits<StackType>::migrate(stack_type& pStack) { return stack_type::migrate(pStack); }