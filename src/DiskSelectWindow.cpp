#include "DiskSelectWindow.h"

DiskSelectWindow::DiskSelectWindow() {
	__BuildWindow();
	while (Fl::wait()) {
		//运行按钮被按下
		if (m_pButtonStart->changed()) {
			if (__ExistSelectedDiskButton()) {
				//合法的选择
				break;
			}
			else {
				//不合法的选择，弹出提示且重置按钮
				fl_message_title(u8"错误");
				fl_alert(u8"至少选择一个分区");
				m_pButtonStart->value(0);
				m_pButtonStart->clear_changed();
			}
		}
	}
	if (m_pButtonStart->changed()) {
		//处理合法的选择，将盘符集合保存到public变量中
		__ListSelectedDisk();
	}
	else {
		//如果是直接关闭窗口，则为不合法的输入
		strSelectedDisk.clear();
	}
}

DiskSelectWindow::~DiskSelectWindow() {
	__Cleanup();
}

void DiskSelectWindow::__BuildWindow() {
	m_pWindow = new	Fl_Window(240, 240, u8"勾选分区");
	m_pWindow->end();
	m_pScroll = new Fl_Scroll(0, 0, m_pWindow->w(), m_pWindow->h() - 32);
	m_pScroll->end();
	m_pPack = new Fl_Pack(0, 0, m_pWindow->w(), 32 * 26);
	m_pPack->end();

	m_pButtonStart = new Fl_Button(0, m_pWindow->h() - 32, m_pWindow->w(), 32, u8"运行");
	m_pWindow->add(m_pButtonStart);

	m_pWindow->add(m_pScroll);
	m_pScroll->add(m_pPack);

	//build sel buttons
	__GenerateSelButton(__GetSysExistPartition());

	//set widget attr
	m_pPack->type(Fl_Pack::VERTICAL);
	m_pScroll->type(Fl_Scroll::VERTICAL);

	//make avaliable
	m_pWindow->show();
}

std::string DiskSelectWindow::__GetSysExistPartition() {
	char disk = 'A';
	std::string avaliableDisk;
	for (; disk <= 'Z'; disk++) {
		if (FileManager::IsPartitionExist(disk)) {
			avaliableDisk.push_back(disk);
		}
	}
	return avaliableDisk;
}

void DiskSelectWindow::__GenerateSelButton(const std::string& avaliableDisk) {
	for (auto ch : avaliableDisk) {
		std::string tmpLabel;
		tmpLabel.push_back(ch);
		auto btn = new Fl_Check_Button(0, 0, 64, 32);
		btn->copy_label(tmpLabel.c_str());
		m_pPack->add(btn);
		m_vpDiskSelButton.push_back(btn);
	}
}

bool DiskSelectWindow::__ExistSelectedDiskButton() {
	for (auto& btn : m_vpDiskSelButton) {
		if (btn->value() == 1) {
			return true;
		}
	}
	return false;
}

void DiskSelectWindow::__ListSelectedDisk() {
	std::string selectedDisk;
	for (auto& btn : m_vpDiskSelButton) {
		if (btn->value() == 1) {
			selectedDisk.append(btn->label());
		}
	}
	strSelectedDisk = selectedDisk;
}

void DiskSelectWindow::__Cleanup() {
	//for (auto& pBtn : m_vpDiskSelButton) delete pBtn;
	//m_vpDiskSelButton.swap(std::vector<Fl_Check_Button*>());
	//delete m_pPack;
	//m_pPack = nullptr;
	//delete m_pScroll;
	//m_pScroll = nullptr;
	//delete m_pWindow;
	//m_pWindow = nullptr;

	//auto GC
	delete m_pWindow;
}