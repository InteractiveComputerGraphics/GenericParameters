#ifndef __ParameterObject_h__
#define __ParameterObject_h__

#include <vector>
#include <memory>
#include <string>
#include "NumericParameter.h"
#include "EnumParameter.h"
#include "VectorParameter.h"
#include "FunctionParameter.h"

namespace GenParam
{
	template<typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args)
	{
	    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	/** An object that uses generic parameters should be inherited from this class.
	* An example is given in the class TestParameterObject.
	*/
	class ParameterObject
	{
	protected:
		std::vector<ParameterBase::Ptr> m_parameters;

	public:
		ParameterObject() : m_parameters() {}
		virtual ~ParameterObject() { m_parameters.clear(); }

		ParameterObject(const ParameterObject& other)
		{
			m_parameters.reserve(other.m_parameters.size());
			for (const auto& e : other.m_parameters)
				m_parameters.push_back(make_unique<GenParam::ParameterBase>(*e));
		}

		ParameterObject& operator=(const ParameterObject& other)
		{
			m_parameters.reserve(other.m_parameters.size());
			for (const auto& e : other.m_parameters)
				m_parameters.push_back(make_unique<GenParam::ParameterBase>(*e));
			return *this;
		}

		/** This method should be overwritten to init the parameter definitions. */
		virtual void initParameters() {}
		unsigned int numParameters() const { return static_cast<unsigned int>(m_parameters.size()); }
		ParameterBase* getParameter(const unsigned int index) { return m_parameters[index].get(); }
		ParameterBase* const getParameter(const unsigned int index) const { return m_parameters[index].get(); }

		template<typename T>
		int createNumericParameter(const std::string &name, const std::string &label, T* valuePtr)
		{
			m_parameters.push_back(std::unique_ptr<NumericParameter<T>>(new NumericParameter<T>(name, label, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		template<typename T>
		int createNumericParameter(const std::string &name, const std::string &label, ParameterBase::GetFunc<T> getValue, ParameterBase::SetFunc<T> setValue = {})
		{
			m_parameters.push_back(std::unique_ptr<NumericParameter<T>>(new NumericParameter<T>(name, label, getValue, setValue)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createBoolParameter(const std::string &name, const std::string &label, bool* valuePtr)
		{
			m_parameters.push_back(std::unique_ptr<Parameter<bool>>(new Parameter<bool>(name, label, ParameterBase::BOOL, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createBoolParameter(const std::string &name, const std::string &label, Parameter<bool>::GetFunc<bool> getValue, Parameter<bool>::SetFunc<bool> setValue = {})
		{
			m_parameters.push_back(std::unique_ptr<Parameter<bool>>(new Parameter<bool>(name, label, ParameterBase::BOOL, getValue, setValue)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createEnumParameter(const std::string &name, const std::string &label, int* valuePtr)
		{
			m_parameters.push_back(std::unique_ptr<EnumParameter>(new EnumParameter(name, label, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createEnumParameter(const std::string &name, const std::string &label, ParameterBase::GetFunc<int> getValue, ParameterBase::SetFunc<int> setValue = {})
		{
			m_parameters.push_back(std::unique_ptr<EnumParameter>(new EnumParameter(name, label, getValue, setValue)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createStringParameter(const std::string &name, const std::string &label, std::string* valuePtr)
		{
			m_parameters.push_back(std::unique_ptr<Parameter<std::string>>(new Parameter<std::string>(name, label, ParameterBase::STRING, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createStringParameter(const std::string &name, const std::string &label, Parameter<std::string>::GetFunc<std::string> getValue, Parameter<std::string>::SetFunc<std::string> setValue = {})
		{
			m_parameters.push_back(std::unique_ptr<Parameter<std::string>>(new Parameter<std::string>(name, label, ParameterBase::STRING, getValue, setValue)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		template<typename T>
		int createVectorParameter(const std::string &name, const std::string &label, const unsigned int dim, T* valuePtr)
		{
			m_parameters.push_back(std::unique_ptr<VectorParameter<T>>(new VectorParameter<T>(name, label, dim, valuePtr)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		template<typename T>
		int createVectorParameter(const std::string &name, const std::string &label, const unsigned int dim, ParameterBase::GetVecFunc<T> getVecValue, ParameterBase::SetVecFunc<T> setVecValue = {})
		{
			m_parameters.push_back(std::unique_ptr<VectorParameter<T>>(new VectorParameter<T>(name, label, dim, getVecValue, setVecValue)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		int createFunctionParameter(const std::string &name, const std::string &label, FunctionParameter::CallbackFunc function)
		{
			m_parameters.push_back(std::unique_ptr<FunctionParameter>(new FunctionParameter(name, label, function)));
			return static_cast<int>(m_parameters.size() - 1);
		}

		/** Get the parameter value by its id. */
		template<typename T>
		T getValue(const unsigned int parameterId) const
		{
			Parameter<T>* param = static_cast<Parameter<T>*>(getParameter(parameterId));
			return param->getValue();
		}

		/** Set the parameter value by its id. */
		template<typename T>
		void setValue(const unsigned int parameterId, const T v) 
		{
			ParameterBase *paramBase = getParameter(parameterId);
			if (paramBase->checkType(v))
				static_cast<Parameter<T>*>(paramBase)->setValue(v);
			else
				std::cerr << "Type mismatch in setValue!" << std::endl;
		}

		/** Get the parameter value by its id. */
		template<typename T>
		T* getVecValue(const unsigned int parameterId) const
		{
			VectorParameter<T>* param = static_cast<VectorParameter<T>*>(getParameter(parameterId));
			return param->getValue();
		}

		/** Set the parameter value by its id. */
		template<typename T>
		void setVecValue(const unsigned int parameterId, T *v)
		{
			ParameterBase *paramBase = getParameter(parameterId);
			if (paramBase->checkType(v))
				static_cast<VectorParameter<T>*>(paramBase)->setValue(v);
			else
				std::cerr << "Type mismatch in setValue!" << std::endl;
		}

		/** Call the function of a function parameter by its id. */
		void callFunction(const unsigned int parameterId)
		{
			ParameterBase *paramBase = getParameter(parameterId);
			if (paramBase->getType() == ParameterBase::FUNCTION)
				static_cast<FunctionParameter*>(paramBase)->callFunction();
			else
				std::cerr << "Type mismatch in callFunction!" << std::endl;
		}

		void setVisible(const unsigned int parameterId, const bool v) { m_parameters[parameterId]->setVisible(v); }
		bool getVisible(const unsigned int parameterId) { return m_parameters[parameterId]->getVisible(); }

		void setReadOnly(const unsigned int parameterId, const bool v) { m_parameters[parameterId]->setReadOnly(v); }
		bool getReadOnly(const unsigned int parameterId) { return m_parameters[parameterId]->getReadOnly(); }

		void setName(const unsigned int parameterId, const std::string &v) { m_parameters[parameterId]->setName(v); }
		std::string getName(const unsigned int parameterId) { return m_parameters[parameterId]->getName(); }

		void setLabel(const unsigned int parameterId, const std::string &v) { m_parameters[parameterId]->setLabel(v); }
		std::string getLabel(const unsigned int parameterId) { return m_parameters[parameterId]->getLabel(); }

		void setGroup(const unsigned int parameterId, const std::string &v) { m_parameters[parameterId]->setGroup(v); }
		std::string getGroup(const unsigned int parameterId) { return m_parameters[parameterId]->getGroup(); }

		void setDescription(const unsigned int parameterId, const std::string &v) { m_parameters[parameterId]->setDescription(v); }
		std::string getDescription(const unsigned int parameterId) { return m_parameters[parameterId]->getDescription(); }

		void setHotKey(const unsigned int parameterId, const std::string &v) { m_parameters[parameterId]->setHotKey(v); }
		std::string getHotKey(const unsigned int parameterId) { return m_parameters[parameterId]->getHotKey(); }

		GenParam::ParameterBase::DataTypes getType(const unsigned int parameterId) const { return m_parameters[parameterId]->getType(); }
	};

}
#endif
