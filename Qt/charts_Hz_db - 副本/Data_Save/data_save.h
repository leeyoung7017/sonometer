#ifndef DATA_SAVE_H
#define DATA_SAVE_H

#include <QDialog>

namespace Ui {
class data_save;
}

class data_save : public QDialog
{
    Q_OBJECT

public:
    explicit data_save(QWidget *parent = nullptr);
    ~data_save();

private slots:
    void on_pushButton_clicked();

private:
    Ui::data_save *ui;
};

#endif // DATA_SAVE_H
