#include <context/header/context_function.hpp>
#include <type_traits>

namespace context {

    class context_controller
    {
    public:
        using context_type    = context_entity;
        using context_pointer = std::conditional_t<std::is_pointer_v<context_type>, 
                                                                     context_type, 
                                                                     std::add_pointer_t<context_type>>;
        
    public:
        template <typename StackAllocator>
        static context_pointer allocate_context  (StackAllocator::size_type);
        static context_pointer allocate_context  ()                         { return new context_entity; }
        template <typename StackAllocator>
        static void            deallocate_context(context_pointer);
        
        template <typename Fp, typename... Args>
        static void            switch_context    (context_type& prev, context_type& next, Fp&& next_exec, Args&&... next_args);
        static void            switch_context    (context_type& prev, context_type& next);
    };
}

template <typename StackAllocator>
context::context_controller::context_pointer context::context_controller::allocate_context  (StackAllocator::size_type stack_size)
{
    context_pointer alloc_context   = new context_entity;
    alloc_context->stack_pointer    = StackAllocator::allocate(stack_size);
    
    alloc_context->stack_context.rsp = reinterpret_cast<void*>(alloc_context->stack_pointer) + stack_size;
    alloc_context->stack_context.rbp = alloc_context->stack_context.rsp;

    return alloc_context;
}

template <typename StackAllocator>
void context::context_controller::deallocate_context(context::context_controller::context_pointer dealloc_context)
{
    if(dealloc_context->stack_pointer != 0)
    {
        StackAllocator::deallocate(reinterpret_cast<void*>(dealloc_context->stack_pointer),
                                                           dealloc_context->stack_size)   ;
    }
    
    delete dealloc_context;
}
        
template <typename Fp, typename... Args>
void context::context_controller::switch_context(context::context_controller::context_type& prev, 
                                                 context::context_controller::context_type& next, 
                                                 Fp&& next_exec, Args&&... next_args)
{
    execution_argument<Fp, Args...> switch_argument(next_exec, std::forward<Args>(next_args)...);
    execute_to                                     (prev, next, switch_argument);
}
void context::context_controller::switch_context(context_type& prev, context_type& next)
{
    switch_to(prev, next);
}