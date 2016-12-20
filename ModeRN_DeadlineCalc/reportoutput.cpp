#include "reportoutput.h"
#include "ui_reportoutput.h"

ReportOutput::ReportOutput(QWidget *parent, QString Contingencies) :
    QDialog(parent),
    ui(new Ui::ReportOutput)
{
    ui->setupUi(this);

    ui->textBrowser->setText(Contingencies);
}

ReportOutput::~ReportOutput()
{
    delete ui;
}

void ReportOutput::on_pushButton_Close_clicked()
{
    this->close();
}
