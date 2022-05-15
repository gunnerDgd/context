#include <context/traits/default_traits.hpp>

#include <context/asm_export/export.hpp>

void context::default_traits::switch_to(native_handle_type* ct_prev, native_handle_type* ct_next)
{
	asm_export::store_and_switch(*ct_prev, *ct_next);
}