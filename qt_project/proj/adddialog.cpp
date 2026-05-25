#include "adddialog.h"
#include "ui_adddialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <mainwindow.h>

AddDialog::AddDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT name FROM category");
    while (queryCombo->next())
    {
        ui->comboBox->addItem(queryCombo->value(0).toString());
    }

    ui->dateEdit->setDate(QDate::currentDate());
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_pushButton_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("INSERT INTO product (name, ImagePath, catID, prodDate)"
                   "VALUES(:name, :image, :category, :date)");
    query->bindValue(":name", ui->lineEdit->text());
    query->bindValue(":image",Img);
    query->bindValue(":category", ui->comboBox->currentIndex()+1);
    query->bindValue(":date", ui->dateEdit->text());

    if(query->exec())
    {
        close();
    }
}


void AddDialog::on_toolButton_clicked()
{
    Img = QFileDialog::getOpenFileName(0, "Открыть файл", Img,"*.jpg");
    ui->label_3->setPixmap(Img);
}

