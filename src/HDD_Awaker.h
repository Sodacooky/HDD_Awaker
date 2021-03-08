#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "CmdlineParser.h"
#include "FileManager.h"
#include "Timer.h"
#include "DiskSelectWindow.h"

/*
 * 程序运行的一些设置
 */
struct ExecutionOption {
	//周期（秒
	unsigned int unPeriod;
	//盘符
	char chPartition;
	//程序结束是否清理文件
	bool bIsRemoveAtQuit;
};

// application
class Awaker {
public:
	// in main
	int Main(int argc, char* argv[]);

	// gui testing main
	int TestMain();

private:
	//打印状态的线程
	void __PrintStateThreadFunc();

	//根据参数填充配置
	ExecutionOption __CmdblocksParse(int argc, char* argv[]);

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