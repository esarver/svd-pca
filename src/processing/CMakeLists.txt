set(
  sources
  svd.cpp
)

set(
  headers
  svd.hpp
)

add_library(processing
    ${sources}
    ${headers}
)

target_link_libraries(processing PRIVATE types)
target_include_directories(processing PUBLIC
    .
    ${CMAKE_SOURCE_DIR}/src/types
    ${CMAKE_SOURCE_DIR}/vendor/eigen-git-mirror
    )

