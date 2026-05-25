#include "modifydialog.h"
#include "ui_modifydialog.h"
#include <QSqlQuery>
#include "mainwindow.h"

int TempID;
ModifyDialog::ModifyDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyDialog)
{
    ui->setupUi(this);
    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT name FROM category");
    while (queryCombo->next())
    {
        ui->comboBox->addItem(queryCombo->value(0).toString());
    }
}

ModifyDialog::~ModifyDialog()
{
    delete ui;
}

void ModifyDialog::on_pushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE product SET name = :name,"
                   "ImagePath = :image,"
                   "catID = :category WHERE ID = :ID");
    query->bindValue(":ID", TempID);
    query->bindValue(":name",ui->lineEdit->text());
    query->bindValue(":image",Img);
    query->bindValue(":category",ui->comboBox->currentIndex()+1);
    if(query->exec())
    {
        close();
    }
}


void ModifyDialog::sendingID(int aa)
{
    TempID = aa;
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, ImagePath, catID FROM product WHERE ID =:ID");
    query->bindValue(0,aa);
    if (query->exec())
    {
        query->next();
        ui->lineEdit->setText(query->value(0).toString());
        Img = query->value(1).toString();
        ui->label_3->setPixmap(Img);
        ui->comboBox->setCurrentIndex(query->value(2).toInt()-1);
    }
}


void ModifyDialog::on_toolButton_clicked()
{
    Img = QFileDialog::getOpenFileName(0, "Открыть файл", Img,"*.jpg");
    ui->label_3->setPixmap(Img);
}

