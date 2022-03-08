#include "search_null.h"
#include "ui_search_null.h"

search_null::search_null(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search_null)
{
    ui->setupUi(this);
}

search_null::~search_null()
{
    delete ui;
}

void search_null::on_pushButton_clicked()
{
    this->close();
}
