#include <type_traits>
#include <iostream>
#include <tuple>

namespace context {
    template <typename F, typename... Args>
    struct context_wrapper
    {
        context_wrapper(F&& ctx_fp, std::tuple<Args...>& ctx_args)
            : wrapped_function(ctx_fp),
              wrapped_argument(ctx_args) { }
        
        void execute()                   { std::apply(wrapped_function, wrapped_argument); }

        std::tuple<Args...>& wrapped_argument;
        F&                   wrapped_function;
    };

    template <typename C, typename R, typename... Args>
    struct class_context_wrapper
    {
        class_context_wrapper(C* ctx_class, R(C::*ctx_fp)(Args...), std::tuple<Args...>& ctx_args)
            : wrapped_function(ctx_fp)   ,
              wrapped_class   (ctx_class),
              wrapped_argument(ctx_args) { }
        
        void execute()                   { std::apply(wrapped_function, std::tuple_cat(std::make_tuple(wrapped_class), wrapped_argument)); }

        std::tuple<Args...>& wrapped_argument;
        C*                   wrapped_class   ;
        R               (C::*wrapped_function)(Args...);
    };

    template <typename Fp, typename... Args>
    void context_executor(void* exec_args) { reinterpret_cast<context_wrapper<Fp, Args...>*>  (exec_args)->execute(); }

    template <typename C, typename R, typename... Args>
    void context_executor(void* exec_args) { reinterpret_cast<class_context_wrapper<C, R, Args...>*>(exec_args)->execute(); };

    template <typename Fp>
    void context_executor(void* exec_args) { reinterpret_cast<Fp>(exec_args)(); }
}