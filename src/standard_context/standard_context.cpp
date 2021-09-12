#include <context/header/standard_context/standard_context.hpp>

thread_local context::context_entity* context_block = NULL;

void context::internal::execute_to(context::context_entity& context, void(*exec)(void*), void* args)
{
    context_store_cpu  (context_block->cpu_context)  ;
    context_store_stack(context_block->stack_context);

    context_block  = &context;
    context_load_stack (context_block->stack_context); // RDI : next.stack_context.
    
    exec(args);                                 // Execute Function.
}

void context::internal::switch_to(context::context_entity& next)
{
    context_store_cpu  (context_block->cpu_context)  ; // Store Previous CPU Context.
    context_store_stack(context_block->stack_context);
    
    context_switch_to  (next);               // Restore Stack Context and Instruction Pointer.
}

void context::execute_to(context::context_entity& context, void(*exec)(void*), void* args)
{
    internal::execute_to(context, exec, args);
    context_load_cpu    (context_block->cpu_context);
}

void context          ::switch_to(context::context_entity& next)
{
    internal::switch_to(next);
    context_load_cpu   (context_block->cpu_context);
}