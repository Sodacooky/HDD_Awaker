#include "HDD_Awaker.h"

using namespace std;

int main() {
  Awaker app;
  return app.Main();
}

int Awaker::Main() {
  m_pfilem = new FileManager("E:/HDD_Awaker_File.txt");

  Timer tmr(std::bind(&Awaker::Write, this));
  tmr.Run();

  std::cout << "running...\n";
  std::cin.get();

  tmr.Quit();
  m_pfilem->Delete();
  delete m_pfilem;
  return 0;
}

void Awaker::Write() {
  m_pfilem->WriteLine();
  m_pfilem->WriteLine("Done!");
  std::cout << m_pfilem->lBytesWritten << "\t bytes" << std::endl;
}