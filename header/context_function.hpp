#include <context/header/types.hpp>

#include <cstring>
#include <tuple>

extern "C"
{
    void context_store_cpu    (context::cpu_register& curr);
    void context_load_cpu     (context::cpu_register& curr);

    void context_capture_stack(context::frame&        curr);
    void context_store_stack  (context::frame&        curr);
    void context_load_stack   (context::frame&        curr);

    void context_switch_to    (context::context_entity& next);
}

namespace context  {
namespace internal {
    void switch_to (context::context_entity&, context::context_entity&); // Switch to Other Branch Context.
    template <typename Fp, typename... Args>
    void execute_to(context::context_entity&, context::context_entity&, execution_argument<Fp, Args...>&);
}

    void switch_to (context::context_entity&, context::context_entity&);
    template <typename Fp, typename... Args>
    void execute_to(context::context_entity&, context::context_entity&, execution_argument<Fp, Args...>&);
}

template <typename Fp, typename... Args>
void context::internal::execute_to(context::context_entity& prev, context::context_entity& next_ctx, execution_argument<Fp, Args...>& next)
{
    context_store_cpu  (prev.cpu_context)  ;
    context_store_stack(prev.stack_context);

    context_load_stack (next_ctx.stack_context); // RDI : next.stack_context.
    std::apply         (next.exec_function, next.exec_argument);
}

template <typename Fp, typename... Args>
void context::execute_to(context::context_entity& prev, context::context_entity& next_ctx, execution_argument<Fp, Args...>& next)
{
    volatile auto* instack_prev = &prev;
    volatile auto* instack_next = &next_ctx;
    
    internal::execute_to(prev, next_ctx, next);
    context_load_cpu    ((cpu_register&)instack_prev->cpu_context);
}

void context::internal::switch_to(context::context_entity& prev, context::context_entity& next)
{
    context_store_cpu  (prev.cpu_context)  ; // Store Previous CPU Context.
    context_store_stack(prev.stack_context);
    
    context_switch_to  (next);               // Restore Stack Context and Instruction Pointer.
}

void context          ::switch_to(context::context_entity& prev, context::context_entity& next)
{
    volatile context_entity* instack_prev = &prev;
    volatile context_entity* instack_next = &next;
    
    internal::switch_to(prev, next);
    context_load_cpu   ((cpu_register&)instack_prev->cpu_context);
    
}