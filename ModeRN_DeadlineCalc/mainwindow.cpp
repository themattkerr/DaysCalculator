#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reportoutput.h"
#include "textforcontingencies.h"
#include <QDate>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <qfiledialog.h>
#include <QDataStream>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupCustomComboBoxes();
    hideMoreInfo();
    setDefaults();

    ui->dateEdit_AcceptedOffer->setDate(m_dtAcceptedOffer);


}

MainWindow::~MainWindow()
{
    if(m_bUnsavedData)
    {
        QMessageBox UnsavedWarning;
        UnsavedWarning.setText("Warning!!! There is unsaved data present!");
        UnsavedWarning.exec();
        on_actionSave_File_triggered();
    }
    delete ui;

}



void MainWindow::on_calendarWidget_clicked(const QDate &date)
{

    m_dtAcceptedOffer = date;
    refreshfields();


}

void MainWindow::on_dateEdit_AcceptedOffer_userDateChanged(const QDate &date)
{

    m_dtAcceptedOffer = date;
    calculateDates();
    calculateDays();
    refreshfields();


}

void MainWindow::on_spinBox_NumOfDays_valueChanged(int arg1)
{
    m_dtClosingDate = m_dtAcceptedOffer.addDays(arg1);
    refreshfields();


}
void MainWindow::on_dateEdit_CalculatedDate_dateChanged(const QDate &date)
{
    m_dtClosingDate = date;
    refreshfields();

}



void MainWindow::on_daysForEarnestMoney_spinBox_valueChanged(int arg1)
{
    m_dtEarnestMoney_date = m_dtAcceptedOffer.addDays(arg1);
    refreshfields();

}
void MainWindow::on_daysForInspection_spinBox_valueChanged(int arg1)
{
    m_dtInspection_date = m_dtAcceptedOffer.addDays(arg1);
    refreshfields();

}

void MainWindow::on_earnestMoney_dateEdit_dateChanged(const QDate &date)
{
    m_dtEarnestMoney_date = date;
    refreshfields();

}



void MainWindow::on_inspection_dateEdit_dateChanged(const QDate &date)
{
    m_dtInspection_date = date;
    refreshfields();

}

void MainWindow::on_daysForAppraisal_spinBox_valueChanged(int arg1)
{
    m_dtAppraisal_date = m_dtAcceptedOffer.addDays(arg1);
    refreshfields();
}

void MainWindow::on_appraisal_dateEdit_dateChanged(const QDate &date)
{
    m_dtAppraisal_date = date;
    refreshfields();
}

void MainWindow::on_daysForFinaincing_spinBox_valueChanged(int arg1)
{
    m_dtFinancing_date = m_dtAcceptedOffer.addDays(arg1);
    refreshfields();
}

void MainWindow::on_financing_dateEdit_dateChanged(const QDate &date)
{
    m_dtFinancing_date = date;
    refreshfields();
}



