#include <context/stack/default_stack/default_stack.h>
#include <context/stack/default_stack/details/context_stack_default_stack.h>

#include <stdlib.h>

synapse_context_stack_traits*
synapse_context_stack_default_stack_initialize(size_t pAllocUnit)
{
	synapse_context_stack_traits* ptr_traits
		= malloc(sizeof(synapse_context_stack_traits));

	ptr_traits->stack_entity = __synapse_context_stack_default_stack_initialize(pAllocUnit);
	
	ptr_traits->allocate	 = &synapse_context_stack_default_stack_allocate			   ;
	ptr_traits->deallocate	 = &synapse_context_stack_default_stack_deallocate			   ;
	
	ptr_traits->resize		 = &synapse_context_stack_default_stack_resize				   ;
	ptr_traits->migrate  	 = &synapse_context_stack_default_stack_migrate				   ;

	return ptr_traits;
}

void
synapse_context_stack_default_stack_cleanup(synapse_context_stack_traits* pTraits)
{
	__synapse_context_stack_default_stack_cleanup(pTraits->stack_entity);
	free										 (pTraits)			    ;
}

void*
synapse_context_stack_default_stack_allocate(void* pTraits, void* pHint, size_t pAllocSize)
{
	return __synapse_context_stack_default_stack_allocate(pTraits, pHint, pAllocSize);
}

void
synapse_context_stack_default_stack_deallocate(void* pTraits, void* pDealloc, size_t pDeallocSize)
{
	__synapse_context_stack_default_stack_deallocate(pTraits, pDealloc, pDeallocSize);
}

void*
synapse_context_stack_default_stack_resize(void* pTraits, void* pPrevPointer, size_t pPrevSize, size_t pNewSize)
{
	return __synapse_context_stack_default_stack_resize(pTraits, pPrevPointer, pPrevSize, pNewSize);
}

void*
synapse_context_stack_default_stack_migrate(void* pTraits, void* pPrevPointer, size_t pPrevSize)
{
	return __synapse_context_stack_default_stack_migrate(pTraits, pPrevPointer, pPrevSize);
}