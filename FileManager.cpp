#include "FileManager.h"

FileManager::FileManager(const std::string &file_path) {
  lBytesWritten = 0;
  m_strFilePath = file_path;
  m_tpStartTime = std::chrono::system_clock::now();
  m_randEngine.seed(std::chrono::system_clock::to_time_t(m_tpStartTime));
}

bool FileManager::WriteLine() {
  std::uniform_int_distribution<int> distribution(0, 1000);
  return WriteLine(std::to_string(distribution(m_randEngine)));
}

bool FileManager::WriteLine(const std::string &content) {
  if (!__TryOpenFile()) {
    return false;
  }

  std::stringstream ss;
  ss << __TimePrefixGenerate() << "\t" << content << std::endl;

  m_fstrmFile.write(ss.str().c_str(), ss.str().size());
  lBytesWritten += ss.str().size();
  m_fstrmFile.sync();

  if (!__TryCloseFile()) {
    return false;
  }

  return true;
}

bool FileManager::Delete() {
  // 1. closed
  if (m_fstrmFile.is_open()) {
    return false;
  }

  // 2. exist
  if (__TestIfFileExist()) {
    remove(m_strFilePath.c_str());
    return true;
  }

  return false;
}

bool FileManager::__TestIfFileExist() {
  // new ifstream object
  std::ifstream file(m_strFilePath);
  if (file.is_open()) {
    file.close();
    return true;
  } else {
    return false;
  }
}

bool FileManager::__TryOpenFile() {
  m_fstrmFile.open(m_strFilePath, std::ios_base::app);
  if (!m_fstrmFile.is_open()) {
    return false;
  } else {
    return true;
  }
}

bool FileManager::__TryCloseFile() {
  if (m_fstrmFile.is_open()) {
    m_fstrmFile.close();
    return true;
  } else {
    return false;
  }
}

std::string FileManager::__TimePrefixGenerate() {
  auto now = std::chrono::system_clock::now();
  auto dura = now - m_tpStartTime;
  return std::to_string(dura.count());
}