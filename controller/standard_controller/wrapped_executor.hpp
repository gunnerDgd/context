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

    template <typename F>
    struct context_wrapper<F, void>
    {
        context_wrapper(F&& ctx_fp)
            : wrapped_function(ctx_fp) { }
        
        void execute()                   { wrapped_function(); }

        F&                   wrapped_function;
    };

    template <typename C, typename Fp, typename... Args>
    struct class_context_wrapper
    {
        class_context_wrapper(C* ctx_class, Fp& ctx_fp, std::tuple<Args...>& ctx_args)
            : wrapped_function(ctx_fp)   ,
              wrapped_class   (ctx_class),
              wrapped_argument(ctx_args) { }
        
        void execute()      { std::apply(wrapped_function, std::tuple_cat(std::make_tuple(wrapped_class), wrapped_argument)); }

        std::tuple<Args...>& wrapped_argument;
        C*                   wrapped_class   ;
        Fp&                  wrapped_function;
    };

    template <typename C, typename Fp>
    struct class_context_wrapper<C, Fp, void>
    {
        class_context_wrapper(C* ctx_class, Fp& ctx_fp)
            : wrapped_function(ctx_fp)   ,
              wrapped_class   (ctx_class) { }
        
        void execute() { std::apply(wrapped_function, std::make_tuple(wrapped_class)); }

        C*  wrapped_class   ;
        Fp& wrapped_function;
    };


    template <typename Fp, typename... Args>
    void context_executor      (void* exec_args) { reinterpret_cast<context_wrapper<Fp, Args...>*>(exec_args)->execute(); }

    template <typename C, typename Fp, typename... Args>
    void class_context_executor(void* exec_args) { reinterpret_cast<class_context_wrapper<C, Fp, Args...>*>(exec_args)->execute(); };
}