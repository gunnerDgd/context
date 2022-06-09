#include <context/traits/default/default.hpp>

context::default_context::default_context()
	: __M_context_handle(synapse_context_default_initialize()) {  }

context::default_context::default_context(native_handle_type pHandle)
	: __M_context_handle(pHandle) {}

void context::default_context::switch_to(default_context& pPrev, default_context& pNext)
{
	synapse_context_default_switch_to(pPrev.__M_context_handle, pNext.__M_context_handle);
}