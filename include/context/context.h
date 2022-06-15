#pragma once

typedef struct synapse_context_handle { void* opaque; } synapse_context_handle;
typedef struct synapse_context_interface
{
	synapse_context_handle handle;
	
	synapse_context_handle(*initialize)(void*);
	void				  (*cleanup)   (synapse_context_handle);
} synapse_context_interface;