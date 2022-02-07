#pragma once

namespace context {
	template <typename AllocBackend>
	class basic_stack
	{
	public:
		typedef			 AllocBackend				backend_type;
		typedef typename AllocBackend::pointer_type pointer_type;
		typedef typename AllocBackend::size_type    size_type;

	public:
		basic_stack (size_type);
		~basic_stack();

	private:
		pointer_type __M_stack_pointer;
		size_type    __M_stack_size   ;
	};
}

template <typename AllocBackend>
context::basic_stack<AllocBackend>::basic_stack(size_type alloc_size) : __M_stack_size   (alloc_size),
																		__M_stack_pointer(backend_type::allocate(alloc_size)) {  }

template <typename AllocBackend>
context::basic_stack<AllocBackend>::~basic_stack()																			  { backend_type::deallocate(__M_stack_pointer); }