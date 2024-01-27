#include "clerkwidget.h"
#include "ui_clerkwidget.h"
//#include "dbghelp.h"

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
 //   DBHelperInstance::GetRef().QueryClerkInfoByUserId(user_id, m_clerk);
}
