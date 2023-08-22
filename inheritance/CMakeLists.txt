cmake_minimum_required(VERSION 3.1)

# Solution
project( inheritance )

# Application
add_executable(${PROJECT_NAME} shape.c rect.c main.c)
target_link_libraries(${PROJECT_NAME} )
