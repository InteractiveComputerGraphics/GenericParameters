#ifndef __FunctionParameter_h__
#define __FunctionParameter_h__

#include "Parameter.h"

namespace GenParam
{
	/** Class of a function parameter. This parameter type contains a callback function.
	*/
	class FunctionParameter : public ParameterBase
	{
	public:
		using CallbackFunc = std::function<void()>;

	protected:
		CallbackFunc m_function;

	public:
		/** Constructor */
		FunctionParameter(const std::string& name, const std::string& label, CallbackFunc function)
			: ParameterBase(name, label, ParameterBase::FUNCTION),
			m_function(function)
		{
		}

		void callFunction() 
		{
			if (m_function != nullptr) 
				m_function(); 
		}

		virtual ~FunctionParameter() {}

		virtual void setReadOnly(const bool val) 
		{
		}
	};
}

#endif
