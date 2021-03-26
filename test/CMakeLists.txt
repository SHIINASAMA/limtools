project(testApp)

add_executable(testApp test.cpp)

include_directories("../src")
target_link_libraries(testApp io)
target_link_libraries(testApp net)
target_link_libraries(testApp thread)