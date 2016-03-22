#include "mainframe.h"

#include "messagebox.h"

MainFrame::MainFrame(QWidget *parent)
	: BaseStyleWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(onExit()));
}

MainFrame::~MainFrame()
{

}

void MainFrame::initUI()
{

}


void MainFrame::onExit()
{
	if (PayMessageBox(NULL, TYPE_QUESTION, tr("exit"), tr("are you sure to exit?")) == QDialog::Accepted)
	{
		close();
	}
	
}
