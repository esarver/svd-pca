set(sources
  all_tests.cpp
)

set(headers
    svd_tests.hpp
)

add_executable(processing-tests
  ${sources}
  ${headers}
)

target_link_libraries(processing-tests PRIVATE processing gtest_main)
add_test(NAME processing-tests COMMAND processing-tests)
target_compile_options(processing-tests
PRIVATE 
"-Wno-write-strings" # these get thrown because we are mocking argv
)
