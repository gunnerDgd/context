#pragma once
#include <context/declare.hpp>
#include <memory>

#include <cstdlib>
#include <cstring>

namespace context {
	template <typename ContextTraits> 
	class basic_context
	{
	public:
		using traits_type		 =			ContextTraits;
		using native_handle_type = typename ContextTraits::native_handle_type;

	public:
		template <typename Stack> basic_context (Stack&&)				  ; // Attaches Stack.
								  basic_context ()				 = default; // Just Create Control Block

								  basic_context (basic_context&) ;
								  basic_context (basic_context&&);
								  ~basic_context()				  {  }

	public:
												 static void		  switch_to   (basic_context&, basic_context&);
		template <typename Fn, typename... Args> static void		  execute_from(basic_context&, basic_context&, Fn&&, Args&&...);
		template <typename Fn, typename... Args> static basic_context execute_from(basic_context&,				   Fn&&, Args&&...);

	public:
		basic_context& operator=(basic_context&  rhs) { __M_context_entity =		   rhs.__M_context_entity ; return *this; }
		basic_context& operator=(basic_context&& rhs) { __M_context_entity = std::move(rhs.__M_context_entity); return *this; }

	private:
		basic_context  (native_handle_type*);
		std::shared_ptr<native_handle_type> __M_context_entity;
	};
}

template <typename ContextTraits>
template <typename Stack>
context::basic_context<ContextTraits>::basic_context(Stack&& at_stack) : __M_context_entity(new native_handle_type)
{
	traits_type::attach_stack(__M_context_entity.get(), at_stack);
}

template <typename ContextTraits>
context::basic_context<ContextTraits>::basic_context(native_handle_type* hnd)
	: __M_context_entity(hnd) {  }

template <typename ContextTraits>
context::basic_context<ContextTraits>::basic_context(basic_context& pCopy)
	: __M_context_entity(pCopy)			   {  }

template <typename ContextTraits>
context::basic_context<ContextTraits>::basic_context(basic_context&& pMove)
	: __M_context_entity(std::move(pMove)) {  }

template <typename ContextTraits>
void context::basic_context<ContextTraits>::switch_to(basic_context& curr, basic_context& exec)
{
	traits_type::switch_to(curr.__M_context_entity.get(), exec.__M_context_entity.get());
}

template <typename ContextTraits>
template <typename Fn, typename... Args> 
void context::basic_context<ContextTraits>::execute_from(basic_context& curr, basic_context& exec, Fn&& fn, Args&&... args)
{
	traits_type::execute_from(curr.__M_context_entity.get(),
							  exec.__M_context_entity.get(), fn, std::forward<Args>(args)...);
}

template <typename ContextTraits>
template <typename Fn, typename... Args> 
context::basic_context<ContextTraits>
context::basic_context<ContextTraits>::execute_from(basic_context& exec, Fn&& fn, Args&&... args)
{
	return basic_context(
				traits_type::execute_from(exec.__M_context_entity.get(), fn, std::forward<Args>(args)...));
}