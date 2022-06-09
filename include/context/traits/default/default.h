#pragma once
#include <context/traits/default/default_types.h>

synapse_context_default_entity
synapse_context_default_initialize  ();

void
synapse_context_default_cleanup     (synapse_context_default_entity);

synapse_context_default_entity
synapse_context_default_execute_from(synapse_context_default_entity, void(*)(void*), void*);

void
synapse_context_default_switch_to   (synapse_context_default_entity, synapse_context_default_entity);

void
synapse_context_default_attach_stack(synapse_context_default_entity, void*, size_t);