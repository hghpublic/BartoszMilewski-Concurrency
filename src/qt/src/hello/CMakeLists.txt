cmake_minimum_required(VERSION 3.19)
project(hello LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

set(target hello)
qt_add_executable(${target}
    main.cpp
)

target_link_libraries(${target}
    PRIVATE
        Qt::Core
)

install(TARGETS ${target}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
