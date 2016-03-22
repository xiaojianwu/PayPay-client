#include "messagebox.h"


int PayMessageBox(QWidget *parent, int type, QString qsTitle, QString qsContentText)
{

	UIMessageBox cUIMessageBox(parent);
	// ��ʼ����������
	cUIMessageBox.initUI(type, qsTitle, qsContentText);
	return cUIMessageBox.exec();
}

UIMessageBox::UIMessageBox(QWidget *parent) :  BaseStyleWindow(parent)
{
    ui.setupUi(this);
	centerWindow();

	// ����
	connect(ui.messagebox_ok, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.messagebox_cancel, SIGNAL(clicked()), this, SLOT(onCancel()));
}

UIMessageBox::~UIMessageBox()
{
}

void UIMessageBox::onOK()
{
	done(QDialog::Accepted);
}
void UIMessageBox::onCancel()
{
	done(QDialog::Rejected);
}

void UIMessageBox::initUI(int type, QString qsTitle, QString qsContentText)
{
	// ģ̬�ͱ���
	ui.label_title->setText(qsTitle);

	ui.label_text->setText(qsContentText);

	switch (type)
	{
	case TYPE_INFO:
	case TYPE_WARNING:
		ui.label_icon->setPixmap(QPixmap(":/Resources/Images/messagebox_warning.png"));
		break;
	case TYPE_QUESTION:
		ui.label_icon->setPixmap(QPixmap(":/Resources/Images/messagebox_qus.png"));
		break;
	}

}