#pragma once

#include <io.h>

#include <fstream>
#include <string>
#include <chrono>

/*
	用于对硬盘进行读取
	附带检测分区功能
*/
class FileManager {
public:
	//构造时指定分区
	FileManager(char partition);

	//析构时清空文件
	~FileManager();

	//测试某个分区是否存在
	//只需要输入分区字母
	static bool IsPartitionExist(char part_char);

	//尝试向分区的文件写入数据
	//写入失败返回false
	bool TryWrite();

private:
	//生成文件名
	void __GenerateFilename();
private:
	//盘符
	char m_chPartition;
	//文件名
	std::string m_strFilename;
};