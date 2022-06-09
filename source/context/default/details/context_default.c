#include <context/traits/default/details/context_default.h>

#include <stdlib.h>
#include <stdalign.h>

__synapse_context_default_entity*
__synapse_context_default_initialize() { return _aligned_malloc(sizeof(__synapse_context_default_entity), 16); }

void
__synapse_context_default_cleanup(__synapse_context_default_entity* pEntity) { _aligned_free(pEntity); }

void
__synapse_context_default_switch_to(__synapse_context_default_entity* pPrev, __synapse_context_default_entity* pNext)
{
	store_and_switch(&pPrev->register_field, &pNext->register_field);
}

__synapse_context_default_entity*
__synapse_context_default_execute_from(__synapse_context_default_entity* pPrev, void(*pExec)(void*), void* pExecArgs)
{
	__synapse_context_default_entity* ptr_curr
		= __synapse_context_default_initialize();

	store_and_execute(&pPrev->register_field, &ptr_curr->register_field, pExec, pExecArgs);
	return ptr_curr;
}

void
__synapse_context_default_attach_stack(__synapse_context_default_entity* pEntity, void* pStack, size_t pStackSize)
{
	pEntity->attached_stack		 = (uint64_t)pStack	   ;
	pEntity->attached_stack_size =			 pStackSize;
}