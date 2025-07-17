set(NAME "Cubix.Linux.src")
project(${NAME})

file(GLOB_RECURSE SRC "./*.cpp")
add_library(${NAME} ${SRC})

target_link_libraries(${NAME} PRIVATE pthread)