#include "Logger.h"

std::string g_strLogFilename = "null";
std::future<void> g_futureLastTask;

void Logger::SetLogOutputFilename(const std::string& filename) {
	g_strLogFilename = filename;
}

void Logger::Add(const std::string& log_line) {
	if (g_futureLastTask.valid()) g_futureLastTask.wait();
	g_futureLastTask = std::async(Logger::__AddAsyncFunc, log_line);
}

void Logger::__AddAsyncFunc(const std::string& log_line) {
	std::string printContent = __GenerateTimePrefix() + " : " + log_line;
	if (g_strLogFilename == "null") {
		std::cerr << printContent << std::endl;
	}
	else {
		std::ofstream file(g_strLogFilename, std::ios::app);
		if (file.is_open()) {
			file << printContent << std::endl;
			file.close();
		}
	}
}

std::string Logger::__GenerateTimePrefix() {
	auto time_timet = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm* time_tm = localtime(&time_timet);
	if (time_tm == nullptr) {
		return "nulltime";
	}
	char buff[32];
	std::strftime(buff, 32, "%T", time_tm);
	return std::string(buff);
}