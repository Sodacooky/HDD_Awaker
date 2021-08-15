#ifndef __RUNNINGWINDOW_H__
#define __RUNNINGWINDOW_H__

#include <chrono>
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <stdint.h>
#include <string>

//运行时窗口，显示运行时间和写入的总数据量
//构造函数传入要工作的分区
//实际写入时仍然会检查分区的存在，若不存在则忽略不写(也不报错)
class RunningWindow
{
public:
	RunningWindow(const std::string &selected_partition);

public:
	//开始写线程，阻塞直到窗口关闭
	void Exec();

private:
	//在分离出来的线程上写
	void __RunningThread();
	//分区是否存在
	bool __IsPartitionExist(char partition);
	//成功true
	bool __TryWriteData(char partition, const void *to_write, size_t to_write_size);
	//更新窗口label
	void __UpdateLabel();

private:
	//
	const std::string &m_rstrSelectedPartition;
	//thread keep running
	bool m_bKeepRunning;
	//写入量
	uint32_t m_unWrittenBytes;
	//程序启动时间
	std::chrono::system_clock::time_point m_tpStartTime;
	//gui
	nana::form m_formWindow;
	nana::label m_lbPartitionInfo;
	nana::label m_lbRunningState;
};

#endif // __RUNNINGWINDOW_H__