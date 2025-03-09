# Link main file to executable namee
add_executable(${projectName} leo_user_link.cpp)
# Examples
# add_executable(counter_tester main_counter_tester.cpp)
# add_executable(testcase_counter main_testcase_counter.cpp)

# Add required libraries and include directories
target_include_directories(${projectName} PRIVATE "." "include" $ENV{CADMIUM})
# Examples
# target_include_directories(counter_tester PRIVATE "." "include" $ENV{CADMIUM})
# target_include_directories(testcase_counter PRIVATE "." "include" $ENV{CADMIUM})

# Set c++ standard
target_compile_options(${projectName} PUBLIC -std=gnu++2b)
# Examples
# target_compile_options(counter_tester PUBLIC -std=gnu++2b)
# target_compile_options(testcase_counter PUBLIC -std=gnu++2b)
