#include "kclientwidget.h"
#include "ui_kclientwidget.h"

kClientWidget::kClientWidget(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::kClientWidget)
{
	ui->setupUi(this);
}

kClientWidget::~kClientWidget()
{
	delete ui;
}

void kClientWidget::changeText(const QString& p_str)
{
	ui->labelTest->setText(p_str);
}
