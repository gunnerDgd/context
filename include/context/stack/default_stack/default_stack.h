#pragma once
#include <context/stack/stack_traits.h>

synapse_context_stack_traits*
synapse_context_stack_default_stack_initialize(size_t);

void
synapse_context_stack_default_stack_cleanup   (synapse_context_stack_traits*);

void*
synapse_context_stack_default_stack_allocate(void*, void*, size_t);

void
synapse_context_stack_default_stack_deallocate(void*, void*, size_t);

void*
synapse_context_stack_default_stack_resize    (void*, void*, size_t, size_t);

void*
synapse_context_stack_default_stack_migrate   (void*, void*, size_t);