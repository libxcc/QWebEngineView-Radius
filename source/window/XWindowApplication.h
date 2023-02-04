#ifndef			_X_WINDOW_X_H_
#define			_X_WINDOW_X_H_

#include "XccEngineWidget.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
	class XWindowApplication;
}
QT_END_NAMESPACE

// 主界面
class XWindowApplication : public QWidget
{
Q_OBJECT

public:
	// constructor
	explicit XWindowApplication(QWidget* _Parent) noexcept;

	// destructor
	~XWindowApplication() noexcept override;

private:
	// UI
	Ui::XWindowApplication*			ui;
};


#endif
