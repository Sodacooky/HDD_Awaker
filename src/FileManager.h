#pragma once

#include <io.h>

#include <fstream>
#include <string>
#include <random>

/*
	用于对硬盘进行读取
	附带检测分区功能
*/
class FileManager {
public:
	//构造时指定分区
	FileManager(char partition);

	//测试某个分区是否存在
	//只需要输入分区字母
	static bool IsPartitionExist(char part_char);

	//尝试读取一次不存在的文件以激活硬盘
	void TryRead();

private:
	//生成随机的文件名
	std::string __GenerateRandomFilename();

private:
	//盘符
	char m_chPartition;
};