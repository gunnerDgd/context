#pragma once
#include <Windows.h>
#include <cstdlib>

namespace context {
namespace stack   {

	template <typename AllocType>
	class page_alloc
	{
	public:
		typedef			 AllocType   alloc_type  ;
		typedef			 AllocType*  pointer_type;
		static constexpr std::size_t alloc_unit = 4096; // Size of the x86_64 Page.
	public:
		static pointer_type allocate  (void*, std::size_t);
		static pointer_type allocate  (void*);
		
		static void			deallocate(pointer_type, std::size_t);
		static void			deallocate(pointer_type);
	};

}
}

template <typename AllocType>
using allocT = context::stack::page_alloc<AllocType>;

template <typename AllocType>
typename allocT<AllocType>::pointer_type allocT<AllocType>::allocate(void* hint, std::size_t size)
{
	return (pointer_type)VirtualAlloc(hint, size, MEM_COMMIT, PAGE_READWRITE);
}

template <typename AllocType>
typename allocT<AllocType>::pointer_type allocT<AllocType>::allocate(void* hint)
{
	return (pointer_type)VirtualAlloc(hint, sizeof(AllocType), MEM_COMMIT, PAGE_READWRITE);
}

template <typename AllocType>
void  allocT<AllocType>::deallocate(pointer_type addr, std::size_t size)
{
	VirtualFree(addr, size, MEM_DECOMMIT);
}

template <typename AllocType>
void  allocT<AllocType>::deallocate(pointer_type addr)
{
	VirtualFree(addr, sizeof(AllocType), MEM_DECOMMIT);
}