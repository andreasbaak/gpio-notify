cmake_minimum_required(VERSION 2.6)
project (gpio-notify)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

find_package(glib-2.0 REQUIRED)

include_directories(${glib-2.0_INCLUDE_DIRS})

add_executable(gpio-notify gpio-notify.cpp)
target_link_libraries(gpio-notify ${glib-2.0_LIBRARIES})

install(TARGETS gpio-notify
  RUNTIME DESTINATION bin
)

