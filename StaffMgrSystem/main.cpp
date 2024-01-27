#include "mainwindow.h"
#include "uilog.h"
#include "logindialog.h"
#include "mainwidget.h"
#include "clerkwidget.h"
#include "globle.h"

#include <QApplication>
#include <QTextCodec>

static UiLog g_log("../log/", "log.txt", "0.0.1");

void messageOutput(QtMsgType msgType, const QMessageLogContext &context, const QString &msg)
{
    g_log.WriteLog(msgType, msg.toStdString().c_str());
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    qInstallMessageHandler(messageOutput);
    LoginDialog dialog;
    MainWidget w;
    ClerkWidget cw;
    if (dialog.exec() == QDialog::Accepted)
    {
        if(g_is_admin)
        {
            w.show();
        }
        else
        {
            cw.SetUserId(g_user_id);
            cw.show();
        }

    }
    return a.exec();
}
