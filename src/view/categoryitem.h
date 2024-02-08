#ifndef CATEGORYITEM_H
#define CATEGORYITEM_H

#include <QWidget>

namespace Ui {
class CategoryItem;
}

class CategoryItem : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryItem(QWidget *parent = nullptr, int id = 0,
                          const QString& name = "", const QString& slug = "");
    ~CategoryItem();

signals:
    void viewButton_clicked(int categoryId);

    void deleteButton_clicked();

private slots:
    void on_viewButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::CategoryItem *ui;
    int categoryId;
};

#endif // CATEGORYITEM_H
