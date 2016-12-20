#ifndef REPORTOUTPUT_H
#define REPORTOUTPUT_H

#include <QDialog>
#include <QString>

namespace Ui {
class ReportOutput;
}

class ReportOutput : public QDialog
{
    Q_OBJECT

public:
    explicit ReportOutput(QWidget *parent = 0, QString Contingencies = 0);
    ~ReportOutput();

private slots:
    void on_pushButton_Close_clicked();

private:
    Ui::ReportOutput *ui;
};

#endif // REPORTOUTPUT_H
