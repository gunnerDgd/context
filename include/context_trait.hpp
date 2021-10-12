#pragma once
#include <iostream>
#include <context/include/execute/execute.hpp>

#include <context/include/stack/page_allocator.hpp>
#include <context/include/stack/heap_allocator.hpp>

#define PAGE_TO_MEMORY_SIZE(page_count)		4096 * page_count
#define INITIALIZE_STACK(context, ssize) (context)->r_stack.rsp = (context)->r_allocated_stack + ssize;

namespace context {
	template <typename T>
	concept AllocatorT = requires(std::size_t alloc_size,
								  void*       alloc_ptr )
	{
		T::allocate  (alloc_ptr, alloc_size);
		T::allocate  (alloc_ptr);
		
		T::deallocate(reinterpret_cast<typename T::pointer_type>(alloc_ptr), alloc_size);
		T::deallocate(reinterpret_cast<typename T::pointer_type>(alloc_ptr));
	};
	
	template <AllocatorT StackAllocator   = context::stack::page_alloc<uint8_t>,
			  AllocatorT ContextAllocator = context::stack::heap_alloc<context::asm_export::types::register_field>>
	class context_type
	{
	public:
		typedef StackAllocator							   stack_allocT  ;
		typedef ContextAllocator						   context_allocT;

		typedef context::asm_export::types::register_field contextT   ;
		typedef std::size_t								   stack_sizeT;
		static constexpr std::size_t					   default_stack = PAGE_TO_MEMORY_SIZE(3);

	public:
		static contextT* create_context();
		static contextT* create_context(stack_sizeT ssize);
		
		static void	     delete_context(contextT*);
	};
}

using namespace context;

template <AllocatorT Allocator, AllocatorT ContextAllocator>
context_type<Allocator, ContextAllocator>::contextT* context_type<Allocator, ContextAllocator>::create_context()
{
	contextT*   new_context = context_allocT::allocate(nullptr);
	std::memset(new_context, 0x00, sizeof(contextT));
	
	return		new_context;
}

template <AllocatorT Allocator, AllocatorT ContextAllocator>
context_type<Allocator, ContextAllocator>::contextT* context_type<Allocator, ContextAllocator>::create_context(stack_sizeT ssize)
{
	stack_sizeT new_stack_size = (ssize < PAGE_TO_MEMORY_SIZE(3)) ? PAGE_TO_MEMORY_SIZE(3) : ssize;

	contextT*   new_context	   = context_allocT::allocate(nullptr);
	std::memset(new_context, 0x00, sizeof(contextT));

	new_context->r_allocated_stack = (uint64_t)stack_allocT::allocate(nullptr, new_stack_size);
	new_context->r_allocated_size  = new_stack_size;

	INITIALIZE_STACK(new_context, new_stack_size)
	return			 new_context;
}


template <AllocatorT Allocator, AllocatorT ContextAllocator>
void context_type<Allocator, ContextAllocator>::delete_context(contextT* context)
{
	if (!context->r_allocated_stack) // Stack Wasn't Allocated for this Context.
		context_allocT::deallocate(context);
	else
	{
		stack_allocT  ::deallocate((uint8_t*)context->r_allocated_stack, context->r_allocated_size);
		context_allocT::deallocate(context);
	}
}