void MainWindow::refreshfields()
{
    unsavedDataPresent ();
    saveCheckBoxes();
    calculateDays();


    ui->lineEdit_Address->setText(m_strPropertyAddress );
    ui->lineEdit_Earnest_Money_Amount->setText(m_strEarnestMoneyAmount);
    ui->lineEdit_Listing_Trust->setText(m_strListingFirmTrustName);


    ui->dateEdit_AcceptedOffer->setDate(m_dtAcceptedOffer);

    ui->spinBox_NumOfDays->setValue(m_nDaysToClosing);
    ui->daysForEarnestMoney_spinBox->setValue(m_nDaysForEarnestMoney);
    ui->daysForInspection_spinBox->setValue(m_nDaysForInspection);
    ui->daysForAppraisal_spinBox->setValue(m_nDaysForAppraisal);
    ui->daysForFinaincing_spinBox->setValue(m_nDaysForFinaincing);
    ui->spinBox_DaysCust1->setValue(m_nDaysCustom1);
    ui->spinBox_DaysCust2->setValue(m_nDaysCustom2);
    ui->spinBox_DaysCust3->setValue(m_nDaysCustom3);
    ui->spinBox_DaysCust4->setValue(m_nDaysCustom4);
    ui->spinBox_DaysCust5->setValue(m_nDaysCustom5);

    ui->dateEdit_CalculatedDate->setDate(m_dtClosingDate);
    ui->earnestMoney_dateEdit->setDate(m_dtEarnestMoney_date);
    ui->inspection_dateEdit->setDate(m_dtInspection_date);
    ui->appraisal_dateEdit->setDate(m_dtAppraisal_date);
    ui->financing_dateEdit->setDate(m_dtFinancing_date);
    ui->custom1_dateEdit->setDate(m_dtCustom1);
    ui->custom2_dateEdit->setDate(m_dtCustom2);
    ui->custom3_dateEdit->setDate(m_dtCustom3);
    ui->custom4_dateEdit->setDate(m_dtCustom4);
    ui->custom5_dateEdit->setDate(m_dtCustom5);

    ui->label_LongClosingDate->setText(m_dtClosingDate.toString(LONG_DATE_FORMAT));
    ui->label_LongEMoneyDate ->setText(m_dtEarnestMoney_date .toString(LONG_DATE_FORMAT));
    ui->label_LongInspDate->setText(m_dtInspection_date.toString(LONG_DATE_FORMAT ) );
    ui->label_LongAppraisalDate ->setText(m_dtAppraisal_date .toString(LONG_DATE_FORMAT));
    ui->label_LongFinancingDate ->setText(m_dtFinancing_date .toString(LONG_DATE_FORMAT));
    ui->label_LongDateCust1->setText(m_dtCustom1.toString(LONG_DATE_FORMAT));
    ui->label_LongDateCust2->setText(m_dtCustom2.toString(LONG_DATE_FORMAT));
    ui->label_LongDateCust3->setText(m_dtCustom3.toString(LONG_DATE_FORMAT));
    ui->label_LongDateCust4->setText(m_dtCustom4.toString(LONG_DATE_FORMAT));
    ui->label_LongDateCust5->setText(m_dtCustom5.toString(LONG_DATE_FORMAT));

    if(ui->checkBox_1->isChecked())     {ui->checkBox_1->setText(FROM_CLOSING_MESSAGE);}
    else                                {ui->checkBox_1->setText(FROM_AO_MESSAGE);}
    if(ui->checkBox_2->isChecked())     {ui->checkBox_2->setText(FROM_CLOSING_MESSAGE);}
    else                                {ui->checkBox_2->setText(FROM_AO_MESSAGE);}
    if(ui->checkBox_3->isChecked())     {ui->checkBox_3->setText(FROM_CLOSING_MESSAGE);}
    else                                {ui->checkBox_3->setText(FROM_AO_MESSAGE);}
    if(ui->checkBox_4->isChecked())     {ui->checkBox_4->setText(FROM_CLOSING_MESSAGE);}
    else                                {ui->checkBox_4->setText(FROM_AO_MESSAGE);}
    if(ui->checkBox_5->isChecked())     {ui->checkBox_5->setText(FROM_CLOSING_MESSAGE);}
    else                                {ui->checkBox_5->setText(FROM_AO_MESSAGE);}

    ui->calendarWidget->setDateRange(m_dtAcceptedOffer,m_dtClosingDate);
}

void MainWindow::setDefaults()
{

    m_bUnsavedData = false;
    m_dtAcceptedOffer = QDate::currentDate();

        int nDefaultDaysToClosing = 60;
        int nDefaultDaysEarnestDays = 5;
        int nDefaultDaysForInspection = 14;
        int nDefaultDaysForAppraisal = 30;
        int nDefaultDaysForFinaincing = 45;
        int nDefaultDaysForCustom = 0;

        sData sTemp;
        sTemp.dtOfContingency = QDate::currentDate();
        sTemp.strReportInfo = "";
        m_nNumOfContingencies =0;

        for(int zzz = 0;zzz < MAX_NUM_CONTINGENCIES;zzz++)
            m_sContingencySorting[zzz] = sTemp;

        m_strPropertyAddress = "";
        m_strListingFirmTrustName = "";
        m_strEarnestMoneyAmount = "$ ";

        m_dtClosingDate = m_dtAcceptedOffer.addDays(nDefaultDaysToClosing);
        m_dtEarnestMoney_date = m_dtAcceptedOffer.addDays(nDefaultDaysEarnestDays);
        m_dtInspection_date = m_dtAcceptedOffer.addDays(nDefaultDaysForInspection);
        m_dtAppraisal_date = m_dtAcceptedOffer.addDays(nDefaultDaysForAppraisal);
        m_dtFinancing_date = m_dtAcceptedOffer.addDays(nDefaultDaysForFinaincing);

        m_dtCustom1 = m_dtAcceptedOffer.addDays(nDefaultDaysForCustom);
        m_dtCustom2 = m_dtAcceptedOffer.addDays(nDefaultDaysForCustom);
        m_dtCustom3 = m_dtAcceptedOffer.addDays(nDefaultDaysForCustom);
        m_dtCustom4 = m_dtAcceptedOffer.addDays(nDefaultDaysForCustom);
        m_dtCustom5 = m_dtAcceptedOffer.addDays(nDefaultDaysForCustom);

        ui->comboBox_Custom1->setCurrentText(BLANK);
        ui->comboBox_Custom2->setCurrentText(BLANK);
        ui->comboBox_Custom3->setCurrentText(BLANK);
        ui->comboBox_Custom4->setCurrentText(BLANK);

        ui->lineEdit_Custom5->setText("");

        ui->checkBox_1->setChecked(false);
        ui->checkBox_2->setChecked(false);
        ui->checkBox_3->setChecked(false);
        ui->checkBox_4->setChecked(false);
        ui->checkBox_5->setChecked(false);

        calculateDays();
        refreshfields();
}

