#ifndef CLERKWIDGET_H
#define CLERKWIDGET_H

#include <QWidget>
#include "clerk.h"

namespace Ui {
class ClerkWidget;
}

class ClerkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClerkWidget(QWidget *parent = nullptr);
    ~ClerkWidget();
    void SetUserId(int user_id);

private:
    Ui::ClerkWidget *ui;
    Clerk m_clerk;
    int m_iUserId;
};

#endif // CLERKWIDGET_H
