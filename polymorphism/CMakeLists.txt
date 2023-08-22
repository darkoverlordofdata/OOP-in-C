cmake_minimum_required(VERSION 3.1)

# Solution
project( polymorphism)
include_directories ( /usr/local/include )
link_directories ( /usr/local/lib )
# Application
add_executable(${PROJECT_NAME} shape.c rect.c circle.c main.c)
target_link_libraries(${PROJECT_NAME} corefw )
