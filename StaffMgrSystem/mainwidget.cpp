#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("职工信息管理");
    ui->widget->setFixedWidth(250);
    this->setMinimumSize(1550, 800);
    initClerkTableview();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initClerkTableview()
{
    ui->tableViewClerk->resizeRowsToContents();
    ui->tableViewClerk->verticalHeader()->setHidden(true);
    ui->tableViewClerk->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableViewClerk->setSelectionMode(QAbstractItemView::SingleSelection);

    m_pClerkQuery = new ClerkSqlQueryModel(this);
    m_pClerkQuery->select();

   //设置模型
   ui->tableViewClerk->setModel(m_pClerkQuery);
}