void MainWindow::calculateDays()
{
    m_nDaysToClosing = m_dtAcceptedOffer.daysTo(m_dtClosingDate);
    m_nDaysForEarnestMoney = m_dtAcceptedOffer.daysTo(m_dtEarnestMoney_date);
    m_nDaysForInspection = m_dtAcceptedOffer.daysTo(m_dtInspection_date);
    m_nDaysForAppraisal = m_dtAcceptedOffer.daysTo(m_dtAppraisal_date);
    m_nDaysForFinaincing = m_dtAcceptedOffer.daysTo(m_dtFinancing_date);

    if(!(ui->checkBox_1->isChecked()))
        m_nDaysCustom1 = m_dtAcceptedOffer.daysTo(m_dtCustom1);
    else
    {
        //m_nDaysCustom1 = ui->spinBox_DaysCust1->value();
        m_dtCustom1 = m_dtClosingDate.addDays(m_nDaysCustom1);
    }

    if(!(ui->checkBox_2->isChecked()))
        m_nDaysCustom2 = m_dtAcceptedOffer.daysTo(m_dtCustom2);
    else
    {
        //m_nDaysCustom2 = ui->spinBox_DaysCust2->value();
        m_dtCustom2 = m_dtClosingDate.addDays(m_nDaysCustom2);
    }

    if(!(ui->checkBox_3->isChecked()))
        m_nDaysCustom3 = m_dtAcceptedOffer.daysTo(m_dtCustom3);
    else
    {
        //m_nDaysCustom3 = ui->spinBox_DaysCust3->value();
        m_dtCustom3 = m_dtClosingDate.addDays(m_nDaysCustom3);
    }

    if(!(ui->checkBox_4->isChecked()))
        m_nDaysCustom4 = m_dtAcceptedOffer.daysTo(m_dtCustom4);
    else
    {
        //m_nDaysCustom4 = ui->spinBox_DaysCust4->value();
        m_dtCustom4 = m_dtClosingDate.addDays(m_nDaysCustom4);
    }

    if(!(ui->checkBox_5->isChecked()))
        m_nDaysCustom5 = m_dtAcceptedOffer.daysTo(m_dtCustom5);
    else
    {
        //m_nDaysCustom5 = ui->spinBox_DaysCust5->value();
        m_dtCustom5 = m_dtClosingDate.addDays(m_nDaysCustom5);
    }

}

void MainWindow::calculateDates()
{
    //m_dtClosingDate = m_dtAcceptedOffer.addDays(m_nDaysToClosing);
    m_dtEarnestMoney_date = m_dtAcceptedOffer.addDays(m_nDaysForEarnestMoney);
    m_dtInspection_date = m_dtAcceptedOffer.addDays(m_nDaysForInspection);
    m_dtAppraisal_date = m_dtAcceptedOffer.addDays(m_nDaysForAppraisal);
    m_dtFinancing_date = m_dtAcceptedOffer.addDays(m_nDaysForFinaincing);

    if(!(ui->checkBox_1->isChecked()))
        m_dtCustom1 = m_dtAcceptedOffer.addDays(m_nDaysCustom1);
    else
        m_dtCustom1 = m_dtClosingDate.addDays(m_nDaysCustom1);

    if(!(ui->checkBox_2->isChecked()))
        m_dtCustom2 = m_dtAcceptedOffer.addDays(m_nDaysCustom2);
    else
        m_dtCustom2 = m_dtClosingDate.addDays(m_nDaysCustom2);

    if(!(ui->checkBox_3->isChecked()))
        m_dtCustom3 = m_dtAcceptedOffer.addDays(m_nDaysCustom3);
    else
        m_dtCustom3 = m_dtClosingDate.addDays(m_nDaysCustom3);

    if(!(ui->checkBox_4->isChecked()))
        m_dtCustom4 = m_dtAcceptedOffer.addDays(m_nDaysCustom4);
    else
        m_dtCustom4 = m_dtClosingDate.addDays(m_nDaysCustom4);

    if(!(ui->checkBox_5->isChecked()))
        m_dtCustom5 = m_dtAcceptedOffer.addDays(m_nDaysCustom5);
    else
        m_dtCustom5 = m_dtClosingDate.addDays(m_nDaysCustom5);
}

void MainWindow::on_pushButton_MakeAOToday_clicked()
{
   m_dtAcceptedOffer = QDate::currentDate();
   refreshfields();

}


void MainWindow::on_pushButton_ShowMore_clicked()
{
    showMoreInfo();
}

void MainWindow::on_pushButton_ShowLess_clicked()
{
    hideMoreInfo();

}

