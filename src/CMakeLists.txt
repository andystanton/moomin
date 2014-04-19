FILE (GLOB_RECURSE project_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

SET (project_LIBS ${GLFW_LIBRARIES})

if (APPLE)
   SET(project_LIBS ${project_LIBS} "-framework OpenGL")
endif()

SET (project_BIN ${PROJECT_NAME})

ADD_EXECUTABLE(${project_BIN} ${project_SRCS})

TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})
SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)

INSTALL(TARGETS ${project_BIN} DESTINATION bin)
