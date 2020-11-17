add_executable(	ParameterTest 
				ParameterTest.cpp
				TestParameterObject.h
				TestParameterObject.cpp

				CMakeLists.txt
			)

target_link_libraries(ParameterTest GenericParameters)
set_target_properties(ParameterTest PROPERTIES FOLDER "Tests")
set_target_properties(ParameterTest PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
