#include <context/header/standard_context/standard_context.hpp>
#include <type_traits>

namespace context {

    template <typename StackAllocator>
    class standard_controller
    {
    public:
        using controller_type = standard_controller<StackAllocator>;
        using context_type    = context_entity;
        using context_pointer = std::conditional_t<std::is_pointer_v<context_type>, context_type, std::add_pointer_t<context_type>>;
        
        // Necessary Parts for ControllerTraits.
    public:
        static context_pointer  allocate_context  (typename StackAllocator::size_type);
        static context_pointer  allocate_context  ()                                  { return (context_block = new context_entity); }
        static void             deallocate_context(context_pointer);
        
        template <typename Fp, typename... Args>
        static void             switch_context    (context_type& next, Fp&& next_exec, Args&&... next_args);
        static void             switch_context    (context_type& next);

        static context_pointer& current_context   () { return context_block; }
    };
}

template <typename StackAllocator>
typename context::context_controller<StackAllocator>::context_pointer context::context_controller<StackAllocator>::allocate_context  (typename StackAllocator::size_type stack_size)
{
    context_pointer alloc_context    = new context_entity;
    alloc_context->stack_pointer     = reinterpret_cast<uint64_t>(StackAllocator::allocate(stack_size));
    
    alloc_context->stack_context.rsp = reinterpret_cast<uint64_t>(alloc_context->stack_pointer) + stack_size;
    alloc_context->stack_context.rbp = alloc_context->stack_context.rsp;

    context_block = alloc_context;
    return          alloc_context;
}

template <typename StackAllocator>
void context::context_controller<StackAllocator>::deallocate_context(context::context_controller<StackAllocator>::context_pointer dealloc_context)
{
    if(dealloc_context->stack_pointer != 0)
    {
        StackAllocator::deallocate(reinterpret_cast<void*>(dealloc_context->stack_pointer),
                                                           dealloc_context->stack_size)   ;
    }
    
    delete dealloc_context;
}
        
template <typename StackAllocator>
template <typename Fp, typename... Args>
void context::context_controller<StackAllocator>::switch_context(context::context_controller<StackAllocator>::context_type& next, 
                                                                 Fp&& next_exec, Args&&... next_args)
{
    context_wrapper<Fp, Args...> switch_argument(next_exec, std::forward<Args>(next_args)...);
    execute_to                                  (next, &controller_type::execution_wrapper, (void*)&switch_argument);
}

template <typename StackAllocator>
void context::context_controller<StackAllocator>::switch_context(context_type& next) { switch_to(next); }

template <typename StackAllocator>
template <typename R, typename... Args>
void context::context_controller<StackAllocator>::context_executor(void* args)
{
    auto   exec_args = reinterpret_cast<context_wrapper<R, Args...>*>(args);
    std::apply        (exec_args->context_function, 
                      *reinterpret_cast<std::tuple<Args&&...>*>(exec_args->context_argument));
}
