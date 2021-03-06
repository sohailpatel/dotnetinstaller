#pragma once

namespace DVLib
{
	namespace UnitTests 
	{
		class ExecuteComponentCallbackImpl : public IExecuteCallback
		{
		public:
			long starts;
			long begins;
			long waits;
			long successes;
			long errors;
		public:
			ExecuteComponentCallbackImpl();
			void OnExecBegin();
			bool OnComponentExecBegin(const ComponentPtr&);
			bool OnComponentExecWait(const ComponentPtr&);
			bool OnComponentExecSuccess(const ComponentPtr& component);
			bool OnComponentExecError(const ComponentPtr& component, std::exception& ex);
		};
	}
}