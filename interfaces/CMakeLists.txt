find_package(pybind11 REQUIRED)

pybind11_add_module(controller_py 
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/interface.cpp
)

set_target_properties(controller_py 
    PROPERTIES
        OUTPUT_NAME controller_py
)

target_include_directories(controller_py
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(controller_py
    PRIVATE
        pid_controller
)

install(TARGETS controller_py)
