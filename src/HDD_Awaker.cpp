#include "HDD_Awaker.h"

using namespace std;

int main(int argc, char* argv[]) {
	Awaker app;
	//return app.Main(argc, argv);
	return app.TestMain();
}

int Awaker::Main(int argc, char* argv[]) {
	//处理命令行
	m_eoOption = __CmdblocksParse(argc, argv);

	//尝试打开文件
	if (FileManager::IsPartitionExist(m_eoOption.chPartition) == false) {
		cout << "分区不存在！" << endl;
		exit(-2);
	}
	m_pfmFile = new FileManager(
		string(":/HDD_Awaker.txt").insert(0, 1, m_eoOption.chPartition));

//申请线程
	m_ptimerWriteData = new Timer(bind(&FileManager::WriteRandomLine, m_pfmFile),
																m_eoOption.unPeriod);
	m_ptimerUpdateConsole = new Timer(bind(&Awaker::__PrintStateThreadFunc, this),
																		m_eoOption.unPeriod);

	//开始运行
	m_ptimerUpdateConsole->Run();
	m_ptimerWriteData->Run();

	//等待用户停止输入
	cin.get();

	//等待线程停止
	cout << "等待线程停止...\n如果你弄了非常长的周期那么建议你kill了吧。" << endl;
	m_ptimerWriteData->Quit();
	m_ptimerUpdateConsole->Quit();

	//清理
	if (m_eoOption.bIsRemoveAtQuit) {
		m_pfmFile->Delete();
	}

	return 0;
}

int Awaker::TestMain() {
	auto disk_sel_window = new DiskSelectWindow();
	std::cout << disk_sel_window->strSelectedDisk << std::endl;
	delete disk_sel_window;

	_getch();

	return 0;
}

void Awaker::__PrintStateThreadFunc() {
	using namespace std;

	system("cls");

	cout << "------------------------------------------------\n"; //'-' x32
	cout << "\t操作文件: " << m_pfmFile->GetFilename() << endl;
	cout << "\t写入总量: " << m_pfmFile->lBytesWritten << " 字节" << endl;
	cout << "\t写入周期: " << m_eoOption.unPeriod << " 秒" << endl;
	cout << "------------------------------------------------\n\n"; //'-' x32

	cout << "按回车键停止..." << endl;
}

ExecutionOption Awaker::__CmdblocksParse(int argc, char* argv[]) {
	ExecutionOption eo;
	eo.bIsRemoveAtQuit = false;
	eo.chPartition = 'E';
	eo.unPeriod = 4;

	CmdlineParser cmdParser(argc, argv);
	auto cmd_map = cmdParser.DoProcess();

	//对应
	for (auto& pair : cmd_map) {
		if (pair.first == "-p" || pair.first == "--period") {
			if (pair.second.size() == 0) {
				cout << "命令 -p/--period 需要参数，已设置为默认的4" << endl;
				continue;
			}
			else {
				unsigned int seconds;
				stringstream ss(pair.second);
				ss >> seconds;
				if (seconds == 0) {
					cout << "命令 -p/--period 的参数不能为0，已设置为默认的4" << endl;
					seconds = 4;
				}
				eo.unPeriod = seconds;
			}
		}
		else if (pair.first == "-r" || pair.first == "--remove") {
			eo.bIsRemoveAtQuit = true;
		}
		else if (pair.first == "-d" || pair.first == "--disk") {
			if (pair.second.size() == 0) {
				cout << "命令 -d/--disk 需要参数，已设置为默认的E" << endl;
				continue;
			}
			else {
				if (isalpha(pair.second[0])) {
					eo.chPartition = pair.second[0];
				}
				else {
					cout << "命令 -d/--disk 的参数需要为分区号，已设置为默认的E" << endl;
				}
			}
		}
		else {
			cout << "命令 " << pair.first << " / " << pair.second << " 未定义，已忽略"
				<< endl;
		}
	}

	return eo;
}