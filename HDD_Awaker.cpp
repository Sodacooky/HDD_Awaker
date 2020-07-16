#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <random>
#include <stdio.h>

using namespace std;

bool g_bRunning = false;
string g_strPath;

void CycleWriteThread(fstream& file)
{
	if (!file.is_open())
	{
		throw "文件并未打开";
	}

	default_random_engine random_engine;

	while (g_bRunning)
	{
		file.seekp(0, fstream::_Seekbeg);
		file << random_engine() << endl;
		file.flush();

		this_thread::sleep_for(chrono::duration<int>(16));
	}
}

void CreateFile(fstream& file)
{
	ofstream ofile(g_strPath + "/HDD_Awaker_File.txt");
	ofile.close();

	if (file.is_open())
	{
		file.close();
	}

	file.open(g_strPath + "/HDD_Awaker_File.txt");
	if (!file.is_open())
	{
		throw "文件打开失败";
	}
}

void CloseAndRemoveFile(fstream& file)
{
	if (file.is_open())
	{
		file.close();
	}
	remove((g_strPath + "/HDD_Awaker_File.txt").c_str());
}

bool IsDiskNameAvaliable(string input)
{
	if (input.size() != 1)
	{
		return false;
	}

	if (input[0] < 'A' || input[0] > 'z')
	{
		return false;
	}

	return true;
}

int main()
{
	while (true)
	{
		string input;
		cout << "输入驱动器号(如c D a): ";
		cin >> input;
		cin.ignore();
		if (IsDiskNameAvaliable(input))
		{
			g_strPath = input + ":";
			break;
		}
		else
		{
			cout << "错误的输入" << endl;
		}
	}

	fstream file;
	CreateFile(file);

	g_bRunning = true;
	thread thr(&CycleWriteThread, ref(file));

	cout << "按下回车停止..." << endl;
	cin.get();
	cout << "正在停止..." << endl;
	g_bRunning = false;
	thr.join();

	CloseAndRemoveFile(file);

	return 0;
}
