#ifndef KCLIENTWIDGET_H
#define KCLIENTWIDGET_H

#include <QMainWindow>
#include <QThread>
#include "pomelog.h"

#include "ksir_common.h"

namespace Ui {
class kClientWidget;
}

class kClientWidget : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit kClientWidget(QWidget *parent = 0);
	~kClientWidget();

	void changeText(const QString&);
	
private:
	Ui::kClientWidget *ui;
};

#endif // KCLIENTWIDGET_H
