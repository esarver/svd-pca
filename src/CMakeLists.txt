add_subdirectory(utility)

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
)

target_link_libraries(
    ${exec_name}
    PRIVATE
    utility
)
