#include "ctedit.h"
#include "ui_ctedit.h"
//#include "parser.h"
#include "utils.h"

#include <QFile>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QModelIndexList>
#include <QString>
#include <QRect>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QDebug>
#include <QAction>
#include <QLocale>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QMenu>
#include <QAction>
#include <QVariant>
#include <QInputDialog>
#include <QCoreApplication>
#include <QProcess>
#include <QTextStream>

/* ----  Local Defines:   ----------------------------------------------------- */
#define _TRUE  1
#define _FALSE 0
#define MAX_DISPLAY_TIME 30
#define MAXBLOCKSIZE 64
#define MIN_RETENTIVE 1
#define MAX_RETENTIVE 192
#define MIN_NONRETENTIVE 193
#define MAX_NONRETENTIVE 4999
#define MIN_SYSTEM 5000
#define MAX_DIAG 5171
#define MIN_NODE 5172
#define MAX_NODE 5299
#define MIN_LOCALIO 5300
#define MAX_LOCALIO 5389
// Tabs in TabWidget
#define TAB_CT 0
#define TAB_SYSTEM 1

// String Costants
const QString szDEF_IP_PORT = QString::fromAscii("502");
const QString szEMPTY_IP = QString::fromAscii("0.0.0.0");
const QString szTitle = QString::fromAscii("Mect Cross Table Editor");
const QString szSlash = QString::fromAscii("/");
const QString szCrossCompier = QString::fromAscii("ctc");
const QString szTemplateFile = QString::fromAscii("template.pri");

enum colonne_e
{
    colPriority = 0,
    colUpdate,
    colName,
    colType,
    colDecimal,
    colProtocol,
    colIP,
    colPort,
    colNodeID,
    colRegister,
    colBlock,
    colBlockSize,
    colComment,
    colBehavior,
    colCondition,
    colTotals
};

enum behavior_e
{
    bevReadOnly = 0,
    bevReadWrite,
    bevAlarm,
    bevEvent,
    bevTotals
};

//extern int LoadXTable(char *crossTableFile);
//extern int SaveXTable(char *crossTableFile);
//extern char *ipaddr2str(uint32_t ipaddr, char *buffer);
//extern uint32_t str2ipaddr(char *str);

ctedit::ctedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ctedit)
{
    int     nCol = 0;
    int     nValMin = 0;
    int     nValMax = 9999;
    int     nValMaxInt16 = 65535;
    QString szToolTip;

    ui->setupUi(this);
    // Liste di servizio
    lstUsedVarNames.clear();
    lstUndo.clear();
    // Stringhe generiche per Default campi
    szEMPTY.clear();
    szZERO.fromAscii("0");
    lstHeadCols.clear();
    for (nCol = 0; nCol < colTotals; nCol++)  {
        lstHeadCols.append(szEMPTY);
    }
    // Riempimento liste
    // Titoli colonne
    lstHeadCols[colPriority] = trUtf8("Priority");
    lstHeadCols[colUpdate] = trUtf8("Update");
    lstHeadCols[colName] = trUtf8("Name");
    lstHeadCols[colType] = trUtf8("Type");
    lstHeadCols[colDecimal] = trUtf8("Decimal");
    lstHeadCols[colProtocol] = trUtf8("Protocol");
    lstHeadCols[colIP] = trUtf8("IP Address");
    lstHeadCols[colPort] = trUtf8("Port");
    lstHeadCols[colNodeID] = trUtf8("Node ID");
    lstHeadCols[colRegister] = trUtf8("Register");
    lstHeadCols[colBlock] = trUtf8("Block");
    lstHeadCols[colBlockSize] = trUtf8("Blk Size");
    lstHeadCols[colComment] = trUtf8("Comment");
    lstHeadCols[colBehavior] = trUtf8("Behavior");
    lstHeadCols[colCondition] = trUtf8("Condition");
    // Lista Priorità
    lstPriority.clear();
    lstPriority
            << QString::fromAscii("0")
            << QString::fromAscii("1")
            << QString::fromAscii("2")
            << QString::fromAscii("3")
        ;
    // Lista PLC (Frequenza Aggiornamento
    lstPLC.clear();
    for (nCol = Htype; nCol <= Xtype; nCol++)  {
        lstPLC.append(QString::fromAscii(updateTypeName[nCol]));
    }
    // Lista TIPI Variabili
    lstTipi.clear();
    for (nCol = BIT; nCol <= UNKNOWN; nCol++)  {
        lstTipi.append(QString::fromAscii(varTypeName[nCol]));
    }
    // Lista Protocolli (tipi di Bus)
    lstBusType.clear();
    lstBusEnabler.clear();
    for (nCol = PLC; nCol <= TCPRTU_SRV; nCol++)  {
        lstBusType.append(QString::fromAscii(fieldbusName[nCol]));
        lstBusEnabler.append(true);         // Di default tutti i tipi di Bus sono abilitati
    }
    // Lista Prodotti
    lstProductName.clear();
    for (nCol = AnyTPAC; nCol <= TPAC1008_02_AF; nCol++)  {
        lstProductName.append(QString::fromAscii(product_name[nCol]));
    }
    // Lista Significati
    lstBehavior.clear();
    lstBehavior
            << QString::fromAscii("READ")
            << QString::fromAscii("READ/WRITE")
            << QString::fromAscii("ALARM")
            << QString::fromAscii("EVENT")
        ;
    // Lista condizioni di Allarme / Eventi
    lstCondition.clear();
    lstCondition.append(QString::fromAscii(">"));
    lstCondition.append(QString::fromAscii(">="));
    lstCondition.append(QString::fromAscii("<"));
    lstCondition.append(QString::fromAscii("<="));
    lstCondition.append(QString::fromAscii("=="));
    lstCondition.append(QString::fromAscii("!="));
    lstCondition.append(QString::fromAscii("RISING EDGE"));
    lstCondition.append(QString::fromAscii("FALLING EDGE"));
    // Caricamento delle varie Combos
    // Combo Priority
    szToolTip.clear();
    szToolTip.append(tr("Enabling the exchange of data with remote devices:\n"));
    szToolTip.append(tr("0 - Disabled\n"));
    szToolTip.append(tr("1 - Enabled High Priority\n"));
    szToolTip.append(tr("2 - Enabled Medium Priority\n"));
    szToolTip.append(tr("3 - Enabled Low Priority"));
    for  (nCol=0; nCol<4; nCol++)   {
        ui->cboPriority->addItem(lstPriority[nCol], QString::number(nCol));
    }
    ui->cboPriority->setToolTip(szToolTip);
    // Combo Update
    szToolTip.clear();
    szToolTip.append(tr("PLC Refresh Rate:\n"));
    szToolTip.append(tr("H - Only in current page\n"));
    szToolTip.append(tr("P - Permanent\n"));
    szToolTip.append(tr("S - Permanent Slow Logging\n"));
    szToolTip.append(tr("F - Permanent Fast Logging\n"));
    szToolTip.append(tr("V - Permanent Logging if Changed"));
    for  (nCol=0; nCol<lstPLC.count(); nCol++)   {
        ui->cboUpdate->addItem(lstPLC[nCol], lstPLC[nCol]);
    }
    ui->cboUpdate->setToolTip(szToolTip);
    // ToolTip nome variabile
    szToolTip.clear();
    szToolTip.append(tr("Name of the variable to be used in HMI:\n"));
    szToolTip.append(tr("Must follow C++ variable naming conventions"));
    ui->txtName->setToolTip(szToolTip);
    // Combo TipoCrossTable
    szToolTip.clear();
    szToolTip.append(tr("Variable Data Type"));
    for  (nCol=0; nCol<lstTipi.count(); nCol++)   {
        ui->cboType->addItem(lstTipi[nCol], lstTipi[nCol]);
    }
    ui->cboType->setToolTip(szToolTip);
    // Decimals
    szToolTip.clear();
    szToolTip.append(tr("Number of decimal places to display data if from 0 to 4,\n"));
    szToolTip.append(tr("otherwise is the position of the variable that contains the number of decimal places\n"));
    szToolTip.append(tr("In the case of BIT variables, it is the position of the bit as low as 1"));
    ui->txtDecimal->setToolTip(szToolTip);
    // Combo Tipo Bus
    szToolTip.clear();
    szToolTip.append(tr("Protocol with the remote device"));
    for  (nCol=0; nCol<lstBusType.count(); nCol++)   {
        ui->cboProtocol->addItem(lstBusType[nCol], lstBusType[nCol]);
    }
    ui->cboProtocol->setToolTip(szToolTip);
    // Indirizzo IP
    szToolTip.clear();    // Lista Priorità
    szToolTip.append(tr("IP address for TCP, TCP_RTU, TCP_SRV, TCPRTU SRV like 192.168.0.42"));
    ui->txtIP->setToolTip(szToolTip);
    // Porta di comunicazione
    szToolTip.clear();
    szToolTip.append(tr("Communication Port, e.g. 502"));
    ui->txtPort->setToolTip(szToolTip);
    // Indirizzo nodo remoto
    szToolTip.clear();
    szToolTip.append(tr("Remode Node Address, 0 for broadcast"));
    ui->txtNode->setToolTip(szToolTip);
    // Register
    szToolTip.clear();
    szToolTip.append(tr("Modbus address of the Register to be used"));
    ui->txtRegister->setToolTip(szToolTip);
    // Block
    szToolTip.clear();
    szToolTip.append(tr("Address of the first register of the block"));
    ui->txtBlock->setToolTip(szToolTip);
    // Block size
    szToolTip.clear();
    szToolTip.append(tr("Number of registers in the block"));
    ui->txtBlockSize->setToolTip(szToolTip);
    // Combo Behavior
    szToolTip.clear();
    szToolTip.append(tr("Variable behavior: Reading, Reading and Writing, Alarm, Event"));
    for  (nCol=0; nCol<lstBehavior.count(); nCol++)   {
        ui->cboBehavior->addItem(lstBehavior[nCol], lstBehavior[nCol]);
    }
    ui->cboBehavior->setToolTip(szToolTip);
    // Combo Condition
    szToolTip.clear();
    szToolTip.append(trUtf8("Alarm Event Condition:\n"));
    szToolTip.append(trUtf8("GREATER\n"));
    szToolTip.append(trUtf8("GREATER OR EQL\n"));
    szToolTip.append(trUtf8("LESS\n"));
    szToolTip.append(trUtf8("LESS OR EQL\n"));
    szToolTip.append(trUtf8("EQUAL\n"));
    szToolTip.append(trUtf8("RISING EDGE\n"));
    szToolTip.append(trUtf8("FALLING EDGE"));
    ui->cboCondition->setEditable(true);
    // ui->cboCondition->lineEdit()->setReadOnly(true);
    ui->cboCondition->lineEdit()->setAlignment(Qt::AlignCenter);
    for  (nCol=0; nCol<lstCondition.count(); nCol++)   {
        ui->cboCondition->addItem(lstCondition[nCol], lstCondition[nCol]);
        ui->cboCondition->setItemData(nCol, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
    ui->cboCondition->lineEdit()->setReadOnly(true);
    ui->cboCondition->setToolTip(szToolTip);
    // Init Valori
    m_szCurrentCTFile.clear();
    m_szCurrentCTPath.clear();
    m_szCurrentCTName.clear();
    m_szCurrentModel.clear();
    m_szCurrentProjectPath.clear();
    m_nGridRow = 0;
    lstCopiedRecords.clear();
    lstCTRecords.clear();
    // Validator per Interi
    ui->txtDecimal->setValidator(new QIntValidator(nValMin, DimCrossTable, this));
    ui->txtPort->setValidator(new QIntValidator(nValMin, nValMaxInt16, this));
    ui->txtNode->setValidator(new QIntValidator(nValMin, nValMax, this));
    ui->txtRegister->setValidator(new QIntValidator(nValMin, nValMax, this));
    ui->txtNode->setValidator(new QIntValidator(nValMin, MAXBLOCKSIZE -1, this));
    ui->txtBlock->setValidator(new QIntValidator(nValMin, nValMax, this));
    ui->txtBlockSize->setValidator(new QIntValidator(nValMin, nValMax, this));
    // Validator per txtIp
    QString szExp = QString::fromAscii("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    QRegExp regExprIP(szExp);
    ui->txtIP->setValidator(new QRegExpValidator(regExprIP, this));
    // Validator per Nome variabile
    QString szNameExp = QString::fromAscii("\\w+");
    QRegExp regExprName(szNameExp);
    ui->txtName->setValidator(new QRegExpValidator(regExprName, this));
    // Campi sempre locked
    ui->txtRow->setEnabled(false);
    ui->fraOptions->setEnabled(false);
    ui->txtBlock->setEnabled(false);
    ui->txtBlockSize->setEnabled(false);
    // Model Name
    ui->lblModel->setText(szEMPTY);
    // Stringhe generiche per gestione dei formati di Data e ora
    m_szFormatDate = QString::fromAscii("yyyy.MM.dd");
    m_szFormatTime = QString::fromAscii("hh:mm:ss");
    // Costanti per i colori di sfondo
    colorRetentive[0] = QColor(170,255,255,255);           // Azzurro Dark
    colorRetentive[1] = QColor(210,255,255,255);           // Azzurro
    colorNonRetentive[0] = QColor(255,255,190,255);        // Giallino Dark
    colorNonRetentive[1] = QColor(255,255,220,255);        // Giallino
    colorSystem[0] = QColor(255,227,215,255);              // Rosa Dark
    colorSystem[1] = QColor(255,240,233,255);              // Rosa
    szColorRet[0] = QString::fromAscii("color: #AAFFFF");
    szColorRet[1] = QString::fromAscii("color: #D2FFFF");
    szColorNonRet[0] = QString::fromAscii("color: #FFFFBE");
    szColorNonRet[1] = QString::fromAscii("color: #FFFFDC");
    szColorSystem[0] = QString::fromAscii("color: #FFE3D7");
    szColorSystem[1] = QString::fromAscii("color: #FFF0E9");
    // Variabili di stato globale dell'editor
    m_isCtModified = false;
    m_fShowAllRows = false;
    m_nCurTab = 0;
    // Seleziona il primo Tab
    ui->tabWidget->setCurrentIndex(m_nCurTab);
    ui->tabWidget->setTabEnabled(TAB_SYSTEM, false);
    // Connessione Segnali - Slot
    ui->tblCT->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tblCT, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(displayUserMenu(const QPoint &)));
    // connect(ui->tblCT, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));
    connect(ui->tblCT->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            SLOT(tableItemChanged(const QItemSelection &, const QItemSelection & ) ));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected(int)));
}

