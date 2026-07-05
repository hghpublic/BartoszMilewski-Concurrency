cmake_minimum_required(VERSION 3.19)
project(hello-vcpkg LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS dependencies"     "fmt"
  ])

qt_standard_project_setup()

set(target hello-vcpkg)
qt_add_executable(${target}
    main.cpp
    # vcpkg.json
)

target_link_libraries(hello-vcpkg PRIVATE Qt6::dependencies" Qt6::    "fmt"
  ])

target_link_libraries(${target}
    PRIVATE
        Qt::Core
)

install(TARGETS ${target}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
