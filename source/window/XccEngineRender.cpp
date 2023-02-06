#include "XccEngineRender.h"


// constructor
XccEngineRender::XccEngineRender(QWidget* _Parent) noexcept : QWebEngineView(_Parent)
{
	memberChildWidget = nullptr;

	this->setAttribute(Qt::WA_DeleteOnClose, true);
	this->setWindowFlags(this->windowFlags() | Qt::Tool);
	this->setWindowFlags(this->windowFlags() | Qt::ToolTip);
	this->setWindowFlags(this->windowFlags() | Qt::X11BypassWindowManagerHint);
}

// destructor
XccEngineRender::~XccEngineRender() noexcept = default;



// [opt] 通知事件
bool XccEngineRender::sendEvent(QEvent* _Event) noexcept
{
	if(memberChildWidget)
	{
		switch(_Event->type())
		{
			case QEvent::MouseButtonPress:
			case QEvent::MouseButtonRelease:
			case QEvent::MouseButtonDblClick:
			case QEvent::MouseMove:
			case QEvent::KeyPress:
			case QEvent::KeyRelease:
			case QEvent::FocusIn:
			case QEvent::FocusOut:
			case QEvent::FocusAboutToChange:
			case QEvent::Enter:
			case QEvent::Leave:
			case QEvent::Paint:
			case QEvent::Show:
			case QEvent::Hide:
			case QEvent::WindowActivate:
			case QEvent::WindowDeactivate:
			case QEvent::Wheel:
			case QEvent::Clipboard:
			case QEvent::InputMethod:
			case QEvent::HoverEnter:
			case QEvent::HoverLeave:
			case QEvent::HoverMove:
			case QEvent::ScrollPrepare:
			case QEvent::Scroll:
				return QApplication::sendEvent(memberChildWidget, _Event);
			default:
				break;
		}
	}
	return false;
}

// [get] 当前渲染图像
QPixmap XccEngineRender::renderPixmap() const noexcept
{
	return memberChildWidget->grab();
}



// [event] 汇总
bool XccEngineRender::event(QEvent* _Event)
{
	if (_Event->type() == QEvent::ChildPolished)
	{
		auto		vChildEvent = dynamic_cast<QChildEvent*>(_Event);
		memberChildWidget = qobject_cast<QWidget*>(vChildEvent->child());
		if (memberChildWidget)
		{
			memberChildWidget->installEventFilter(this);
		}
	}
	else if(_Event->type() == QEvent::ChildRemoved)
	{
		auto		vChildEvent = dynamic_cast<QChildEvent*>(_Event);
		if (memberChildWidget == vChildEvent->child())
		{
			memberChildWidget = nullptr;
		}
	}
	return QWebEngineView::event(_Event);
}

// [event] 过滤器
bool XccEngineRender::eventFilter(QObject* _Object, QEvent* _Event)
{
	if (_Object == memberChildWidget && _Event->type() == QEvent::Paint)
	{
		auto		vPaintEvent = dynamic_cast<QPaintEvent*>(_Event);
		emit signalPaintEvent(vPaintEvent);
	}
	if (_Object == memberChildWidget && _Event->type() == QEvent::CursorChange)
	{
		auto		vCursorStatus = memberChildWidget->cursor().shape();
		emit signalCursorChange(vCursorStatus);
	}
	return QWebEngineView::eventFilter(_Object, _Event);
}
