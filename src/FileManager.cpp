#include "FileManager.h"

FileManager::FileManager(char partition) {
	lBytesWritten = 0;
	m_chPartition = partition;
	m_strFilePath = partition + ":/HDD_Awaker.txt";
	//创建文件
	__TryOpenFile();
	__ClearFile();
	__TryCloseFile();
}

void FileManager::Write() {
	if (!__IsFileExist() && !IsPartitionExist(m_chPartition)) {
		//文件不存在是因为分区不存在
		throw FileManegerException();
	}
	__TryOpenFile();
	std::string tmpContent = std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	m_fstrmFile << tmpContent;
	lBytesWritten+=tmpContent.size();
	__TryCloseFile();
}

bool FileManager::IsPartitionExist(char part_char) {
	std::string path;
	path.push_back(part_char);

	if (path[0] < 'A' || path[0] > 'z') {
		return false;
	}

	path += ":/*";

	bool ret = false;
	_finddata_t find_data;
	auto find_handle = _findfirst(path.c_str(), &find_data);
	if (find_handle != -1) {
		ret = true;
	}
	else {
		ret = false;
	}
	_findclose(find_handle);
	return ret;
}

std::string FileManager::GetFilename() {
	return m_strFilePath;
}

bool FileManager::__IsFileExist() {
// 不用成员变量来操作
	std::ifstream file(m_strFilePath);
	if (file.is_open()) {
		file.close();
		return true;
	}
	else {
		return false;
	}
}

bool FileManager::__TryOpenFile() {
	m_fstrmFile.open(m_strFilePath, std::ios_base::app);
	if (!m_fstrmFile.is_open()) {
		return false;
	}
	else {
		return true;
	}
}

bool FileManager::__TryCloseFile() {
	if (m_fstrmFile.is_open()) {
		m_fstrmFile.close();
		return true;
	}
	else {
		return false;
	}
}

void FileManager::__ClearFile() {
	m_fstrmFile.clear();
}