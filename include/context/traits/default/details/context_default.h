#pragma once
#include <context/traits/default/details/context_default_types.h>

__synapse_context_default_entity*
__synapse_context_default_initialize();

void
__synapse_context_default_cleanup     (__synapse_context_default_entity*);

void
__synapse_context_default_switch_to   (__synapse_context_default_entity*, __synapse_context_default_entity*);

__synapse_context_default_entity*
__synapse_context_default_execute_from(__synapse_context_default_entity*, void(*)(void*), void*);

void
__synapse_context_default_attach_stack(__synapse_context_default_entity*, void*, size_t);