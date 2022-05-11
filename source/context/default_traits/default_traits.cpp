#include <context/traits/default_traits.hpp>
#include <context/traits/default_traits_exec.hpp>

#include <context/asm_export/export.hpp>

void context::default_traits::switch_to(control_block& ct_prev, control_block& ct_next)
{
	asm_export::store_and_switch(ct_prev, ct_next);
}

void context::default_traits::execute_from(control_block& ex_prev, control_block& ex_curr, executable& exec)
{
	asm_export::store_and_execute(ex_prev, ex_curr, 
								  exec.__M_exec_func, 
								  exec.__M_exec_args);
}