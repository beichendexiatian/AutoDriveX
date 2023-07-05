cmake_minimum_required (VERSION 3.5)

project (autodrivex)

# 增加 CMake 对汇编代码的支持
ENABLE_LANGUAGE(ASM)
set(SOURCES croutine/context/croutine_context.cpp)
# 创建协程上下文动态库
add_library(croutine_context SHARED ${SOURCES} croutine/context/swap_x86_64.S)

set(SOURCES_CROUTINE croutine/croutine.cpp)
# 创建动态库
add_library(my_croutine_library SHARED ${SOURCES_CROUTINE})

target_link_libraries(my_croutine_library croutine_context)

add_executable(autodrivex mainprogram/mainprogram.cpp)

target_link_libraries(autodrivex my_croutine_library)