ctedit::~ctedit()
{
    delete ui;
}
void    ctedit::setProjectPath(QString szProjectPath)
{
    m_szCurrentProjectPath = szProjectPath;
}

bool    ctedit::selectCTFile(QString szFileCT)
// Select a current CT File
{
    QString     szFile;
    bool        fRes = false;

    if (fileExists(szFileCT)) {
        szFile = szFileCT;
    }
    else {
        szFile = QFileDialog::getOpenFileName(this, tr("Open Cross Table File"), szFileCT, tr("Cross Table File (*.csv)"));
    }
    // Tries to Open CT File
    if (! szFile.isEmpty())   {
        m_szCurrentCTFile = szFile;
        fRes = loadCTFile(m_szCurrentCTFile, lstCTRecords, true);
        if (fRes)
            qDebug() << tr("Loaded CT File: %1 Result: OK") .arg(szFile);
        else
            qDebug() << tr("Loaded CT File: %1 Result: ERROR") .arg(szFile);
    }
    else  {
        m_szCurrentCTFile.clear();
        fRes = false;
        qDebug() << tr("CT File: %1 Not Found or not Selected") .arg(szFile);
    }
    // Retrieving Path and Name of Cross Table file
    m_szCurrentModel.clear();
    m_szCurrentCTPath.clear();
    m_szCurrentCTName.clear();
    // Load Ok, init default values
    if (fRes)  {
        QFileInfo fInfo(m_szCurrentCTFile);
        m_szCurrentCTPath = fInfo.absolutePath();
        m_szCurrentCTPath.append(szSlash);
        m_szCurrentCTName = fInfo.baseName();
        // Reading Model from template.pri
        m_szCurrentModel = getModelName();
        ui->lblModel->setText(m_szCurrentModel);
        m_isCtModified = false;
        enableInterface();
    }
    return fRes;
}
bool    ctedit::loadCTFile(QString szFileCT, QList<CrossTableRecord> &lstCtRecs, bool fLoadGrid)
// Load the current CT File. If fShowGrid then load data to user Grid
{
    int nRes = 0;
    int nCur = 0;
    bool fRes = false;

    if (szFileCT.isEmpty())
        return false;
    // Clear Data
    lstCtRecs.clear();
    this->setCursor(Qt::WaitCursor);
    // Opening File
    nRes = LoadXTable(szFileCT.toAscii().data(), &CrossTable[0]);
    // Return value is the result of Parsing C structure to C++ Objects.
    // Data in Array starts from element #1, in list from 0...
    if (nRes == 0)  {
        for (nCur = 1; nCur <= DimCrossTable; ++nCur)  {
            lstCtRecs.append(CrossTable[nCur]);
        }
        if (fLoadGrid)  {
            fRes = ctable2Grid();
        }
        else
            fRes = true;
    }
    else  {
        m_szMsg = tr("Error Loading CrossTable file: %1") .arg(szFileCT);
        warnUser(this, szTitle, m_szMsg);
    }
    this->setCursor(Qt::ArrowCursor);
    return fRes;
}
bool    ctedit::list2GridRow(QStringList &lstRecValues, int nRow)
// Inserimento o modifica elemento in Grid (valori -> GRID)
{
    int                 nCol = 0;
    QString             szTemp;
    QTableWidgetItem    *tItem;
    bool                fAdd = false;

    // Insert Items at Row, Col
    for (nCol = 0; nCol < colTotals; nCol++)  {
        szTemp = lstRecValues[nCol];
        tItem = ui->tblCT->item(nRow, nCol);
        // Allocazione Elemento se non già definito
        if (tItem == NULL)  {
            fAdd = true;
            tItem = new QTableWidgetItem(szTemp);
        }
        else  {
            tItem->setText(szTemp);
        }
        // Allineamento
        if (nCol == colName || nCol == colComment)
            // Item Allineato a Sx
            tItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        else
            // Item Centrato in Cella
            tItem->setTextAlignment(Qt::AlignCenter);
        // Rende il valore non Editabile
        tItem->setFlags(tItem->flags() ^ Qt::ItemIsEditable);
        // Flag Marcatore della riga
        if (lstCTRecords[nRow].UsedEntry)
            ui->tblCT->showRow(nRow);
        else
            ui->tblCT->hideRow(nRow);
        // Aggiunta al Grid
        if (fAdd)  {
            ui->tblCT->setItem(nRow, nCol, tItem);
        }
    }
    return true;
}

