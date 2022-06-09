#pragma once
#include <stdint.h>

typedef struct synapse_context_stack_traits
{
	void*   stack_entity;
	void* (*allocate)  (void*, void*, size_t);
	void  (*deallocate)(void*, void*, size_t);
	
	void* (*resize)    (void*, void*, size_t, size_t);
	void* (*migrate)   (void*, void*, size_t);
} synapse_context_stack_traits;

#define synapse_context_stack_traits_allocate(pTraits, pHint, pSize)\
	pTraits.allocate(pTraits.stack_entity, pHint, pSize)

#define synapse_context_stack_traits_deallocate(pTraits, pDealloc, pSize)\
	pTraits.deallocate(pTraits.stack_entity, pDealloc, pSize)

#define synapse_context_stack_traits_resize(pTraits, pPrevious, pSize, pNewSize)\
	pTraits.resize(pTraits.stack_entity, pPrevious, pSize, pNewSize)

#define synapse_context_stack_traits_migrate(pTraits, pPrevious, pPrevSize)\
	pTraits.migrate(pTraits.stack_entity, pPrevious, pPrevSize)