cmake_minimum_required(VERSION 3.10)

project(csmtp VERSION 0.0.1)

add_library(utils
	src/parser.cpp
	src/response.cpp
)
target_include_directories(utils PUBLIC src/ include/)

add_executable(smtp-server src/smtp-server.cpp)
target_link_libraries(smtp-server utils)

add_executable(smtp-client src/smtp-client.cpp)
target_link_libraries(smtp-client utils)

target_compile_options(smtp-server PUBLIC -Wall -Wextra -Werror)

