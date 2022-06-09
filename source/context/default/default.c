#include <context/traits/default/default.h>
#include <context/traits/default/details/context_default.h>

synapse_context_default_entity
synapse_context_default_initialize()
{
	synapse_context_default_entity ptr_return
		= { .opaque = __synapse_context_default_initialize() };

	return ptr_return;
}

void
synapse_context_default_cleanup(synapse_context_default_entity pEntity)
{
	__synapse_context_default_cleanup(pEntity.opaque);
}

synapse_context_default_entity
synapse_context_default_execute_from(synapse_context_default_entity pEntity, void(*pExec)(void*), void* pExecArgs)
{
	synapse_context_default_entity ptr_return = 
		{ .opaque = __synapse_context_default_execute_from(pEntity.opaque, pExec, pExecArgs) };

	return ptr_return;
}

void
synapse_context_default_switch_to(synapse_context_default_entity pPrev, synapse_context_default_entity pNext)
{
	__synapse_context_default_switch_to(pPrev.opaque, pNext.opaque);
}

void
synapse_context_default_attach_stack(synapse_context_default_entity pEntity, void* pStack, size_t pStackSize)
{
	__synapse_context_default_attach_stack(pEntity.opaque, pStack, pStackSize);
}