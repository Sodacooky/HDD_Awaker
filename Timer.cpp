#include "Timer.h"

Timer::Timer(std::function<void(void)> callback) {
  m_bContinue = false;
  m_unSecondSleep = 4;
  m_funcCallback = callback;
}

void Timer::SetPeriod(unsigned int seconds) { m_unSecondSleep = seconds; }

void Timer::Run() {
  m_bContinue = true;
  m_pthread = new std::thread(&Timer::__ThreadFunc, this);
}

void Timer::Quit() {
  m_bContinue = false;
  m_pthread->join();
  delete m_pthread;
}

void Timer::__ThreadFunc() {
  while (m_bContinue) {
    std::this_thread::sleep_for(std::chrono::seconds(m_unSecondSleep));
    m_funcCallback();
  }
}