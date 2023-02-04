#include "XccEngineWidget.h"


// constructor
XccEngineWidget::XccEngineWidget(QWidget* _Parent) noexcept : QWidget(_Parent)
{
	this->setMouseTracking(true);
	this->setAttribute(Qt::WA_InputMethodEnabled, true);
	this->setAttribute(Qt::WA_DeleteOnClose, true);
	this->setFocusPolicy(Qt::StrongFocus);

	setEngineRender(new(std::nothrow) XccEngineRender(nullptr));

	memberRadiusLT = 20;
	memberRadiusLD = 20;
	memberRadiusRT = 20;
	memberRadiusRD = 20;
}

// destructor
XccEngineWidget::~XccEngineWidget() noexcept = default;



// [event] 汇总
bool XccEngineWidget::event(QEvent* _Event)
{
	auto		vSync = QWidget::event(_Event);
	if(memberEngineRender)
	{
		memberEngineRender->sendEvent(_Event);
	}
	return vSync;
}

// [event] 鼠标按下
void XccEngineWidget::mousePressEvent(QMouseEvent* _Event)
{
	this->setFocus();
	QWidget::mousePressEvent(_Event);
}

// [event] 大小改变
void XccEngineWidget::resizeEvent(QResizeEvent* _Event)
{
	if(memberEngineRender)
	{
		auto		vSize = this->size();
		memberEngineRender->move(0 - vSize.width() - 1000, 0 - vSize.height() - 1000);
		memberEngineRender->resize(vSize);
	}
	QWidget::resizeEvent(_Event);
	updatePainterPath();
}

// [event] 绘图
void XccEngineWidget::paintEvent(QPaintEvent* _Event)
{
	Q_UNUSED(_Event);

	QPainter	vPainter(this);
	vPainter.setRenderHints(QPainter::Antialiasing);
	vPainter.setRenderHints(QPainter::SmoothPixmapTransform);

	vPainter.setClipPath(memberEnginePath);

	vPainter.drawPixmap(this->rect(), memberEnginePixmap);
}

// [event] 关闭
void XccEngineWidget::closeEvent(QCloseEvent* _Event)
{
	if(memberEngineRender)
	{
		memberEngineRender->close();
		memberEngineRender = nullptr;
	}
	QWidget::closeEvent(_Event);
}

// [event] 显示
void XccEngineWidget::showEvent(QShowEvent* _Event)
{
	setAttribute(Qt::WA_Mapped);
	QWidget::showEvent(_Event);
}



// [set] 设置圆角
void XccEngineWidget::setEngineRadius(int _LT, int _LD, int _RT, int _RD) noexcept
{
	memberRadiusLT = _LT;
	memberRadiusLD = _LD;
	memberRadiusRT = _RT;
	memberRadiusRD = _RD;
	updatePainterPath();
}

// [opt] 更新绘图区域
void XccEngineWidget::updatePainterPath() noexcept
{
	memberEnginePath.clear();

	auto		vArea = this->rect();
	memberEnginePath.moveTo(0, memberRadiusLT);

	// 左上
	if(memberRadiusLT == 0)
	{
		memberEnginePath.lineTo(0, 0);
		memberEnginePath.lineTo(memberRadiusLT, 0);
	}
	else
	{
		memberEnginePath.arcTo(QRect(0, 0, memberRadiusLT, memberRadiusLT), 180, -90);
	}

	// 上
	memberEnginePath.lineTo(vArea.width() - memberRadiusRT, 0);

	// 右上
	if(memberRadiusRT == 0)
	{
		memberEnginePath.lineTo(vArea.width(), 0);
		memberEnginePath.lineTo(vArea.width(), memberRadiusRT);
	}
	else
	{
		memberEnginePath.arcTo(QRect(vArea.width() - memberRadiusRT, 0, memberRadiusRT, memberRadiusRT), 90, -90);
	}

	// 右
	memberEnginePath.lineTo(vArea.width(), vArea.height() - memberRadiusRD);

	// 右下
	if(memberRadiusRD == 0)
	{
		memberEnginePath.lineTo(vArea.width(), vArea.height());
		memberEnginePath.lineTo(vArea.width() - memberRadiusRD, vArea.height());
	}
	else
	{
		memberEnginePath.arcTo(QRect(vArea.width() - memberRadiusRD, vArea.height() - memberRadiusRD, memberRadiusRD, memberRadiusRD), 0, -90);
	}

	// 下
	memberEnginePath.lineTo(memberRadiusLD, vArea.height());

	// 左下
	if(memberRadiusLD == 0)
	{
		memberEnginePath.lineTo(0, vArea.height());
		memberEnginePath.lineTo(0, vArea.height() - memberRadiusLD);
	}
	else
	{
		memberEnginePath.arcTo(QRect(0, vArea.height() - memberRadiusLD, memberRadiusLD, memberRadiusLD), 270, -90);
	}

	// 左
	memberEnginePath.lineTo(0, memberRadiusLT);

	update();
}

// [set] 浏览器窗口
void XccEngineWidget::setEngineRender(XccEngineRender* _Render) noexcept
{
	if(memberEngineRender)
	{
		memberEngineRender->close();
	}
	memberEngineRender = _Render;

	QObject::connect(memberEngineRender, &XccEngineRender::signalPaintEvent, this, &XccEngineWidget::receivePaintEvent);

	memberEngineRender->setParent(nullptr);
	memberEngineRender->move(-1000, -1000);
	memberEngineRender->show();
}

// [get] 浏览器窗口
XccEngineRender* XccEngineWidget::engineRender() const noexcept
{
	return memberEngineRender;
}



// [receive] 绘图事件
void XccEngineWidget::receivePaintEvent(QPaintEvent* _Event) noexcept
{
	Q_UNUSED(_Event);

	if(memberEngineRender)
	{
		memberEnginePixmap = memberEngineRender->renderPixmap();
	}
	update();
}
