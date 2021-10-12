#pragma once
#include <context/include/asm/types.hpp>

namespace context    {
namespace asm_export {

	extern "C"
	{
		void store_and_execute(context::asm_export::types::register_field&,
							   context::asm_export::types::register_field&,
							   void(*)(void*),
							   void *);
		void store_and_switch (context::asm_export::types::register_field&,
							   context::asm_export::types::register_field&);
	}
}
}