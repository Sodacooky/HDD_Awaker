#include "HDD_Awaker.h"

using namespace std;

int main(int argc, char* argv[])
{
	Awaker app;
	return app.Main(argc, argv);
}

int Awaker::Main(int argc, char* argv[])
{
	//处理命令行
	try
	{
		auto blocks = __CmdlineParse(argc, argv);
		m_eoOption = __CmdblocksParse(blocks);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		exit(-1);
	}

	//尝试打开文件
	if (FileManager::IsPartitionExist(m_eoOption.chPartition) == false)
	{
		cout << "分区不存在！" << endl;
		exit(-2);
	}
	m_pfmFile = new FileManager(std::string(&m_eoOption.chPartition) + ":/HDD_Awaker.txt");

	//申请线程
	m_ptimerWriteData = new Timer(bind(&FileManager::WriteRandomLine, m_pfmFile), m_eoOption.unPeriod);
	m_ptimerUpdateConsole = new Timer(bind(&Awaker::__PrintStateThreadFunc, this), m_eoOption.unPeriod);

	//开始运行
	m_ptimerUpdateConsole->Run();
	m_ptimerWriteData->Run();

	//等待用户停止输入
	cin.get();

	//等待线程停止
	cout << "等待线程停止...\n如果你弄了非常长的周期那么建议你kill了吧。" << endl;
	this_thread::sleep_for(chrono::seconds(1));
	m_ptimerWriteData->Quit();
	m_ptimerUpdateConsole->Quit();

	//清理
	if (m_eoOption.bIsRemoveAtQuit)
	{
		m_pfmFile->Delete();
	}

	return 0;
}

void Awaker::__PrintStateThreadFunc()
{
	using namespace std;

	system("cls");

	cout << "------------------------------------------------\n"; //'-' x32
	cout << "\t操作文件: " << m_pfmFile->GetFilename() << endl;
	cout << "\t写入总量: " << m_pfmFile->lBytesWritten << " 字节" << endl;
	cout << "\t写入周期: " << m_eoOption.unPeriod << " 秒" << endl;
	cout << "------------------------------------------------\n\n"; //'-' x32

	cout << "按回车键停止..." << endl;
}

std::vector<std::string> Awaker::__CmdlineParse(int argc, char* argv[])
{
	std::vector<std::string> blocks;
	for (int index_argc = 0; index_argc != argc; index_argc++)
	{
		blocks.push_back(argv[index_argc]);
	}
	return blocks; // moved?
}

ExecutionOption
Awaker::__CmdblocksParse(const std::vector<std::string>& blocks)
{
	ExecutionOption eo;
	eo.bIsRemoveAtQuit = false;
	eo.chPartition		 = 'e';
	eo.unPeriod				 = 4;

	for (int index = 0; index != blocks.size(); /*里面控制*/)
	{
		if (blocks[index][0] == '-')
		{
			switch (blocks[index][1])
			{
				case 'p': //"-p"
					if (index + 1 < blocks.size())
					{
						sscanf_s(blocks[index + 1].c_str(), "%u", &eo.unPeriod);
					}
					else
					{
						throw std::exception("周期，预期无符号整数参数");
					}
					index++;
					break;
				case 'd': //"-d"
					if (index + 1 < blocks.size())
					{
						sscanf_s(blocks[index + 1].c_str(), "%c", &eo.chPartition, sizeof(char));
					}
					else
					{
						throw std::exception("工作分区，预期字符参数");
					}
					index++;
					break;
				case 'r': //"-r"
					eo.bIsRemoveAtQuit = true;
					break;

				default:
					break;
			}
		}
		index++;
	}

	return eo;
}