set(sources
  all_tests.cpp
)

set(headers
  float16_tests.hpp
)

add_executable(types-tests
  ${sources}
  ${headers}
)

target_link_libraries(types-tests PRIVATE types gtest_main)
add_test(NAME types-tests COMMAND types-tests)
target_compile_options(types-tests
PRIVATE 
"-Wno-write-strings" # these get thrown because we are mocking argv
)
