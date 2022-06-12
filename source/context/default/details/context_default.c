#include <context/traits/default/details/context_default.h>
#include <context/traits/default/default_types.h>

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

void
____synapse_context_default_execute_from(void *pExecArgs)
{
	__synapse_context_default_exec_param* ptr_exec_param
		= pExecArgs;

	__synapse_context_default_entity *ptr_context_prev
		= ptr_exec_param->ptr_context_prev,
									 *ptr_context_curr
		= ptr_exec_param->ptr_context_curr;

	synapse_context_default_entity		  ptr_exec_prev
		= { .opaque = ptr_exec_param->ptr_context_prev };

	ptr_exec_param->ptr_exec(ptr_exec_prev, ptr_exec_param->ptr_param);
	free					(ptr_exec_param);

	__synapse_context_default_switch_to(ptr_context_curr, ptr_context_prev);
}

__synapse_context_default_entity*
__synapse_context_default_execute_from(__synapse_context_default_entity* pCurr, void(*pExec)(synapse_context_default_entity, void*), void* pExecArgs)
{
	__synapse_context_default_entity* ptr_prev
		= __synapse_context_default_initialize();

	__synapse_context_default_exec_param* ptr_exec_param
		= malloc(sizeof(__synapse_context_default_exec_param));

	ptr_exec_param->ptr_context_curr = pCurr	;
	ptr_exec_param->ptr_context_prev = ptr_prev ;
	
	ptr_exec_param->ptr_exec		 = pExec    ;
	ptr_exec_param->ptr_param		 = pExecArgs;

	store_and_execute(&ptr_prev->register_field,
					  &pCurr   ->register_field, 
					  &____synapse_context_default_execute_from, 
					   ptr_exec_param);
	
	return			   ptr_prev;
}

void
__synapse_context_default_attach_stack(__synapse_context_default_entity* pEntity, void* pStack, size_t pStackSize)
{
	pEntity->attached_stack		 = (uint64_t)pStack	   ;
	pEntity->attached_stack_size =			 pStackSize;

	pEntity->register_field.r_stack.rbp = pEntity->attached_stack + pStackSize - 0x16;
	pEntity->register_field.r_stack.rsp = pEntity->attached_stack + pStackSize - 0x16;
}