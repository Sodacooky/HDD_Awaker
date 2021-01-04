#pragma once

#include <io.h>
#include <stdio.h>

#include <chrono>
#include <fstream>
#include <random>
#include <sstream>
#include <string>

/*
				负责文件读写
				用文件目录字符串创建一个对象，然后一直使用这个对象来打开、写入、关闭
*/
class FileManager
{
public:
	//时间计算从构造开始
	//传入文件路径以备随时打开
	FileManager(const std::string& file_path);

	//写入 自动生成的时间和随机数
	void WriteRandomLine();

	//写入 自动生成的时间和指定内容
	void WriteTextLine(const std::string& content);

	//删除文件
	bool Delete();

	//测试某个分区是否存在
	//只需要输入分区字母
	static bool IsPartitionExist(char part_char);

	//获取正在操作的文件，带路径全程
	std::string GetFilename();

public:
	//累积写入字节数
	long lBytesWritten;

private:
	bool __TestIfFileExist();
	bool __TryOpenFile();
	bool __TryCloseFile();

	std::string __TimePrefixGenerate();

private:
	//
	std::string m_strFilePath;
	//
	std::default_random_engine m_randEngine;
	//
	std::fstream m_fstrmFile;
	//
	std::chrono::system_clock::time_point m_tpStartTime;
};
