#pragma once

#include <io.h>
#include <stdio.h>

#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

/*
		负责文件读写
		文件目录字符串创建一个对象，然后一直使用这个对象来打开、写入、关闭
*/
class FileManager {
public:
	//时间计算从构造开始
	//传入分区盘符以备随时打开
	FileManager(char partition);

	//写入 自动生成的时间
	void Write();

	//测试某个分区是否存在
	//只需要输入分区字母
	static bool IsPartitionExist(char part_char);

	//获取正在操作的文件，带路径全程
	std::string GetFilename();

public:
	//累积写入字节数
	long lBytesWritten;

private:
	bool __IsFileExist();
	bool __TryOpenFile();
	bool __TryCloseFile();
	void __ClearFile();

private:
	//盘符
	char m_chPartition;
	//生成的文件名
	std::string m_strFilePath;
	//
	std::fstream m_fstrmFile;
};

class FileManegerException : public std::exception {};