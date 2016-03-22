#include "messagebox.h"


int PayMessageBox(QWidget *parent, QString qsTitle, QString qsContentText)
{

	UIMessageBox cUIMessageBox(parent);
	// ��ʼ����������
	cUIMessageBox.initUI(qsTitle, qsContentText);
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

void UIMessageBox::initUI(QString qsTitle, QString qsContentText)
{
	// ģ̬�ͱ���
	ui.label_title->setText(qsTitle);

	ui.label_text->setText(qsContentText);

	

}