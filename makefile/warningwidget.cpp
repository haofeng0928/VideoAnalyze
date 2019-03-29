#include "warningwidget.h"
#include "ui_warningwidget.h"

WarningWidget::WarningWidget(int level, QString position, QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::WarningWidget();
	ui->setupUi(this);
	ui->levelLabel->setText(QString::number(level) + QStringLiteral("��Ԥ��"));
	ui->levelLabel->setAlignment(Qt::AlignCenter);
	ui->comboBox->addItem(QStringLiteral("1���Ӻ�Ԥ��"));
	ui->comboBox->addItem(QStringLiteral("5���Ӻ�Ԥ��"));
	ui->comboBox->addItem(QStringLiteral("ȡ��Ԥ��"));
	connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectTime(int)));
	connect(ui->enterButton, SIGNAL(clicked()), this, SLOT(enterButtonSlot()));
}
void WarningWidget::enterButtonSlot()
{
	emit enterSignal(minutes);
	this->close();
}
void WarningWidget::selectTime(int index)
{
	switch (index)
	{
	case 0: this->minutes = 1;
	case 1: this->minutes = 5;
	case 3: this->minutes = -1;
	}
}
WarningWidget::~WarningWidget()
{
	delete ui;
}
