#find_package(SQLite3)

#include_directories(${SQLite3_INCLUDE_FIRECTORIES})
add_library(account SHARED account.cpp)
add_library(customer SHARED customer.cpp)
add_library(administrator SHARED administrator.cpp)
add_library(bank SHARED bank.cpp)

#target_link_libraries(customer SQLite3)
#set(LIB_DIR_LOCATION "/usr/share/libsqlite3-deb")
#find_library(SQLite3 NAMES libsqlite3-dev PATHS ${LIB_DIR_LOCATION})

install(TARGETS account customer bank administrator
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
