#pragma once
#include <context/asm_export/export.hpp>
#include <context/asm_export/export_types.hpp>

#include <tuple>
#include <type_traits>

namespace context {
	class standard_entity
	{
	public:
		template <typename ExecType, typename... ExecArgs>
		class binded_execution;

		template <typename ExecType, typename... ExecArgs>
		static auto bind(ExecType&&, ExecArgs&&...);
		
	public:
		typedef void(*execute_type)(void*);
		typedef void* parameter_type;
		
	public:
		template <typename T>
		struct is_executable								    { static constexpr bool value = false; };

		template <>
		struct is_executable<asm_export::types::context_entity> { static constexpr bool value = true; } ;
		 
	public:
		template <typename PcbObject, typename ExecType, typename... ExecArgs>
		static PcbObject* execute_at(PcbObject&&, ExecType&&, ExecArgs&&...) requires is_executable<typename PcbObject::entity_type>::value;
		template <typename PcbPrev, typename PcbCurr>
		static void		  switch_to (PcbPrev&&, PcbCurr&&)					 requires is_executable<typename PcbPrev::entity_type>::value && is_executable<typename PcbCurr::entity_type>::value;
	};

	template <typename ExecType, typename... ExecArgs>
	class standard_entity::binded_execution
	{
	public:
		typedef std::conditional_t<std::is_reference_v<ExecType>, ExecType, ExecType&> exec_type;
		typedef std::tuple<ExecArgs...>												   args_type;
		typedef binded_execution<ExecType, ExecArgs...>								   bind_exec_type;

	public:
		binded_execution   (exec_type, args_type);
		static void execute(bind_exec_type*);

	public:
		exec_type   binded_executor;
		args_type   binded_argument;
	};
}

template <typename ExecType, typename... ExecArgs>
context::standard_entity::binded_execution<ExecType, ExecArgs...>::binded_execution(exec_type exec, args_type args)
	: binded_executor(exec),
	  binded_argument(std::move(args)) {  }

template <typename ExecType, typename... ExecArgs>
auto context::standard_entity::bind(ExecType&& exec, ExecArgs&&... args)
{
	return new binded_execution<ExecType, ExecArgs...>(exec, std::make_tuple(args...));
}

template <typename ExecType, typename... ExecArgs>
void context::standard_entity::binded_execution<ExecType, ExecArgs...>::execute(bind_exec_type* exec_bind)
{
	std::apply(exec_bind->binded_executor, exec_bind->binded_argument);
	delete	   exec_bind;
}

template <typename PcbObject, typename ExecType, typename... ExecArgs>
PcbObject* context::standard_entity::execute_at(PcbObject&& pcb, ExecType&& exec, ExecArgs&&... args) requires is_executable<typename PcbObject::entity_type>::value
{
	PcbObject* exec_pcb  = new PcbObject;
	auto	   exec_bind = bind(exec, args...);

	asm_export::store_and_execute(pcb, *exec_pcb, (execute_type)std::remove_pointer_t<decltype(exec_bind)>::execute, exec_bind);
	return exec_bind;
}

template <typename PcbPrev, typename PcbCurr>
void context::standard_entity::switch_to(PcbPrev&& pcb_prev, PcbCurr&& pcb_curr) requires is_executable<typename PcbPrev::entity_type>::value&& is_executable<typename PcbCurr::entity_type>::value
{
	asm_export::store_and_switch(pcb_prev, pcb_curr);
}