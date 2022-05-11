#include <context/stack/default_stack/default_stack.hpp>
#include <Windows.h>

#include <cstdlib>
#include <cstring>

context::stack::default_stack::default_stack(size_type sz_stack) // Creates Stack with Given Size.
	: __M_def_stack_size(sz_stack)
{
	__M_def_stack_pointer = ::VirtualAlloc(nullptr, sz_stack, MEM_COMMIT, PAGE_READWRITE);
}

context::stack::default_stack::default_stack() // Creates Empty Stack.
	: __M_def_stack_size   (0),
	  __M_def_stack_pointer(nullptr) {  }

context::stack::default_stack::~default_stack() // Creates Empty Stack.
{
	::VirtualFree(__M_def_stack_pointer, )
}

context::stack::default_stack::default_stack(default_stack& cp_stack) // Migrates Stack.
	: __M_def_stack_size(cp_stack.__M_def_stack_size)
{
	__M_def_stack_pointer = ::VirtualAlloc(nullptr, cp_stack.__M_def_stack_size, MEM_COMMIT, PAGE_READWRITE);
	std::memcpy			(__M_def_stack_pointer, 
				cp_stack.__M_def_stack_pointer, 
			    cp_stack.__M_def_stack_size)  ;
}

context::stack::default_stack::default_stack(default_stack&& mv_stack) noexcept // Moves Stack and Makes Previous Stack Object Empty.
	: __M_def_stack_size   (mv_stack.__M_def_stack_size),
	  __M_def_stack_pointer(mv_stack.__M_def_stack_pointer)
{
	mv_stack.__M_def_stack_size    = 0;
	mv_stack.__M_def_stack_pointer = nullptr;
}

typename context::stack::default_stack::pointer   
		 context::stack::default_stack::get_pointer() { return __M_def_stack_pointer; }

typename context::stack::default_stack::size_type 
		 context::stack::default_stack::size()		  { return __M_def_stack_size   ; }