cmake_minimum_required(VERSION 3.30)
project(QSearch LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(target QSearch)
qt_add_executable(${target}
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    searchcontroller.h searchcontroller.cpp
    filescontroller.h filescontroller.cpp
)

target_link_libraries(${target}
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS ${target}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${target}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
