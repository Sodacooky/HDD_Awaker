#pragma once

#include "FileManager.h"
#include "Timer.h"
#include <iostream>
#include <string>

// application
class Awaker {
public:
  // in main
  int Main();

private:
  //
  void __PrintState();

  //
  void __ProcessCmd();

  //
  void __CmdHelp();
  //
  void __CmdPeriod(unsigned int seconds);
  //
  void __CmdStop();
  //
  void __CmdSet(const std::string &disk);

private:
  //
  Timer *m_timerUpdateConsole;
  //
  Timer *m_timerWriteData;
  //
  FileManager *m_filemanager;
  //
  bool m_bContinue;
};