#pragma once

#include "ExecutionOption.h"
#include "FileManager.h"
#include "Timer.h"
#include <iostream>
#include <string>
#include <vector>

// application
class Awaker
{
public:
	// in main
	int Main(int argc, char* argv[]);

private:
	//打印状态的线程
	void __PrintStateThreadFunc();

	//将C语言main函数命令行转为string块
	std::vector<std::string> __CmdlineParse(int argc, char* argv[]);

	//根据参数填充配置
	ExecutionOption __CmdblocksParse(const std::vector<std::string>& blocks);

private:
	// ---> __PrintStateThreadFunc()
	Timer* m_ptimerUpdateConsole;
	// ---> m_filemanager.WriteLine()
	Timer* m_ptimerWriteData;
	//
	FileManager* m_pfmFile;
	//
	bool m_bContinue;
	//
	ExecutionOption m_eoOption;
};