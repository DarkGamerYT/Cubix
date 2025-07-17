set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NAME "Cubix.shared.src-server")
project(${NAME})

file(GLOB_RECURSE SRC "./*.cpp")
add_library(${NAME} ${SRC})

target_link_libraries(${NAME} PRIVATE "Cubix.shared.src")