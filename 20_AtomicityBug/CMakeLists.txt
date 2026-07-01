
set(target 20_AtomicityBug)

add_executable(${target})
target_sources(${target} PRIVATE
    AtomicityBug.cpp
)