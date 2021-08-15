#include "Application.h"

#include "RunningWindow.h"
#include "StartupWindow.h"

int WinMain()
{
	Application app;
	return app.Main();
}

int Application::Main()
{
	__Startup();
	__Running();
	return 0;
}

void Application::__Startup()
{
	StartupWindow sw(m_strSelectedPartition);
	sw.Exec();
}

void Application::__Running()
{
	if (m_strSelectedPartition.size() != 0)
	{
		RunningWindow rw(m_strSelectedPartition);
		rw.Exec();
	}
}
