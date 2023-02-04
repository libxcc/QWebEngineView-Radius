#include "XWindowApplication.h"
#include "ui_XWindowApplication.h"


// constructor
XWindowApplication::XWindowApplication(QWidget* _Parent) noexcept : QWidget(_Parent), ui(new Ui::XWindowApplication)
{
	ui->setupUi(this);

	this->setStyleSheet("QWidget{ border:none; border-radius:0px; background-color:#FF6C6C; }");

	auto 		vEngineWidget = new(std::nothrow) XccEngineWidget(this);
	ui->Layout_1->addWidget(vEngineWidget);
	vEngineWidget->setStyleSheet("QWidget{ border:none; border-radius:20px; background-color:#006C6C; }");

	auto 		vEngineRender = vEngineWidget->engineRender();
	vEngineRender->load(QUrl("https://www.baidu.com"));
}

// destructor
XWindowApplication::~XWindowApplication() noexcept
{
	delete ui;
}
