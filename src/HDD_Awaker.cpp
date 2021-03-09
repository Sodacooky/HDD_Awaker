#include "HDD_Awaker.h"

using namespace std;

int main(int argc, char* argv[]) {
	Awaker app;
	//return app.Main(argc, argv);
	return app.Main();
}

int Awaker::Main() {
	auto disk_sel_window = new DiskSelectWindow();
	std::cout << disk_sel_window->strSelectedDisk << std::endl;
	delete disk_sel_window;

	cin.get();

	return 0;
}