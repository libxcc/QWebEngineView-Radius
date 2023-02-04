#ifndef			_XCC_ENGINE_WIDGET_H_
#define			_XCC_ENGINE_WIDGET_H_

#include "XccEngineHeader.h"
#include "XccEngineRender.h"


// 浏览器交互窗口
class XCC_ENGINE_API XccEngineWidget : public QWidget
{
Q_OBJECT

public:
	// constructor
	explicit XccEngineWidget(QWidget* _Parent = nullptr) noexcept;

	// destructor
	~XccEngineWidget() noexcept override;

private:
	// 浏览器渲染窗口
	XccEngineRender*			memberEngineRender = nullptr;

	// 浏览器渲染图片
	QPixmap					memberEnginePixmap;

	// 浏览器渲染区域
	QPainterPath				memberEnginePath;

	// 圆角: 左上
	int					memberRadiusLT;

	// 圆角: 左下
	int					memberRadiusLD;

	// 圆角: 右上
	int					memberRadiusRT;

	// 圆角: 右下
	int					memberRadiusRD;

protected:
	// [event] 汇总
	bool event(QEvent* _Event) override;

	// [event] 鼠标按下
	void mousePressEvent(QMouseEvent* _Event) override;

	// [event] 大小改变
	void resizeEvent(QResizeEvent* _Event) override;

	// [event] 绘图
	void paintEvent(QPaintEvent* _Event) override;

	// [event] 关闭
	void closeEvent(QCloseEvent* _Event) override;

	// [event] 显示
	void showEvent(QShowEvent* _Event) override;

public:
	// [set] 设置圆角
	virtual void setEngineRadius(int _LT, int _LD, int _RT, int _RD) noexcept final;

	// [opt] 更新绘图区域
	virtual void updatePainterPath() noexcept final;

	// [set] 浏览器窗口
	virtual void setEngineRender(XccEngineRender* _Render) noexcept final;

	// [get] 浏览器窗口
	virtual XccEngineRender* engineRender() const noexcept final;

public slots:
	// [receive] 绘图事件
	virtual void receivePaintEvent(QPaintEvent* _Event) noexcept final;
};

#endif
