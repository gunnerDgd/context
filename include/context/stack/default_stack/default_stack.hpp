#pragma once
#include <type_traits>

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

		default_stack(default_stack&)		   ; // Migrates Stack.
		default_stack(default_stack&&) noexcept; // Moves Stack and Makes Previous Stack Object Empty.

	public:
		pointer   get_pointer(); // Requirement of PointerBasedStack
		size_type size		 (); // Requirement of ExecutionStack.

	private:
		pointer   __M_def_stack_pointer;
		size_type __M_def_stack_size   ;
	};
}