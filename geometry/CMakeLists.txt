cmake_minimum_required(VERSION 3.16)
SET(CMAKE_INSTALL_RPATH "${PROJECT_SOURCE_DIR}/bin")
SET(TASK_NAME geometry)

add_compile_options(-pedantic -Werror -Wextra -fsanitize=address -fsanitize=undefined -std=c++17)

add_link_options(-pedantic -Werror -Wextra -fsanitize=address -fsanitize=undefined -std=c++17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
add_executable(${TASK_NAME} geometry.cpp tests.cpp)

add_test(${TASK_NAME} ${Testing_SOURCE_DIR}/bin/testing)

target_link_libraries(${TASK_NAME} Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

install (
        TARGETS ${TASK_NAME}
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)
