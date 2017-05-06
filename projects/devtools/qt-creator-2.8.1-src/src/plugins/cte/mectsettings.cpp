#include "mectsettings.h"
#include "ui_mectsettings.h"
#include "utils.h"

#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QDirIterator>
#include <QFileInfo>
#include <QSettings>
#include <QTextStream>
#include <QValidator>
#include <QIntValidator>


#define MAX_SPACE_AVAILABLE_MAX 128
#define LINE_SIZE 1024


const QString szPAGE = QString::fromAscii("page");
const QString szDEFLANG  = QString::fromAscii("it");
const QString szLANGMAPFILE = QString::fromAscii(":/csv/others/lang_table.csv");


MectSettings::MectSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MectSettings)
{
    int     nValMaxInt16 = 65535;
    int     i = 0;

    ui->setupUi(this);
    // Impostazione degli opportuni Validator per i campi integers
    ui->lineEdit_Retries->setValidator(new QIntValidator(0, nValMaxInt16, this));
    ui->lineEdit_Blacklist->setValidator(new QIntValidator(0, nValMaxInt16, this));
    ui->lineEdit_ReadPeriod1->setValidator(new QIntValidator(1, nValMaxInt16, this));
    ui->lineEdit_ReadPeriod2->setValidator(new QIntValidator(1, nValMaxInt16, this));
    ui->lineEdit_ReadPeriod3->setValidator(new QIntValidator(1, nValMaxInt16, this));
    ui->lineEdit_PwdTimeout->setValidator(new QIntValidator(0, nValMaxInt16, this));
    ui->lineEdit_ScreenSaver->setValidator(new QIntValidator(0, nValMaxInt16, this));
    ui->lineEdit_SlowLogPeriod->setValidator(new QIntValidator(2, nValMaxInt16, this));
    ui->lineEdit_FastLogPeriod->setValidator(new QIntValidator(1, nValMaxInt16, this));
    ui->lineEdit_MaxLogSpace->setValidator(new QIntValidator(1, MAX_SPACE_AVAILABLE_MAX, this));
    ui->lineEdit_TraceWindow->setValidator(new QIntValidator(0, nValMaxInt16, this));
    /* SERIAL 0 */
    ui->lineEdit_Silence_SERIAL_PORT_0->setValidator(new QIntValidator(0, nValMaxInt16, this));
    ui->lineEdit_Timeout_SERIAL_PORT_0->setValidator(new QIntValidator(0, nValMaxInt16, this));
    /* SERIAL 1 */
    ui->lineEdit_Silence_SERIAL_PORT_1->setValidator(new QIntValidator(0, nValMaxInt16, this));
    ui->lineEdit_Timeout_SERIAL_PORT_1->setValidator(new QIntValidator(0, nValMaxInt16, this));
    /* SERIAL 2 */
    ui->lineEdit_Silence_SERIAL_PORT_2->setValidator(new QIntValidator(0, nValMaxInt16, this));
    ui->lineEdit_Timeout_SERIAL_PORT_2->setValidator(new QIntValidator(0, nValMaxInt16, this));
    /* TCP_IP */
    ui->lineEdit_Silence_TCP_IP_PORT->setValidator(new QIntValidator(0, nValMaxInt16, this));
    ui->lineEdit_Timeout_TCP_IP_PORT->setValidator(new QIntValidator(0, nValMaxInt16, this));
    // Clear Model Info
    m_nModel = -1;
    m_szModel.clear();
    // Tab Enabler
    for (i = 0; i < tabTotals; i++)
        m_tabEnabled[i] = true;

}

MectSettings::~MectSettings()
{
    delete ui;
}

