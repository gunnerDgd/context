#include <type_traits>
#include <xmmintrin.h>

#include <context/header/standard_context/standard_context.hpp>
#include <context/controller/standard_controller/wrapped_executor.hpp>

namespace context {
    template <typename ContextType, typename StackAllocator>
    class context_controller;
}