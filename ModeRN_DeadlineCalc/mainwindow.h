#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QString>
#include <QFile>
#include <QDataStream>
#include "contingencydata.h"

#define CURRENT_VERSION "1.2.0"
#define LONG_DATE_FORMAT "ddd MMMM d, yyyy"
#define FROM_CLOSING_MESSAGE "From Closing"
#define FROM_AO_MESSAGE ""
#define MAX_NUM_CONTINGENCIES 11

struct sData{
    QDate dtOfContingency;
    QString strReportInfo;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:

    void on_calendarWidget_clicked(const QDate &date);

    void on_dateEdit_AcceptedOffer_userDateChanged(const QDate &date);

    void on_spinBox_NumOfDays_valueChanged(int arg1);
    void on_daysForEarnestMoney_spinBox_valueChanged(int arg1);
    void on_daysForInspection_spinBox_valueChanged(int arg1);
    void on_daysForAppraisal_spinBox_valueChanged(int arg1);
    void on_daysForFinaincing_spinBox_valueChanged(int arg1);
    void on_spinBox_DaysCust1_valueChanged(int arg1);
    void on_spinBox_DaysCust2_valueChanged(int arg1);
    void on_spinBox_DaysCust3_valueChanged(int arg1);
    void on_spinBox_DaysCust4_valueChanged(int arg1);
    void on_spinBox_DaysCust5_valueChanged(int arg1);


    void on_dateEdit_CalculatedDate_dateChanged(const QDate &date);
    void on_earnestMoney_dateEdit_dateChanged(const QDate &date);
    void on_inspection_dateEdit_dateChanged(const QDate &date);
    void on_appraisal_dateEdit_dateChanged(const QDate &date);
    void on_financing_dateEdit_dateChanged(const QDate &date);
    void on_custom1_dateEdit_dateChanged(const QDate &date);
    void on_custom2_dateEdit_dateChanged(const QDate &date);
    void on_custom3_dateEdit_dateChanged(const QDate &date);
    void on_custom4_dateEdit_dateChanged(const QDate &date);
    void on_custom5_dateEdit_dateChanged(const QDate &date);


    void on_checkBox_1_clicked();
    void on_checkBox_2_clicked();
    void on_checkBox_3_clicked();
    void on_checkBox_4_clicked();
    void on_checkBox_5_clicked();

    void on_pushButton_MakeAOToday_clicked();
    void on_pushButton_ShowMore_clicked();
    void on_pushButton_ShowLess_clicked();
    void on_pushButton_ResetDefaults_clicked();

    void on_pushButton_Generat_Report_clicked();

    void on_comboBox_Custom1_currentIndexChanged(const QString &arg1);
    void on_actionSave_File_triggered();
    void on_actionOpen_File_triggered();

    void on_lineEdit_Address_editingFinished();
    void on_lineEdit_Earnest_Money_Amount_editingFinished();
    void on_lineEdit_Listing_Trust_editingFinished();
    void on_spinBox_DaysCust1_valueChanged(const QString &arg1);

private:

    Ui::MainWindow *ui;

    QString m_strFileName;
    QString m_strVerNum = CURRENT_VERSION;

    QString m_strPropertyAddress;
    QString m_strListingFirmTrustName;
    QString m_strEarnestMoneyAmount;

    bool m_bUnsavedData;
    int m_nNumOfContingencies;

    QDate   m_dtAcceptedOffer,
            m_dtClosingDate,
            m_dtEarnestMoney_date,
            m_dtInspection_date,
            m_dtAppraisal_date,
            m_dtFinancing_date,
            m_dtCustom1,
            m_dtCustom2,
            m_dtCustom3,
            m_dtCustom4,
            m_dtCustom5;

    int m_nDaysToClosing,
        m_nDaysForEarnestMoney,
        m_nDaysForInspection,
        m_nDaysForAppraisal,
        m_nDaysForFinaincing,
        m_nDaysCustom1,
        m_nDaysCustom2,
        m_nDaysCustom3,
        m_nDaysCustom4,
        m_nDaysCustom5;

    bool    m_bCust1FromClosing,
            m_bCust2FromClosing,
            m_bCust3FromClosing,
            m_bCust4FromClosing,
            m_bCust5FromClosing;

    sData m_sContingencySorting[MAX_NUM_CONTINGENCIES];

    void unsavedDataPresent();
    void noUnsavedDataPresent();
    void setupCustomComboBoxes();
    void setDefaults();
    void refreshfields();
    void calculateDays();
    void calculateDates();

    void hideMoreInfo();
    void showMoreInfo();
    QString getContingencyText(QString comboText);
    void strSort();

    QString getOrderedContingencies();
    bool saveAsContingencyFile();
    bool readContingencyFile();
    void setCheckBoxes();
    void saveCheckBoxes();
   // void setDayFieldsToMembers();
};


#endif // MAINWINDOW_H
