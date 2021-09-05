#pragma once
#include <iostream>
#include <tuple>

namespace context {
    class alignas(16) cpu_register // 64 Byte.
    {
    public:
        union
        {
            struct
            {
                uint64_t     rax, rbx, rcx, rdx,
                             rsi, rdi, rip     ; // 56 Byte
            };  uint64_t     register_block[7] ;
        };
    };

    class alignas(16) frame // 16 Byte
    {
    public:
        union
        {
            struct { uint64_t rbp, rsp; }      ;
            uint64_t          stack_register[2];
        };
    };

    struct context_entity
    {
        cpu_register cpu_context  ; // 64
        frame        stack_context; // 16
        
        uint64_t     stack_pointer = 0;
        uint64_t     stack_size    = 0;
    };

    enum  execution_state
    {
        standby,
        running,
        stopped
    };

    template <typename Fp, typename... Args>
    struct execution_argument
    {
        execution_argument(Fp f, Args&&... a)
            : exec_argument(std::forward_as_tuple(a...)),
              exec_function(f)                          {  }

        Fp                  exec_function;
        std::tuple<Args...> exec_argument;
    };
}