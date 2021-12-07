#pragma once
#include <context/asm_export/export_types.hpp>

namespace context    {
namespace asm_export {

	extern "C"
	{
		void store_and_execute(types::register_field&, types::register_field&, void(*)(void*), void *);
		void store_and_switch (types::register_field&, types::register_field&);
	}
}
}