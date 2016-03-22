#include "basestylewindow.h"

#include <QPainter>

#include <QStyle>
#include <QStyleOption>

#include <QIcon>

#include <qapplication.h>

#include <qdesktopwidget.h>


BaseStyleWindow::BaseStyleWindow(QWidget *parent)
	: QDialog(parent)
{

	// 设置无边框和任务栏触发最小化
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

	// 关闭窗口时释放资源
	setAttribute(Qt::WA_DeleteOnClose, false);

	setWindowIcon(QIcon(":/Resource/logo.ico"));

	setFocus();
}

BaseStyleWindow::~BaseStyleWindow()
{

}


void BaseStyleWindow::centerWindow()
{
	QSize desktopSize = QApplication::desktop()->availableGeometry().size();
	move((desktopSize.width() - this->width()) / 2, (desktopSize.height() - this->height()) / 2);
}




void BaseStyleWindow::paintEvent(QPaintEvent *event)
{
	// 背景图
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}