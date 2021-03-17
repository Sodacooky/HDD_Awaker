#include "HDD_Awaker.h"

using namespace std;

int main(void) {
	Application app;
	return app.Main();
}

int Application::Main() {
	//get disk selection
	auto disk_sel_window = new DiskSelectWindow();
	string diskSelection;
	diskSelection = disk_sel_window->strSelectedDisk;
	delete disk_sel_window;

	if (diskSelection.empty()) {
		return 1;
	}

	//main interface
	auto main_work_window = new WorkingWindow(diskSelection);

	return 0;
}