bool    ctedit::ctable2Grid()
// Lettura di tutta la CT in Grid
{
    bool        fRes = true;
    int         nCur = 0;
    QStringList lstFields;

    lstFields.clear();
    lstUsedVarNames.clear();
    // Preparazione tabella
    this->setCursor(Qt::WaitCursor);
    ui->tblCT->setEnabled(false);
    ui->tblCT->clearSelection();
    ui->tblCT->setRowCount(0);
    ui->tblCT->clear();
    ui->tblCT->setColumnCount(colTotals);
    // Caricamento elementi
    for (nCur = 0; nCur < lstCTRecords.count(); ++nCur)  {
        // Covert CT Record 2 User Values
        fRes = recCT2List(lstFields, nCur);
        // Add Var Name to Variable List
        if (! lstFields[colName].isEmpty())
            lstUsedVarNames.append(lstFields[colName].trimmed());
        // If Ok add row to Table View
        if (fRes)  {
            ui->tblCT->insertRow(nCur);
            fRes = list2GridRow(lstFields, nCur);
        }
    }
    qDebug() << tr("Loaded Rows: %1") .arg(nCur);
    // Ordinamento Lista Variabili
    lstUsedVarNames.sort();
    // Impostazione parametri TableView
    ui->tblCT->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblCT->setHorizontalHeaderLabels(lstHeadCols);
    // ui->tblCT->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblCT->setEnabled(true);
    // Show All Elements
    if (fRes)  {
        m_fShowAllRows = false;
        m_isCtModified = false;
        ui->cmdHideShow->setChecked(m_fShowAllRows);
        ui->cmdSave->setEnabled(true);
        // ui->cmdSave->setEnabled(m_isCtModified);
        showAllRows(m_fShowAllRows);
    }
    else
        qDebug() << tr("Error Loading Rows");
    // Return value
    this->setCursor(Qt::ArrowCursor);
    return fRes;
}
bool ctedit::recCT2List(QStringList &lstRecValues, int nRow)
// Conversione da CT Record a record come Lista Stringhe per Interfaccia (Grid)
// Da Record C a QStringList di valori per caricamento griglia
{
    QString szTemp;
    char ip[MAX_IPADDR_LEN];

    if (nRow < 0 || nRow >= lstCTRecords.count())
        return false;
    // Pulizia Buffers
    szTemp.clear();
    listClear(lstRecValues);
    // Recupero informazioni da Record CT
    // Abilitazione riga
    if (lstCTRecords[nRow].UsedEntry)  {
        // Priority
        if (lstCTRecords[nRow].Enable >= 0 && lstCTRecords[nRow].Enable < lstPriority.count())
            lstRecValues[colPriority] = lstPriority[lstCTRecords[nRow].Enable];
        // Campo Update
        if (lstCTRecords[nRow].Plc >= 0 && lstCTRecords[nRow].Plc < lstPLC.count())
            lstRecValues[colUpdate] = lstPLC[lstCTRecords[nRow].Plc];
        // Campo Name
        lstRecValues[colName] = QString::fromAscii(lstCTRecords[nRow].Tag);
        // Campo Type
        if (lstCTRecords[nRow].Types >= BIT && lstCTRecords[nRow].Types <= UNKNOWN)
            lstRecValues[colType] = lstTipi[lstCTRecords[nRow].Types];
        // Campo Decimal
        lstRecValues[colDecimal] = QString::number(lstCTRecords[nRow].Decimal);
        // Protocol
        if (lstCTRecords[nRow].Protocol >= 0 && lstCTRecords[nRow].Protocol < lstBusType.count())
            lstRecValues[colProtocol] = lstBusType[lstCTRecords[nRow].Protocol];
        // IP Address (Significativo solo per Protocolli a base TCP)
        if (lstCTRecords[nRow].Protocol == TCP || lstCTRecords[nRow].Protocol == TCPRTU ||
                lstCTRecords[nRow].Protocol == TCP_SRV || lstCTRecords[nRow].Protocol ==TCPRTU_SRV)  {
            ipaddr2str(lstCTRecords[nRow].IPAddress, ip);
            szTemp = QString::fromAscii(ip);
        }
        else
            szTemp = szEMPTY;
        lstRecValues[colIP] = szTemp;
        // Port
        lstRecValues[colPort] = QString::number(lstCTRecords[nRow].Port);
        // Node Id
        lstRecValues[colNodeID] = QString::number(lstCTRecords[nRow].NodeId);
        // Register
        lstRecValues[colRegister] = QString::number(lstCTRecords[nRow].Offset);
        // Block
        lstRecValues[colBlock] = QString::number(lstCTRecords[nRow].Block);
        // N.Registro
        lstRecValues[colBlockSize] = QString::number(lstCTRecords[nRow].BlockSize);
        // Commento
        lstRecValues[colComment] = QString::fromAscii(lstCTRecords[nRow].Comment).trimmed();
        // Behavior
        // Caso Read/ReadWrite
        if (lstCTRecords[nRow].Output == _FALSE)
            lstRecValues[colBehavior] = lstBehavior[bevReadOnly];
        else if (lstCTRecords[nRow].Output == _TRUE)
            lstRecValues[colBehavior] = lstBehavior[bevReadWrite];
        // Caso Alarm / Event
            // bevAlarm,
            // bevEvent,

    }
    // Return value
    return true;
}

void ctedit::on_cmdHideShow_clicked(bool checked)
{

    // Titolo del Bottone
    if (checked)  {
        m_fShowAllRows = true;
        ui->cmdHideShow->setText(tr("Hide Unused"));
    }
    else  {
        m_fShowAllRows = false;
        ui->cmdHideShow->setText(tr("Show All"));
    }
    // Show-Hide Rows
    showAllRows(m_fShowAllRows);
}
bool ctedit::values2Iface(QStringList &lstRecValues)
// Copia Lista Stringhe convertite da CT Record a Zona di Editing
// Caricamento Lista valori stringa su area editing
{
    QString szTemp;
    int     nPos = 0;

    // Row #
    szTemp = QLocale::system().toString(m_nGridRow + 1);
    ui->txtRow->setText(szTemp);
    // Priority
    szTemp = lstRecValues[colPriority].trimmed();
    ui->cboPriority->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = searchCombo(ui->cboPriority, szTemp);
        if (nPos >= 0 && nPos < ui->cboPriority->count())
            ui->cboPriority->setCurrentIndex(nPos);
    }       
    // Update
    szTemp = lstRecValues[colUpdate].trimmed();
    ui->cboUpdate->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = searchCombo(ui->cboUpdate, szTemp);
        if (nPos >= 0 && nPos < ui->cboUpdate->count())
            ui->cboUpdate->setCurrentIndex(nPos);
    }
    // Name
    szTemp = lstRecValues[colName].trimmed();
    ui->txtName->setText(szTemp);
    // Type
    szTemp = lstRecValues[colType].trimmed();
    ui->cboType->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = searchCombo(ui->cboType, szTemp);
        if (nPos >= 0 && nPos < ui->cboType->count())
            ui->cboType->setCurrentIndex(nPos);
    }
    // Decimal
    szTemp = lstRecValues[colDecimal].trimmed();
    ui->txtDecimal->setText(szTemp);
    /*ui->cboDecimal->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = searchCombo(ui->cboDecimal, szTemp);
        if (nPos >= 0 && nPos < ui->cboDecimal->count())
            ui->cboDecimal->setCurrentIndex(nPos);
    } */
    // Protocol
    szTemp = lstRecValues[colProtocol].trimmed();
    ui->cboProtocol->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = searchCombo(ui->cboProtocol, szTemp);
        if (nPos >= 0 && nPos < ui->cboProtocol->count())
            ui->cboProtocol->setCurrentIndex(nPos);
    }
    // IP
    szTemp = lstRecValues[colIP].trimmed();
    ui->txtIP->setText(szTemp);
    // Port
    szTemp = lstRecValues[colPort].trimmed();
    ui->txtPort->setText(szTemp);
    // Node ID
    szTemp = lstRecValues[colNodeID].trimmed();
    ui->txtNode->setText(szTemp);
    // Register
    szTemp = lstRecValues[colRegister].trimmed();
    ui->txtRegister->setText(szTemp);
    // Block
    szTemp = lstRecValues[colBlock].trimmed();
    ui->txtBlock->setText(szTemp);
    // N° Registro
    szTemp = lstRecValues[colBlockSize].trimmed();
    ui->txtBlockSize->setText(szTemp);
    // Comment
    szTemp = lstRecValues[colComment].trimmed();
    ui->txtComment->setText(szTemp);
    // Behavior
    szTemp = lstRecValues[colBehavior].trimmed();
    ui->cboBehavior->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = searchCombo(ui->cboBehavior, szTemp);
        if (nPos >= 0 && nPos < ui->cboBehavior->count())
            ui->cboBehavior->setCurrentIndex(nPos);
    }
    enableFields();
    return true;
}
bool ctedit::iface2values(QStringList &lstRecValues)
// Copia da Zona Editing a Lista Stringhe per Grid e Record CT
{
    QString szTemp;
    int     nPos = 0;

    // Pulizia Buffers
    szTemp.clear();
    listClear(lstRecValues);
    // Priority
    nPos = ui->cboPriority->currentIndex();
    if (nPos>= 0 && nPos < lstPriority.count())
        szTemp = ui->cboPriority->itemData(nPos).toString();
    else
        szTemp = szEMPTY;
    lstRecValues[colPriority] = szTemp.trimmed();
    // Update colUpdate
    nPos = ui->cboUpdate->currentIndex();
    if (nPos >= 0 && nPos < lstPLC.count())
        szTemp = ui->cboUpdate->itemData(nPos).toString();
    else
        szTemp = szEMPTY;
    lstRecValues[colUpdate] = szTemp;
    // Name
    szTemp = ui->txtName->text().trimmed();
    lstRecValues[colName] = szTemp;
    // Type colType
    nPos = ui->cboType->currentIndex();
    if (nPos >= 0 && nPos < lstTipi.count())
        szTemp = ui->cboType->itemData(nPos).toString();
    else
        szTemp = szEMPTY;
    lstRecValues[colType] = szTemp.trimmed();
    // Decimal
    szTemp = ui->txtDecimal->text();
    lstRecValues[colDecimal] = szTemp.trimmed();
    // Protocol lstBusType
    nPos = ui->cboProtocol->currentIndex();
    if (nPos >= 0 && nPos < lstBusType.count())
        szTemp = ui->cboProtocol->itemData(nPos).toString();
    else
        szTemp = szEMPTY;
    lstRecValues[colProtocol] = szTemp.trimmed();
    // IP
    szTemp = ui->txtIP->text();
    lstRecValues[colIP] = szTemp.trimmed();
    // Port
    szTemp = ui->txtPort->text();
    lstRecValues[colPort] = szTemp.trimmed();
    // Node ID
    szTemp = ui->txtNode->text();
    lstRecValues[colNodeID]  = szTemp.trimmed();
    // Register
    szTemp = ui->txtRegister->text();
    lstRecValues[colRegister] = szTemp.trimmed();
    // Block
    szTemp = ui->txtBlock->text();
    lstRecValues[colBlock] = szTemp.trimmed();
    // N° Registro
    szTemp = ui->txtBlockSize->text();
    lstRecValues[colBlockSize] = szTemp.trimmed();
    // Comment
    szTemp = ui->txtComment->text();
    lstRecValues[colComment] = szTemp.trimmed();
    // Behavior
    nPos = ui->cboBehavior->currentIndex();
    if (nPos >= 0 && nPos < lstBehavior.count())
        szTemp = ui->cboBehavior->itemData(nPos).toString();
    else
        szTemp = szEMPTY;
    lstRecValues[colBehavior] = szTemp.trimmed();
    // Return value
    return true;
}

