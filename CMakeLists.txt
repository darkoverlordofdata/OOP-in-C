cmake_minimum_required( VERSION 3.1 )

# Solution
project( OOP-in-C  VERSION 0.0.1 )

# Options
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

#
# enable features
#
include ( CMakeToolsHelpers OPTIONAL )

# Projects
add_subdirectory( encapsulation )
add_subdirectory( inheritance )
add_subdirectory( polymorphism )
