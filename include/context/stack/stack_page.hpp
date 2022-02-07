#pragma once
#include <Windows.h>

#include <cstddef>
#include <cstdint>

namespace context {
	class stack_page
	{
	public:
		typedef std::size_t size_type;
		typedef void*		pointer_type;

	public:
		static pointer_type allocate  (size_type);
		static void		    deallocate(pointer_type, size_type);
	};
}