void ctedit::on_cmdBlocchi_clicked()
{
    if (riassegnaBlocchi())  {
        m_isCtModified = true;
    }
    // Refresh abilitazioni interfaccia
    enableInterface();
}

void ctedit::on_cmdSave_clicked()
{
    bool fRes = false;

    fRes = saveCTFile();
    if (!fRes)  {
        m_szMsg = tr("Error Saving Cross Table File: %1\n").arg(m_szCurrentCTFile);
        warnUser(this, szTitle, m_szMsg);
    }
    else {
        m_isCtModified = false;
    }
    // Refresh abilitazioni interfaccia
    enableInterface();
}
// Riassegnazione blocchi variabili
bool    ctedit::riassegnaBlocchi()
{
    int             nRow = 0;
    bool            fRes = false;
    int             nPrevRow = -2;
    int             nBlockStart = -1;
    int             j = 0;
    FieldbusType    prevProtocol = (FieldbusType) 0;
    uint32_t        prevIpAdr = 0;
    uint16_t        prevPort = 0;
    int16_t         prevPriority = 0;
    varTypes        prevType = (varTypes) 0;
    uint8_t         prevNodeId = 0;
    uint16_t        curBlock = 0;
    int16_t         curBSize = (int16_t) 0;

    ui->cmdBlocchi->setEnabled(false);
    this->setCursor(Qt::WaitCursor);
    // Copia l'attuale CT nella lista Undo
    lstUndo.append(lstCTRecords);
    for (nRow = 0; nRow < MIN_SYSTEM; nRow++)  {
        // Ignora le righe con Priority == 0
        if (lstCTRecords[nRow].Enable > 0)  {
            // Salto riga o condizione di inizio nuovo blocco
            // Inizio nuovo blocco
            if (nPrevRow != nRow - 1 || prevPriority != lstCTRecords[nRow].Enable || prevType != lstCTRecords[nRow].Types || prevProtocol !=  lstCTRecords[nRow].Protocol
                    || prevIpAdr != lstCTRecords[nRow].IPAddress || prevPort != lstCTRecords[nRow].Port || prevNodeId != lstCTRecords[nRow].NodeId
                    || curBSize >= MAXBLOCKSIZE)  {
                // Rinumera block start del Blocco precedente se esiste
                if ((nBlockStart > 0) && (nRow - nBlockStart > 1))  {
                    for (j = nBlockStart; j < nRow; j++)  {
                        lstCTRecords[j].BlockSize = curBSize;
                    }
                }
                // Imposta i valori di confronto correnti
                nBlockStart = nRow;
                prevPriority = lstCTRecords[nRow].Enable;
                prevProtocol =  lstCTRecords[nRow].Protocol;
                prevIpAdr = lstCTRecords[nRow].IPAddress;
                prevPort = lstCTRecords[nRow].Port;
                prevType = lstCTRecords[nRow].Types;
                prevNodeId = lstCTRecords[nRow].NodeId;
                curBlock = (int16_t) nBlockStart + 1;
                curBSize = 1;
            }
            // Prosecuzione Blocco corrente
            else  {
                ++curBSize;
            }
            // Aggiornamento Blocco e Size
            lstCTRecords[nRow].Block = curBlock;
            lstCTRecords[nRow].BlockSize = curBSize;
            // Incremento ultima riga significativa
            nPrevRow = nRow;
        }
        else
            lstCTRecords[nRow].Block = 0;
    }
    // Rinumera ultimo blocco trattato (se esiste)
    if (nBlockStart > 0)  {
        for (j = nBlockStart; j < nRow; j++)  {
            lstCTRecords[j].BlockSize = curBSize;
        }
    }
    // Return value as reload CT
    fRes = ctable2Grid();
    qDebug() << "Reload finished";
    ui->cmdBlocchi->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
    return fRes;
}
bool ctedit::saveCTFile()
{
    int nRes = 0;
    int nCur = 0;

    // Back-Up Copy of CT File
    fileBackUp(m_szCurrentCTFile);
    // Copy CT Record List to C Array
    for (nCur = 0; nCur < lstCTRecords.count(); ++nCur)  {
        if (nCur < DimCrossTable)
            CrossTable[nCur + 1] = lstCTRecords[nCur];
    }
    /*
    QString szCtFile;
    // Trigo per ora per preparare un File name differente per non perdere l'originale
    // Al momento riscrive (forse) una fotocopia della stuttura C di partenza
    szCtFile = QString(QDate::currentDate().toString(m_szFormatDate));
    szCtFile.prepend(QString::fromAscii("_"));
    szCtFile.append(QString::fromAscii("_"));
    szCtFile.append(QString(QTime::currentTime().toString(m_szFormatTime)));
    szCtFile.prepend(m_szCurrentCTFile);
    */
    // Saving File to Juornaled Copy
    // nRes = SaveXTable(szCtFile.toAscii().data(), CrossTable);
    // Saving Source Array to file
    nRes = SaveXTable(m_szCurrentCTFile.toAscii().data(), CrossTable);
    // Return Value
    return nRes == 0;
}
bool ctedit::grid2CTable()
// Dump di tutto il Grid in lista di CT Records
{
    bool        fRes = true;
    int         nCur = 0;
    int         nCol = 0;
    QString     szTemp;
    QTableWidgetItem    *tItem;
    QStringList lstFields;

    // Ciclo sugli elementi di Grid
    for (nCur = 1; nCur <= ui->tblCT->rowCount(); ++nCur)  {
        lstFields.clear();
        // Insert Items at Row, Col
        for (nCol = 1; nCol < colTotals; nCol++)  {
            tItem = ui->tblCT->item(nCur, nCol);
            szTemp = tItem->text();
            // Aggiunta alla Lista
            lstFields.append(szTemp);
        }
        // Covert back User Values 2 CT Record
        fRes = list2CTrec(lstFields, nCur);
    }
    // Return Value
    return fRes;
}
void ctedit::freeCTrec(int nRow)
// Marca il Record della CT come inutilizzato
{
    if (nRow < 0 || nRow >= lstCTRecords.count())
        return;
    lstCTRecords[nRow].UsedEntry = 0;
    lstCTRecords[nRow].Enable = 0;
    lstCTRecords[nRow].Plc = (UpdateType) 0;
    strcpy(lstCTRecords[nRow].Tag, "");
    lstCTRecords[nRow].Types = (varTypes) 0;
    lstCTRecords[nRow].Decimal = 0;
    lstCTRecords[nRow].Protocol = (FieldbusType) 0;
    lstCTRecords[nRow].IPAddress = 0;
    lstCTRecords[nRow].Port = 0;
    lstCTRecords[nRow].NodeId = 0;
    lstCTRecords[nRow].Offset = 0;
    lstCTRecords[nRow].Block = 0;
    lstCTRecords[nRow].BlockBase = 0;
    lstCTRecords[nRow].Output = 0;
    lstCTRecords[nRow].Counter = 0;
    lstCTRecords[nRow].OldVal = 0;
    lstCTRecords[nRow].Error = 0;
    lstCTRecords[nRow].usedInAlarmsEvents = 0;
    lstCTRecords[nRow].device = 0;
    strcpy(lstCTRecords[nRow].Comment, "");
}
void ctedit::listClear(QStringList &lstRecValues)
// Svuotamento e pulizia Lista Stringhe per passaggio dati Interfaccia <---> Record CT
{
    int nCol = 0;
    lstRecValues.clear();
    for (nCol = 0; nCol < colTotals; nCol++)  {
        lstRecValues.append(szEMPTY);
    }
}

