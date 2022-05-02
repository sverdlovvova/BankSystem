cmake_minimum_required(VERSION 3.0)

project(BankSystem)

include_directories(include)

#set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BankSystem_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BankSystem_SOURCE_DIR}/lib)

add_subdirectory(src)

add_executable(Main main.cpp)

#target_include_directories(Main PUBLIC "/usr/bin/sqlite3")

target_link_libraries(Main sqlite3)
#set_property(TARGET Main PROPERTY PUBLIC_HEADER
#        "${BankSystem_SOURCE_DIR}/include/account.h")

INSTALL(TARGETS Main
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

#target_link_libraries(Main account)
#target_link_libraries(Main customer)
