cmake_minimum_required( VERSION 3.1 )

# Solution
project( encapsulation )

# Application
add_executable( ${PROJECT_NAME} shape.c main.c )
target_link_libraries( ${PROJECT_NAME} ) 
