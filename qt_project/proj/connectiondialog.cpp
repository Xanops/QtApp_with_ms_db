#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_pushButton_clicked()
{
    //В следующей строке указывается используемый драйвер
    db =QSqlDatabase::addDatabase("QODBC");

    /*Перенос в следующей строке использовался для удобства и не
    является обязательным*/
    //Далее формируется строка подключения
    db.setDatabaseName("DRIVER={SQL Server}; SERVER="
    +ui->lineEdit->text()+
    ";DATABASE="+ui->lineEdit_2->text()+";");

    //Указывается логин и пароль соответственно
    db.setUserName(ui->lineEdit_3->text());
    db.setPassword(ui->lineEdit_4->text());

    msg = new QMessageBox(); //создаём объект для вывода сообщения
    if (db.open()) //попытка подключения к БД
    {
        msg->setText("Соединение установлено"); //
    }
    else
    {
        msg->setText("Соединение НЕ установлено");
    }
    msg->show();
}

