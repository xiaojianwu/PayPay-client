#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "ui_messagebox.h"
#include "basestylewindow.h"


// 提示窗图标类型
enum MESSAGE_BOX_TYPE {
	TYPE_INFO = 0,
	TYPE_WARNING,
	TYPE_QUESTION,
	TYPE_SUCCESS
};

int PayMessageBox(QWidget *parent, int type, QString qsTitle, QString qsContentText);


class UIMessageBox : public BaseStyleWindow
{
    Q_OBJECT

public:
    explicit UIMessageBox(QWidget *parent = 0);
    ~UIMessageBox();

	void UIMessageBox::initUI(int type, QString qsTitle, QString qsContentText);

private slots:
	void onOK();
	void onCancel();

private:
	Ui::MessageBoxClass ui;
};

#endif // MESSAGEBOX_H
