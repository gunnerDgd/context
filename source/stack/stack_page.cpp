#include <context/stack/stack_page.hpp>

context::stack_page::pointer_type context::stack_page::allocate  (size_type size)
{
	return ::VirtualAlloc(nullptr, size, MEM_COMMIT, PAGE_READWRITE);
}

void							  context::stack_page::deallocate(pointer_type ptr, size_type size)
{
	::VirtualFree(ptr, size, MEM_DECOMMIT);
	::VirtualFree(ptr, 0   , MEM_RELEASE) ;
}