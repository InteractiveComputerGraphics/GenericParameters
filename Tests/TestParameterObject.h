#ifndef __TestParameterObject_h__
#define __TestParameterObject_h__

#include "GenericParameters/ParameterObject.h"

namespace GenParam
{
	class TestParameterObject : public ParameterObject
	{
	protected:
		bool m_boolValue;
		int m_intValue;		
		double m_doubleValue;
		int m_enumValue;
		int m_enumValue2;
		std::string m_strValue;
		double m_vec3Value[3];

	public:
		static int MY_BOOL_PARAMETER;
		static int MY_INT_PARAMETER;
		static int MY_DOUBLE_PARAMETER;
		static int MY_ENUM_PARAMETER;
		static int MY_ENUM_PARAMETER2;
		static int MY_STRING_PARAMETER;
		static int MY_VEC3_PARAMETER;

		static int MY_ENUM_VALUE1;
		static int MY_ENUM_VALUE2;
		static int MY_ENUM2_VALUE1;
		static int MY_ENUM2_VALUE2;
		
		TestParameterObject() { initParameters();  };
		~TestParameterObject() {};

		virtual void initParameters();
		
		double getDoubleValue() { return m_doubleValue; }
		void setDoubleValue(double val) { m_doubleValue = val; }

		double getIntValue() { return m_intValue; }
		void setIntValue(int val) { m_intValue = val; }

		int getEnumValue2() const { return m_enumValue2; }
	};
}

#endif