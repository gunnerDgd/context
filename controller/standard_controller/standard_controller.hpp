#include <context/controller/context_controller.hpp>

namespace context {

    /*
    Requirement of the Context Controller

    [!! Must Accept One Stack Allocator Template.]

    1) allocate_context(typename StackAllocator::size_type)
        --> Allocate Context and Its Stack Space (Can be Heap, or Page)

    2) allocate_context()
        --> Capture Current Context and Its Stack Space.
        --> Or, Just Create Context Control Block for New Context.

    3) deallocate_context()
        --> Delete Context and Destruct Its Stack Space.

    4) switch_context(context_type& next, Fp&& next_exec, Args&&... next_args)
        --> Starts New Context at New Stack Space Specified in Variable "next (Type : context_type)".

    5) switch_context(context_type& next)
        --> Switch Current Context to Context Specified in Variable "next".

    6) current_context()
        --> Get Current Context.

    */

    template <typename StackAllocator>
    class context_controller<context_entity, StackAllocator>
    {
    public:
        using controller_type = context_controller<context::context_entity, StackAllocator>;
        using context_type    = context_entity;
        using context_pointer = std::conditional_t<std::is_pointer_v<context_type>, context_type, std::add_pointer_t<context_type>>;
        static constexpr context_pointer empty_context = nullptr;
        
        // Necessary Parts for ControllerTraits.
    public:
        static context_pointer  allocate_context  (typename StackAllocator::size_type);
        static context_pointer  allocate_context  (context_type&, typename StackAllocator::size_type);
        static context_pointer  allocate_context  ()                                  { return (new context_entity); }
        
        static void             deallocate_context(context_pointer);
        static void             deallocate_context(context_type&)  ;
        
        template <typename C, typename Fp, typename... Args>
        static void             switch_context    (context_type&, Fp&&, std::tuple<Args...>&&, C*) requires std::is_member_function_pointer_v<Fp>;
        template <typename C, typename Fp>
        static void             switch_context    (context_type&, Fp&&, C*)                        requires std::is_member_function_pointer_v<Fp>;
        
        template <typename Fp, typename... Args>
        static void             switch_context    (context_type&, Fp&&, std::tuple<Args...>&&)     requires std::is_invocable_v<Fp, Args...>;
        template <typename Fp>
        static void             switch_context    (context_type&, Fp&&)                            requires std::is_invocable_v<Fp, void>;
        static void             switch_context    (context_type& dc);

        static context_pointer& current_context   () { return context_block; }
    };
}

template <typename StackAllocator>
typename context::context_controller<context::context_entity, StackAllocator>::context_pointer 
         context::context_controller<context::context_entity, StackAllocator>::allocate_context  (typename StackAllocator::size_type stack_size)
{
    context_pointer alloc_context    = new context_entity;
    alloc_context->stack_pointer     = reinterpret_cast<uint64_t>(StackAllocator::allocate(stack_size));
    
    alloc_context->stack_context.rsp = reinterpret_cast<uint64_t>(alloc_context->stack_pointer) + stack_size;
    alloc_context->stack_context.rbp = alloc_context->stack_context.rsp;

    return          alloc_context;
}

template <typename StackAllocator>
typename context::context_controller<context::context_entity, StackAllocator>::context_pointer  
         context::context_controller<context::context_entity, StackAllocator>::allocate_context(context_type& alloc_context, typename StackAllocator::size_type stack_size)
{
    alloc_context.stack_pointer     = reinterpret_cast<uint64_t>(StackAllocator::allocate(stack_size));
    
    alloc_context.stack_context.rsp = reinterpret_cast<uint64_t>(alloc_context.stack_pointer) + stack_size;
    alloc_context.stack_context.rbp = alloc_context.stack_context.rsp;
}

template <typename StackAllocator>
void context::context_controller<context::context_entity, StackAllocator>::deallocate_context(context_pointer dealloc_context)
{
    if(dealloc_context->stack_pointer != 0)
    {
        StackAllocator::deallocate(reinterpret_cast<void*>(dealloc_context->stack_pointer),
                                                           dealloc_context->stack_size)   ;
    }
    
    delete dealloc_context;
}

template <typename StackAllocator>
void context::context_controller<context::context_entity, StackAllocator>::deallocate_context(context_type& dealloc_context)
{
    if(dealloc_context.stack_pointer != 0)
    {
        StackAllocator::deallocate(reinterpret_cast<void*>(dealloc_context.stack_pointer),
                                                           dealloc_context.stack_size)   ;
    }
}

template <typename StackAllocator>
void context::context_controller<context::context_entity, StackAllocator>::switch_context(context_type& next) 
{
    switch_to   (next); 
}

template <typename StackAllocator>
template <typename Fp, typename... Args>
void context::context_controller<context::context_entity, StackAllocator>::switch_context(context_type& next, 
                                                                                          Fp&& next_exec, std::tuple<Args...>&& next_args) requires std::is_invocable_v<Fp, Args...>
{
    context_wrapper<Fp, Args...> switch_argument(next_exec, next_args);
    execute_to                                  (next, context_executor<Fp, Args...>, (void*)&switch_argument);
}

template <typename StackAllocator>
template <typename Fp>
void context::context_controller<context::context_entity, StackAllocator>::switch_context(context_type& next, Fp&& next_exec) requires std::is_invocable_v<Fp, void>
{
    class_context_wrapper<Fp, void> switch_argument(next_exec);
    execute_to                                     (next, context_executor<Fp, void>, (void*)&switch_argument);
}

template <typename StackAllocator>
template <typename C, typename Fp, typename... Args>
void context::context_controller<context::context_entity, StackAllocator>::switch_context(context_type& next,
                                                                                          Fp&& next_exec, std::tuple<Args...>&& next_args, C* next_class) requires std::is_member_function_pointer_v<Fp>
{
    class_context_wrapper<C, Fp, Args...> switch_argument(next_class, next_exec, next_args);
    execute_to                                           (next, class_context_executor<C, Fp, Args...>, (void*)&switch_argument);
}

template <typename StackAllocator>
template <typename C, typename Fp>
void context::context_controller<context::context_entity, StackAllocator>::switch_context(context_type& next,
                                                                                          Fp&& next_exec, C* next_class) requires std::is_member_function_pointer_v<Fp>
{
    class_context_wrapper<C, Fp, void> switch_argument(next_class, next_exec);
    execute_to                                        (next, class_context_executor<C, Fp, void>, (void*)&switch_argument);
}