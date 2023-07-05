#ifndef CROUTINE_ROUTINE_CONTEXT_H_
#define CROUTINE_ROUTINE_CONTEXT_H_

#include <cstdlib>
#include <iostream>

// extern "C" {
// extern void ctx_swap(void**, void**) asm("ctx_swap");
// };

namespace autodrivex {
namespace croutine {

extern "C" void ctx_swap(void**, void**);

constexpr size_t STACK_SIZE = 2 * 1024 * 1024;
constexpr size_t REGISTERS_SIZE = 56;

typedef void (*func)(void*);

struct RoutineContext {
  char stack[STACK_SIZE]; // 协程栈空间大小 2MB
  char* sp = nullptr;     // 栈顶指针
};

/**
 * @brief 设置 ctx 中设置协程的入口函数，并在 ctx 中设置协程的指针
 * 
 * @param f1  协程的入口函数
 * @param arg 指向协程自己的指针（指向 CRoutine 对象）
 * @param ctx 当前协程的上下文指针，上下文最后都存在 ctx 指向的空间里
 */
void MakeContext(const func& f1, const void* arg, RoutineContext* ctx);

/**
 * @brief 切换协程的上下文
 * @param src_sp  用来存储当前要被切换出去的上下文的栈顶指针
 * @param dest_sp 即将切换进来要执行的上下文的栈顶指针
 */
inline void SwapContext(char** src_sp, char** dest_sp) {
  ctx_swap(reinterpret_cast<void**>(src_sp), reinterpret_cast<void**>(dest_sp));
}


} // namespace croutine
} // namespace autodrivex

#endif  // CROUTINE_ROUTINE_CONTEXT_H_