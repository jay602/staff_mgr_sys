#include "addclerkdialog.h"
#include "ui_addclerkdialog.h"

AddClerkDialog::AddClerkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClerkDialog)
{
    ui->setupUi(this);
}

AddClerkDialog::~AddClerkDialog()
{
    delete ui;
}
