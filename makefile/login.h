#pragma once

#include <QDialog>
namespace Ui { class Login; };
#define DEFAULTSERVERADDRESS "10.173.80.254"
#define DEFAULTSERVERPORT 8800
#define DEFAULTUSERNAME "loadmin"
#define DEFAULTPASSWORD "123456admin"

//#define DEFAULTSERVERADDRESS "10.10.10.1"
//#define DEFAULTSERVERPORT 8800
//#define DEFAULTUSERNAME "test002"
//#define DEFAULTPASSWORD "123456"

class Login : public QDialog
{
	Q_OBJECT
public:
	Login(QWidget *parent = Q_NULLPTR);
	~Login();
	QString serverAddress;
	int serverPort;
	QString userName;
	QString password;
public slots:
	void clearButtonSlot();
	void enterButtonSlot();
	void cancalButtonSlot();
private:
	Ui::Login *ui;
};
