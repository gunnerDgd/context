#include <context/stack/default_stack/details/context_stack_default_stack.h>
#include <Windows.h>

__synapse_context_stack_default_stack_entity*
__synapse_context_stack_default_stack_initialize(size_t pUnitSize)
{
	__synapse_context_stack_default_stack_entity* ptr_entity
		= malloc(sizeof(__synapse_context_stack_default_stack_entity));

		   ptr_entity->alloc_unit = pUnitSize;
	return ptr_entity;
}

void
__synapse_context_stack_default_stack_cleanup(__synapse_context_stack_default_stack_entity* pDealloc)
{
	free(pDealloc);
}

void*
__synapse_context_stack_default_stack_allocate(__synapse_context_stack_default_stack_entity* pEntity, void* pHint, size_t pCount)
{
	return VirtualAlloc(pHint, pCount * pEntity->alloc_unit, MEM_COMMIT, PAGE_READWRITE);
}

void
__synapse_context_stack_default_stack_deallocate(__synapse_context_stack_default_stack_entity* pEntity, void* pDealloc, size_t pCount)
{
	VirtualFree(pDealloc, 0, MEM_FREE);
}

void*
__synapse_context_stack_default_stack_resize(__synapse_context_stack_default_stack_entity* pEntity, void* pPrevPointer, size_t pPrevSize, size_t pNewSize)
{
	void* ptr_new
		= VirtualAlloc(pPrevPointer, pNewSize * pEntity->alloc_unit, MEM_COMMIT, PAGE_READWRITE);
	
	CopyMemory (ptr_new, pPrevPointer, ((pPrevSize < pNewSize) ? pPrevSize : pNewSize));
	VirtualFree(pPrevPointer, 0, MEM_FREE);

	return ptr_new;
}

void*
__synapse_context_stack_default_stack_migrate(__synapse_context_stack_default_stack_entity* pEntity, void* pPrevPointer, size_t pPrevSize)
{
	return __synapse_context_stack_default_stack_resize(pEntity, pPrevPointer, pPrevSize, pPrevSize);
}