bool ctedit::list2CTrec(QStringList &lstRecValues, int nRow)
// Conversione da Lista Valori di Interfaccia a CT Record (Form -> REC SINGOLO)
// Scrive un Record letto da interfaccia direttamente in lista di Record C
{
    bool        fRes = true;
    bool        fOk = false;
    int         nPos = 0;
    char        ip[MAX_IPADDR_LEN];

    // Abilitazione riga (Nome Vuoto => Riga disabilitata)
    if (lstRecValues[colName].isEmpty())  {
        freeCTrec(nRow);
    }
    else  {
        // Priority
        nPos = lstPriority.indexOf(lstRecValues[colPriority]);
        nPos = (nPos >= 0 && nPos < lstPriority.count()) ? nPos : 0;
        lstCTRecords[nRow].Enable = (int16_t) nPos;
        // Update
        nPos = lstPLC.indexOf(lstRecValues[colUpdate]);
        nPos = (nPos >= 0 && nPos < lstPLC.count()) ? nPos : 0;
        lstCTRecords[nRow].Plc = (UpdateType) nPos;
        // Campo Name
        strcpy(lstCTRecords[nRow].Tag, lstRecValues[colName].trimmed().toAscii().data());
        // Campo Abilitazione record
        if (strlen(lstCTRecords[nRow].Tag) > 0)
            lstCTRecords[nRow].UsedEntry = 1;
        else
            lstCTRecords[nRow].UsedEntry = 0;
        // Campo Type
        nPos = lstTipi.indexOf(lstRecValues[colType]);
        nPos = (nPos >= 0 && nPos < lstTipi.count()) ? nPos : 0;
        lstCTRecords[nRow].Types = (varTypes) nPos;
        // Campo Decimal
        nPos = lstRecValues[colDecimal].toInt(&fOk);
        nPos = fOk ? nPos : 0;
        lstCTRecords[nRow].Decimal = nPos;
        // Protocol
        nPos = lstBusType.indexOf(lstRecValues[colProtocol]);
        nPos = (nPos >= 0 && nPos < lstBusType.count()) ? nPos : 0;
        lstCTRecords[nRow].Protocol = (FieldbusType) nPos;
        // IP Address (Significativo solo per Protocolli a base TCP)
        if (lstCTRecords[nRow].Protocol == TCP || lstCTRecords[nRow].Protocol == TCPRTU ||
                lstCTRecords[nRow].Protocol == TCP_SRV || lstCTRecords[nRow].Protocol ==TCPRTU_SRV)  {
            strcpy(ip, lstRecValues[colIP].trimmed().toAscii().data());
            nPos = str2ipaddr(ip);
            lstCTRecords[nRow].IPAddress = (uint32_t) nPos;
        }
        else
            lstCTRecords[nRow].IPAddress = (uint32_t) 0 ;
        // Port
        nPos = lstRecValues[colPort].toInt(&fOk);
        nPos = fOk ? nPos : 0;
        lstCTRecords[nRow].Port = nPos;
        // Node Id
        nPos = lstRecValues[colNodeID].toInt(&fOk);
        nPos = fOk ? nPos : 0;
        lstCTRecords[nRow].NodeId = nPos;
        // Register
        nPos = lstRecValues[colRegister].toInt(&fOk);
        nPos = fOk ? nPos : 0;
        lstCTRecords[nRow].Offset = nPos;
        // Block
        nPos = lstRecValues[colBlock].toInt(&fOk);
        nPos = fOk ? nPos : 0;
        lstCTRecords[nRow].Block = nPos;
        // N.Registro
        nPos = lstRecValues[colBlockSize].toInt(&fOk);
        nPos = fOk ? nPos : 0;
        lstCTRecords[nRow].BlockSize = nPos;
        // Commento
        strcpy(lstCTRecords[nRow].Comment, lstRecValues[colComment].trimmed().toAscii().data());
        // Behavior
        nPos = lstBehavior.indexOf(lstRecValues[colBehavior]);
        nPos = (nPos >= 0 && nPos < lstBehavior.count()) ? nPos : 0;
        lstCTRecords[nRow].Output= (int) nPos;
    }
    // Return Value
    return fRes;
}
void ctedit::enableFields()
// Abilitazione dei campi form in funzione del Protocollo
{
    // Frame tipo Vars
    showGroupVars(m_nGridRow);
    // Disabilita tutti i campi
    ui->cboPriority->setEnabled(false);
    ui->cboUpdate->setEnabled(false);
    ui->txtName->setEnabled(false);
    ui->cboType->setEnabled(false);
    ui->txtDecimal->setEnabled(false);
    ui->cboProtocol->setEnabled(false);
    ui->txtIP->setEnabled(false);
    ui->txtPort->setEnabled(false);
    ui->txtNode->setEnabled(false);
    ui->txtRegister->setEnabled(false);
    ui->txtComment->setEnabled(false);
    ui->cboBehavior->setEnabled(false);
    // Variabili di Sistema, abilitate in modifica solo il nome, priorità, update. No Insert in campi vuoti
    if (m_nGridRow >= MIN_SYSTEM -1)  {
        if (ui->cboProtocol->currentIndex() != -1)  {
            ui->cboPriority->setEnabled(true);
            ui->cboUpdate->setEnabled(true);
            ui->txtName->setEnabled(true);
            ui->txtComment->setEnabled(true);
        }
    }
    else  {
        // Campi comuni
        ui->cboPriority->setEnabled(true);
        ui->cboUpdate->setEnabled(true);
        ui->txtName->setEnabled(true);
        ui->cboType->setEnabled(true);
        ui->txtDecimal->setEnabled(true);
        ui->cboProtocol->setEnabled(true);
        ui->txtComment->setEnabled(true);
        ui->cboBehavior->setEnabled(true);
        // Abilitazione dei campi in funzione del Tipo
        // Protocollo non definito, es per Riga vuota
        if (ui->cboProtocol->currentIndex() == -1)  {
            ui->txtIP->setEnabled(true);
            ui->txtPort->setEnabled(true);
            ui->txtNode->setEnabled(true);
            ui->txtRegister->setEnabled(true);
        }
        // PLC
        else if (ui->cboProtocol->currentIndex() == PLC)  {
            // All Data Entry Locked
        }
        // RTU
        else if (ui->cboProtocol->currentIndex() == RTU)  {
            ui->txtPort->setEnabled(true);
            ui->txtNode->setEnabled(true);
            ui->txtRegister->setEnabled(true);
        }
        // TCP, TCPRTU, TCP_SRV, TCPRTU_SRV
        else if (ui->cboProtocol->currentIndex() == TCP || ui->cboProtocol->currentIndex() == TCPRTU  ||
                 ui->cboProtocol->currentIndex() == TCP_SRV || ui->cboProtocol->currentIndex() == TCPRTU_SRV)  {
            ui->txtIP->setEnabled(true);
            ui->txtPort->setEnabled(true);
            ui->txtNode->setEnabled(true);
            ui->txtRegister->setEnabled(true);
        }
        // CANOPEN
        else if (ui->cboProtocol->currentIndex() == CANOPEN)  {
            ui->txtNode->setEnabled(true);
            ui->txtRegister->setEnabled(true);
        }
        // MECT
        else if (ui->cboProtocol->currentIndex() == MECT_PTC)  {
            ui->txtNode->setEnabled(true);
            ui->txtRegister->setEnabled(true);
        }
        // RTU_SRV
        else if (ui->cboProtocol->currentIndex() == RTU_SRV)  {
            ui->txtNode->setEnabled(true);
            ui->txtRegister->setEnabled(true);
        }
    }
}
void ctedit::showGroupVars(int nRow)
// Imposta il gruppo di appartenenza di una variabile (Ritentivo, NR, System)
{
    // Variabile Ritentiva
    if (nRow >= 0 && nRow < MAX_RETENTIVE)  {
        ui->optRetentive->setChecked(true);
        ui->optNonRetentive->setChecked(false);
        ui->optSystem->setChecked(false);
    }
    // Variabile NON Ritentiva
    else if (nRow >= MIN_NONRETENTIVE - 1 && nRow < MAX_NONRETENTIVE)  {
        ui->optRetentive->setChecked(false);
        ui->optNonRetentive->setChecked(true);
        ui->optSystem->setChecked(false);
    }
    // Variabile System
    else if (nRow >= MIN_SYSTEM -1 && nRow < DimCrossTable)  {
        ui->optRetentive->setChecked(false);
        ui->optNonRetentive->setChecked(false);
        ui->optSystem->setChecked(true);
    }
}
void ctedit::on_cboType_currentIndexChanged(int index)
// Cambio di tipo della variabile
{

    // Il tipo Bit forza i Decimali a 0 e rende il campo non editabile
    if (index == BIT)  {
        ui->txtDecimal->setText(szZERO);
        ui->txtDecimal->setEnabled(false);
    }
    else  {
        ui->txtDecimal->setEnabled(true);
        // Default 1 decimale se non specificato o presente valore
        if (ui->txtDecimal->text().isEmpty())
            ui->txtDecimal->setText(QString::fromAscii("1"));
    }
}
void ctedit::on_cboProtocol_currentIndexChanged(int index)
// Cambio di Protocollo della Variabile
{
    QString     szTemp;

    szTemp.clear();
    // No Index
    if (index == -1)  {
        ui->txtIP->setText(szEMPTY);
        ui->txtPort->setText(szEMPTY);
        ui->txtNode->setText(szEMPTY);
        ui->txtRegister->setText(szEMPTY);
    }
    // PLC
    else if (index == PLC)  {
        // All Data Entry Cleared
        ui->txtIP->setText(szEMPTY);
        ui->txtPort->setText(szEMPTY);
        ui->txtNode->setText(szEMPTY);
        ui->txtRegister->setText(szEMPTY);
    }
    // RTU
    else if (index == RTU)  {
        // Ip Vuoto
        ui->txtIP->setText(szEMPTY);
        // Port in funzione del modello e non editabile
        szTemp = ui->txtPort->text();
        if (szTemp.isEmpty())  {
            szTemp = QString::fromAscii("1");
            ui->txtPort->setText(szTemp);
        }

    }
    // TCP, TCPRTU,
    else if (index == TCP || index == TCPRTU)  {
        szTemp = szDEF_IP_PORT;
        ui->txtPort->setText(szTemp);
    }
    // TCP_SRV, TCPRTU_SRV
    else if (index == TCP_SRV || index == TCPRTU_SRV)  {
        szTemp = szDEF_IP_PORT;
        ui->txtPort->setText(szTemp);
        szTemp = szEMPTY_IP;
        ui->txtIP->setText(szTemp);
    }
    // CANOPEN
    else if (index == CANOPEN)  {
        ui->txtIP->setText(szEMPTY);
        szTemp = QString::fromAscii("1");
        ui->txtPort->setText(szTemp);
    }
    // MECT
    else if (index == MECT_PTC)  {
        ui->txtIP->setText(szEMPTY);
        ui->txtPort->setText(szZERO);
    }
    // RTU_SRV
    else if (index == RTU_SRV)  {
        ui->txtIP->setText(szEMPTY);
        ui->txtPort->setText(szZERO);
    }
    // Abilitazione del campi di data entry in funzione del Protocollo
    enableFields();
}
void ctedit::tableItemChanged(const QItemSelection & selected, const QItemSelection & deselected)
// Slot attivato ad ogni cambio di riga in
{
    int     nRow = -1;
    bool    fRes = true;
    QStringList lstFields;
    bool    fIsModif = false;

    if (! deselected.isEmpty())  {
        // Considera sempre la prima riga della lista
        nRow = deselected.indexes().at(0).row();
        qDebug() << "Previous Row: " << nRow;
    }
    // Se la riga corrente è stata modificata, salva il contenuto
    if (nRow >= 0 && nRow < lstCTRecords.count())  {
        if (isLineModified())  {
            // Primo controllo di coerenza sulla riga corrente
            fRes = checkFields();
            if (fRes)  {
                // Copia l'attuale CT nella lista Undo
                lstUndo.append(lstCTRecords);
                // Valori da interfaccia a CT
                fRes = iface2values(lstFields);
                if (fRes)  {
                    // Salva Record
                    fIsModif = list2CTrec(lstFields, nRow);
                    // Aggiorna Grid Utente per riga corrente
                    if (fIsModif)  {
                        fRes = list2GridRow(lstFields, nRow);
                    }
                    qDebug() << "Row changed:" << nRow;
                }
            }
        }
    }
    // Cambio riga Ko
    if (! fRes)    {
        ui->tblCT->selectRow(nRow);
        return;
    }
    // Marca CT come modificata
    if (! m_isCtModified && fIsModif)  {
        m_isCtModified = true;
    }
    // Si può cambiare riga, legge contenuto
    if (! selected.isEmpty())  {
        clearEntryForm();
        // Estrae il numero di riga del modello lavorando sulla prima riga selezionata
        nRow = selected.indexes().at(0).row();
        qDebug() << "New Row: " << nRow;
        if (nRow >= 0)  {
            // Cambia riga corrente
            m_nGridRow = nRow;
            // Covert CT Record 2 User Values
            fRes = recCT2List(lstFields, nRow);
            if (fRes)
                fRes = values2Iface(lstFields);
        }
    }
    else  {
        clearEntryForm();
    }
    // Refresh abilitazioni interfaccia
    enableInterface();
}
void ctedit::clearEntryForm()
// Svutamento elementi Form Data Entry
{
    ui->cboPriority->setCurrentIndex(-1);
    ui->cboUpdate->setCurrentIndex(-1);
    ui->txtName->setText(szEMPTY);
    ui->cboType->setCurrentIndex(-1);
    ui->txtDecimal->setText(szEMPTY);
    ui->cboProtocol->setCurrentIndex(-1);
    ui->txtIP->setText(szEMPTY);
    ui->txtPort->setText(szEMPTY);
    ui->txtNode->setText(szEMPTY);
    ui->txtRegister->setText(szEMPTY);
    ui->txtBlock->setText(szEMPTY);
    ui->txtBlockSize->setText(szEMPTY);
    ui->txtComment->setText(szEMPTY);
    ui->cboBehavior->setCurrentIndex(-1);
}
bool ctedit::checkFields()
// Primi controlli formali sulla riga a termine editing
{
    bool    fRes = true;

    // Nessun Controllo su riga vuota
    if (lstCTRecords[m_nGridRow].UsedEntry == 0)  {
        return true;
    }
    // Return Value
    return fRes;
}

