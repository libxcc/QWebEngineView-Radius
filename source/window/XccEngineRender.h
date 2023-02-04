#ifndef			_XCC_ENGINE_RENDER_H_
#define			_XCC_ENGINE_RENDER_H_

#include "XccEngineHeader.h"


// 浏览器渲染窗口
class XCC_ENGINE_API XccEngineRender : public QWebEngineView
{
Q_OBJECT

public:
	// constructor
	explicit XccEngineRender(QWidget* _Parent) noexcept;

	// destructor
	~XccEngineRender() noexcept override;

private:
	// 子级
	QWidget*			memberChildWidget;

public:
	// [opt] 通知事件
	virtual bool sendEvent(QEvent* _Event) noexcept final;

	// [get] 当前渲染图像
	virtual QPixmap renderPixmap() const noexcept final;

protected:
	// [event] 汇总
	bool event(QEvent* _Event) override;

	// [event] 过滤器
	bool eventFilter(QObject* _Object, QEvent* _Event) override;

signals:
	// [signal] PaintEvent
	void signalPaintEvent(QPaintEvent* _Event);
};

#endif
