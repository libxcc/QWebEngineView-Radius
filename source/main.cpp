#include "window/XWindowApplication.h"


// 入口函数
int main(int _Argc, char** _Argv)
{
#if defined(Q_OS_WIN)
	WSADATA		vWsaData;
	WSAStartup(MAKEWORD(2, 2), &vWsaData);
	OleInitialize(nullptr);
#endif

	QApplication		vApplication(_Argc, _Argv);

	// QT的初始化工作
	qsrand((unsigned int)std::time(nullptr));

	// 创建并运行应用程序
	auto		vWindow = new(std::nothrow) XWindowApplication(nullptr);
	if(vWindow)
	{
		vWindow->show();
	}

	auto		vExec = QApplication::exec();

#if defined(Q_OS_WIN)
	OleUninitialize();
	WSACleanup();
#endif

	return vExec;
}
