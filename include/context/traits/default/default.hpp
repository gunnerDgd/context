#pragma once
#include <type_traits>

extern "C"
{
#include <context/traits/default/default.h>
}

namespace context {
	class default_context
	{
	public:
		template <typename ExecType, typename... ExecArgs>
		class executable;
		using native_handle_type = synapse_context_default_entity;
	
	private:
		default_context(native_handle_type);

	public:
		template <typename StackType> default_context(StackType&&);
									  default_context();

	public:
		template <typename Executable>
		static default_context execute_from(default_context&, Executable&&);
		static void			   switch_to   (default_context&, default_context&);

	private:
		native_handle_type
			__M_context_handle;
	};
}

template <typename StackType> 
context::default_context::default_context(StackType&& pStack)
	: __M_context_handle(synapse_context_default_initialize())
{
	synapse_context_default_attach_stack(__M_context_handle, pStack.get_pointer(), pStack.size());
}

template <typename Executable>
context::default_context 
context::default_context::execute_from(default_context& pPrev, Executable&& pExec)
{
	typedef std::remove_reference_t<Executable> __exec_t;
	return default_context(synapse_context_default_execute_from(pPrev.__M_context_handle, 
																__exec_t::__execute,
															   (__exec_t*)&pExec));
}