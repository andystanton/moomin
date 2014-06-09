FILE (GLOB_RECURSE project_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)


SET (project_LIB ${PROJECT_NAME}-lib CACHE INTERNAL "Moomin library target name")

message("project_lib is ${project_LIB}")

#message("input sources")
# add test sources to global variable so they can be linked with test sources
foreach(sourceFile ${project_SRCS})
    set(ALL_SRCS ${ALL_SRCS} ${sourceFile} CACHE INTERNAL "All Moomin Library Sources")
endforeach()

ADD_LIBRARY(${project_LIB} ${project_SRCS})

include_directories(${project_INCLUDES})

TARGET_LINK_LIBRARIES(${project_LIB} ${project_LIBS})

SET_TARGET_PROPERTIES(${project_LIB} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_LIB} CLEAN_DIRECT_OUTPUT 1)

INSTALL(TARGETS ${project_LIB} DESTINATION bin)
