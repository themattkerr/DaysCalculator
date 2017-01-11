#ifndef CONTINGENCYDATA_H
#define CONTINGENCYDATA_H

#include <QDate>
#include <QString>
#include <QTime>

enum CalculateFrom {

    HARD_DATE           = 0,
    CALC_FROM_AO        = 1,
    CALC_FROM_CLOSING   = 2,

};

class ContingencyData
{
public:
    ContingencyData() {}

    ~ContingencyData(){}

    void enterDate(QDate dInputDate);
    void enterDays(int nDays);
    void setCalcType(int nCalcType);

    void enterDateOfContingency(QDate dtDateOfContingency);
    void enterTimeOfDay(QTime TimeOfDay);
    void enterReportInfo(QString strReportInfo);
    void enterAODate(QDate dtAODate);
    void enterClosingDate(QDate dtClosingDate);

    void refreshData();

private:

    QDate m_dtAODate;
    QDate m_dtClosingDate;
    QDate m_dtDateOfContingency;
    QTime m_tTimeOfDay;
    QString m_strReportInfo;

    int m_nCalcType;

};

#endif // CONTINGENCYDATA_H
