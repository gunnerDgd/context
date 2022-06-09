#pragma once
#include <context/traits/default/asm_export/export_types.h>

void store_and_execute(synapse_context_default_register_field*, synapse_context_default_register_field*, void(*)(void*), void *);
void store_and_switch (synapse_context_default_register_field*, synapse_context_default_register_field*);