void ctedit::displayUserMenu(const QPoint &pos)
// Menu contestuale Grid
{
    int             nRow = ui->tblCT->rowAt(pos.y());
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();

    // Aggiornamento numero riga
    if (nRow >= 0)  {
        m_nGridRow = nRow;
    }
    // Oggetto menu contestuale
    QMenu gridMenu(this);
    // Items del Menu contestuale
    // Inserisci righe
    QAction *insRows = gridMenu.addAction(trUtf8("Inserisci righe"));
    insRows->setEnabled(selection.count() > 0);
    // Elimina righe
    QAction *remRows = gridMenu.addAction(trUtf8("Elimina righe"));
    remRows->setEnabled(selection.count() > 0);
    // Sep1
    QAction *sep1 = gridMenu.addSeparator();
    // Copia righe
    QAction *copyRows = gridMenu.addAction(trUtf8("Copia righe"));
    copyRows->setEnabled(selection.count() > 0);
    // Taglia righe
    QAction *cutRows = gridMenu.addAction(trUtf8("Taglia righe"));
    cutRows->setEnabled(selection.count() > 0);
    // Sep 2
    QAction *sep2 = gridMenu.addSeparator();
    // Paste Rows
    QAction *pasteRows = gridMenu.addAction(trUtf8("Incolla righe"));
    pasteRows->setEnabled(lstCopiedRecords.count() > 0 && m_nGridRow < MIN_SYSTEM);
    // Abilitazione delle voci di Menu
    // Esecuzione del Menu
    QAction *actMenu = gridMenu.exec(ui->tblCT->viewport()->mapToGlobal(pos));
    // Controllo dell'Azione selezionata
    // Inserimento righe
    if (actMenu == insRows)  {
        insertRows();
    }
    // Rimozione righe
    else if (actMenu == remRows)  {
        removeSelected();
    }
    // Copia
    else if (actMenu == copyRows)  {
        copySelected();
    }
    // Taglia
    else if (actMenu == cutRows)  {
        cutSelected();
    }
    // Incolla
    else if (actMenu == pasteRows)  {
        pasteSelected();
    }

}
void ctedit::copySelected()
// Copia delle righe selezionate in Buffer di Copiatura
{
    // Recupera righe selezionate
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();
    int             nRow = 0;
    int             nCur = 0;

    // Clear Copied Items Rows
    lstCopiedRecords.clear();
    // Compile Selected Row List
    for (nCur = 0; nCur < selection.count(); nCur++)  {
        // Reperisce l'Item Row Number dall'elenco degli elementi selezionati
        QModelIndex index = selection.at(nCur);
        nRow = index.row();
        if (nRow < MAX_NONRETENTIVE)  {
            lstCopiedRecords.append(lstCTRecords[nRow]);
        }
    }
    m_szMsg = tr("Rows Copied: ") .arg(lstCopiedRecords.count());
    displayStatusMessage(m_szMsg);
    qDebug() << m_szMsg;
}
void ctedit::pasteSelected()
// Incolla righe da Buffer di copiatura a Riga corrente
{
    int     nRow = ui->tblCT->currentRow();
    int     nCur = 0;

    // Paste Rows
    if (nRow >= 0 && nRow < MAX_NONRETENTIVE - 1 && lstCopiedRecords.count() > 0)  {
        if (nRow + lstCopiedRecords.count() < MAX_NONRETENTIVE)  {
            // Append to Undo List
            lstUndo.append(lstCTRecords);
            // Compile Selected Row List
            for (nCur = 0; nCur < lstCopiedRecords.count(); nCur ++)  {
                // Retrieve element
                lstCTRecords[nRow++] = lstCopiedRecords[nCur];
            }
            // Restore Grid
            ctable2Grid();
            m_isCtModified = true;
        }
        else  {
            m_szMsg = tr("The Copy Buffer Excedes System Variables Limit. Rows not copied");
            warnUser(this, szTitle, m_szMsg);
        }
    }
    m_szMsg = tr("Rows Pasted: ") .arg(lstCopiedRecords.count());
    displayStatusMessage(m_szMsg);
    qDebug() << m_szMsg;
    lstCopiedRecords.clear();
    enableInterface();
}

void ctedit::insertRows()
// Aggiunta righe in posizione cursore
{
    // Recupera righe selezionate
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();

    // Controllo di restare nei Bounding delle variabili utente
    if (m_nGridRow + selection.count() < MAX_NONRETENTIVE)  {
        // Append to Undo List
        lstUndo.append(lstCTRecords);
        //
        m_isCtModified = true;
    }
    m_szMsg = tr("Rows Inserted: ") .arg(selection.count());
    displayStatusMessage(m_szMsg);
    qDebug() << m_szMsg;
    enableInterface();
}
void ctedit::removeSelected()
// Rimozione delle righe correntemente selezionate
{
    // Recupera righe selezionate
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();
    int             nRow = 0;
    int             nCur = 0;
    int             nRemoved = 0;

    // Check Modif. and append data to Undo List
    if (selection.isEmpty())
        return;
    else
        lstUndo.append(lstCTRecords);
    // Compile Selected Row List
    for (nCur = 0; nCur < selection.count(); nCur++)  {
        // Reperisce l'Item Row Number dall'elenco degli elementi selezionati
        QModelIndex index = selection.at(nCur);
        nRow = index.row();
        if (nRow < MAX_NONRETENTIVE)  {
            freeCTrec(nRow);
            nRemoved++;
        }
    }
    // Refresh Grid
    if (nRemoved)  {
        ctable2Grid();
        m_isCtModified = true;
    }
    m_szMsg = tr("Rows Removed: ") .arg(lstCopiedRecords.count());
    displayStatusMessage(m_szMsg);
    qDebug() << m_szMsg;
    // Update Iface
    enableInterface();
}
void ctedit::cutSelected()
// Taglia righe in Buffer di copiatura
{
    // Copia Righe
    copySelected();
    // Elimina Righe
    if(lstCopiedRecords.count() > 0)
        removeSelected();
    // Result
    m_szMsg = tr("Rows Cutted: ") .arg(lstCopiedRecords.count());
    displayStatusMessage(m_szMsg);
    qDebug() << m_szMsg;
}
bool ctedit::isLineModified()
// Check su modifica record corrente
{
    bool    fRes = false;
    int     nModif = 0;

    // Confronto tra Interfaccia e Grid video
    if(m_nGridRow >= 0 && m_nGridRow < lstCTRecords.count())  {
        nModif += (ui->cboPriority->currentText().trimmed() != ui->tblCT->item(m_nGridRow, colPriority)->text().trimmed());
        nModif += (ui->cboUpdate->currentText().trimmed() != ui->tblCT->item(m_nGridRow, colUpdate)->text().trimmed());
        nModif += (ui->txtName->text().trimmed() != ui->tblCT->item(m_nGridRow, colName)->text().trimmed());
        nModif += (ui->cboType->currentText().trimmed() != ui->tblCT->item(m_nGridRow, colType)->text().trimmed());
        nModif += (ui->txtDecimal->text().trimmed() != ui->tblCT->item(m_nGridRow, colDecimal)->text().trimmed());
        nModif += (ui->cboProtocol->currentText().trimmed() != ui->tblCT->item(m_nGridRow, colProtocol)->text().trimmed());
        nModif += (ui->txtIP->text().trimmed() != ui->tblCT->item(m_nGridRow, colIP)->text().trimmed());
        nModif += (ui->txtPort->text().trimmed() != ui->tblCT->item(m_nGridRow, colPort)->text().trimmed());
        nModif += (ui->txtNode->text().trimmed() != ui->tblCT->item(m_nGridRow, colNodeID)->text().trimmed());
        nModif += (ui->txtRegister->text().trimmed() != ui->tblCT->item(m_nGridRow, colRegister)->text().trimmed());
        // nModif += (ui->txtBlock->text().trimmed() != ui->tblCT->item(m_nGridRow, colBlock)->text().trimmed());
        // nModif += (ui->txtBlockSize->text().trimmed() != ui->tblCT->item(m_nGridRow, colBlockSize)->text().trimmed());
        nModif += (ui->txtComment->text().trimmed() != ui->tblCT->item(m_nGridRow, colComment)->text().trimmed());
        nModif += (ui->cboBehavior->currentText().trimmed() != ui->tblCT->item(m_nGridRow, colBehavior)->text().trimmed());
        fRes = (nModif > 0);
    }
    qDebug() << "Modified():" << fRes << "N.Row:" << m_nGridRow << "Numero Modifiche:" << nModif;
    return fRes;
}

