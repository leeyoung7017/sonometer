#include "data_save.h"
#include "ui_data_save.h"

data_save::data_save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::data_save)
{
    ui->setupUi(this);
}

data_save::~data_save()
{
    delete ui;
}

void data_save::on_pushButton_clicked()
{
    this->close();
}
