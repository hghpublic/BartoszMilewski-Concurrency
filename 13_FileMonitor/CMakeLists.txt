
set(target 13_FileMonitor)

add_executable(${target})
target_sources(${target} PRIVATE
    FileMonitor.cpp
)