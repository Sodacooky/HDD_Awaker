#include "RunningWindow.h"

#include <filesystem>
#include <fstream>
#include <functional>
#include <sstream>
#include <thread>

void RunningWindow::__RunningThread()
{
	while (m_bKeepRunning)
	{
		//write
		auto to_write = std::chrono::system_clock::now().time_since_epoch().count();
		for (auto &partition : m_rstrSelectedPartition)
		{
			if (__IsPartitionExist(partition))
			{
				if (__TryWriteData(partition, &to_write, sizeof(to_write)))
				{
					m_unWrittenBytes += sizeof(to_write);
				}
			}
		}
		//update windows info
		__UpdateLabel();
		//sleep
		std::this_thread::sleep_for(std::chrono::seconds(8));
	}
}

bool RunningWindow::__IsPartitionExist(char partition)
{
	std::string path = ":/";
	path.insert(path.begin(), partition);
	std::filesystem::directory_entry entry(path);
	return entry.exists();
}

bool RunningWindow::__TryWriteData(char partition, const void *to_write, size_t to_write_size)
{
	std::string filename = ":/HDD_Aaker_File.txt";
	filename.insert(filename.begin(), partition);
	std::ofstream file(filename);
	if (file)
	{
		file.write((char *)to_write, to_write_size);
		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

void RunningWindow::__UpdateLabel()
{
	//partition info
	std::stringstream partition_stream;
	partition_stream << u8"运行于 ";
	for (auto partition : m_rstrSelectedPartition)
	{
		partition_stream << partition << u8": ";
	}
	m_lbPartitionInfo.caption(partition_stream.str());

	//running state
	auto now_time = std::chrono::system_clock::now();
	auto delta_seconds = std::chrono::duration_cast<std::chrono::seconds>(now_time - m_tpStartTime)
							 .count();
	std::stringstream state_stream;
	state_stream << u8"已经运行: " << delta_seconds << u8" 秒" << std::endl;
	state_stream << u8"总共写入: " << m_unWrittenBytes << u8" 字节";
	m_lbRunningState.caption(state_stream.str());
}

RunningWindow::RunningWindow(const std::string &selected_partition)
	: m_rstrSelectedPartition(selected_partition),
	  m_formWindow(nana::API::make_center(300, 120), nana::appear::decorate<nana::appear::minimize>()),
	  m_lbPartitionInfo(m_formWindow, nana::rectangle(32, 10, 280, 32)),
	  m_lbRunningState(m_formWindow, nana::rectangle(32, 48, 280, 64))
{
	//set widget
	m_formWindow.caption(u8"HDD_Awaker");
	m_formWindow.show();
	m_lbRunningState.caption(u8"启动中...");
	//
	m_unWrittenBytes = 0;
	m_tpStartTime = std::chrono::system_clock::now();
}

void RunningWindow::Exec()
{
	m_bKeepRunning = true;
	std::thread write_thread(std::bind(&RunningWindow::__RunningThread, this));
	nana::exec();
	//exited
	m_bKeepRunning = false;
	if (write_thread.joinable())
	{
		write_thread.join();
	}
}
