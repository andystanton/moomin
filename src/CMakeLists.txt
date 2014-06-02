FILE (GLOB_RECURSE project_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

SET (project_LIBS
     ${GLFW_LIBRARIES}
     glfw
     libglew_static)

SET (project_INCLUDES
     ${GLFW_INCLUDE_PATH}
     ${GLEW_INCLUDE_PATH})

SET (project_BIN ${PROJECT_NAME})

#message("input sources")
# add test sources to global variable so they can be linked with test sources
foreach(sourceFile ${project_SRCS})
    if(${sourceFile} STREQUAL ${MAINFOLDER}/src/main.cpp)
    else()
        #message(${sourceFile})
        set(ALL_SRCS ${ALL_SRCS} ${sourceFile} CACHE INTERNAL "description")
    endif()
endforeach()

ADD_EXECUTABLE(${project_BIN} ${project_SRCS})

include_directories(${project_INCLUDES})

TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS} ${project_LIBS})

copy_files("${MAINFOLDER}/src/shaders" "${EXECUTABLE_OUTPUT_PATH}")

SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)

INSTALL(TARGETS ${project_BIN} DESTINATION bin)
