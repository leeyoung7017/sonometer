#ifndef SEARCH_NULL_H
#define SEARCH_NULL_H

#include <QDialog>

namespace Ui {
class search_null;
}

class search_null : public QDialog
{
    Q_OBJECT

public:
    explicit search_null(QWidget *parent = nullptr);
    ~search_null();

private slots:
    void on_pushButton_clicked();

private:
    Ui::search_null *ui;
};

#endif // SEARCH_NULL_H
