#include <context/stack/default_stack/default_stack.hpp>

context::stack::default_stack::default_stack(size_type pSize) // Creates Stack with Given Size.
	: __M_stack_traits	  (synapse_context_stack_default_stack_initialize(4096)),
	  __M_stack_alloc_size(pSize)
{
	__M_stack_alloc = 
		synapse_context_stack_traits_allocate((*__M_stack_traits), NULL, (pSize / 4096) + 1);
}

context::stack::default_stack::default_stack() // Creates Empty Stack.
	: __M_stack_traits(nullptr)	{  }

context::stack::default_stack::~default_stack() // Creates Empty Stack.
{
	synapse_context_stack_default_stack_cleanup(__M_stack_traits);
}

context::stack::default_stack
context::stack::default_stack::resize(default_stack& pPrevStack, size_t pNewSize) // Migrates Stack.
{
	pointer ptr_new_stack =
		synapse_context_stack_traits_resize((*pPrevStack.__M_stack_traits), pPrevStack.__M_stack_alloc, pPrevStack.size(), pNewSize);

	pPrevStack.__M_stack_alloc_size = pNewSize;
	pPrevStack.__M_stack_alloc      = ptr_new_stack;
	
	return default_stack(std::move(pPrevStack));
}

context::stack::default_stack
context::stack::default_stack::migrate(default_stack& pPrevStack) // Migrates Stack.
{
	pointer ptr_new_stack =
		synapse_context_stack_traits_migrate((*pPrevStack.__M_stack_traits), pPrevStack.__M_stack_alloc, pPrevStack.size());

										 pPrevStack.__M_stack_alloc = ptr_new_stack;
	return default_stack(std::move(pPrevStack));
}

context::stack::default_stack::default_stack(default_stack&& pMove) noexcept // Moves Stack and Makes Previous Stack Object Empty.
	: __M_stack_alloc     (pMove.__M_stack_alloc)     ,
	  __M_stack_alloc_size(pMove.__M_stack_alloc_size),
	  __M_stack_traits    (pMove.__M_stack_traits)
{
	pMove.__M_stack_alloc  = nullptr;
	pMove.__M_stack_traits = nullptr;
}

typename context::stack::default_stack::pointer   
		 context::stack::default_stack::get_pointer() { return __M_stack_alloc; }

typename context::stack::default_stack::size_type 
		 context::stack::default_stack::size()		  { return __M_stack_alloc_size; }