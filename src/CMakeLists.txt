add_library(pid_controller
       SHARED 
              pid_controller.cpp
)

target_include_directories(pid_controller
       PUBLIC
              ${PROJECT_SOURCE_DIR}/include
              ${PROJECT_SOURCE_DIR}/src
              ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pid_controller
       PUBLIC
            rg-dynamics::rg-dynamics
)

install(TARGETS pid_controller)