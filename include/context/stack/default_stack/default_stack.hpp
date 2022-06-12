#pragma once
#include <type_traits>

extern "C"
{
#include <context/stack/stack_traits.h>
#include <context/stack/default_stack/default_stack.h>
}

namespace context::stack {
	class default_stack
	{
	public:
		typedef void*          pointer		  ;
		typedef std::size_t    size_type	  ;
		typedef std::ptrdiff_t difference_type;

	public:
		default_stack (size_type); // Creates Stack with Given Size.
		default_stack ()		 ; // Creates Empty Stack.
		~default_stack()		 ;

		default_stack (default_stack&&)  noexcept; // Moves Stack and Makes Previous Stack Object Empty.

	public:
		static default_stack resize (default_stack&, size_t);
		static default_stack migrate(default_stack&);

		pointer				 get_pointer(); // Requirement of PointerBasedStack
		size_type			 size		(); // Requirement of ExecutionStack.

	private:
		synapse_context_stack_traits* __M_stack_traits	  ;
		pointer						  __M_stack_alloc	  ;
		size_type					  __M_stack_alloc_size;
	};
}