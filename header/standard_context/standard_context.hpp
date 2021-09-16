#include <context/asm/standard_context/export.hpp>

namespace context  {
namespace internal {
    void execute_to(context::context_entity&, void(*)(void*), void*);
    void switch_to (context::context_entity&); // Switch to Other Branch Context.
}

    void switch_to (context::context_entity&);
    void execute_to(context::context_entity&, void(*)(void*), void*);
}