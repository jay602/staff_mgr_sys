#include "clerkwidget.h"
#include "ui_clerkwidget.h"
#include "sqlserver.h"

ClerkWidget::ClerkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClerkWidget)
{
    ui->setupUi(this);
}

ClerkWidget::~ClerkWidget()
{
    delete ui;
}

void ClerkWidget::SetUserId(int user_id)
{
    m_iUserId = user_id;
    SqlServerInstance::GetRef().queryClerkInfoByUserId(user_id, m_clerk);
}