void ctedit::on_cmdImport_clicked()
// Import another Cross Table File
{
    QString szSourceFile;
    QString szMsg;
    QList<CrossTableRecord>  lstNewRecs, lstSourceRecs;
    int     nRow = 0;
    bool    fRes = false;

    szSourceFile = QFileDialog::getOpenFileName(this, tr("Import From Cross Table File"), m_szCurrentCTFile, tr("Cross Table File (*.csv)"));
    if (! szSourceFile.isEmpty())  {
        szMsg = tr("Rows from %1 to %2 will be overwritten !!\nDo you want to continue?") .arg(MIN_RETENTIVE) .arg(MAX_NONRETENTIVE);
        if (queryUser(this, szTitle, szMsg))  {
            lstNewRecs.clear();
            lstSourceRecs.clear();
            if (loadCTFile(szSourceFile, lstNewRecs, false))  {
                for (nRow = 0; nRow < MAX_NONRETENTIVE; nRow++)  {
                    lstSourceRecs.append(lstCTRecords[nRow]);
                    lstCTRecords[nRow] = lstNewRecs[nRow];
                }
                // Ricarica la lista dei dati CT in Grid
                fRes = ctable2Grid();
                if (fRes)  {
                    szMsg = tr("Loaded Cross Table from file:\n%1") .arg(szSourceFile);
                    notifyUser(this, szTitle, szMsg);
                }
                else {
                    szMsg = tr("Error Loading Cross Table from file:\n%1") .arg(szSourceFile);
                    szMsg.append(tr("\nOriginal Content Reloaded"));
                    warnUser(this, szTitle, szMsg);
                    for (nRow = 0; nRow < lstSourceRecs.count(); nRow++)  {
                        lstCTRecords[nRow] = lstSourceRecs[nRow];
                    }
                    fRes = ctable2Grid();
                }
            }
        }
    }
}
void ctedit::setRowColor(int nRow, int nAlternate)
// Imposta il colore di sfondo di una riga
{
    QColor      cSfondo = colorRetentive[0];

    // Impostazione del Backgound color in funzione della zona
    if (nRow >= 0 && nRow < MAX_RETENTIVE)  {
        cSfondo = colorRetentive[nAlternate];
        // qDebug() << tr("Row: %1 Alt: %2 - Retentive Row") .arg(nRow) .arg(nAlternate);
    }
    else if (nRow >= MIN_NONRETENTIVE - 1 && nRow <= MAX_NONRETENTIVE -1) {
        cSfondo = colorNonRetentive[nAlternate];
        // qDebug() << tr("Row: %1 Alt: %2 - NON Retentive Row") .arg(nRow) .arg(nAlternate);
    }
    else if (nRow >= MIN_SYSTEM - 1)  {
        // qDebug() << tr("Row: %1 Alt: %2 - SYSTEM Row") .arg(nRow) .arg(nAlternate);
        if (nRow < MAX_DIAG-1)  {
            cSfondo = colorSystem[0];
        }
        else if (nRow >= MIN_NODE - 1 && nRow < MAX_NODE - 1)  {
            cSfondo = colorSystem[1];
        }
        else if (nRow >= MIN_LOCALIO - 1  && nRow < MAX_LOCALIO - 1)  {
            cSfondo = colorSystem[0];
        }
        else  {
            cSfondo = colorSystem[1];
        }
    }
    // Impostazione del colore di sfondo
    QBrush bCell(cSfondo, Qt::SolidPattern);
    setRowBackground(bCell, ui->tblCT->model(), nRow);
    /*for (nCol = 0; nCol < colTotals; nCol++)  {
        tItem = ui->tblCT->item(nRow, nCol);
        tItem->setData(Qt::BackgroundRole, bCell);
        // tItem->setBackground(bCell);
    } */
}

void ctedit::showAllRows(bool fShowAll)
// Visualizza o nascondi tutte le righe
{
    int         nAlternate = 0;
    int         nFirstVisible = -1;
    int         nRow = 0;
    int16_t     nPrevBlock = -1;

    // Items del Grid
    for (nRow = 0; nRow < lstCTRecords.count(); nRow++)  {
        // Determina se il blocco corrente è cambiato dal precedente
        if (lstCTRecords[nRow].UsedEntry)  {
            if (nPrevBlock != lstCTRecords[nRow].Block)
                nAlternate = ((nAlternate + 1) % 2);
            nPrevBlock = lstCTRecords[nRow].Block;
        }
        else
            nPrevBlock = -1;
        // Impostazione colore riga
        setRowColor(nRow, nAlternate);
        // Mostra tutti
        if (fShowAll)  {
            ui->tblCT->showRow(nRow);
        }
        // Nascondi i non abilitati
        else  {
            // Mostra o nascondi le righe se sono abilitate
            if (lstCTRecords[nRow].UsedEntry)  {
                ui->tblCT->showRow(nRow);
                // Ricerca il primo Item visibile
                if (nFirstVisible < 0)
                    nFirstVisible = nRow ;
            }
            else  {
                ui->tblCT->hideRow(nRow);
            }
        }
    }
    // Riga corrente non definita
    if (m_nGridRow < 0 || m_nGridRow >= ui->tblCT->rowCount())  {
        m_nGridRow = nFirstVisible >= 0 ? nFirstVisible : 0;
    }
    else  {
        // Riga corrente piena ?
        if (lstCTRecords[m_nGridRow].UsedEntry == 0)
            m_nGridRow = nFirstVisible;
    }
    ui->tblCT->selectRow(m_nGridRow);
    ui->tblCT->scrollToItem(ui->tblCT->currentItem(), QAbstractItemView::PositionAtCenter);
    ui->tblCT->setFocus();
}
void ctedit::on_cmdGotoRow_clicked()
// Goto Row n
{

    bool fOk;

    if (! checkFields())
        return;
    // Input Dialog per Numero riga
    int nRow = QInputDialog::getInt(this, tr("Row to Jump To"),
                                 tr("Enter Row Number to Jump to:"), m_nGridRow + 1, 1, DimCrossTable, 1, &fOk);
    if (fOk)  {
        nRow--;
        jumpToGridRow(nRow);
    }
}
void ctedit::on_cmdSearch_clicked()
// Search Variable by Name
{
    bool fOk;
    int  nRow = 0;

    if (! checkFields())
        return;
    // Input Dialog per Nome Variabile
    QString szText;

    szText.clear();
    szText = QInputDialog::getItem(this, tr("Variable Name"),
                                            tr("Enter Variable Name:"), lstUsedVarNames, 0, true, &fOk);
    if (fOk)  {
        // Ricerca sequenziale della stringa
        for (nRow = 0; nRow < lstCTRecords.count(); nRow++)    {
            QString szVarName = QString::fromAscii(lstCTRecords[nRow].Tag);
            if (QString::compare(szText, szVarName, Qt::CaseSensitive) == 0)  {
                break;
            }
        }
        // Item Found
        if (nRow < lstCTRecords.count()) {
            jumpToGridRow(nRow);
        }
    }
}
void ctedit::jumpToGridRow(int nRow)
// Salto alla riga nRow del Grid
{
    // Controlla se la riga selezionata è abilitata. In caso contrario deve abilitare visualizzazione di tutte le righe
    ui->tblCT->selectRow(nRow);
    if (lstCTRecords[nRow].UsedEntry == 0)  {
        on_cmdHideShow_clicked(true);
    }
    // In entrambi i casi cerca di centrare la riga nel grid
    ui->tblCT->scrollToItem(ui->tblCT->currentItem(), QAbstractItemView::PositionAtCenter);
    ui->tblCT->setFocus();
    m_nGridRow = nRow;
}