void MainWindow::hideMoreInfo()
{
    ui->pushButton_ShowLess->hide();
    ui->label_AOorClosing->hide();

    ui->label_LongDateCust1->hide();
    ui->label_LongDateCust2->hide();
    ui->label_LongDateCust3->hide();
    ui->label_LongDateCust4->hide();
    ui->label_LongDateCust5->hide();

    ui->label_CustomDate->hide();
    ui->custom1_dateEdit->hide();
    ui->custom2_dateEdit->hide();
    ui->custom3_dateEdit->hide();
    ui->custom4_dateEdit->hide();
    ui->custom5_dateEdit->hide();

    ui->label_CustomDays->hide();
    ui->spinBox_DaysCust1->hide();
    ui->spinBox_DaysCust2->hide();
    ui->spinBox_DaysCust3->hide();
    ui->spinBox_DaysCust4->hide();
    ui->spinBox_DaysCust5->hide();

    ui->label_CustomDescription->hide();
    ui->comboBox_Custom1->hide();
    ui->comboBox_Custom2->hide();
    ui->comboBox_Custom3->hide();
    ui->comboBox_Custom4->hide();

    //ui->lineEdit_Custom1->hide();
    //ui->lineEdit_Custom2->hide();
    //ui->lineEdit_Custom3->hide();
    //ui->lineEdit_Custom4->hide();
    ui->lineEdit_Custom5->hide();

    ui->checkBox_1->hide();
    ui->checkBox_2->hide();
    ui->checkBox_3->hide();
    ui->checkBox_4->hide();
    ui->checkBox_5->hide();

    ui->label_Blank->hide();

    ui->pushButton_ShowMore->show();

}

void MainWindow::showMoreInfo()
{

    ui->pushButton_ShowLess->show();
    ui->label_AOorClosing->show();

    ui->label_LongDateCust1->show();
    ui->label_LongDateCust2->show();
    ui->label_LongDateCust3->show();
    ui->label_LongDateCust4->show();
    ui->label_LongDateCust5->show();

    ui->label_CustomDate->show();
    ui->custom1_dateEdit->show();
    ui->custom2_dateEdit->show();
    ui->custom3_dateEdit->show();
    ui->custom4_dateEdit->show();
    ui->custom5_dateEdit->show();

    ui->label_CustomDays->show();
    ui->spinBox_DaysCust1->show();
    ui->spinBox_DaysCust2->show();
    ui->spinBox_DaysCust3->show();
    ui->spinBox_DaysCust4->show();
    ui->spinBox_DaysCust5->show();

    ui->label_CustomDescription->show();
    ui->comboBox_Custom1->show();
    ui->comboBox_Custom2->show();
    ui->comboBox_Custom3->show();
    ui->comboBox_Custom4->show();


    //ui->lineEdit_Custom1->show();
    //ui->lineEdit_Custom2->show();
    //ui->lineEdit_Custom3->show();
    //ui->lineEdit_Custom4->show();
    ui->lineEdit_Custom5->show();

    ui->checkBox_1->show();
    ui->checkBox_2->show();
    ui->checkBox_3->show();
    ui->checkBox_4->show();
    ui->checkBox_5->show();

    ui->label_Blank->show();

    ui->pushButton_ShowMore->hide();

}

void MainWindow::on_checkBox_1_clicked()
{
    if(ui->checkBox_1->isChecked())
    {
       // ui->checkBox_1->setText(FROM_CLOSING_MESSAGE);
    }
    else
    {
        //ui->checkBox_1->setText(FROM_AO_MESSAGE);
        m_dtCustom1 = m_dtAcceptedOffer.addDays(ui->spinBox_DaysCust1->value());
    }
    refreshfields();
}

void MainWindow::on_spinBox_DaysCust1_valueChanged(int arg1)
{
    m_nDaysCustom1 = arg1;
    if(ui->checkBox_1->isChecked())
        m_dtCustom1 = m_dtClosingDate.addDays(arg1);
    else  m_dtCustom1 = m_dtAcceptedOffer.addDays(arg1);
    refreshfields();
}

void MainWindow::on_custom1_dateEdit_dateChanged(const QDate &date)
{
    m_dtCustom1 = date;
    refreshfields();
}



void MainWindow::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked())
    {}//ui->checkBox_2->setText(FROM_CLOSING_MESSAGE);
    else
    {
        //ui->checkBox_2->setText(FROM_AO_MESSAGE);
        m_dtCustom2 = m_dtAcceptedOffer.addDays(ui->spinBox_DaysCust2->value());
    }
    refreshfields();
}

void MainWindow::on_spinBox_DaysCust2_valueChanged(int arg1)
{
    m_nDaysCustom2 = arg1;
    if(ui->checkBox_2->isChecked())
        m_dtCustom2 = m_dtClosingDate.addDays(arg1);
    else  m_dtCustom2 = m_dtAcceptedOffer.addDays(arg1);
    refreshfields();
}

void MainWindow::on_custom2_dateEdit_dateChanged(const QDate &date)
{
    m_dtCustom2 = date;
    refreshfields();
}


void MainWindow::on_checkBox_3_clicked()
{
    if(ui->checkBox_3->isChecked())
    {}//ui->checkBox_3->setText(FROM_CLOSING_MESSAGE);
    else
    {
        //ui->checkBox_3->setText(FROM_AO_MESSAGE);
        m_dtCustom3 = m_dtAcceptedOffer.addDays(ui->spinBox_DaysCust3->value());
    }
    refreshfields();
}

