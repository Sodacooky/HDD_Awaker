#pragma once

#include "FileManager.h"
#include "Timer.h"
//#include <FL/Fl.H>
#include <iostream>

// application
class Awaker {
public:
  // in main
  int Main();

  //ÖÜÆÚĞ´Èë
  void Write();

private:
  FileManager *m_pfilem;
};