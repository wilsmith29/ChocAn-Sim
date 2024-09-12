# Add test executable
add_executable(ChocAnTests
    person_test.cpp
    person_vec_test.cpp
    ser_pro_test.cpp
    service_test.cpp
    service_vec_test.cpp
    utilities_test.cpp
    # Add all your test source files here
)

# Link with Google Test and your project library
target_link_libraries(ChocAnTests gtest gtest_main ChocAnLib)

# Optionally, if you want to run tests automatically after building
include(GoogleTest)
gtest_discover_tests(ChocAnTests)