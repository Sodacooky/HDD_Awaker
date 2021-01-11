#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>

/*
 * 定时触发器
 * period callback trigger
 * callback: void func(void);
 */
class Timer {
public:
  Timer(std::function<void(void)> callback, unsigned int period);

  //开始运行
  void Run();

  //等待一次循环然后退出循环
  void Quit();

private:
  void __ThreadFunc();

private:
  std::function<void(void)> m_funcCallback;
  std::thread *m_pthread;
  std::atomic<bool> m_atm_bContinue;
  unsigned int m_unSecondSleep;
};