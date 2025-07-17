set(NAME "Cubix.server")
project(${NAME})

file(GLOB_RECURSE SRC_SERVER "./*.cpp")
add_executable(${NAME} ${SRC_SERVER})

target_link_libraries(${NAME} PRIVATE "Cubix.shared.src-server" "Cubix.Windows.src")