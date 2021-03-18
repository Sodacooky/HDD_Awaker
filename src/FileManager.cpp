#include "FileManager.h"

FileManager::FileManager(char partition) {
	m_chPartition = partition;
	__GenerateFilename();
}

FileManager::~FileManager() {
	std::fstream file(m_strFilename);
	if (file.is_open()) {
		file.clear();
		file.close();
	}
}

bool FileManager::IsPartitionExist(char part_char) {
	//判断分区是否合法输入
	if (isalpha(part_char) == 0) {
		return false;
	}
	//制作搜索参数
	std::string path;
	path.push_back(part_char);
	path += ":/*";
	//搜索
	bool ret = false;
	_finddata_t find_data;
	auto find_handle = _findfirst(path.c_str(), &find_data);
	if (find_handle != -1) {
		ret = true;//有目录
	}
	else {
		ret = false;
	}
	_findclose(find_handle);
	return ret;
}

bool FileManager::TryWrite() {
	std::ofstream file(m_strFilename);
	if (!file.is_open()) {
		return false;
	}
	file << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << std::endl;
	file.close();
	return true;
}

void FileManager::__GenerateFilename() {
	m_strFilename = ":/HDD_Awaker";
	m_strFilename.insert(m_strFilename.begin(), m_chPartition);
	m_strFilename.append(".cache");
}