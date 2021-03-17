#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <thread>
#include <chrono>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "FileManager.h"

/*
	主工作窗口
	构造后立刻开始工作
*/
class WorkingWindow {
public:
	WorkingWindow(const std::string& partition);
	~WorkingWindow();
private:
	void __BuildWindow();
	void __MainLoop();
	void __ReadLoop();
	void __MakeFileManager(const std::string& partition);
private:
	Fl_Window* m_pWindow;
	//打印的内容，有上限
	std::string m_strLogText;
	unsigned int m_unLogStrSizeLast;
	//写数据打工仔
	std::vector<FileManager> m_vecFileManager;
	std::future<void> m_futureReadLoop;
	bool m_bContinueRead;
};
