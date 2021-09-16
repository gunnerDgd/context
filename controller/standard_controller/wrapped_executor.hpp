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

    template <typename Fp, typename... Args>
    static void context_executor(void* exec_args) { reinterpret_cast<context_wrapper<Fp, Args...>*>(exec_args)->execute(); }
}