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

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonEdit_clicked();

private:
    Ui::ClerkWidget *ui;
    Clerk m_clerk;
    int m_iUserId;
    bool m_isEdited = false;
};

#endif // CLERKWIDGET_H
