FILE (GLOB_RECURSE project_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

message("Project lib is ${project_LIB}")

SET (project_LIBS
     moomin-lib
     ${GLFW_LIBRARIES}
     glfw
     libglew_static)

SET (project_INCLUDES
     ${GLFW_INCLUDE_PATH}
     ${GLM_INCLUDE_PATH}
     ${GLEW_INCLUDE_PATH})

SET (project_BIN ${PROJECT_NAME}-example)

ADD_EXECUTABLE(${project_BIN} ${project_SRCS})

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_LIST_DIR}/include")

include_directories(${project_INCLUDES})

TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS} ${project_LIBS})

copy_files("${MAINFOLDER}/example/shaders" "${EXECUTABLE_OUTPUT_PATH}")

SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)

INSTALL(TARGETS ${project_BIN} DESTINATION bin)
