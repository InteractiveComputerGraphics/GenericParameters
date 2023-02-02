add_library(GenericParameters INTERFACE)

target_sources(GenericParameters INTERFACE 
	${CMAKE_CURRENT_LIST_DIR}/Parameter.h
	${CMAKE_CURRENT_LIST_DIR}/EnumParameter.h
	${CMAKE_CURRENT_LIST_DIR}/FunctionParameter.h
	${CMAKE_CURRENT_LIST_DIR}/NumericParameter.h
	${CMAKE_CURRENT_LIST_DIR}/ParameterObject.h
	${CMAKE_CURRENT_LIST_DIR}/VectorParameter.h
	)


install(DIRECTORY ./
DESTINATION include
FILES_MATCHING PATTERN "*.h")
	