#pragma once
#include <type_traits>

namespace context {
	template <typename BlockEntity, typename BlockTraits>
	class basic_processor_block
	{
	public:
		typedef basic_processor_block<BlockEntity, BlockTraits> this_type;
		typedef BlockEntity										entity_type;
		typedef BlockTraits										traits_type;

	public:
		basic_processor_block ();
		~basic_processor_block();

	private:
		entity_type __M_pcb_entity;
	};
}