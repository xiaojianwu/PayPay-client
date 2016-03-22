#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QtWidgets/QWidget>
#include "ui_mainframe.h"

#include "basestylewindow.h"

class MainFrame : public BaseStyleWindow
{
	Q_OBJECT

public:
	MainFrame(QWidget *parent = 0);
	~MainFrame();


private slots:
	void onExit();

private:
	Ui::MainFrameClass ui;
};

#endif // MAINFRAME_H
