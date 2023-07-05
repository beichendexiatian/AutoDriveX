#ifndef AUTODRIVEX_CROUTINE_CROUTINE_H_
#define AUTODRIVEX_CROUTINE_CROUTINE_H_

#include <functional>
#include <mutex>
#include <iostream>
#include <memory>
#include "context/croutine_context.h"

namespace autodrivex {
namespace croutine {

enum class RoutineState { READY, FINISHED, SLEEP, IO_WAIT, DATA_WAIT };
using RoutineFunc = std::function<void()>;

class CRoutine {
public:
    CRoutine(const RoutineFunc &func);

    virtual ~CRoutine();

    static void Yield();
    static void Yield(const RoutineState &state);

    RoutineState Resume();

    char **GetStack();

    static char **GetMainStack();

    static CRoutine *GetCurrentRoutine();

    void Run();

    RoutineState state() const;
    void set_state(const RoutineState &state);
private:

    std::shared_ptr<RoutineContext> context_;       // 当前协程上下文
    RoutineFunc func_;                              // 协程要执行的函数对象
    RoutineState state_;                            // 协程的状态
    static thread_local CRoutine *current_routine_; // 当前调度的协程
    static thread_local char *main_stack_;          // 线程主体的系统栈顶指针，起调度作用
};

} // namespace croutine
} // namespace autodrivex

#endif  // AUTODRIVEX_CROUTINE_CROUTINE_H_