#pragma once

/*
				程序运行的一些设置枚举
*/
struct ExecutionOption
{
//周期（秒
	unsigned int unPeriod;
	//盘符
	char chPartition;
	//程序结束是否清理文件
	bool bIsRemoveAtQuit;
};