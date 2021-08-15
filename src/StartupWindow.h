#ifndef __STARTUPWINDOW_H__
#define __STARTUPWINDOW_H__

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <string>

//启动窗口，选择分区
//自动加载上次设定的分区勾选上
//构造函数传入保存已勾选分区的字符串
class StartupWindow
{
public:
	//build window
	StartupWindow(std::string &selected_partition);

public:
	//阻塞直到窗口关闭(nana::exec)
	void Exec();

private:
	//扫描存在的分区
	void __ScanAvaliablePartition();
	//尝试读取配置文件并勾选
	void __TryReloadSelection();
	//按钮按下回调
	//按下开始按钮后，更新“选定的字符串”并写出“上次设定文件”
	void __StartButtonCallback();

private:
	//存在的盘符字符串
	std::string m_strAvaliablePartition;
	//选定的字符串
	std::string &m_rstrSelectedPartition;
	//gui
	nana::form m_formWindow;
	nana::listbox m_lstbPartitionSelector;
	nana::button m_btnStart;
};

#endif // __STARTUPWINDOW_H__