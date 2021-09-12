#include <type_traits>
#include <tuple>

namespace context {
    template <typename F, typename... Args>
    struct context_wrapper
    {
        template <typename Fp, typename... FArg>
        context_wrapper(Fp&& arg_fp, FArg&&... arg_farg) requires std::is_same_v<F, Fp>
            : context_function(arg_fp),
              context_argument(std::tuple<FArg&&...>(std::forward<FArg>(arg_farg)...)) { }
            
        ~context_wrapper() { delete reinterpret_cast<std::tuple<Args&&...>*>(context_argument); }

        F                     context_function;
        void*                 context_argument;
    };

    template <typename Fp, typename... Args>
    static void context_executor(void*);
}