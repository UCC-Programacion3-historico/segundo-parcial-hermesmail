project(test)

add_subdirectory(lib/gtest-1.8.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(run_test
        tests.cpp
        ../src/MailManager.cpp
        ../src/email.cpp
        )
target_link_libraries(run_test gtest gtest_main gcov)