void MainWindow::on_spinBox_DaysCust3_valueChanged(int arg1)
{
    m_nDaysCustom3 = arg1;
    if(ui->checkBox_3->isChecked())
        m_dtCustom3 = m_dtClosingDate.addDays(arg1);
    else  m_dtCustom3 = m_dtAcceptedOffer.addDays(arg1);
    refreshfields();
}

void MainWindow::on_custom3_dateEdit_dateChanged(const QDate &date)
{
    m_dtCustom3 = date;
    refreshfields();
}

void MainWindow::on_checkBox_4_clicked()
{
    if(ui->checkBox_4->isChecked())
    {}//ui->checkBox_4->setText(FROM_CLOSING_MESSAGE);
    else
    {
        //ui->checkBox_4->setText(FROM_AO_MESSAGE);
        m_dtCustom4 = m_dtAcceptedOffer.addDays(ui->spinBox_DaysCust4->value());
    }
    refreshfields();
}

void MainWindow::on_spinBox_DaysCust4_valueChanged(int arg1)
{
    m_nDaysCustom4 = arg1;
    if(ui->checkBox_4->isChecked())
        m_dtCustom4 = m_dtClosingDate.addDays(arg1);
    else  m_dtCustom4 = m_dtAcceptedOffer.addDays(arg1);
    refreshfields();
}

void MainWindow::on_custom4_dateEdit_dateChanged(const QDate &date)
{
    m_dtCustom4 = date;
    refreshfields();
}

void MainWindow::on_checkBox_5_clicked()
{

    if(ui->checkBox_5->isChecked())
    {}//ui->checkBox_5->setText(FROM_CLOSING_MESSAGE);
    else
    {
        //ui->checkBox_5->setText(FROM_AO_MESSAGE);
        m_dtCustom5 = m_dtAcceptedOffer.addDays(ui->spinBox_DaysCust5->value());
    }
    refreshfields();
}

void MainWindow::on_spinBox_DaysCust5_valueChanged(int arg1)
{
    m_nDaysCustom5 = arg1;
    if(ui->checkBox_5->isChecked())
        m_dtCustom5 = m_dtClosingDate.addDays(arg1);
    else  m_dtCustom5 = m_dtAcceptedOffer.addDays(arg1);
    refreshfields();
}

void MainWindow::on_custom5_dateEdit_dateChanged(const QDate &date)
{
    m_dtCustom5 = date;
    refreshfields();
}

void MainWindow::on_pushButton_ResetDefaults_clicked()
{
    setDefaults();
    refreshfields();
}

