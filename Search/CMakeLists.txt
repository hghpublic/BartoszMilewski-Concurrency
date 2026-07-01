
set(target Search)

add_executable(${target} WIN32)
target_sources(${target} PRIVATE
    Main.cpp
    
    Ctrl.cpp
    Ctrl.h
    
    Model.cpp
    Model.h
    
    View.cpp
    View.h
)
add_subdirectory(Win)
# target_link_libraries(${target} PRIVATE user32 gdi32)
target_compile_definitions(${target} PRIVATE UNICODE _UNICODE)