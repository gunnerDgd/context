#include <context/asm/standard_context/types.hpp>

namespace context {
    thread_local extern context::context_entity* context_block;
}

extern "C"
{
    void context_store_cpu    (context::cpu_register& curr);
    void context_load_cpu     (context::cpu_register& curr);

    void context_capture_stack(context::frame&        curr);
    void context_store_stack  (context::frame&        curr);
    void context_load_stack   (context::frame&        curr);

    void context_switch_to    (context::context_entity& next);
}