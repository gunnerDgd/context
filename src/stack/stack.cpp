#include <context/stack/stack.hpp>

context::stack::pointer_type context::stack::allocate(pointer_type __pa_hint, size_type __pa_size)
{
	return VirtualAlloc(__pa_hint, __pa_size, MEM_COMMIT, PAGE_READONLY);
}

void						 context::stack::deallocate(pointer_type __pa_addr)
{
	VirtualFree(__pa_addr, 0, MEM_RELEASE);
}