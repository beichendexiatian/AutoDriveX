#include <iostream>
#include "../croutine/croutine.h"
using namespace autodrivex::croutine;

void print1() {
  for (int i = 0; i < 5; i++) {
    std::cout << "CRoutine 1: " << i << std::endl;
  }
  CRoutine::Yield(RoutineState::READY);
}

void print2() {
  for (int i = 0; i < 5; i++) {
    std::cout << "CRoutine 2: " << i << std::endl;
  }
  CRoutine::Yield(RoutineState::READY);
}


int main(int argc, char** argv) {
  std::cout << "welcome to AutoDriveX" << std::endl;
  CRoutine *cr1 = new CRoutine(print1);
  CRoutine *cr2 = new CRoutine(print2);
  cr1->Resume();
  std::cout << "return to main()" << std::endl;
  cr2->Resume();
  std::cout << "return to main()" << std::endl;

  return 0;
}