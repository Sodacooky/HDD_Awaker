#include "FileManager.h"

FileManager::FileManager(char partition) {
	m_chPartition = partition;
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

void FileManager::TryRead() {
	std::ifstream file(__GenerateRandomFilename());
	if (file.is_open()) file.close();
}

std::string FileManager::__GenerateRandomFilename() {
	std::default_random_engine e;
	std::uniform_int_distribution<int> d(65, 65 + 25);//范围是A-Z 65->Z

	std::string filename = ":/HDD_Awaker_";
	filename.insert(filename.begin(), m_chPartition);
	for (int i=0; i != 16; i++) {
		filename.push_back((char)d(e));
	}
	filename.append(".fakefile");

	return filename;
}