void MainWindow::on_pushButton_Generat_Report_clicked()
{
    QString strHeadings;
    QString strContingencyReport;
    m_nNumOfContingencies = 5;

    strHeadings.append("Offer milestones:\t").append(m_strPropertyAddress).append("\n");

    strHeadings.append("Date of the accepted offer:\t\t").append(m_dtAcceptedOffer.toString(LONG_DATE_FORMAT) ).append("\n");
    strHeadings.append("Date of the closing is currently:\t").append(m_dtClosingDate.toString(LONG_DATE_FORMAT) ).append("\n\n");

    strContingencyReport.append("Closing\n").append(m_dtClosingDate.toString(LONG_DATE_FORMAT)).append(" (").append(QString::number(m_nDaysToClosing)).append(" days from acceptance)").append("\n").append(CLOSING).append("\n\n");
    m_sContingencySorting[1].strReportInfo = strContingencyReport;
    m_sContingencySorting[1].dtOfContingency = m_dtClosingDate;
    strContingencyReport.clear();

   m_sContingencySorting[2].strReportInfo = strContingencyReport.append("Earnest Money\nDue: ")
           .append(m_dtEarnestMoney_date.toString(LONG_DATE_FORMAT))
           .append(" (").append(QString::number(m_nDaysForEarnestMoney))
           .append(" days from acceptance)").append("\n").append(EARNEST_MONEY1).append(m_strListingFirmTrustName).append(EARNEST_MONEY2).append(m_strEarnestMoneyAmount ).append(EARNEST_MONEY3).append("\n\n");
   m_sContingencySorting[2].dtOfContingency = m_dtEarnestMoney_date;
   strContingencyReport.clear();

   m_sContingencySorting[3].strReportInfo = strContingencyReport.append("Inspection Contingency\nDue: ").append(m_dtInspection_date.toString(LONG_DATE_FORMAT)).append(" (").append(QString::number(m_nDaysForInspection)).append(" days from acceptance)").append("\n").append(INSPECTION).append("\n\n");
   m_sContingencySorting[3].dtOfContingency = m_dtInspection_date;
   strContingencyReport.clear();

   m_sContingencySorting[4].strReportInfo = strContingencyReport.append("Appraisal Contingency\nDue: ").append(m_dtAppraisal_date.toString(LONG_DATE_FORMAT)).append(" (").append(QString::number(m_nDaysForAppraisal)).append(" days from acceptance)").append("\n").append(APPRAISAL).append("\n\n");
   m_sContingencySorting[4].dtOfContingency = m_dtAppraisal_date;
   strContingencyReport.clear();

   m_sContingencySorting[5].strReportInfo = strContingencyReport.append("Financing Contingency\nDue: ").append(m_dtFinancing_date.toString(LONG_DATE_FORMAT)).append(" (").append(QString::number(m_nDaysForFinaincing)).append(" days from acceptance)").append("\n").append(FINANCING).append("\n\n");
   m_sContingencySorting[5].dtOfContingency = m_dtFinancing_date;
   strContingencyReport.clear();

   if((ui->comboBox_Custom1->currentText()) != BLANK )
    {
       m_nNumOfContingencies++;
       strContingencyReport.append(ui->comboBox_Custom1->currentText()).append("\nDue: ").append(m_dtCustom1.toString(LONG_DATE_FORMAT)).append(" (").append(QString::number(m_nDaysCustom1));
        if(ui->checkBox_1->isChecked())
            strContingencyReport.append(" days from closing)");
        else
            strContingencyReport.append(" days from acceptance)");
        strContingencyReport.append("\n");
        strContingencyReport.append(getContingencyText(ui->comboBox_Custom1->currentText())).append("\n\n");

        m_sContingencySorting[m_nNumOfContingencies].strReportInfo = strContingencyReport;
        m_sContingencySorting[m_nNumOfContingencies].dtOfContingency = m_dtCustom1;
        strContingencyReport.clear();
    }


    if((ui->comboBox_Custom2->currentText()) != BLANK )
    {
        m_nNumOfContingencies++;
        strContingencyReport.append(ui->comboBox_Custom2->currentText()).append("\nDue: ").append(m_dtCustom2.toString(LONG_DATE_FORMAT)).append(" (").append(QString::number(m_nDaysCustom2));
        if(ui->checkBox_2->isChecked())
            strContingencyReport.append(" days from closing)");
        else
            strContingencyReport.append(" days from acceptance)");
        strContingencyReport.append("\n");
        strContingencyReport.append(getContingencyText(ui->comboBox_Custom2->currentText())).append("\n\n");

        m_sContingencySorting[m_nNumOfContingencies].strReportInfo = strContingencyReport;
        m_sContingencySorting[m_nNumOfContingencies].dtOfContingency = m_dtCustom2;
        strContingencyReport.clear();
    }

    if((ui->comboBox_Custom3->currentText()) != BLANK )
    {
        m_nNumOfContingencies++;
        strContingencyReport.append(ui->comboBox_Custom3->currentText()).append("\nDue: ").append(m_dtCustom3.toString(LONG_DATE_FORMAT)).append(" (").append(QString::number(m_nDaysCustom3));
        if(ui->checkBox_3->isChecked())
            strContingencyReport.append(" days from closing)");
        else
            strContingencyReport.append(" days from acceptance)");
        strContingencyReport.append("\n");
        strContingencyReport.append(getContingencyText(ui->comboBox_Custom3->currentText())).append("\n\n");
        m_sContingencySorting[m_nNumOfContingencies].strReportInfo = strContingencyReport;
        m_sContingencySorting[m_nNumOfContingencies].dtOfContingency = m_dtCustom3;
        strContingencyReport.clear();
    }

    if((ui->comboBox_Custom4->currentText()) != BLANK )
    {
        m_nNumOfContingencies++;
        strContingencyReport.append(ui->comboBox_Custom4->currentText()).append("\nDue: ").append(m_dtCustom4.toString(LONG_DATE_FORMAT)).append(" (").append(QString::number(m_nDaysCustom4));
        if(ui->checkBox_4->isChecked())
            strContingencyReport.append(" days from closing)");
        else
            strContingencyReport.append(" days from acceptance)");
        strContingencyReport.append("\n");
        strContingencyReport.append(getContingencyText(ui->comboBox_Custom4->currentText())).append("\n\n");
        m_sContingencySorting[m_nNumOfContingencies].strReportInfo = strContingencyReport;
        m_sContingencySorting[m_nNumOfContingencies].dtOfContingency = m_dtCustom4;
        strContingencyReport.clear();
    }
    if(ui->lineEdit_Custom5->text() != "")
    {
        m_nNumOfContingencies++;
        strContingencyReport.append(ui->lineEdit_Custom5->text()).append("\nDue: ").append(m_dtCustom5.toString(LONG_DATE_FORMAT)).append(" (").append(QString::number(m_nDaysCustom5));
        if(ui->checkBox_5->isChecked())
            strContingencyReport.append(" days from closing)");
        else
            strContingencyReport.append(" days from acceptance)");
        strContingencyReport.append("\n");
        strContingencyReport.append("\n\n");
        m_sContingencySorting[m_nNumOfContingencies].strReportInfo = strContingencyReport;
        m_sContingencySorting[m_nNumOfContingencies].dtOfContingency = m_dtCustom5;
        strContingencyReport.clear();
    }


    strSort();
    strContingencyReport.append(strHeadings);
    strContingencyReport.append(getOrderedContingencies());
    ReportOutput *report = new ReportOutput (this, strContingencyReport);
    report->show();
}

