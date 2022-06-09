#pragma once
#include <stdint.h>

typedef struct __synapse_context_stack_default_stack_entity
{
	size_t alloc_unit;
} __synapse_context_stack_default_stack_entity;

__synapse_context_stack_default_stack_entity*
__synapse_context_stack_default_stack_initialize(size_t);

void
__synapse_context_stack_default_stack_cleanup   (__synapse_context_stack_default_stack_entity*);

void*
__synapse_context_stack_default_stack_allocate  (__synapse_context_stack_default_stack_entity*, void*, size_t);

void
__synapse_context_stack_default_stack_deallocate(__synapse_context_stack_default_stack_entity*, void*, size_t);

void*
__synapse_context_stack_default_stack_resize	(__synapse_context_stack_default_stack_entity*, void*, size_t, size_t);

void*
__synapse_context_stack_default_stack_migrate	(__synapse_context_stack_default_stack_entity*, void*, size_t);