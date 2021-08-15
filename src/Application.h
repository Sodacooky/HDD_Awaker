#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <string>

class Application
{
public:
	int Main();

private:
	void __Startup();
	void __Running();

private:
	std::string m_strSelectedPartition;
};

#endif // __APPLICATION_H__