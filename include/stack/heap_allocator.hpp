#pragma once

namespace context {
namespace stack   {

	template <typename AllocType>
	class heap_alloc
	{
	public:
		typedef			 AllocType   alloc_type;
		typedef			 AllocType*  pointer_type;
		static constexpr std::size_t alloc_unit = sizeof(AllocType); // Size of the x86_64 Page.
	public:
		static pointer_type allocate  (void* hint, std::size_t size)		{ return   new alloc_type[size]; }
		static pointer_type allocate  (void* hint)							{ return   new alloc_type; }

		static void			deallocate(pointer_type addr, std::size_t size) { delete[] addr; }
		static void			deallocate(pointer_type addr)					{ delete   addr; }
	};

}
}