void MainWindow::strSort()
{
    sData copy [1];

    for(int iii=1;iii <= m_nNumOfContingencies; iii++)
    {
        for (int jjj = 1 ;jjj <= m_nNumOfContingencies; jjj++)
        {
            if ((m_sContingencySorting[iii].dtOfContingency <= m_sContingencySorting[jjj].dtOfContingency ))
            {
                copy[0] = m_sContingencySorting[iii];
                m_sContingencySorting[iii] = m_sContingencySorting[jjj];
                m_sContingencySorting[jjj] = copy[0];
            }
        }
    }

}

void MainWindow::on_comboBox_Custom1_currentIndexChanged(const QString &arg1)
{/*
    if(ui->comboBox_Custom1->currentText() == "Condo Docs")
    {
        ui->checkBox_1->setChecked(true);
        refreshfields();
    }   */
}

QString MainWindow::getContingencyText(QString comboText)
{
    if(comboText == BLANK)
        return BLANK;
    if(comboText == "Final Walk-through")
        return FINAL_WALKTHROUGH;
    if(comboText == "Radon Test")
        return RADON;
    if(comboText == "Condo Docs")
        return CONDO_DOCS;
    if(comboText == "Well & Septic")
        return WELL_SEPTIC;
    if(comboText == "Comfort Letter")
        return COMFORT_LETTER;
    if(comboText == "Environmental Test")
        return ENVIRONMENTAL_TEST;
    if(comboText == "Attorney Review")
        return ATTORNEY_REVIEW;
    if(comboText == "Home-owner inssurence")
        return HOME_OWNER_INSSURENCE;
    if(comboText == "Condition Report")
        return CONDITION_REPORT;
    if(comboText == "Sewer")
        return SEWER;
    if(comboText == "Zoning")
        return ZONING;
    if(comboText == "Survey")
        return SURVEY;
    if(comboText == "Loan Rate Lock Expiration")
        return RATE_LOCK;
return "Error";
}
void MainWindow::setupCustomComboBoxes()
{
    QStringList strlCustomItems;
    strlCustomItems << "-" << "Final Walk-through" << "Radon Test" << "Condo Docs" <<
                       "Well & Septic" << "Comfort Letter" << "Environmental Test" <<
                       "Attorney Review" << "Home-owner inssurence" << "Condition Report" <<
                       "Sewer" << "Zoning" << "Survey" << "Loan Rate Lock Expiration";

    ui->comboBox_Custom1->addItems(strlCustomItems);
    ui->comboBox_Custom2->addItems(strlCustomItems);
    ui->comboBox_Custom3->addItems(strlCustomItems);
    ui->comboBox_Custom4->addItems(strlCustomItems);

}
QString MainWindow::getOrderedContingencies()
{
    QString strTemp;

    for (int iii = 1; iii<11;iii++)
        strTemp.append(m_sContingencySorting[iii].strReportInfo );

    return strTemp;
}

void MainWindow::on_actionSave_File_triggered()
{
    bool ok;
    QMessageBox SaveStatus;
    m_strFileName =  QFileDialog::getSaveFileName(this, tr("Save as Contingency File"),  "" ,tr("Contingencyu (*.MDRN)"));
    ok = saveAsContingencyFile();
    if(ok)
    {
        SaveStatus.setText("Save Successful!");
        noUnsavedDataPresent();
    }
    else
    {
        SaveStatus.setText("File NOT saved.");

    }
    SaveStatus.exec();
}

bool MainWindow::saveAsContingencyFile()

    {
        QFile file (m_strFileName);
        if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
            QDataStream stream (&file);


            stream << QString (CURRENT_VERSION);
            stream << m_strPropertyAddress;
            stream << m_strListingFirmTrustName;
            stream << m_strEarnestMoneyAmount;
            stream << m_nNumOfContingencies;
            stream << m_dtAcceptedOffer
                   << m_dtClosingDate
                   << m_dtEarnestMoney_date
                   << m_dtInspection_date
                   << m_dtAppraisal_date
                   << m_dtFinancing_date
                   << m_dtCustom1
                   << m_dtCustom2
                   << m_dtCustom3
                   << m_dtCustom4
                   << m_dtCustom5;
            stream << m_nDaysToClosing
                << m_nDaysForEarnestMoney
                << m_nDaysForInspection
                << m_nDaysForAppraisal
                << m_nDaysForFinaincing
                << m_nDaysCustom1
                << m_nDaysCustom2
                << m_nDaysCustom3
                << m_nDaysCustom4
                << m_nDaysCustom5;
            stream
                <<  m_bCust1FromClosing
                <<  m_bCust2FromClosing
                <<  m_bCust3FromClosing
                <<  m_bCust4FromClosing
                <<  m_bCust5FromClosing;
            stream
                << ui->comboBox_Custom1->currentText()
                << ui->comboBox_Custom2->currentText()
                << ui->comboBox_Custom3->currentText()
                << ui->comboBox_Custom4->currentText();
            stream
                << ui->lineEdit_Custom5->text();



           file.flush();
           file.close();
           return true;
        }
       else
            return false;

}

