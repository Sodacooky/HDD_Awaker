#pragma once

#include <stdio.h>

#include <chrono>
#include <fstream>
#include <random>
#include <sstream>
#include <string>

/*
                                �����ļ���д
                                ���ļ�Ŀ¼�ַ�������һ������Ȼ��һֱʹ������������򿪡�д�롢�ر�
*/
class FileManager {
public:
  //
  FileManager(const std::string &file_path);

  //д�� �Զ����ɵ�ʱ��������
  bool WriteLine();

  //д�� �Զ����ɵ�ʱ���ָ������
  bool WriteLine(const std::string &content);

  //ɾ���ļ�
  bool Delete();

public:
  //�ۻ�д���ֽ���
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