void    MectSettings::setModel(const int nModel)
{
    int i = 0;

    if (nModel >= 0 && MODEL_TOTALS)  {
        m_nModel = nModel;
        m_szModel = QString::fromAscii(product_name[nModel]);        
        // Get Port Config from Model Number
        enablePortsFromModel(nModel);
    }
    else  {
        m_nModel = AnyTPAC;
        m_szModel.clear();
    }
    // Refresh Port Tabs config
    qDebug() << tr("Model: %1") .arg(nModel);
    for (i = 0; i < tabTotals; i++)  {
        // ui->tabWidget->setTabEnabled(i, m_tabEnabled[i]);
        ui->tabWidget->widget(i)->setEnabled(m_tabEnabled[i]);
        qDebug() << tr("Tab %1: %2") .arg(i) .arg(m_tabEnabled[i]);
    }
    // Set Tab System as current Tab
    ui->tabWidget->setCurrentIndex(tabSystem);
}
bool    MectSettings::loadProjectFiles(const QString &szFileSettings, const QString szFilePro, const QString &szProjectPath, const int nModel)
{
    // Copy of Setting File, Project File, Project Path
    m_szFileSettings = szFileSettings;
    m_szFilePro = szFilePro;
    m_szProjectPath = szProjectPath;
    // qDebug() << "Settings: " << m_szFileSettings;
    // qDebug() << "Project:  " << m_szFilePro;
    // qDebug() << "Path Prj: " << m_szProjectPath;

    // Enable All Tabs as default
    int nTab = 0;
    for (nTab = 0; nTab < tabTotals; nTab++)
        m_tabEnabled[nTab] = true;

    // Ricerca del file di Settings
    if (!QFile(szFileSettings).exists())
    {
        QMessageBox::critical(this,trUtf8("Error"),trUtf8("System.ini file don't exist, it's impossible tool open."));
        return false;
    }

    /*Lettura del file.pro per sapere e costruire la combobox @ le pagine attualmente in uso nel progetto*/
    /* open and load crosstable file */
    QFile file(szFilePro);
    if(!file.exists()) {
        QMessageBox::information(this, trUtf8("Error"),trUtf8("Project File %1 don't exist, it's impossible tool open.") .arg(szFilePro));
        return false;
    }
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QStringList pagesList;

    // Cerca nel file .pro le righe relative agli oggetti ui
    while(!in.atEnd()) {
        QString line = in.readLine().trimmed();
        line.replace(szBACKSLASH, QString::fromAscii(""));
        line = line.trimmed();
        if (! line.isEmpty())  {
            QStringList lstItems = line.split(chSpace);
            if (lstItems.at(0).startsWith(szPAGE) && lstItems.at(0).endsWith(QString::fromAscii(".ui")))
            {
                // Verifica che il file esista nella directory corrente
                pagesList << QFileInfo(lstItems.at(0)).baseName();
            }
        }
    }
    file.close();
    // qDebug() << "Ui File list" << pagesList;
    /* Aggiungo in coda le pagine di Libreria */
    pagesList << QString::fromAscii("alarms")
              << QString::fromAscii("alarms_history")
              << QString::fromAscii("recipe")
              << QString::fromAscii("recipe_select")
              << QString::fromAscii("store")
              << QString::fromAscii("store_filter")
              << QString::fromAscii("data_manager")
              << QString::fromAscii("display_settings")
              << QString::fromAscii("info")
              << QString::fromAscii("menu")
              << QString::fromAscii("options")
              << QString::fromAscii("system_ini")
              << QString::fromAscii("time_set")
              << QString::fromAscii("trend")
              << QString::fromAscii("trend_option")
              << QString::fromAscii("trend_range");

    /*Inserimento della lista delle pagine all'interno delle combobox*/
    ui->comboBox_HomePage->clear();
    ui->comboBox_HomePage->addItems(pagesList);
    ui->comboBox_StartPage->clear();
    ui->comboBox_StartPage->addItems(pagesList);
    ui->comboBox_PwdLogoutPage->clear();
    ui->comboBox_PwdLogoutPage->addItem(szEMPTY);
    ui->comboBox_PwdLogoutPage->addItems(pagesList);

    QSettings settings(szFileSettings, QSettings::IniFormat);

    LanguageMap.clear();
    ui->comboBoxLanguage->clear();

    /* load Global MECT map of the language and his locale abbreviation */
    QFile langFile(szLANGMAPFILE);
    QString szLine;
    if (langFile.exists() && langFile.open(QFile::ReadOnly | QIODevice::Text)) {
        QTextStream langStream(&langFile);
        while (! langStream.atEnd())  {
            szLine = langStream.readLine(LINE_SIZE);
            QStringList strlist = szLine.split(szSEMICOL);
            if (strlist.count()==2)
            {
                LanguageMap.insert(strlist.at(1).trimmed(), strlist.at(0).trimmed());
            }
        }
        langFile.close();
    }
    // qDebug() << "LanguageMap Items: " << LanguageMap.count();
    /* load the translations file list */
    QDirIterator lang_it(szProjectPath, QDirIterator::Subdirectories);
    QString lang = settings.value(QString::fromAscii("SYSTEM/language"), szDEFLANG).toString();
    QString szLangTempl = QString::fromAscii("languages_");
    int i = -1;
    int indexlang = 0;
    while (lang_it.hasNext()) {
        QString item = lang_it.next();
        // Cerca tutti i files con estensione .qm
        if (item.endsWith (QString::fromAscii(".qm")) == true)
        {
            // Determina il codice della Lingua dal nome file (es: languages_it ==> it)
            QString tmplang = item.mid(item.indexOf(szLangTempl) + szLangTempl.length(), 2);
            if (lang == tmplang)
            {
                indexlang = i;
            }
            if (LanguageMap.count() > 0 && LanguageMap.contains(tmplang))
            {
                // La lingua esiste come chiave, inserisce in combo il valore associato
                ui->comboBoxLanguage->addItem(LanguageMap.value(tmplang));
            }
            else
            {
                // La lingua Non esiste come chiave, inserisce in combo solo la chiave
                ui->comboBoxLanguage->addItem(tmplang);
            }
            i++;
        }
    }
    QString szValue;
    ui->comboBoxLanguage->setCurrentIndex(indexlang);
    ui->lineEdit_Retries->setText(settings.value(QString::fromAscii("SYSTEM/retries")).toString());
    ui->lineEdit_Blacklist->setText(settings.value(QString::fromAscii("SYSTEM/blacklist")).toString());
    ui->lineEdit_ReadPeriod1->setText(settings.value(QString::fromAscii("SYSTEM/read_period_ms_1")).toString());
    ui->lineEdit_ReadPeriod2->setText(settings.value(QString::fromAscii("SYSTEM/read_period_ms_2")).toString());
    ui->lineEdit_ReadPeriod3->setText(settings.value(QString::fromAscii("SYSTEM/read_period_ms_3")).toString());
    szValue = settings.value(QString::fromAscii("SYSTEM/home_page")).toString();
    ui->comboBox_HomePage->setCurrentIndex(ui->comboBox_HomePage->findText(szValue));
    // qDebug() << "Home Page" << szValue;
    szValue = settings.value(QString::fromAscii("SYSTEM/start_page")).toString();
    ui->comboBox_StartPage->setCurrentIndex(ui->comboBox_StartPage->findText(szValue));
    // qDebug() << "Start Page" << szValue;
    ui->checkBox_BuzzerTouch->setChecked(settings.value(QString::fromAscii("SYSTEM/buzzer_touch")).toBool());
    ui->checkBox_BuzzerAlarm->setChecked(settings.value(QString::fromAscii("SYSTEM/buzzer_alarm")).toBool());
    ui->lineEdit_PwdTimeout->setText(settings.value(QString::fromAscii("SYSTEM/pwd_timeout_s")).toString());
    szValue = settings.value(QString::fromAscii("SYSTEM/pwd_logout_page")).toString();
    ui->comboBox_PwdLogoutPage->setCurrentIndex(ui->comboBox_PwdLogoutPage->findText(szValue));
    // qDebug() << "Pwd Logout Page" << szValue;
    ui->lineEdit_ScreenSaver->setText(settings.value(QString::fromAscii("SYSTEM/screen_saver_s")).toString());
    ui->lineEdit_SlowLogPeriod->setText(settings.value(QString::fromAscii("SYSTEM/slow_log_period_s")).toString());
    ui->lineEdit_FastLogPeriod->setText(settings.value(QString::fromAscii("SYSTEM/fast_log_period_s")).toString());
    ui->lineEdit_MaxLogSpace->setText(settings.value(QString::fromAscii("SYSTEM/max_log_space_MB")).toString());
    ui->lineEdit_TraceWindow->setText(settings.value(QString::fromAscii("SYSTEM/trace_window_s")).toString());

    int index;
    QString value;
    /* La presenza del Baud Rate abilita o meno il Tab per la porta in esame */
    value = settings.value(QString::fromAscii("SERIAL_PORT_0/baudrate")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Baudrate_SERIAL_PORT_0->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'baudrate' parameter for SERIAL_PORT_0 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Baudrate_SERIAL_PORT_0->itemText(index)));
        }
        ui->comboBox_Baudrate_SERIAL_PORT_0->setCurrentIndex(index);
    }
    else  {
        // Disable all Tab
        m_tabEnabled[tabSerial0] = false;
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_0/databits")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Databits_SERIAL_PORT_0->findText(value);
        if ( index < 0)
        {
            index = 3;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'databits' parameter for SERIAL_PORT_0 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Databits_SERIAL_PORT_0->itemText(index)));
        }
        ui->comboBox_Databits_SERIAL_PORT_0->setCurrentIndex(index);
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_0/parity")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Parity_SERIAL_PORT_0->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'parity' parameter for SERIAL_PORT_0 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Parity_SERIAL_PORT_0->itemText(index)));
        }
        ui->comboBox_Parity_SERIAL_PORT_0->setCurrentIndex(index);
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_0/stopbits")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Stopbits_SERIAL_PORT_0->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'stopbits' parameter for SERIAL_PORT_0 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Stopbits_SERIAL_PORT_0->itemText(index)));
        }
        ui->comboBox_Stopbits_SERIAL_PORT_0->setCurrentIndex(index);
    }

    ui->lineEdit_Silence_SERIAL_PORT_0->setText(settings.value(QString::fromAscii("SERIAL_PORT_0/silence_ms")).toString());
    ui->lineEdit_Timeout_SERIAL_PORT_0->setText(settings.value(QString::fromAscii("SERIAL_PORT_0/timeout_ms")).toString());

    value = settings.value(QString::fromAscii("SERIAL_PORT_1/baudrate")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Baudrate_SERIAL_PORT_1->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'baudrate' parameter for SERIAL_PORT_1 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Baudrate_SERIAL_PORT_1->itemText(index)));
        }
        ui->comboBox_Baudrate_SERIAL_PORT_1->setCurrentIndex(index);
    }
    else  {
        // Disable all Tab
        m_tabEnabled[tabSerial1] = false;
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_1/databits")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Databits_SERIAL_PORT_1->findText(value);
        if ( index < 0)
        {
            index = 3;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'databits' parameter for SERIAL_PORT_1 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Databits_SERIAL_PORT_1->itemText(index)));
        }
        ui->comboBox_Databits_SERIAL_PORT_1->setCurrentIndex(index);
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_1/parity")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Parity_SERIAL_PORT_1->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'parity' parameter for SERIAL_PORT_1 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Parity_SERIAL_PORT_1->itemText(index)));
        }
        ui->comboBox_Parity_SERIAL_PORT_1->setCurrentIndex(index);
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_1/stopbits")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Stopbits_SERIAL_PORT_1->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'stopbits' parameter for SERIAL_PORT_1 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Stopbits_SERIAL_PORT_1->itemText(index)));
        }
        ui->comboBox_Stopbits_SERIAL_PORT_1->setCurrentIndex(index);
    }

    ui->lineEdit_Silence_SERIAL_PORT_1->setText(settings.value(QString::fromAscii("SERIAL_PORT_1/silence_ms")).toString());
    ui->lineEdit_Timeout_SERIAL_PORT_1->setText(settings.value(QString::fromAscii("SERIAL_PORT_1/timeout_ms")).toString());

    value = settings.value(QString::fromAscii("SERIAL_PORT_2/baudrate")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Baudrate_SERIAL_PORT_2->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'baudrate' parameter for SERIAL_PORT_2 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Baudrate_SERIAL_PORT_2->itemText(index)));
        }
        ui->comboBox_Baudrate_SERIAL_PORT_2->setCurrentIndex(index);
    }
    else  {
        // Disable all Tab
        m_tabEnabled[tabSerial2] = false;
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_2/databits")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Databits_SERIAL_PORT_2->findText(value);
        if ( index < 0)
        {
            index = 3;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'databits' parameter for SERIAL_PORT_2 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Databits_SERIAL_PORT_2->itemText(index)));
        }
        ui->comboBox_Databits_SERIAL_PORT_2->setCurrentIndex(index);
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_2/parity")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Parity_SERIAL_PORT_2->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'parity' parameter for SERIAL_PORT_2 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Parity_SERIAL_PORT_2->itemText(index)));
        }
        ui->comboBox_Parity_SERIAL_PORT_2->setCurrentIndex(index);
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_2/stopbits")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Stopbits_SERIAL_PORT_2->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'stopbits' parameter for SERIAL_PORT_2 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Stopbits_SERIAL_PORT_2->itemText(index)));
        }
        ui->comboBox_Stopbits_SERIAL_PORT_2->setCurrentIndex(index);
    }

    ui->lineEdit_Silence_SERIAL_PORT_2->setText(settings.value(QString::fromAscii("SERIAL_PORT_2/silence_ms")).toString());
    ui->lineEdit_Timeout_SERIAL_PORT_2->setText(settings.value(QString::fromAscii("SERIAL_PORT_2/timeout_ms")).toString());

    value = settings.value(QString::fromAscii("SERIAL_PORT_3/baudrate")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Baudrate_SERIAL_PORT_3->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'baudrate' parameter for SERIAL_PORT_3 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Baudrate_SERIAL_PORT_3->itemText(index)));
        }
        ui->comboBox_Baudrate_SERIAL_PORT_3->setCurrentIndex(index);
    }
    else  {
        // Disable all Tab
        m_tabEnabled[tabSerial3] = false;
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_3/databits")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Databits_SERIAL_PORT_3->findText(value);
        if ( index < 0)
        {
            index = 3;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'databits' parameter for SERIAL_PORT_3 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Databits_SERIAL_PORT_3->itemText(index)));
        }
        ui->comboBox_Databits_SERIAL_PORT_3->setCurrentIndex(index);
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_3/parity")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Parity_SERIAL_PORT_3->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'parity' parameter for SERIAL_PORT_3 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Parity_SERIAL_PORT_3->itemText(index)));
        }
        ui->comboBox_Parity_SERIAL_PORT_3->setCurrentIndex(index);
    }

    value = settings.value(QString::fromAscii("SERIAL_PORT_3/stopbits")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Stopbits_SERIAL_PORT_3->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'stopbits' parameter for SERIAL_PORT_3 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Stopbits_SERIAL_PORT_3->itemText(index)));
        }
        ui->comboBox_Stopbits_SERIAL_PORT_3->setCurrentIndex(index);
    }

    ui->lineEdit_Silence_SERIAL_PORT_3->setText(settings.value(QString::fromAscii("SERIAL_PORT_3/silence_ms")).toString());
    ui->lineEdit_Timeout_SERIAL_PORT_3->setText(settings.value(QString::fromAscii("SERIAL_PORT_3/timeout_ms")).toString());

    ui->lineEdit_Silence_TCP_IP_PORT->setText(settings.value(QString::fromAscii("TCP_IP_PORT/silence_ms")).toString());
    ui->lineEdit_Timeout_TCP_IP_PORT->setText(settings.value(QString::fromAscii("TCP_IP_PORT/timeout_ms")).toString());

    value = settings.value(QString::fromAscii("CANOPEN_0/baudrate")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Baudrate_CANOPEN_0->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'stopbits' parameter for CANOPEN_0 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Baudrate_CANOPEN_0->itemText(index)));
        }
        ui->comboBox_Baudrate_CANOPEN_0->setCurrentIndex(index);
    }
    else  {
        // Disable all Tab
        m_tabEnabled[tabCan0] = false;
    }

    value = settings.value(QString::fromAscii("CANOPEN_1/baudrate")).toString();
    if (value.length() > 0)
    {
        index = ui->comboBox_Baudrate_CANOPEN_1->findText(value);
        if ( index < 0)
        {
            index = 0;
            QMessageBox::critical(0,trUtf8("Error"),trUtf8("'stopbits' parameter for CANOPEN_1 have an invalid value: %1. it will be set it as %2.").arg(value).arg(ui->comboBox_Baudrate_CANOPEN_1->itemText(index)));
        }
        ui->comboBox_Baudrate_CANOPEN_1->setCurrentIndex(index);
    }
    else  {
        // Disable all Tab
        m_tabEnabled[tabCan1] = false;
    }
    // Set Model Info for current Model
    setModel(nModel);
    // All Ok, return true
    return true;
}

