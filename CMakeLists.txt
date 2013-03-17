project(ExtraNotes)
cmake_minimum_required(VERSION 2.6)

# set the output destination
set(EXTRANOTES_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/Builds/Linux/build/ExtraNotes.so)

# create a custom target that will run each time you type make 
add_custom_target(build_ExtraNotes ALL 
                  COMMAND ${CMAKE_MAKE_PROGRAM}
                  WORKING_DIRECTORY
                  ${CMAKE_CURRENT_SOURCE_DIR}/Builds/Linux
                  COMMENT "Building Introjucer generated Makefile")

# now create an imported static target
add_library(ExtraNotes SHARED IMPORTED)
set_target_properties(ExtraNotes PROPERTIES PREFIX "")
set_property(TARGET ExtraNotes APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ExtraNotes PROPERTIES IMPORTED_LOCATION_NOCONFIG "${EXTRANOTES_LIBRARY}")

add_dependencies(ExtraNotes build_ExtraNotes)
