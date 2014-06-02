FILE (GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
SET (test_LIBS
     gtest
     gtest_main
     gmock
     gmock_main
     ${GLFW_LIBRARIES}
     glfw
     libglew_static)

SET (test_INCLUDES
     ${GMOCK_INCLUDE_PATH}
     ${GTEST_INCLUDE_PATH}
     ${BANDIT_INCLUDE_PATH}
     ${GLFW_INCLUDE_PATH}
     ${GLEW_INCLUDE_PATH})

SET (test_BIN ${PROJECT_NAME}-unittests)

include_directories(${test_INCLUDES})

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_LIST_DIR}/include")

set_source_files_properties("${CMAKE_CURRENT_LIST_DIR}/spec/util/FloatingPointHelper.spec.cpp" PROPERTIES COMPILE_FLAGS "-Wno-float-equal")

# message("Output sources")
# foreach(source ${ALL_SRCS})
#     message(${source})
# endforeach()

ADD_EXECUTABLE(${test_BIN} ${test_SRCS} ${ALL_SRCS})
TARGET_LINK_LIBRARIES(${test_BIN} ${test_LIBS} ${test_LIBS})

ADD_TEST(${test_BIN} ${EXECUTABLE_OUTPUT_PATH}/${test_BIN} --reporter=spec)
