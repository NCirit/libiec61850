cmake_minimum_required(VERSION 3.12)

cmake_policy(SET CMP0078 NEW)

if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.14.0")
    cmake_policy(SET CMP0086 NEW)
endif()

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(Python COMPONENTS Interpreter Development REQUIRED)

include_directories(${Python_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${Python_LIBRARY_DIRS})

set(CMAKE_SWIG_FLAGS "")
set(BUILD_PYTHON_BINDINGS ON)
set_property(SOURCE iec61850.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE iec61850.i PROPERTY SWIG_MODULE_NAME pyiec61850)

set(LIBS iec61850-shared)

swig_add_library(pyiec61850
    LANGUAGE python
    SOURCES iec61850.i
)

swig_link_libraries(pyiec61850 ${LIBS})

if(HEADER_PATH_HINT)
set_property(TARGET pyiec61850 PROPERTY SWIG_INCLUDE_DIRECTORIES ${HEADER_PATH_HINT})
target_include_directories(pyiec61850 PRIVATE ${HEADER_PATH_HINT})
endif()

if(LINK_PATH_HINT)
target_link_directories(pyiec61850 PRIVATE ${LINK_PATH_HINT})
endif()

# Finding python modules install path
execute_process(
	COMMAND ${Python_EXECUTABLE} -c
	"from sysconfig import get_path; import sys; sys.stdout.write(get_path('platlib'))"
	OUTPUT_VARIABLE PYTHON_SITE_DIR
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pyiec61850.py DESTINATION ${PYTHON_SITE_DIR})
install(TARGETS pyiec61850 LIBRARY DESTINATION ${PYTHON_SITE_DIR})

add_test(test_pyiec61850 ${Python_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test_pyiec61850.py)
