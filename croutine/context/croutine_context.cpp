#include "croutine_context.h"
#include <cstring>

namespace autodrivex {
namespace croutine {

void MakeContext(const func& f1, const void* arg, RoutineContext* ctx) {
  ctx->sp = ctx->stack + STACK_SIZE - 2 * sizeof(void *) - REGISTERS_SIZE; // 设置栈顶指针
  std::memset(ctx->sp, 0, REGISTERS_SIZE);
  char *sp = ctx->stack + STACK_SIZE - 2 * sizeof(void *);
  *reinterpret_cast<void **>(sp) = reinterpret_cast<void *>(f1);           // 设置协程的入口函数
  sp -= sizeof(void *);
  *reinterpret_cast<void **>(sp) = const_cast<void *>(arg);                // 设置协程的入口函数的参数
}

} // namespace croutine
} // namespace autodrivex