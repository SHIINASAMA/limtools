project(testApp)

add_executable(testApp test.cpp)

include_directories("../src")
target_link_libraries(testApp limtools)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	MESSAGE(STATUS "平台: Linux ")
	MESSAGE(STATUS "增加链接库: thread")
    find_package(Threads)
    target_link_libraries(testApp ${CMAKE_THREAD_LIBS_INIT})
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "平台: Windows ")
	MESSAGE(STATUS "增加链接库: wsock32")
    target_link_libraries(testApp wsock32)
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Windows")