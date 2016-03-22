#ifndef BASESTYLEWINDOW_H
#define BASESTYLEWINDOW_H

#include <QDialog>

class BaseStyleWindow : public QDialog
{
	Q_OBJECT

public:
	BaseStyleWindow(QWidget *parent = 0);
	~BaseStyleWindow();

public:

	// »æÖÆÊÂ¼þ
	void paintEvent(QPaintEvent*);

	void centerWindow();
private:

};

#endif // BASESTYLEWINDOW_H