void MainWindow::on_actionOpen_File_triggered()
{
    bool ok;
    QMessageBox openStatus;
    m_strFileName = QFileDialog::getOpenFileName(this, tr("Select a file"), "Files", tr("Contingency File (*.MDRN)") );
    ok = readContingencyFile();
    if(ok)
    {
        openStatus.setText("Open Successful!");
        refreshfields();
        noUnsavedDataPresent();
    }
    else
    {
        openStatus.setText("Open Failed!!!");
    }
    openStatus.exec();
    //setDayFieldsToMembers();



}
bool MainWindow::readContingencyFile()
{

    QFile file (m_strFileName);
    file.open(QIODevice::ReadOnly);

        QDataStream stream (&file);

       stream >> m_strVerNum;

       if(m_strVerNum == "1.2.0")
       {
           stream >> m_strPropertyAddress;
           stream >> m_strListingFirmTrustName;
           stream >> m_strEarnestMoneyAmount;
           stream >> m_nNumOfContingencies;

           stream >> m_dtAcceptedOffer
                  >> m_dtClosingDate
                  >> m_dtEarnestMoney_date
                  >> m_dtInspection_date
                  >> m_dtAppraisal_date
                  >> m_dtFinancing_date
                  >> m_dtCustom1
                  >> m_dtCustom2
                  >> m_dtCustom3
                  >> m_dtCustom4
                  >> m_dtCustom5;

           stream
               >> m_nDaysToClosing
               >> m_nDaysForEarnestMoney
               >> m_nDaysForInspection
               >> m_nDaysForAppraisal
               >> m_nDaysForFinaincing
               >> m_nDaysCustom1
               >> m_nDaysCustom2
               >> m_nDaysCustom3
               >> m_nDaysCustom4
               >> m_nDaysCustom5;
           stream
               >>  m_bCust1FromClosing
               >>  m_bCust2FromClosing
               >>  m_bCust3FromClosing
               >>  m_bCust4FromClosing
               >>  m_bCust5FromClosing;

           QString A,B,C,D,E;
           stream
               >> A >> B >> C >> D >> E;
            ui->comboBox_Custom1->setCurrentIndex (ui->comboBox_Custom1->findText (A));
            ui->comboBox_Custom2->setCurrentIndex (ui->comboBox_Custom2->findText (B));
            ui->comboBox_Custom3->setCurrentIndex (ui->comboBox_Custom3->findText (C));
            ui->comboBox_Custom4->setCurrentIndex (ui->comboBox_Custom4->findText (D));
            ui->lineEdit_Custom5->setText(E);


           setCheckBoxes();
           file.close();
           return true;
        }
    return false;

}
void MainWindow::setCheckBoxes()
{
    ui->checkBox_1->setChecked(m_bCust1FromClosing);
    ui->checkBox_2->setChecked(m_bCust2FromClosing);
    ui->checkBox_3->setChecked(m_bCust3FromClosing);
    ui->checkBox_4->setChecked(m_bCust4FromClosing);
    ui->checkBox_5->setChecked(m_bCust5FromClosing);
}

void MainWindow::saveCheckBoxes()
{
    m_bCust1FromClosing = ui->checkBox_1->isChecked();
    m_bCust2FromClosing = ui->checkBox_2->isChecked();
    m_bCust3FromClosing = ui->checkBox_3->isChecked();
    m_bCust4FromClosing = ui->checkBox_4->isChecked();
    m_bCust5FromClosing = ui->checkBox_5->isChecked();
}

/*void MainWindow::setDayFieldsToMembers()
{


}*/

void MainWindow::on_lineEdit_Address_editingFinished()
{
    m_strPropertyAddress = ui->lineEdit_Address->text();
    refreshfields();
}

void MainWindow::on_lineEdit_Earnest_Money_Amount_editingFinished()
{
    m_strEarnestMoneyAmount = ui->lineEdit_Earnest_Money_Amount->text();
    refreshfields();
}

void MainWindow::on_lineEdit_Listing_Trust_editingFinished()
{
    m_strListingFirmTrustName = ui->lineEdit_Listing_Trust->text();
    refreshfields();
}

void MainWindow::on_spinBox_DaysCust1_valueChanged(const QString &arg1)
{

}
void MainWindow::unsavedDataPresent()
{
    m_bUnsavedData = true;
}
void MainWindow::noUnsavedDataPresent()
{
    m_bUnsavedData = false;
}
