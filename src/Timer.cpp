#include "Timer.h"

Timer::Timer(std::function<void(void)> callback, unsigned int period)
{
	m_atm_bContinue = false;
	m_funcCallback = callback;
	m_unSecondSleep = period;
}

void Timer::Run()
{
	m_atm_bContinue = true;
	m_pthread = new std::thread(&Timer::__ThreadFunc, this);
}

void Timer::Quit()
{
	m_atm_bContinue = false;
	//阻塞等待
	m_pthread->join();
	delete m_pthread;
}

void Timer::__ThreadFunc()
{
	while (m_atm_bContinue)
	{
		std::this_thread::sleep_for(std::chrono::seconds(m_unSecondSleep));
		m_funcCallback();
	}
}