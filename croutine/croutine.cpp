#include "croutine.h"

namespace autodrivex {
namespace croutine {

thread_local CRoutine *CRoutine::current_routine_ = nullptr;
thread_local char *CRoutine::main_stack_ = nullptr;

void CRoutineEntry(void *arg) {
  CRoutine *r = static_cast<CRoutine *>(arg);
  r->Run();
  r->Yield(RoutineState::FINISHED);
}

CRoutine::CRoutine(const RoutineFunc &func) : func_(func) {
    // 创建协程的上下文
    context_ = std::make_shared<RoutineContext>();
    MakeContext(CRoutineEntry, this, context_.get());
    state_ = RoutineState::READY;
}

CRoutine::~CRoutine() { context_ = nullptr; }

inline void CRoutine::Yield() {
    std::cout << "执行 Yield() " << std::endl;
    SwapContext(GetCurrentRoutine()->GetStack(), GetMainStack());
}

inline void CRoutine::Yield(const RoutineState &state) {
  auto routine = GetCurrentRoutine();
  routine->set_state(state);
  SwapContext(GetCurrentRoutine()->GetStack(), GetMainStack());
}

RoutineState CRoutine::Resume() {
  if (state_ != RoutineState::READY) {
    std::cout << "Invalid Routine State!" << std::endl;
    return state_;
  }

  current_routine_ = this;
  SwapContext(GetMainStack(), GetStack());
  current_routine_ = nullptr;
  return state_;
}

inline void CRoutine::set_state(const RoutineState &state) { state_ = state; }

inline RoutineState CRoutine::state() const { return state_; }

inline char **CRoutine::GetStack() { return &(context_->sp); }

inline char **CRoutine::GetMainStack() { return &main_stack_; }

inline CRoutine *CRoutine::GetCurrentRoutine() { return current_routine_; }

inline void CRoutine::Run() { this->func_(); }
} // namespace croutine
} // namespace autodrivex