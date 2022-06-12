#pragma once
#include <context/traits/default/asm_export/export.h>
#include <context/traits/default/asm_export/export_types.h>

#include <context/traits/default/default_types.h>

typedef struct __synapse_context_default_entity
{
	synapse_context_default_register_field 
		register_field;
	
	SYNAPSE_CONTEXT_DEFAULT_ALIGNED_REGISTER 
		attached_stack	   ,
		attached_stack_size;
} __synapse_context_default_entity;

typedef struct __synapse_context_default_exec_param
{
	void(*ptr_exec)(synapse_context_default_entity, void*);
	void *ptr_param;

	__synapse_context_default_entity
		* ptr_context_prev,
		* ptr_context_curr;
} __synapse_context_default_exec_param;