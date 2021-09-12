#include <context/header/standard_context/standard_context.hpp>

thread_local context::context_entity* current_context = NULL;

void context::internal::execute_to(context::context_entity& context, void(*exec)(void*), void* args)
{
    context_store_cpu  (current_context->cpu_context)  ;
    context_store_stack(current_context->stack_context);

    current_context  = &context;
    context_load_stack (current_context->stack_context); // RDI : next.stack_context.
    
    exec(args);                                 // Execute Function.
}

void context::internal::switch_to(context::context_entity& next)
{
    context_store_cpu  (current_context->cpu_context)  ; // Store Previous CPU Context.
    context_store_stack(current_context->stack_context);
    
    context_switch_to  (next);               // Restore Stack Context and Instruction Pointer.
}

void context::execute_to(context::context_entity& context, void(*exec)(void*), void* args)
{
    internal::execute_to(context, exec, args);
    context_load_cpu    (current_context->cpu_context);
}

void context          ::switch_to(context::context_entity& next)
{
    internal::switch_to(next);
    context_load_cpu   (current_context->cpu_context);
}