void ctedit::on_cmdCompile_clicked()
// Generate Compiled Files
{
    QString     szCommand = QCoreApplication::applicationDirPath();     // QT Creator Bin Directory
    QStringList lstArguments;
    QString     szTemp;
    QString     szFileName;
    QProcess    procCompile;
    int         nExitCode = 0;

    // CT Compiler Full Path
    szCommand.append(szSlash);
    szCommand.append(szCrossCompier);
    // Parametro 1: -c Nome del File sorgente CrossTable
    szTemp = QString::fromAscii("-c%1.csv") .arg(m_szCurrentCTName);
    lstArguments.append(szTemp);
    // Parametro 2: -g Nome del file GVL (Case preserved)
    szFileName = QString::fromAscii("%1.gvl") .arg(m_szCurrentCTName);
    szTemp = szFileName;
    szTemp.prepend(QString::fromAscii("-g"));
    lstArguments.append(szTemp);
    szFileName.prepend(m_szCurrentCTPath);
    fileBackUp(szFileName);
    // Parametro 3: -i Nome del file .h (Forced LowerCase)
    szFileName = QString::fromAscii("%1.h") .arg(m_szCurrentCTName.toLower());
    szTemp = szFileName;
    szTemp.prepend(QString::fromAscii("-i"));
    lstArguments.append(szTemp);
    szFileName.prepend(m_szCurrentCTPath);
    fileBackUp(szFileName);
    // Parametro 4: -s Nome del file .h (Forced LowerCase)
    szFileName = QString::fromAscii("%1.cpp") .arg(m_szCurrentCTName.toLower());
    szTemp = szFileName;
    szTemp.prepend(QString::fromAscii("-s"));
    lstArguments.append(szTemp);
    szFileName.prepend(m_szCurrentCTPath);
    fileBackUp(szFileName);
    // Imposta come Directory corrente di esecuzione la directory del File CT
    procCompile.setWorkingDirectory(m_szCurrentCTPath);
    // Esecuzione Comando
    qDebug() << szCommand << lstArguments;
    procCompile.start(szCommand, lstArguments);
    if (!procCompile.waitForStarted())  {
        m_szMsg = tr("Error Starting Cross Table Compiler!\n");
        m_szMsg.append(szCommand);
        warnUser(this, szTitle, m_szMsg);
        goto exit_compile;
    }
    // Attesa termine comando
    if (!procCompile.waitForFinished())  {
        m_szMsg = tr("Error Running Cross Table Compiler!\n");
        m_szMsg.append(szCommand);
        warnUser(this, szTitle, m_szMsg);
        goto exit_compile;
    }
    // Esito comando
    nExitCode = procCompile.exitCode();
    if (nExitCode != 0)  {
        m_szMsg = tr("Exit Code of Cross Table Compiler: %1") .arg(nExitCode);
        warnUser(this, szTitle, m_szMsg);
    }
    else {
        m_szMsg = tr("Cross Table Correctly Compiled");
        notifyUser(this, szTitle, m_szMsg);
    }

exit_compile:
    return;
}
QString ctedit::getModelName()
// Lettura del file template.pri per determinare il modello di TPAC
{
    QString     szModel;
    QString     szFileTemplate;
    QFile       fileTemplate;
    QString     szLine;
    int         nPos = -1;

    szModel.clear();
    // Costruzione del nome del file Template
    szFileTemplate = m_szCurrentProjectPath;
    szFileTemplate.append(szSlash);
    szFileTemplate.append(szTemplateFile);
    fileTemplate.setFileName(szFileTemplate);
    // Verifica esistenza filedisplayMessage
    if (fileTemplate.exists())   {
        fileTemplate.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream templateFile(&fileTemplate);
        // Text reading line by line
        while (! templateFile.atEnd()) {
            szLine = templateFile.readLine();
            szLine = szLine.trimmed();
            // Search TYPE string in Line
            if (szLine.startsWith(QString::fromAscii("TYPE"), Qt::CaseSensitive))  {
                qDebug() << tr("Model Line: %1") .arg(szLine);
                nPos = szLine.indexOf(QString::fromAscii("="));
                if (nPos > 0)  {
                    szModel = szLine.mid(nPos + 1).trimmed();
                    szModel.remove(QString::fromAscii("\""));
                    break;
                }
            }
        }
        // Close file
        fileTemplate.close();
    }
    else {
        qDebug() << tr("Template File: %1 not found") .arg(szFileTemplate);
    }
    qDebug() << tr("Curent Model: %1") .arg(szModel);
    // return value
    return szModel;
}
void ctedit::displayStatusMessage(QString szMessage, int nSeconds)
// Show message in ui->lblMessage
{
    // Time Out in display time
    if (nSeconds == 0)
        nSeconds = MAX_DISPLAY_TIME;
    ui->lblMessage->setText(szMessage);
    // Timer per Clear Text
    if (nSeconds > 0)  {
        QTimer::singleShot(nSeconds * 1000, this, SLOT(clearStatusMessage()));
    }
}
void ctedit::clearStatusMessage()
// Clear message in ui->lblMessage
{
    ui->lblMessage->setText(szEMPTY);
}

void ctedit::on_cmdUndo_clicked()
// Retrieve a CT Block from Undo List
{
    if (! lstUndo.isEmpty())  {
        lstCTRecords.clear();
        lstCTRecords = lstUndo[lstUndo.count()-1];
        lstUndo.removeLast();
        // Refresh List
        ctable2Grid();
    }
}
void ctedit::tabSelected(int nTab)
// Change current Tab
{
    m_nCurTab = nTab;
}
void ctedit::enableInterface()
// Abilita l'interfaccia in funzione dello stato del sistema
{
    // Abilitazioni elementi di interfaccia ancora da decidere
    ui->cmdUndo->setEnabled(lstUndo.count() > 0);
    ui->cmdBlocchi->setEnabled(true);
    ui->cmdCompile->setEnabled(! m_isCtModified);
    ui->cmdSave->setEnabled(m_isCtModified);
    ui->fraCondition->setEnabled(true);
    ui->tblCT->setEnabled(true);
}
QStringList ctedit::getPortsFromModel(QString szModel, QString szProtocol)
// Calocolo Porta in funzione di Modello e protocollo
{
    QStringList lstValues;
    int nModel = lstProductName.indexOf(szModel);
    int nProtocol = lstBusType.indexOf(szProtocol);

    lstValues.clear();
    // Valori generici in funzione del Protocollo con modello non specificato
    if (szModel.isEmpty() || nModel == -1)  {
        lstValues.append(QString::fromAscii("0"));
        lstValues.append(QString::fromAscii("1"));
        lstValues.append(QString::fromAscii("2"));
        lstValues.append(QString::fromAscii("3"));
    }
    // Generic IP Port
    else if (nProtocol == TCP || nProtocol == TCPRTU || nProtocol == TCP_SRV)  {
        lstValues.append(QString::fromAscii("502"));
    }
    // Specific Ports by Model and Protocol
    else {
        // Combinazioni possibili tra Modello e Protocollo
        if (nModel == TP1043_01_A && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("1"));
        else if (nModel == TP1043_01_B && (nProtocol == CANOPEN))
            lstValues.append(QString::fromAscii("1"));
        else if (nModel == TP1057_01_A && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("3"));
        else if (nModel == TP1057_01_B && (nProtocol == CANOPEN))
            lstValues.append(QString::fromAscii("1"));
        else if (nModel == TP1070_01_A && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("3"));
        else if (nModel == TP1070_01_B && (nProtocol == CANOPEN))
            lstValues.append(QString::fromAscii("1"));
        else if (nModel == TP1070_01_B && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("3"));
        else if (nModel == TP1070_01_C && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))  {
            lstValues.append(QString::fromAscii("0"));
            lstValues.append(QString::fromAscii("3"));
        }
        else if (nModel == TPAC1006)  {
            lstValues.append(QString::fromAscii("1"));
            lstValues.append(QString::fromAscii("3"));
        }
        else if (nModel == TPAC1007_03 && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("0"));
        else if (nModel == TPAC1007_04_AA && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("0"));
        else if (nModel == TPAC1007_04_AC && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("0"));
        else if (nModel == TPAC1008_02_AA && (nProtocol == CANOPEN))
            lstValues.append(QString::fromAscii("1"));
        else if (nModel == TPAC1008_02_AA && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("3"));
        else if (nModel == TPAC1008_02_AB && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))  {
            lstValues.append(QString::fromAscii("0"));
            lstValues.append(QString::fromAscii("3"));
        }
        else if (nModel == TPAC1008_02_AD && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("3"));
        else if (nModel == TPAC1008_02_AE && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("3"));
        else if (nModel == TPAC1008_02_AF && (nProtocol == RTU || nProtocol == RTU_SRV || nProtocol == MECT_PTC))
            lstValues.append(QString::fromAscii("3"));
    }
    // Return value
    return lstValues;
}
void    ctedit::enableProtocolsFromModel(QString szModel)
// Abilita i Protocolli in funzione del Modello corrente
{
    int nCur = 0;
    int nModel = lstProductName.indexOf(szModel);

    lstBusEnabler.clear();
    // Abilita di default tutti i Protocolli
    for (nCur = 0; nCur < lstBusType.count(); nCur++)  {
        lstBusEnabler.append(true);
    }
    // Abilitazione dei protocolli in funzione del modello
    if (nModel == TP1043_01_A)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TP1043_01_B)  {
        lstBusEnabler[RTU] = false;
        lstBusEnabler[RTU_SRV] = false;
        lstBusEnabler[MECT_PTC] = false;
    }
    else if (nModel == TP1043_01_C)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TP1057_01_A)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TP1057_01_B)  {
        lstBusEnabler[RTU] = false;
        lstBusEnabler[RTU_SRV] = false;
        lstBusEnabler[MECT_PTC] = false;

    }
    else if (nModel == TP1070_01_A)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TP1070_01_B)  {
        // Tutti i protocolli sono abilitiati
    }
    else if (nModel == TP1070_01_C)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TP1070_01_D)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TPAC1006)  {
        // Tutti i protocolli sono abilitiati
    }
    else if (nModel == TPAC1007_03)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TPAC1007_04_AA)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TPAC1007_04_AB)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TPAC1007_04_AC)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TPAC1007_LV)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TPAC1008_01)  {
        // Tutti i protocolli sono abilitiati
    }
    else if (nModel == TPAC1008_02_AA)  {
        //  Tutti i protocolli sono abilitiati
    }
    else if (nModel == TPAC1008_02_AB)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TPAC1008_02_AC)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TPAC1008_02_AD)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TPAC1008_02_AE)  {
        lstBusEnabler[CANOPEN] = false;
    }
    else if (nModel == TPAC1008_02_AF)  {
        lstBusEnabler[CANOPEN] = false;
    }
    // Spegne sulla Combo dei protocolli le voci non abilitate
    for (nCur = 0; nCur < lstBusType.count(); nCur++)  {
        if (lstBusEnabler[nCur])
            enableComboItem(ui->cboProtocol, nCur);
        else
            disableComboItem(ui->cboProtocol, nCur);
    }
}
