#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <chrono>
#include <future>

/*
	全局日志读写（异步
*/
class Logger {
public:
	//指定写出日志的文件，若不调用就写，则只会写到屏幕上
	static void SetLogOutputFilename(const std::string& filename);
	//写入一条
	static void Add(const std::string& log_line);
private:
	//
	static void __AddAsyncFunc(const std::string& log_line);
	//生成时间戳
	static std::string __GenerateTimePrefix();
};
