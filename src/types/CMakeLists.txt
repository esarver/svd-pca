set(
  sources
  float16.cpp
)

set(
  headers
  float16.hpp
)

add_library(types
    ${sources}
    ${headers}
)

target_include_directories(types PUBLIC . ../types/)
