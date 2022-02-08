#pragma once
#include <context/stack/stack_type.hpp>

namespace context {
	template <typename AllocBackend, typename StackType>
	class basic_stack;

	template <typename AllocBackend>
	class basic_stack<AllocBackend, pointer_based>
	{
	public:
		typedef			 pointer_based				allocation_type;
		typedef			 AllocBackend				backend_type   ;
		typedef typename AllocBackend::pointer_type pointer_type   ;
		typedef typename AllocBackend::size_type    size_type	   ;

	public:
		basic_stack (size_type);
		~basic_stack();

	public:
		pointer_type allocated_pointer() { return __M_stack_pointer; }
		size_type    allocated_size   () { return __M_stack_size   ; }

	private:
		pointer_type __M_stack_pointer;
		size_type    __M_stack_size   ;
	};
}

template <typename AllocBackend>
context::basic_stack<AllocBackend, context::pointer_based>::basic_stack(size_type alloc_size) : __M_stack_size   (alloc_size),
																								__M_stack_pointer(backend_type::allocate(alloc_size)) {  }

template <typename AllocBackend>
context::basic_stack<AllocBackend, context::pointer_based>::~basic_stack()																			  { backend_type::deallocate(__M_stack_pointer); }