set(
  sources
  program_options.cpp
  convert.cpp
)

set(
  headers
  program_options.hpp
  convert.hpp
)

add_library(utility
    ${sources}
    ${headers}
)

target_include_directories(utility PUBLIC .)

target_link_libraries(utility PUBLIC stdc++fs )

