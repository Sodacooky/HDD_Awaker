#include "StartupWindow.h"

#include <filesystem>
#include <fstream>
#include <functional>

StartupWindow::StartupWindow(std::string &selected_partition)
	: m_formWindow(nana::API::make_center(320, 240), nana::appear::decorate<>()),
	  m_lstbPartitionSelector(m_formWindow, nana::rectangle(0, 0, 320, 200)),
	  m_btnStart(m_formWindow, nana::rectangle(0, 200, 320, 40)),
	  m_rstrSelectedPartition(selected_partition)
{
	//set widgets
	m_formWindow.caption(u8"选择运行的分区...");
	m_lstbPartitionSelector.checkable(true);
	m_lstbPartitionSelector.append_header(u8"分区", 240);
	m_lstbPartitionSelector.show_header(false);
	m_lstbPartitionSelector.column_movable(false);
	m_lstbPartitionSelector.column_resizable(false);
	m_btnStart.caption(u8"开始运行");

	//register event
	m_btnStart.events().click(std::bind(&StartupWindow::__StartButtonCallback, this));

	//generate partition list
	__ScanAvaliablePartition();
	for (auto chPartition : m_strAvaliablePartition)
	{
		std::string label = ":";
		label.insert(label.begin(), chPartition);

		m_lstbPartitionSelector.at(0).append(label);
	}

	//load and select last time selection
	__TryReloadSelection();

	//show
	m_formWindow.show();
}

void StartupWindow::__TryReloadSelection()
{
	std::ifstream file("HDD_Awaker_LastSelected.txt");
	if (!file)
	{
		return;
	}

	std::string last_select;
	std::getline(file, last_select);
	file.close();

	for (auto last_partition : last_select)
	{
		auto pos = m_strAvaliablePartition.find(last_partition);
		if (pos != m_strAvaliablePartition.npos)
		{
			m_lstbPartitionSelector.at(0).at(pos).check(true);
		}
	}
}

void StartupWindow::Exec()
{
	nana::exec();
}

void StartupWindow::__ScanAvaliablePartition()
{
	for (char now_scanning = 'A'; now_scanning <= 'Z'; now_scanning++)
	{
		std::string path = ":/";
		path.insert(path.begin(), now_scanning);

		std::filesystem::directory_entry entry(path);
		if (entry.exists())
		{
			m_strAvaliablePartition.push_back(now_scanning);
		}
	}
}

void StartupWindow::__StartButtonCallback()
{
	auto checked = m_lstbPartitionSelector.checked();
	if (checked.size() == 0)
	{
		return;
	}

	for (auto &index_pair : checked)
	{
		m_rstrSelectedPartition.push_back(m_strAvaliablePartition[index_pair.item]);
	}

	std::ofstream file("HDD_Awaker_LastSelected.txt");
	file << m_rstrSelectedPartition;
	file.close();

	nana::API::exit();
}