void MectSettings::on_cmdSave_clicked()
{

    // Controllo del contenuto dei campi
    if (! checkFields())
        return;
    if (fileBackUp(m_szFileSettings))
        save_all();
    else
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("Error creating back up copy of file: %1") .arg(m_szFileSettings));

}
void MectSettings::save_all()
{

    QSettings settings(m_szFileSettings, QSettings::IniFormat);
    QStringList groups = settings.childGroups();

    /* SYSTEM */
    if (groups.indexOf(QString::fromAscii("SYSTEM")) >= 0)
    {
        settings.setValue(QString::fromAscii("SYSTEM/language"), LanguageMap.key(ui->comboBoxLanguage->currentText(),szDEFLANG));
        settings.setValue(QString::fromAscii("SYSTEM/retries"), ui->lineEdit_Retries->text());
        settings.setValue(QString::fromAscii("SYSTEM/blacklist"), ui->lineEdit_Blacklist->text());
        settings.setValue(QString::fromAscii("SYSTEM/read_period_ms_1"), ui->lineEdit_ReadPeriod1->text());
        settings.setValue(QString::fromAscii("SYSTEM/read_period_ms_2"), ui->lineEdit_ReadPeriod2->text());
        settings.setValue(QString::fromAscii("SYSTEM/read_period_ms_3"), ui->lineEdit_ReadPeriod3->text());
        settings.setValue(QString::fromAscii("SYSTEM/home_page"), ui->comboBox_HomePage->currentText());
        settings.setValue(QString::fromAscii("SYSTEM/start_page"), ui->comboBox_StartPage->currentText());
        settings.setValue(QString::fromAscii("SYSTEM/buzzer_touch"), (ui->checkBox_BuzzerTouch->isChecked() == true)?1:0);
        settings.setValue(QString::fromAscii("SYSTEM/buzzer_alarm"), (ui->checkBox_BuzzerAlarm->isChecked() == true)?1:0);
        settings.setValue(QString::fromAscii("SYSTEM/pwd_timeout_s"), ui->lineEdit_PwdTimeout->text());
        settings.setValue(QString::fromAscii("SYSTEM/pwd_logout_page"), ui->comboBox_PwdLogoutPage->currentText());
        settings.setValue(QString::fromAscii("SYSTEM/screen_saver_s"), ui->lineEdit_ScreenSaver->text());
        settings.setValue(QString::fromAscii("SYSTEM/slow_log_period_s"), ui->lineEdit_SlowLogPeriod->text());
        settings.setValue(QString::fromAscii("SYSTEM/fast_log_period_s"), ui->lineEdit_FastLogPeriod->text());
        settings.setValue(QString::fromAscii("SYSTEM/max_log_space_MB"), ui->lineEdit_MaxLogSpace->text());
        settings.setValue(QString::fromAscii("SYSTEM/trace_window_s"), ui->lineEdit_TraceWindow->text());
        settings.sync();
    }
    /* SERIAL 0 */
    if (groups.indexOf(QString::fromAscii("SERIAL_PORT_0")) >= 0)
    {
        if (ui->comboBox_Baudrate_SERIAL_PORT_0->currentIndex() > 0)
        {
            settings.setValue(QString::fromAscii("SERIAL_PORT_0/baudrate"), ui->comboBox_Baudrate_SERIAL_PORT_0->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_0/databits"), ui->comboBox_Databits_SERIAL_PORT_0->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_0/parity"), ui->comboBox_Parity_SERIAL_PORT_0->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_0/stopbits"), ui->comboBox_Stopbits_SERIAL_PORT_0->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_0/silence_ms"), ui->lineEdit_Silence_SERIAL_PORT_0->text());
            settings.setValue(QString::fromAscii("SERIAL_PORT_0/timeout_ms"), ui->lineEdit_Timeout_SERIAL_PORT_0->text());
        }
        else
        {
            settings.remove(QString::fromAscii("SERIAL_PORT_0"));
        }
        settings.sync();
    }
    /* SERIAL 1 */
    if (groups.indexOf(QString::fromAscii("SERIAL_PORT_1")) >= 0)
    {
        if (ui->comboBox_Baudrate_SERIAL_PORT_1->currentIndex() > 0)
        {
            settings.setValue(QString::fromAscii("SERIAL_PORT_1/baudrate"), ui->comboBox_Baudrate_SERIAL_PORT_1->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_1/databits"), ui->comboBox_Databits_SERIAL_PORT_1->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_1/parity"), ui->comboBox_Parity_SERIAL_PORT_1->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_1/stopbits"), ui->comboBox_Stopbits_SERIAL_PORT_1->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_1/silence_ms"), ui->lineEdit_Silence_SERIAL_PORT_1->text());
            settings.setValue(QString::fromAscii("SERIAL_PORT_1/timeout_ms"), ui->lineEdit_Timeout_SERIAL_PORT_1->text());
        }
        else
        {
            settings.remove(QString::fromAscii("SERIAL_PORT_1"));
        }
        settings.sync();
    }
    /* SERIAL 2 */
    if (groups.indexOf(QString::fromAscii("SERIAL_PORT_2")) >= 0)
    {
        if (ui->comboBox_Baudrate_SERIAL_PORT_2->currentIndex() > 0)
        {
            settings.setValue(QString::fromAscii("SERIAL_PORT_2/baudrate"), ui->comboBox_Baudrate_SERIAL_PORT_2->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_2/databits"), ui->comboBox_Databits_SERIAL_PORT_2->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_2/parity"), ui->comboBox_Parity_SERIAL_PORT_2->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_2/stopbits"), ui->comboBox_Stopbits_SERIAL_PORT_2->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_2/silence_ms"), ui->lineEdit_Silence_SERIAL_PORT_2->text());
            settings.setValue(QString::fromAscii("SERIAL_PORT_2/timeout_ms"), ui->lineEdit_Timeout_SERIAL_PORT_2->text());
        }
        else
        {
            settings.remove(QString::fromAscii("SERIAL_PORT_2"));
        }
        settings.sync();
    }
    /* SERIAL 3 */
    if (groups.indexOf(QString::fromAscii("SERIAL_PORT_3")) >= 0)
    {
        if (ui->comboBox_Baudrate_SERIAL_PORT_3->currentIndex() > 0)
        {
            settings.setValue(QString::fromAscii("SERIAL_PORT_3/baudrate"), ui->comboBox_Baudrate_SERIAL_PORT_3->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_3/databits"), ui->comboBox_Databits_SERIAL_PORT_3->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_3/parity"), ui->comboBox_Parity_SERIAL_PORT_3->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_3/stopbits"), ui->comboBox_Stopbits_SERIAL_PORT_3->currentText());
            settings.setValue(QString::fromAscii("SERIAL_PORT_3/silence_ms"), ui->lineEdit_Silence_SERIAL_PORT_3->text());
            settings.setValue(QString::fromAscii("SERIAL_PORT_3/timeout_ms"), ui->lineEdit_Timeout_SERIAL_PORT_3->text());
        }
        else
        {
            settings.remove(QString::fromAscii("SERIAL_PORT_3"));
        }
        settings.sync();
    }
    /* TCP_IP */
    if (groups.indexOf(QString::fromAscii("TCP_IP_PORT")) >= 0)
    {
        settings.setValue(QString::fromAscii("TCP_IP_PORT/silence_ms"), ui->lineEdit_Silence_TCP_IP_PORT->text());
        settings.setValue(QString::fromAscii("TCP_IP_PORT/timeout_ms"), ui->lineEdit_Timeout_TCP_IP_PORT->text());
        settings.sync();
    }
    /* CANOPEN 0 */
    if (groups.indexOf(QString::fromAscii("CANOPEN_0")) >= 0)
    {
        if (ui->comboBox_Baudrate_CANOPEN_0->currentIndex() > 0)
        {
            settings.setValue(QString::fromAscii("CANOPEN_0/baudrate"), ui->comboBox_Baudrate_CANOPEN_0->currentText());
        }
        else
        {
            settings.remove(QString::fromAscii("CANOPEN_0"));
        }
        settings.sync();
    }
    /* CANOPEN 1 */
    if (groups.indexOf(QString::fromAscii("CANOPEN_1")) >= 0)
    {
        if (ui->comboBox_Baudrate_CANOPEN_1->currentIndex() > 0)
        {
            settings.setValue(QString::fromAscii("CANOPEN_1/baudrate"), ui->comboBox_Baudrate_CANOPEN_1->currentText());
        }
        else
        {
            settings.remove(QString::fromAscii("CANOPEN_1"));
        }
    }
    settings.sync();

    QMessageBox::information(0,trUtf8("Information"),trUtf8("Configuration has been successfully saved."));
}
bool MectSettings::checkFields()
// Controllo del contenuto dei campi
{
    bool fRes = false;
    bool OK = false;


    //------------------------
    // Tab System
    //------------------------
    if (ui->lineEdit_Retries->text().toInt(&OK) < 0 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Retries' parameter must be greater than or egual 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Retries' parameter must be a number."));
        goto exitCheck;
    }
    if (ui->lineEdit_Blacklist->text().toInt(&OK) < 0 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Blacklist' parameter must be greater than or egual 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Blacklist' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_ReadPeriod1->text().toInt(&OK) < 1 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Read Period 1' parameter must be greater than 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Read Period 1' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_ReadPeriod2->text().toInt(&OK) < 2 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Read Period 2' parameter must be greater than 1."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Read Period 2' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_ReadPeriod3->text().toInt(&OK) < 3 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Read Period 3' parameter must be greater than 2."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Read Period 3' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_ReadPeriod3->text().toInt() < ui->lineEdit_ReadPeriod2->text().toInt())
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Read Period 3' parameter must be greater than 'Read Period 2' parameter."));
        goto exitCheck;
    }

    if (ui->lineEdit_ReadPeriod2->text().toInt() < ui->lineEdit_ReadPeriod1->text().toInt())
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Read Period 2' parameter must be greater than 'Read Period 1' parameter."));
        goto exitCheck;
    }
    if (ui->lineEdit_PwdTimeout->text().toInt(&OK) < 0 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Pwd Timeout' parameter must be greater than or egual 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Pwd Timeout' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_ScreenSaver->text().toInt(&OK) < 0 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Screen Saver' parameter must be greater than or egual 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Screen Saver' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_SlowLogPeriod->text().toInt(&OK) < 2 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Slow Log Period' parameter must be greater than 1."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Slow Log Period' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_FastLogPeriod->text().toInt(&OK) < 1 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Fast Log Period' parameter must be greater than 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Fast Log Period' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_SlowLogPeriod->text().toInt() < ui->lineEdit_FastLogPeriod->text().toInt())
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Slow Log Period' parameter must be greater than 'Fast Log Period' parameter."));
        goto exitCheck;
    }
    if (ui->lineEdit_MaxLogSpace->text().toInt(&OK) <= 0 && ui->lineEdit_MaxLogSpace->text().toInt(&OK) > MAX_SPACE_AVAILABLE_MAX && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Max Log Space' parameter must be greater than 0 and less than %1.").arg(MAX_SPACE_AVAILABLE_MAX));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Max Log Space' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_TraceWindow->text().toInt(&OK) < 3 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Trace Window' parameter must be greater than 2."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Trace Window' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_TraceWindow->text().toInt() < (ui->lineEdit_FastLogPeriod->text().toInt()* 3))
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Trace Window' parameter must be at least three times 'Fast Log Period' parameter."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 0' tab, the 'Silence' parameter must be a number."));
        goto exitCheck;
    }
    //------------------------
    /* SERIAL 0 */
    //------------------------
    if (ui->lineEdit_Silence_SERIAL_PORT_0->text().toInt(&OK) < 0 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 0' tab, the 'Silence' parameter must be greater than or egual 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 0' tab, the 'Silence' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_Timeout_SERIAL_PORT_0->text().toInt(&OK) < 0 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 0' tab, the 'Timeout' parameter must be greater than 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 0' tab, the 'Timeout' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_Timeout_SERIAL_PORT_0->text().toInt() <= ui->lineEdit_Silence_SERIAL_PORT_0->text().toInt())
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 0' tab, the 'Timeout' parameter must be greater than 'Silence' parameter."));
        goto exitCheck;
    }
    //------------------------
    /* SERIAL 1 */
    //------------------------
    if (ui->lineEdit_Silence_SERIAL_PORT_1->text().toInt(&OK) < 0 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 1' tab, the 'Silence' parameter must be greater than or egual 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 1' tab, the 'Silence' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_Timeout_SERIAL_PORT_1->text().toInt(&OK) < 1 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 1' tab, the 'Timeout' parameter must be greater than 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 1' tab, the 'Timeout' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_Timeout_SERIAL_PORT_1->text().toInt() <= ui->lineEdit_Silence_SERIAL_PORT_1->text().toInt())
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 1' tab, the 'Timeout' parameter must be greater than 'Silence' parameter."));
        goto exitCheck;
    }
    //------------------------
    /* SERIAL 2 */
    //------------------------
    if (ui->lineEdit_Silence_SERIAL_PORT_2->text().toInt(&OK) < 0 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 2' tab, the 'Silence' parameter must be greater than or egual 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 2' tab, the 'Silence' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_Timeout_SERIAL_PORT_2->text().toInt(&OK) < 1 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 2' tab, the 'Timeout' parameter must be greater than 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 2' tab, the 'Timeout' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_Timeout_SERIAL_PORT_2->text().toInt() <= ui->lineEdit_Silence_SERIAL_PORT_2->text().toInt())
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'SERIAL PORT 2' tab, the 'Timeout' parameter must be greater than 'Silence' parameter."));
        goto exitCheck;
    }
    //------------------------
    /* TCP_IP */
    //------------------------
    if (ui->lineEdit_Silence_TCP_IP_PORT->text().toInt(&OK) < 0 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'TCP_IP_PORT' tab, the 'Silence' parameter must be greater than or egual 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'TCP_IP_PORT' tab, the 'Silence' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_Timeout_TCP_IP_PORT->text().toInt(&OK) < 1 && OK == true)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'TCP_IP_PORT' tab, the 'Timeout' parameter must be greater than 0."));
        goto exitCheck;
    }

    if(OK == false)/*Controllo che il valore inserito non sia diverso da un numero*/
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'TCP_IP_PORT' tab, the 'Timeout' parameter must be a number."));
        goto exitCheck;
    }

    if (ui->lineEdit_Timeout_TCP_IP_PORT->text().toInt() <= ui->lineEdit_Silence_TCP_IP_PORT->text().toInt())
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("In the 'TCP_IP_PORT' tab, the 'Timeout' parameter must be greater than 'Silence' parameter."));
        goto exitCheck;
    }
    //------------------------
    // All check are Ok, return true
    //------------------------
    fRes = true;

