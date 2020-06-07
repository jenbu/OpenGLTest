cmake_minimum_required(VERSION 3.0.0)
project(OpenGLUTube VERSION 0.1.0)

include(CTest)
enable_testing()

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp
	${CMAKE_SOURCE_DIR}/test/*.cpp
	${CMAKE_SOURCE_DIR}/objects/*.cpp)


message(${CMAKE_SOURCE_DIR})

# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h #CMAKE_SOURCE_DIR is the location where cmakelist.txt is located
	${CMAKE_SOURCE_DIR}/test/*.h
	${CMAKE_SOURCE_DIR}/objects/*.h)

list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/vendor/imgui/main.cpp)

find_package(OpenGL REQUIRED)

find_package (Threads)
find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})


find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

pkg_search_module(UDPCOMM REQUIRED UDPComm)
pkg_search_module(FREETYPE REQUIRED freetype2)

message(${FREETYPE_INCLUDEDIR})


#include(/usr/local/include/freetype2)

include_directories(
	src/vendor
	src/vendor/stb_image
	src/vendor/imgui
	src/OpenGL/
	src/Physics/
	src/Misc/
	src/Menu/
	src/Input/
	src/CollisionDetection/
	src/Communication/
	src/TextRendering/
	src
	test
	objects
	${FREETYPE_INCLUDEDIR}
)


add_executable(OpenGLUTube ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(OpenGLUTube ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} -ldl ${CMAKE_THREAD_LIBS_INIT} ${FREETYPE_LIBRARIES} ${UDPCOMM_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
