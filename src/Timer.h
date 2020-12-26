#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>

/*
        定时触发器
        callback trigger
*/
class Timer {
public:
  Timer(std::function<void(void)> callback);

  //设置触发周期，设置会在当前次等待结束后生效
  //要求是1-16s，不在范围内不会产生改变
  //默认是4s
  void SetPeriod(unsigned int seconds);

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
  std::atomic<unsigned int> m_atm_unSecondSleep;
};