exitCheck:
    return fRes;
}
void MectSettings::enablePortsFromModel(int nModel)
{
    // tab System and TCP are always ON
    m_tabEnabled[tabSystem] = true;
    m_tabEnabled[tabTCP] = true;
    // Check if model is in range
    if (nModel == AnyTPAC || nModel >= MODEL_TOTALS)  {
        return;
    }
    // Seriale 0
    if (nModel == TP1043_01_A ||
        nModel == TP1070_01_C ||
        nModel == TPAC1007_03 ||
        nModel == TPAC1007_04_AA ||
        nModel == TPAC1007_04_AB ||
        nModel == TPAC1007_04_AC ||
        nModel == TPAC1007_LV ||
        nModel == TPAC1008_02_AB ||
        nModel == TPLC100 ||
        nModel == TPLC150 )   {
        m_tabEnabled[tabSerial0] = true;
    }
    else  {
        m_tabEnabled[tabSerial0] = false;
    }
    // Seriale 1
    if (nModel == TPLC100 ||
        nModel == TPLC150 )   {
        m_tabEnabled[tabSerial1] = true;
    }
    else  {
        m_tabEnabled[tabSerial1] = false;
    }
    // Seriale 2
    if (nModel == TPLC100 ||
        nModel == TPLC150 )   {
        m_tabEnabled[tabSerial2] = true;
    }
    else  {
        m_tabEnabled[tabSerial2] = false;
    }
    // Seriale 3
    if (nModel == TP1057_01_A ||
        nModel == TP1057_01_B ||
        nModel == TP1070_01_A ||
        nModel == TP1070_01_B ||
        nModel == TP1070_01_C ||
        nModel == TPAC1006    ||
        nModel == TPAC1008_01 ||
        nModel == TPAC1008_02_AA ||
        nModel == TPAC1008_02_AB ||
        nModel == TPAC1008_02_AD ||
        nModel == TPAC1008_02_AE ||
        nModel == TPAC1008_02_AF ||
        nModel == TPLC100 ||
        nModel == TPLC150 )   {
        m_tabEnabled[tabSerial3] = true;
    }
    else  {
        m_tabEnabled[tabSerial3] = false;
    }
    // Can 0
    m_tabEnabled[tabCan0] = false;
    // Can1
    if (nModel == TP1057_01_A ||

        nModel == TPLC100 ||
        nModel == TPLC150 )   {
        m_tabEnabled[tabCan1] = true;
    }
    else  {
        m_tabEnabled[tabCan1] = false;
    }
}
