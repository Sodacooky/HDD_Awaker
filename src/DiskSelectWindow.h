#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <conio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Scroll.H>
#include <FL/fl_ask.H>

#include "FileManager.h"

class DiskSelectWindow {
public:
	DiskSelectWindow();
	~DiskSelectWindow();
private:
	//构建窗口样式
	void __BuildWindow();

	//获取系统分区集合
	std::string __GetSysExistPartition();

	//生成按钮
	void __GenerateSelButton(const std::string& avaliableDisk);

	//检查是否勾选至少一个分区
	bool __ExistSelectedDiskButton();

	//列出勾选的分区
	void __ListSelectedDisk();

	//清理
	void __Cleanup();
public:
	//选择了的分区盘符集合
	std::string strSelectedDisk;
private:
	Fl_Window* m_pWindow;
	Fl_Pack* m_pPack;
	Fl_Scroll* m_pScroll;
	std::vector<Fl_Check_Button*> m_vpDiskSelButton;
	Fl_Button* m_pButtonStart;
};
