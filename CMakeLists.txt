cmake_minimum_required(VERSION 3.11)
project(toralize VERSION 1.0)
add_library(${PROJECT_NAME} SHARED src/${PROJECT_NAME}.c)
include(GNUInstallDirs)
target_compile_options(${PROJECT_NAME} PRIVATE 
    -fPIC          
    -Wall          
    -Wextra        
)

find_library(DL_LIBRARY dl REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${DL_LIBRARY})
target_compile_definitions(${PROJECT_NAME} PRIVATE _GNU_SOURCE)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER src/${PROJECT_NAME}.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # usr/local/include
)
install(PROGRAMS install.sh
    DESTINATION ${CMAKE_INSTALL_BINDIR} # usr/local/bin
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                GROUP_READ GROUP_EXECUTE
                WORLD_READ WORLD_EXECUTE
    RENAME toralize
)