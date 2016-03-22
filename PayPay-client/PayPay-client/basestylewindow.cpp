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

	// �����ޱ߿��������������С��
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

	// �رմ���ʱ�ͷ���Դ
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
	// ����ͼ
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}