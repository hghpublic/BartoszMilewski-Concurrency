
set(target 16_BankDeadlock)

add_executable(${target})
target_sources(${target} PRIVATE
    BankDeadlock.cpp
)