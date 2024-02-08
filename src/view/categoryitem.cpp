#include "categoryitem.h"
#include "ui_categoryitem.h"

CategoryItem::CategoryItem(QWidget *parent, int id, const QString& name, const QString& slug) :
    QWidget(parent),
    ui(new Ui::CategoryItem)
{
    ui->setupUi(this);
    ui->idLabel->setText(QString::number(id));
    ui->nameLabel->setText(name);
    ui->slugLabel->setText(slug);
    categoryId = id;
}

CategoryItem::~CategoryItem()
{
    delete ui;
}

void CategoryItem::on_viewButton_clicked()
{
    emit viewButton_clicked(categoryId);
}

void CategoryItem::on_deleteButton_clicked()
{
    emit deleteButton_clicked();
}
