# GenericParameters

**GenericParameters** is a C++ header-only library to define generic parameters. A generic parameter can be defined by a pointer to a variable or by set/get-functions. Moreover, a generic parameter stores additional information like the parameter type, max/min limits, a description, etc. Such parameters are very useful, e.g., for an automatic generation of GUI elements. 

The library is used in [SPlisHSPlasH] (https://github.com/InteractiveComputerGraphics/SPlisHSPlasH) to handle all parameters of the implemented fluid simulation methods. 

**Author**: [Jan Bender](http://www.interactive-graphics.de), **License**: MIT

## Libraries using GenericParameters
* [SPlisHSPlasH] (https://github.com/InteractiveComputerGraphics/SPlisHSPlasH) - A C++ library for the physically-based simulation of fluids using Smoothed Particle Hydrodynamics 
* [PBD] (https://github.com/InteractiveComputerGraphics/PositionBasedDynamics) - A C++ library for physically-based simulation of rigid bodies, deformables, cloth and fluids using Position-Based Dynamics (Coming soon)


## Build Instructions

Since this is a header-only library, the build is only required for the tests. 

This project is based on [CMake](https://cmake.org/). Simply generate project, Makefiles, etc. using [CMake](https://cmake.org/) and compile the project with the compiler of your choice. The code was tested with the following configurations:
- Windows 10 64-bit, CMake 3.7, Visual Studio 2015 & 2017
- Debian 8 64-bit, CMake 3.7, GCC 4.9.2.

## Usage
Creating a generic parameter for an integer value by providing the pointer of an integer variable:
```c++
m_intValue = 3;
MY_INT_PARAMETER = createNumericParameter("intParam", "Int param", &m_intValue);
setGroup(MY_INT_PARAMETER, "ParameterGroup");
setDescription(MY_INT_PARAMETER, "Help text");

// Set min and max values
IntParameter* intParam = static_cast<IntParameter*>(getParameter(MY_INT_PARAMETER));
intParam->setMinValue(2);
intParam->setMaxValue(4);
```
The function createNumericParameter returns an integer id of the parameter which can be used to set/get values or to get information about the parameter.
The value of a generic parameter can be set/get by the unified functions getValue/setValue:
```c++
getValue<int>(TestParameterObject::MY_INT_PARAMETER);
setValue<int>(TestParameterObject::MY_INT_PARAMETER, -5);
```
Moreover, you can query the type of any parameter:
```c++
if (getType(TestParameterObject::MY_INT_PARAMETER) == ParameterBase::INT32)
```

In the following an example for an enum parameter is given:
```c++
m_enumValue = 1;
MY_ENUM_PARAMETER = createEnumParameter("enumParam", "Enum param", &m_enumValue);
EnumParameter* enumParam = static_cast<EnumParameter*>(getParameter(MY_ENUM_PARAMETER));
enumParam->addEnumValue("enum1", MY_ENUM_VALUE1);
enumParam->addEnumValue("enum2", MY_ENUM_VALUE2);
enumParam->setGroup("EnumGroup");
enumParam->setDescription("This is an enum.");
```	
Here, the integers MY_ENUM_VALUE1 and MY_ENUM_VALUE2 are set in the function addEnumValue() defining an id for the corresponding enum value.

Another example which uses get/set callback functions instead of a pointer to a variable is given here:
```c++
// header
double getDoubleValue() { return m_doubleValue; }
void setDoubleValue(double val) { m_doubleValue = val; }
```
```c++
// implementation
setDoubleValue(3.123);
ParameterBase::GetFunc<double> getFct = std::bind(&TestParameterObject::getDoubleValue, this);
ParameterBase::SetFunc<double> setFct = std::bind(&TestParameterObject::setDoubleValue, this, std::placeholders::_1);
MY_DOUBLE_PARAMETER = createNumericParameter<double>("doubleParam", "Double param", getFct, setFct);
setGroup(MY_DOUBLE_PARAMETER, "ParameterGroup");
setDescription(MY_DOUBLE_PARAMETER, "Help text");
DoubleParameter* doubleParam = static_cast<DoubleParameter*>(getParameter(MY_DOUBLE_PARAMETER));
doubleParam->setMinValue(0.1);
doubleParam->setMaxValue(0.9);
```	