#include "WorkingWindow.h"

WorkingWindow::WorkingWindow(const std::string& partition) {
	__BuildWindow();
	__MakeFileManager(partition);
	__MainLoop();
}

WorkingWindow::~WorkingWindow() {
	delete m_pWindow;//auto gc
}

void WorkingWindow::__MainLoop() {
	m_bContinueRead = true;
	m_futureReadLoop = std::async(&WorkingWindow::__ReadLoop, this);
	while (Fl::wait()) {
	}
	m_bContinueRead = false;
	m_futureReadLoop.wait();
}

void WorkingWindow::__ReadLoop() {
	auto lastWorkTime = std::chrono::system_clock::now();
	auto nowTime = lastWorkTime;
	while (m_bContinueRead) {
		//sleep直到到点
		nowTime = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> deltaTime = nowTime - lastWorkTime;
		if (deltaTime.count() < 8000) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			continue;
		}
		else {
			lastWorkTime = nowTime;
		}
		//遍历做
		for (auto& fm : m_vecFileManager) {
			fm.TryRead();
		}
	}
}

void WorkingWindow::__MakeFileManager(const std::string& partition) {
	for (auto chPartition : partition) {
		if (FileManager::IsPartitionExist(chPartition)) {
			m_vecFileManager.emplace_back(chPartition);
		}
	}
}

void WorkingWindow::__BuildWindow() {
	m_pWindow = new Fl_Window(320, 100, u8"运行中 HDD_Awaker");
	new Fl_Box(0, 0, m_pWindow->w(), 32, u8"运行中，点击窗口右上角关闭即可退出。");
	new Fl_Box(0, 32, m_pWindow->w(), 32, u8"GUI Library:");
	new Fl_Box(0, 64, m_pWindow->w(), 32, u8"@FLTK");
	m_pWindow->show();
}