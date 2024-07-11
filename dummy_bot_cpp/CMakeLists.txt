cmake_minimum_required(VERSION 3.16)
project(dummy_bot_cpp)

# cmake_policy(SET CMP0135 OLD)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)


# ------- Fetch the Obelisk library ------- #
include(FetchContent)
FetchContent_Declare(
  Obelisk
  SOURCE_DIR $ENV{OBELISK_ROOT}/obelisk/cpp
)

# Lets us Get Obelisk::Core and Obelisk::Zoo
FetchContent_MakeAvailable(Obelisk)

# ------- Controller ------- #
add_executable(position_setpoint_controller src/position_setpoint_controller.cpp)
target_link_libraries(position_setpoint_controller PUBLIC Obelisk::Core Obelisk::Zoo)

# ------- Estimator ------- #
add_executable(jointencoders_passthrough_estimator src/jointencoders_passthrough_estimator.cpp)
target_link_libraries(jointencoders_passthrough_estimator PUBLIC Obelisk::Core Obelisk::Zoo)

# ------- Simulator ------- #
add_executable(obelisk_mujoco_robot src/mujoco_sim.cpp)
target_link_libraries(obelisk_mujoco_robot PUBLIC Obelisk::Core)


if(BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    set(ament_cmake_copyright_FOUND TRUE)
    set(ament_cmake_cpplint_FOUND TRUE)
    ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
    position_setpoint_controller
    DESTINATION lib/${PROJECT_NAME})

install(TARGETS
    jointencoders_passthrough_estimator
    DESTINATION lib/${PROJECT_NAME})

install(TARGETS
    obelisk_mujoco_robot
    DESTINATION lib/${PROJECT_NAME})

ament_package()
