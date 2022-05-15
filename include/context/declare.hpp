#pragma once
#include <type_traits>

namespace context {
	template <typename ContextTraits> class basic_context;
	template <typename ContextType>   using context_traits = typename std::remove_reference_t<ContextType>::traits_type;
	template <typename ContextType>   using executable     = typename context_traits<ContextType>::executable;
}