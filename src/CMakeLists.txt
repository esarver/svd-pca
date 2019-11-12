add_subdirectory(utility)
add_subdirectory(types)
add_subdirectory(processing)

set(
    exec_name
    project_two
)

set(
    sources
    main.cpp
)

add_executable(
    ${exec_name}
    ${sources}
)

target_include_directories(
    ${exec_name}
    PRIVATE
    utility
    types
    processing
)

target_link_libraries(
    ${exec_name}
    PRIVATE
    utility
    types
    processing
)

