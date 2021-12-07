#pragma once
#include <Windows.h>

#include <cstdint>
#include <cstddef>

#include <memory>

namespace context {

/* 
 * context::stack class
 * 
 * 1) Configures Stack Area of task.
 *		--> Allocates / Deallocates Stack Area.
 *		--> Reserve / Lock Stack Area.
 * 
 * 2) 
 * 
 */

	template <typename AllocUnit>
	concept page_allocatable = (4096 % sizeof(AllocUnit) == 0);

	template <typename AllocatorType = void>
	class stack;

	template <>
	class stack<void>  // Standard Stack.
	{
	public:
		typedef std::size_t size_type;
		typedef void*		pointer_type;

		static constexpr size_type default_stack = 4096 * 3;
		static constexpr size_type capture_stack = 0;

	public:
		static pointer_type allocate  (size_type);
		static void			deallocate(pointer_type);
	};

}

context::stack<void>::pointer_type context::stack<void>::allocate(size_type __pa_size)
{
	return ::VirtualAlloc(nullptr, __pa_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

void context::stack<void>::deallocate(pointer_type __pa_addr)
{
	::VirtualFree(__pa_addr, 0, MEM_RELEASE) ;
}