#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>

/*
        ��ʱ��
        callback trigger
*/
class Timer {
public:
  Timer(std::function<void(void)> callback);

  //���ô������ڣ����û��ڵ�ǰ�εȴ���������Ч
  //Ҫ����1-16s�����ڷ�Χ�ڲ�������ı�
  //Ĭ����4s
  void SetPeriod(unsigned int seconds);

  //��ʼ����
  void Run();

  //�ȴ�һ��ѭ��Ȼ���˳�ѭ��
  void Quit();

private:
  void __ThreadFunc();

private:
  std::function<void(void)> m_funcCallback;
  std::thread *m_pthread;
  std::atomic<bool> m_bContinue;
  std::atomic<unsigned int> m_unSecondSleep;
};