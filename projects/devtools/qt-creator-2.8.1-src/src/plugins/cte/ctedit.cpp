#include "ctedit.h"
#include "ui_ctedit.h"
#include "utils.h"
#include "cteerrorlist.h"

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
#include <QProcessEnvironment>

/* ----  Local Defines:   ----------------------------------------------------- */
#define _TRUE  1
#define _FALSE 0
#define MAX_DISPLAY_TIME 15
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
#undef  WORD_BIT

// String Costants
const QString szDEF_IP_PORT = QString::fromAscii("502");
const QString szEMPTY_IP = QString::fromAscii("0.0.0.0");
const QString szTitle = QString::fromAscii("Mect Editor");
const QString szSlash = QString::fromAscii("/");
const QString szCrossCompier = QString::fromAscii("ctc");
const QString szTemplateFile = QString::fromAscii("template.pri");
const QString szPLCEnvVar = QString::fromAscii("PLCUNIXINSTPATH");
const QString szProExt = QString::fromAscii(".pro");
const QString szPLCExt = QString::fromAscii(".4cp");
const QString szPLCDir = QString::fromAscii("plc");

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
    colSourceVar,
    colCondition,
    colCompare,
    colTotals
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
    lstCTErrors.clear();
    // Stringhe generiche per Default campi
    szEMPTY.clear();
    szZERO.fromAscii("0");
    //------------------------
    // Riempimento liste
    //------------------------
    // Lista Messaggi di Errore
    lstErrorMessages.clear();
    for (nCol = 0; nCol < errCTTotals; nCol++)  {
        lstErrorMessages.append(szEMPTY);
    }
    lstErrorMessages[errCTNoError] = trUtf8("No Error");
    lstErrorMessages[errCTDuplicateName] = trUtf8("Duplicate Variable Name");
    lstErrorMessages[errCTNoPriority] = trUtf8("No Priority Selected");
    lstErrorMessages[errCTNoUpdate] = trUtf8("No PLC Refresh Selected");
    lstErrorMessages[errCTNoName] = trUtf8("Invalid or Empty Variable Name");
    lstErrorMessages[errCTNoType] = trUtf8("No Type Selected");
    lstErrorMessages[errCTNoDecimals] = trUtf8("Invalid Decimals");
    lstErrorMessages[errCTNoDecimalZero] = trUtf8("Decimals Must be 0 for BIT Type");
    lstErrorMessages[errCTNoVarDecimals] = trUtf8("Empty or Invalid Decimal Variable");
    lstErrorMessages[errCTWrongDecimals] = trUtf8("Invalid Bit Position");
    lstErrorMessages[errCTNoProtocol] = trUtf8("No Protocol Selected");
    lstErrorMessages[errCTNoIP] = trUtf8("No IP Address");
    lstErrorMessages[errCTBadIP] = trUtf8("Invalid IP Address");
    lstErrorMessages[errCTNoPort] = trUtf8("Empty or Invalid Port Value");
    lstErrorMessages[errCTNoNode] = trUtf8("Empty or Invalid Node Address");
    lstErrorMessages[errCTNoRegister] = trUtf8("Empty or Invalid Register Value");
    lstErrorMessages[errCTNoBehavior] = trUtf8("Empty or Invalid Behavior");
    lstErrorMessages[errCTNoBit] = trUtf8("Alarm/Event Variables must be of BIT type");
    lstErrorMessages[errCTBadPriorityUpdate] = trUtf8("Wrong Priority or Update for Alarm/Event Variable");
    lstErrorMessages[errCTNoVar1] = trUtf8("Empty or Invalid Left Condition Variable");
    lstErrorMessages[errCTNoCondition] = trUtf8("Empty or Invalid Alarm/Event Condition");
    lstErrorMessages[errCTRiseFallNotBit] = trUtf8("Rising/Falling Variable must be of BIT Type");
    lstErrorMessages[errCTInvalidNum] = trUtf8("Invalid Numeric Value in Alarm/Event Condition");
    lstErrorMessages[errCTEmptyCondExpression] = trUtf8("Empty or Invalid Expression in Alarm/Event Condition");
    lstErrorMessages[errCTNoVar2] = trUtf8("Empty or Invalid Right Condition Variable");
    lstErrorMessages[errCTIncompatibleVar] = trUtf8("Incompatible Var in Alarm/Event Condition");
    // Titoli colonne
    lstHeadCols.clear();
    for (nCol = 0; nCol < colTotals; nCol++)  {
        lstHeadCols.append(szEMPTY);
    }
    lstHeadCols[colPriority] = trUtf8("Prior.");
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
    lstHeadCols[colBehavior] = trUtf8("Behav.");
    lstHeadCols[colSourceVar] = trUtf8("Source");
    lstHeadCols[colCondition] = trUtf8("Condition");
    lstHeadCols[colCompare] = trUtf8("Compare");
    // Lista Priorità
    lstPriority.clear();
    lstPriority
            << QString::fromAscii("0")
            << QString::fromAscii("1")
            << QString::fromAscii("2")
            << QString::fromAscii("3")
        ;
    // Lista PLC (Frequenza Aggiornamento)
    lstUpdateNames.clear();
    lstAllUpdates.clear();
    lstNoHUpdates.clear();
    for (nCol = Htype; nCol <= Xtype; nCol++)  {
        lstUpdateNames.append(QString::fromAscii(updateTypeName[nCol]));
        lstAllUpdates.append(nCol);
        if (nCol != Htype)  {
            lstNoHUpdates.append(nCol);
        }
    }
    // Lista TIPI Variabili
    lstTipi.clear();
    lstAllVarTypes.clear();
    for (nCol = BIT; nCol < TYPE_TOTALS; nCol++)  {
        lstTipi.append(QString::fromAscii(varTypeName[nCol]));
        lstAllVarTypes.append(nCol);
    }
    // Lista Protocolli (tipi di Bus)
    lstProtocol.clear();
    lstBusEnabler.clear();
    for (nCol = PLC; nCol <= TCPRTU_SRV; nCol++)  {
        lstProtocol.append(QString::fromAscii(fieldbusName[nCol]));
        lstBusEnabler.append(true);         // Di default tutti i tipi di Bus sono abilitati
    }
    // Lista Prodotti
    lstProductNames.clear();
    for (nCol = AnyTPAC; nCol <= TPAC1008_02_AF; nCol++)  {
        lstProductNames.append(QString::fromAscii(product_name[nCol]));
    }
    // Lista Significati (da mantenere allineata con enum behaviors in parser.h)
    lstBehavior.clear();
    lstBehavior
            << QString::fromAscii("R/O")
            << QString::fromAscii("R/W")
            << QString::fromAscii("AL")
            << QString::fromAscii("EV")
        ;
    // Lista condizioni di Allarme / Eventi
    lstCondition.clear();
    for (nCol = 0; nCol < oper_totals; nCol++)  {
        lstCondition.append(QString::fromAscii(logic_operators[nCol]));
    }
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
    szToolTip.append(tr("X - Permanent Logging on Shot"));
    for  (nCol=0; nCol<lstUpdateNames.count(); nCol++)   {
        ui->cboUpdate->addItem(lstUpdateNames[nCol], lstUpdateNames[nCol]);
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
    for  (nCol=0; nCol<lstProtocol.count(); nCol++)   {
        ui->cboProtocol->addItem(lstProtocol[nCol], lstProtocol[nCol]);
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
    // Validatori per Double
    ui->txtFixedValue->setValidator(new QDoubleValidator(this));
    // Validator per txtIp
    QString szExp = QString::fromAscii("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    QRegExp regExprIP(szExp);
    ui->txtIP->setValidator(new QRegExpValidator(regExprIP, this));
    // Validator per Nome variabile e Comment
    QString szNameExp = QString::fromAscii("\\w+");
    QRegExp regExprName(szNameExp);
    ui->txtName->setValidator(new QRegExpValidator(regExprName, this));
    ui->txtComment->setValidator(new QRegExpValidator(regExprName, this));
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
    m_fCutOrPaste = false;
    m_nCurTab = 0;
    m_vtAlarmVarType = UNKNOWN;
    // Seleziona il primo Tab
    ui->tabWidget->setCurrentIndex(m_nCurTab);
    ui->tabWidget->setTabEnabled(TAB_SYSTEM, false);
    // Connessione Segnali - Slot
    ui->tblCT->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tblCT, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(displayUserMenu(const QPoint &)));
    // connect(ui->tblCT, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));
    connect(ui->tblCT->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this,
            SLOT(tableItemChanged(const QItemSelection &, const QItemSelection & ) ));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected(int)));

}

ctedit::~ctedit()
{
    delete ui;
}
void    ctedit::setProjectPath(QString szProjectPath)
{
    QDir projectDir(szProjectPath);
    QString     szProjectName;

    if (projectDir.exists() && ! szProjectPath.isEmpty())  {
        projectDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
        QStringList filesList;
        filesList.append(QString::fromAscii("*.pro"));
        QStringList lstFile = projectDir.entryList(filesList);

        if (lstFile.count() > 0)  {
            szProjectName = lstFile.at(0);
        }
        // Costruzione del Path progetto
        m_szCurrentProjectPath = szProjectPath;
        // Nome Progetto senza Path
        m_szCurrentProjectName = szProjectName;
        // Costruzione del Path PLC
        m_szCurrentPLCPath = szProjectPath;
        m_szCurrentPLCPath.append(szSlash);
        m_szCurrentPLCPath.append(szPLCDir);
        m_szCurrentPLCPath.append(szSlash);
        QDir dirPlc(m_szCurrentPLCPath);
        // Create if not exists PLC Dir
        if (!dirPlc.exists()) {
            dirPlc.mkpath(m_szCurrentPLCPath);
        }
    }
    else  {
        m_szCurrentProjectPath.clear();
        m_szCurrentProjectName.clear();
        m_szCurrentPLCPath.clear();
    }
    qDebug() << "Project Path:" << m_szCurrentProjectPath;
    qDebug() << "Project Name:" << m_szCurrentProjectName;
    qDebug() << "PLC Path:" << m_szCurrentPLCPath;
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
        // Abilitazione dei protocolli in funzione del Modello
        if (! m_szCurrentModel.isEmpty())  {
            enableProtocolsFromModel(m_szCurrentModel);
        }
        m_isCtModified = false;
        m_fCutOrPaste = false;
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
            fAdd = false;
            tItem->setText(szTemp);
        }
        // Allineamento Celle
        if (nCol == colName || nCol == colComment || nCol == colSourceVar || nCol == colCompare)
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
        // If Ok add row to Table View
        if (fRes)  {
            ui->tblCT->insertRow(nCur);
            fRes = list2GridRow(lstFields, nCur);
        }
    }
    // qDebug() << tr("Loaded Rows: %1") .arg(nCur);
    // Impostazione parametri TableView
    ui->tblCT->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblCT->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tblCT->setHorizontalHeaderLabels(lstHeadCols);
    // Larghezza fissa per alcune colonne
    ui->tblCT->horizontalHeader()->setResizeMode(colPriority, QHeaderView::Stretch);
    ui->tblCT->horizontalHeader()->setResizeMode(colUpdate, QHeaderView::Stretch);
    ui->tblCT->horizontalHeader()->setResizeMode(colBehavior, QHeaderView::Stretch);
    ui->tblCT->setEnabled(true);
    // Show All Elements
    if (fRes)  {
        m_isCtModified = false;
        m_fCutOrPaste = false;
        ui->cmdHideShow->setChecked(m_fShowAllRows);
        ui->cmdSave->setEnabled(true);
        // ui->cmdSave->setEnabled(m_isCtModified);
        showAllRows(m_fShowAllRows);
        fillVarList(lstUsedVarNames, lstAllVarTypes, lstAllUpdates);
    }
    else  {
        qDebug() << tr("Error Loading Rows");
    }
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
        if (lstCTRecords[nRow].Update >= 0 && lstCTRecords[nRow].Update < lstUpdateNames.count())
            lstRecValues[colUpdate] = lstUpdateNames[lstCTRecords[nRow].Update];
        // Campo Name
        lstRecValues[colName] = QString::fromAscii(lstCTRecords[nRow].Tag);
        // Campo Type
        if (lstCTRecords[nRow].VarType >= BIT && lstCTRecords[nRow].VarType < TYPE_TOTALS)
            lstRecValues[colType] = lstTipi[lstCTRecords[nRow].VarType];
        // Campo Decimal
        lstRecValues[colDecimal] = QString::number(lstCTRecords[nRow].Decimal);
        // Protocol
        if (lstCTRecords[nRow].Protocol >= 0 && lstCTRecords[nRow].Protocol < lstProtocol.count())
            lstRecValues[colProtocol] = lstProtocol[lstCTRecords[nRow].Protocol];
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
        // Allarme o Evento
        if (lstCTRecords[nRow].usedInAlarmsEvents && lstCTRecords[nRow].Behavior >= behavior_alarm)  {
            // Tipo Allarme-Evento
            if (lstCTRecords[nRow].ALType == Alarm)
                lstRecValues[colBehavior] = lstBehavior[behavior_alarm];
            else if (lstCTRecords[nRow].ALType == Event)
                lstRecValues[colBehavior] = lstBehavior[behavior_event];
            // Operatore Logico
            if (lstCTRecords[nRow].ALOperator >= 0 && lstCTRecords[nRow].ALOperator < oper_totals)
                lstRecValues[colCondition] = lstCondition[lstCTRecords[nRow].ALOperator];
            else
                lstRecValues[colCondition] = szEMPTY;
            // Source Var
            lstRecValues[colSourceVar] = QString::fromAscii(lstCTRecords[nRow].ALSource);
            // Compare Var or Value
            szTemp = QString::fromAscii(lstCTRecords[nRow].ALCompareVar);
            if (szTemp.isEmpty())
                lstRecValues[colCompare] = QString::number(lstCTRecords[nRow].ALCompareVal, 'f', 4);
            else
                lstRecValues[colCompare] = szTemp;
            // Rising o Falling senza seconda parte
            if (lstCTRecords[nRow].ALOperator == oper_rising || lstCTRecords[nRow].ALOperator == oper_falling)
                lstRecValues[colCompare] = szEMPTY;
        }
        else   {
            // R/O o R/W
            if (lstCTRecords[nRow].Behavior == behavior_readonly)
                lstRecValues[colBehavior] = lstBehavior[behavior_readonly];
            else if (lstCTRecords[nRow].Behavior == behavior_readwrite)
                lstRecValues[colBehavior] = lstBehavior[behavior_readwrite];
            // Source Var - Condition - Compare
            lstRecValues[colSourceVar] = szEMPTY;
            lstRecValues[colCondition] = szEMPTY;
            lstRecValues[colCompare] = szEMPTY;

        }
        // Caso Alarm / Event
            // behavior_alarm,
            // behavior_event,

    }
    // Return value
    return true;
}

void ctedit::on_cmdHideShow_toggled(bool checked)
{

    // Titolo del Bottone
    if (checked)  {
        m_fShowAllRows = true;
        ui->cmdHideShow->setText(tr("Hide"));
    }
    else  {
        m_fShowAllRows = false;
        ui->cmdHideShow->setText(tr("Show"));
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
    QList<int> lstVarTypes;

    lstVarTypes.clear();
    m_vtAlarmVarType = UNKNOWN;
    // Row #
    szTemp = QLocale::system().toString(m_nGridRow + 1);
    ui->txtRow->setText(szTemp);
    // Priority
    szTemp = lstRecValues[colPriority].trimmed();
    ui->cboPriority->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = ui->cboPriority->findText(szTemp, Qt::MatchFixedString);
        if (nPos >= 0 && nPos < ui->cboPriority->count())
            ui->cboPriority->setCurrentIndex(nPos);
    }       
    // Update
    szTemp = lstRecValues[colUpdate].trimmed();
    ui->cboUpdate->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = ui->cboUpdate->findText(szTemp, Qt::MatchFixedString);
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
        nPos = ui->cboType->findText(szTemp, Qt::MatchFixedString);
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
        nPos = ui->cboProtocol->findText(szTemp, Qt::MatchFixedString);
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
    // Analisi del Behavior per determinare uso degli Allarmi
    if (! szTemp.isEmpty())  {
        nPos = ui->cboBehavior->findText(szTemp, Qt::MatchFixedString);
        if (nPos >= 0 && nPos < ui->cboBehavior->count())
            ui->cboBehavior->setCurrentIndex(nPos);
        // Caricamento ulteriori elementi interfaccia Allarmi / Eventi
        if (nPos >= behavior_alarm)  {
            // Clear Data Entry Form for Alarm/Variables
            // Seleziona tutte le variabili tranne le H lstAllVarTypes a prescindere dallo stato della variabile
            ui->cboVariable1->setCurrentIndex(-1);
            ui->cboVariable2->setCurrentIndex(-1);
            fillComboVarNames(ui->cboVariable1, lstAllVarTypes, lstNoHUpdates);
            fillComboVarNames(ui->cboVariable2, lstAllVarTypes, lstNoHUpdates);
            ui->txtFixedValue->setText(szEMPTY);
            // Ricerca posizione prima variabile
            szTemp = lstRecValues[colSourceVar].trimmed();
            qDebug() << "Alarm Source Variable:" << szTemp;
            nPos = -1;
            if (! szTemp.isEmpty())  {
                nPos = ui->cboVariable1->findText(szTemp, Qt::MatchExactly);
            }
            ui->cboVariable1->setCurrentIndex(nPos);
            // Operatore confronto
            nPos = -1;
            szTemp = lstRecValues[colCondition].trimmed();
            if (! szTemp.isEmpty())  {
                nPos = ui->cboCondition->findText(szTemp, Qt::MatchExactly);
            }
//          // Rising e Falling concesso solo per i vari tipi di Bit
//            if (nPos >= oper_rising && nPos <= oper_falling &&
//                    !(m_nAlarmVarType == BIT || m_nAlarmVarType == BYTE_BIT || m_nAlarmVarType == WORD_BIT || m_nAlarmVarType == DWORD_BIT))  {
//                nPos = -1;
//            }
            ui->cboCondition->setCurrentIndex(nPos);
            // Seconda parte dell'espressione
            // Prepara le cose come se non ci fosse una seconda parte
            ui->optFixedVal->setChecked(false);
            ui->optVariableVal->setChecked(false);
            ui->fraSelector->setEnabled(false);
            ui->fraRight->setEnabled(false);
            // Condizione binaria
            if (nPos < oper_rising)  {
                ui->fraSelector->setEnabled(true);
                ui->fraRight->setEnabled(true);
                // Determina se la parte DX espressione è un Numero o un Nome Variabile
                szTemp = lstRecValues[colCompare].trimmed();
                if (! szTemp.isEmpty())  {
                    QChar c = szTemp.at(0);
                    if (! c.isLetter())  {
                        // Numero
                        ui->optFixedVal->setChecked(true);
                        ui->txtFixedValue->setText(szTemp);
                    }
                    else  {
                        // Variabile
                        ui->optVariableVal->setChecked(true);
                        // Riempimento della Combo già avvenuto nella selezione della variabile1
                        nPos = ui->cboVariable2->findText(szTemp, Qt::MatchExactly);
                        ui->cboVariable2->setCurrentIndex(nPos);
                    }
                }
            }
        }
    }
    // Abilitazione campi
    enableFields();
    return true;
}
bool ctedit::iface2values(QStringList &lstRecValues)
// Copia da Zona Editing a Lista Stringhe per Controlli, Grid e Record CT
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
    if (nPos >= 0 && nPos < lstUpdateNames.count())
        szTemp = ui->cboUpdate->itemData(nPos).toString();
    else
        szTemp = szEMPTY;
    lstRecValues[colUpdate] = szTemp;
    // Name
    szTemp = ui->txtName->text().trimmed();
    lstRecValues[colName] = szTemp;
    // Update Used Variable List
    if (! szTemp.isEmpty())  {
        nPos = lstUsedVarNames.indexOf(szTemp);
        if (nPos < 0)  {
            lstUsedVarNames.append(szTemp);
            lstUsedVarNames.sort();
        }
    }
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
    if (nPos >= 0 && nPos < lstProtocol.count())
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
    // Clear all values for Alarms/Events
    lstRecValues[colSourceVar] = szEMPTY;
    lstRecValues[colCondition] = szEMPTY;
    lstRecValues[colCompare] = szEMPTY;
    // Behavior
    nPos = ui->cboBehavior->currentIndex();
    if (nPos >= 0 && nPos < lstBehavior.count())
        szTemp = ui->cboBehavior->itemText(nPos);
    else
        szTemp = szEMPTY;
    lstRecValues[colBehavior] = szTemp.trimmed();
    // Gestione Allarmi/Eventi (Se necessario)
    if (nPos >= behavior_alarm)  {
        // Source Var
        nPos = ui->cboVariable1->currentIndex();
        if (nPos >= 0 && nPos < ui->cboVariable1->count())
            szTemp = ui->cboVariable1->itemText(nPos);
        else
            szTemp = szEMPTY;
        qDebug() << "Variable Var1 Pos: " << nPos;
        lstRecValues[colSourceVar] = szTemp;
        // Operator
        nPos = ui->cboCondition->currentIndex();
        if (nPos >= 0 && nPos < ui->cboCondition->count())
            szTemp = ui->cboCondition->itemText(nPos);
        else
            szTemp = szEMPTY;
        lstRecValues[colCondition] = szTemp;
        // Fixed Value or Variable name
        if (ui->optFixedVal->isChecked())  {
            // Save Fixed Value
            szTemp = ui->txtFixedValue->text().trimmed();
        }
        else  {
            // Save Variable Name
            nPos = ui->cboVariable2->currentIndex();
            if (nPos >= 0 && nPos < ui->cboVariable2->count())
                szTemp = ui->cboVariable2->itemText(nPos);
            else
                szTemp = szEMPTY;
        }
        lstRecValues[colCompare] = szTemp;
    }
    qDebug() << "Alarm Source Variable: " << lstRecValues[colSourceVar];
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
    bool    fRes = false;
    int     nErr = 0;

    nErr = globalChecks();
    if (nErr)  {
        m_szMsg = tr("There are errors in Data. Save anyway?");
        if (! queryUser(this, szTitle, m_szMsg, false))
            return;
    }
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
    for (nRow = 0; nRow < MIN_SYSTEM - 1; nRow++)  {
        // Ignora le righe con Priority == 0
        if (lstCTRecords[nRow].Enable > 0)  {
            // Salto riga o condizione di inizio nuovo blocco
            // Inizio nuovo blocco
            if (nPrevRow != nRow - 1 || prevPriority != lstCTRecords[nRow].Enable || prevType != lstCTRecords[nRow].VarType || prevProtocol !=  lstCTRecords[nRow].Protocol
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
                prevType = lstCTRecords[nRow].VarType;
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
        for (j = nBlockStart; j < MIN_SYSTEM - 1; j++)  {
            if (lstCTRecords[j].UsedEntry == 0)
                break;
            lstCTRecords[j].BlockSize = curBSize;
        }
    }
    // Return value as reload CT
    fRes = ctable2Grid();
    // qDebug() << "Reload finished";
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
    lstCTRecords[nRow].Update = (UpdateType) 0;
    strcpy(lstCTRecords[nRow].Tag, "");
    lstCTRecords[nRow].VarType = (varTypes) 0;
    lstCTRecords[nRow].Decimal = 0;
    lstCTRecords[nRow].Protocol = (FieldbusType) 0;
    lstCTRecords[nRow].IPAddress = 0;
    lstCTRecords[nRow].Port = 0;
    lstCTRecords[nRow].NodeId = 0;
    lstCTRecords[nRow].Offset = 0;
    lstCTRecords[nRow].Block = 0;
    lstCTRecords[nRow].BlockBase = 0;
    lstCTRecords[nRow].Behavior = 0;
    lstCTRecords[nRow].Counter = 0;
    lstCTRecords[nRow].OldVal = 0;
    lstCTRecords[nRow].Error = 0;
    lstCTRecords[nRow].device = 0;
    lstCTRecords[nRow].usedInAlarmsEvents = FALSE;
    lstCTRecords[nRow].ALType = -1;
    strcpy(lstCTRecords[nRow].ALSource, "");
    lstCTRecords[nRow].ALOperator = -1;
    strcpy(lstCTRecords[nRow].ALCompareVar, "");
    lstCTRecords[nRow].ALCompareVal = 0.0;
    lstCTRecords[nRow].ALComparison = -1;
    lstCTRecords[nRow].ALCompatible  = FALSE;
    strcpy(lstCTRecords[nRow].Comment, "");
}
void ctedit::listClear(QStringList &lstRecValues)
// Svuotamento e pulizia Lista Stringhe per passaggio dati Interfaccia <---> Record CT
// La lista passata come parametro viene svuotata e riempita con colTotals stringhe vuote
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
    QList<int>  lstTypes;

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
        nPos = lstUpdateNames.indexOf(lstRecValues[colUpdate]);
        nPos = (nPos >= 0 && nPos < lstUpdateNames.count()) ? nPos : 0;
        lstCTRecords[nRow].Update = (UpdateType) nPos;
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
        lstCTRecords[nRow].VarType = (varTypes) nPos;
        // Campo Decimal
        nPos = lstRecValues[colDecimal].toInt(&fOk);
        nPos = fOk ? nPos : 0;
        lstCTRecords[nRow].Decimal = nPos;
        // Protocol
        nPos = lstProtocol.indexOf(lstRecValues[colProtocol]);
        nPos = (nPos >= 0 && nPos < lstProtocol.count()) ? nPos : 0;
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
        // Clear all Variable - Event fields
        lstCTRecords[nRow].usedInAlarmsEvents = FALSE;
        lstCTRecords[nRow].ALType = -1;
        strcpy(lstCTRecords[nRow].ALSource, szEMPTY.toAscii().data());
        lstCTRecords[nRow].ALOperator = -1;
        strcpy(lstCTRecords[nRow].ALCompareVar, szEMPTY.toAscii().data());
        lstCTRecords[nRow].ALCompareVal = 0.0;
        lstCTRecords[nRow].ALComparison = -1;
        lstCTRecords[nRow].ALCompatible = 0;
        // Behavior
        nPos = lstBehavior.indexOf(lstRecValues[colBehavior]);
        nPos = (nPos >= 0 && nPos < lstBehavior.count()) ? nPos : 0;
        lstCTRecords[nRow].Behavior = nPos;
        // Salvataggio dei valori di Allarme/Evento
        if (nPos >= behavior_alarm)   {
            // Flag isAlarm
            lstCTRecords[nRow].usedInAlarmsEvents = TRUE;
            // Type of Alarm or Event
            if (nPos == behavior_alarm)
                lstCTRecords[nRow].ALType = Alarm;
            else
                lstCTRecords[nRow].ALType = Event;
            // Left Variable Name
            strcpy(lstCTRecords[nRow].ALSource, lstRecValues[colSourceVar].trimmed().toAscii().data());
            // Operator
            nPos = lstCondition.indexOf(lstRecValues[colCondition]);
            nPos = (nPos >= 0 && nPos < lstCondition.count()) ? nPos : -1;
            lstCTRecords[nRow].ALOperator = nPos;
            // Compare VAR - VAL
            QString szCompare = lstRecValues[colCompare].trimmed();
            if (szCompare.isEmpty())  {
                strcpy(lstCTRecords[nRow].ALCompareVar, szEMPTY.toAscii().data());
                lstCTRecords[nRow].ALCompareVal = 0.0;
            }
            else  {
                // Decisione se il secondo lato dell'espressione sia una costante o un nome variabile
                QChar cc = szCompare.at(0);
                if (cc.isLetter())  {
                    // Variable
                    strcpy(lstCTRecords[nRow].ALCompareVar, szCompare.toAscii().data());
                    lstCTRecords[nRow].ALCompareVal = 0.0;
                }
                else  {
                    float fValue = 0;
                    // Value
                    strcpy(lstCTRecords[nRow].ALCompareVar, szEMPTY.toAscii().data());
                    fValue = szCompare.toFloat(&fOk);
                    fValue = fOk ? fValue : 0.0;
                    lstCTRecords[nRow].ALCompareVal = fValue;
                    // TODO: Fill correct values for Comparison and Compatible
                    lstCTRecords[nRow].ALComparison = COMP_UNSIGNED;
                    lstCTRecords[nRow].ALCompatible = 1;
                }
            }
        }
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
        // Abilita possibilità di rendere la variabile un allarme/evento
        enableComboItem(ui->cboBehavior, behavior_alarm);
        enableComboItem(ui->cboBehavior, behavior_event);
    }
    else  {
        ui->txtDecimal->setEnabled(true);
        // Default 1 decimale se non specificato o presente valore
        if (ui->txtDecimal->text().isEmpty())
            ui->txtDecimal->setText(QString::fromAscii("1"));
        // Disabilita possibilità di rendere la variabile un allarme/evento
        disableComboItem(ui->cboBehavior, behavior_alarm);
        disableComboItem(ui->cboBehavior, behavior_event);

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
    int     nErrors = 0;
    QStringList lstFields;
    bool    fIsModif = false;
    bool    fRes = true;
    // Recupera righe selezionate
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();

    // Il cambio riga corrente è dovuto a operazioni di tipo cut-paste.
    // Per evitare duplicazioni accidentali di righe ripulisce il buffer di editing ed esce
    if (m_fCutOrPaste || selection.count() > 1)  {
        clearEntryForm();
        return;
    }
    // Si sta uscendo dalla selezione di una riga sola
    if (! deselected.isEmpty() &&  deselected.count() == 1)  {
        // Considera sempre la prima riga della lista
        nRow = deselected.indexes().at(0).row();
        qDebug() << "Previous Row: " << nRow;
    }
    // Se la riga corrente è stata modificata, salva il contenuto
    if (nRow >= 0 && nRow < lstCTRecords.count())  {
        // Il contenuto viene aggiornato solo se la linea risulta modificata e il form non è vuoto
        if (! isFormEmpty() && isLineModified(nRow))  {
            // Valori da interfaccia a Lista Stringhe
            fRes = iface2values(lstFields);
            // Primo controllo di coerenza sulla riga corrente
            nErrors = checkFormFields(nRow, lstFields, true);
            if (nErrors == 0)  {
                // Copia l'attuale CT nella lista Undo
                lstUndo.append(lstCTRecords);
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
            else
                fRes = false;
        }
    }
    // Cambio riga Ko
    if (nErrors > 0 || ! fRes)    {
        // Disconnette segnale per evitare ricorsione
        disconnect(ui->tblCT->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this,
                SLOT(tableItemChanged(const QItemSelection &, const QItemSelection & ) ));
        // Cambia Selezione (ritorna a riga precedente)
        ui->tblCT->selectRow(nRow);
        // Riconnette slot gestione
        connect(ui->tblCT->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this,
                SLOT(tableItemChanged(const QItemSelection &, const QItemSelection & ) ));
        return;
    }
    // Marca CT come modificata
    if (! m_isCtModified && fIsModif)  {
        m_isCtModified = true;
    }
    // Si può cambiare riga, legge contenuto
    if (! selected.isEmpty() && selected.count() == 1)  {
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
    ui->txtRow->setText(szEMPTY);
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
    // Sottoform per Allarmi/Eventi
    ui->cboVariable1->setCurrentIndex(-1);
    ui->cboCondition->setCurrentIndex(-1);
    ui->optFixedVal->setChecked(false);
    ui->optVariableVal->setChecked(false);
    ui->txtFixedValue->setText(szEMPTY);
    ui->cboVariable2->setCurrentIndex(-1);
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
    QAction *insRows = gridMenu.addAction(trUtf8("Insert Rows"));
    insRows->setEnabled(selection.count() > 0 && m_nGridRow < MIN_SYSTEM - 1);
    // Cancella righe
    QAction *emptyRows = gridMenu.addAction(trUtf8("Empty Rows"));
    emptyRows->setEnabled(selection.count() > 0 && m_nGridRow < MIN_SYSTEM - 1);
    // Elimina righe
    QAction *remRows = gridMenu.addAction(trUtf8("Delete Rows"));
    remRows->setEnabled(selection.count() > 0 && m_nGridRow < MIN_SYSTEM - 1);
    // Sep1
    gridMenu.addSeparator();
    // Copia righe (Sempre permesso)
    QAction *copyRows = gridMenu.addAction(trUtf8("Copy rows"));
    copyRows->setEnabled(selection.count() > 0);
    // Taglia righe
    QAction *cutRows = gridMenu.addAction(trUtf8("Cut Rows"));
    cutRows->setEnabled(selection.count() > 0 && m_nGridRow < MIN_SYSTEM - 1);
    // Sep 2
    gridMenu.addSeparator();
    // Paste Rows
    QAction *pasteRows = gridMenu.addAction(trUtf8("Paste Rows"));
    pasteRows->setEnabled(lstCopiedRecords.count() > 0 && m_nGridRow < MIN_SYSTEM - 1);
    // Abilitazione delle voci di Menu
    // Esecuzione del Menu
    QAction *actMenu = gridMenu.exec(ui->tblCT->viewport()->mapToGlobal(pos));
    this->setCursor(Qt::WaitCursor);
    // Controllo dell'Azione selezionata
    // Inserimento righe
    if (actMenu == insRows)  {
        insertRows();
    }
    // Cancella Righe
    if (actMenu == emptyRows)  {
        emptySelected();
    }
    // Rimozione righe
    else if (actMenu == remRows)  {
        removeSelected();
    }
    // Copia
    else if (actMenu == copyRows)  {
        copySelected(true);
    }
    // Taglia
    else if (actMenu == cutRows)  {
        cutSelected();
    }
    // Incolla
    else if (actMenu == pasteRows)  {
        pasteSelected();
    }
    this->setCursor(Qt::ArrowCursor);

}
void ctedit::copySelected(bool fClearSelection)
// Copia delle righe selezionate in Buffer di Copiatura
{
    // Recupera righe selezionate
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();
    int             nRow = 0;
    int             nCur = 0;
    int             nFirstRow = -1;
    QStringList     lstFields;

    // Check Selection
    if (selection.count() <= 0)
        return;
    // Clear Copied Items Rows
    lstCopiedRecords.clear();
    m_fCutOrPaste = true;
    // Compile Selected Row List
    for (nCur = 0; nCur < selection.count(); nCur++)  {
        // Reperisce l'Item Row Number dall'elenco degli elementi selezionati
        QModelIndex index = selection.at(nCur);
        nRow = index.row();
        // Remember first row of selection
        if (nFirstRow < 0)
            nFirstRow = nRow;
        // Add Row to buffer
        lstCopiedRecords.append(lstCTRecords[nRow]);
    }
    // If only Copy, Set Current index Row to first of Selection
    if (fClearSelection)  {
        selection.clear();
        if (nFirstRow >= 0)  {
            jumpToGridRow(nFirstRow);
            recCT2List(lstFields, nFirstRow);
            values2Iface(lstFields);
        }
    }
    m_szMsg = tr("Rows Copied: %1") .arg(lstCopiedRecords.count());
    displayStatusMessage(m_szMsg);
    enableInterface();
}
void ctedit::pasteSelected()
// Incolla righe da Buffer di copiatura a Riga corrente
{
    int     nRow = ui->tblCT->currentRow();
    int     nCur = 0;
    int     nPasted = 0;
    bool    fUsed = false;
    // Recupera righe selezionate
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();

    // No Records copied
    if (lstCopiedRecords.count() == 0 || m_nGridRow >= MAX_NONRETENTIVE - 1)  {
        m_szMsg = tr("Can't paste rows in System Area");
        displayStatusMessage(m_szMsg);
        selection.clear();
        return;
    }
    m_fCutOrPaste = true;
    // Paste Rows
    if (nRow >= 0 && nRow < MAX_NONRETENTIVE - 1 && lstCopiedRecords.count() > 0)  {
        if (nRow + lstCopiedRecords.count() < MAX_NONRETENTIVE)  {
            // Verifica che la destinazione delle righe sia libera
            for (nCur = nRow; nCur < nRow + lstCopiedRecords.count(); nCur++)  {
                if (lstCTRecords[nCur].UsedEntry)  {
                    fUsed = true;
                    break;
                }
            }
            // Query confirm of used if any row is used
            if (fUsed)  {
                m_szMsg = tr("Some of destination rows may be used. Paste anyway ?");
                fUsed = ! queryUser(this, szTitle, m_szMsg);
            }
            // No row used or overwrite confirmed
            if (! fUsed)  {
                // Append to Undo List
                lstUndo.append(lstCTRecords);
                // Compile Selected Row List
                for (nPasted = 0; nPasted < lstCopiedRecords.count(); nPasted ++)  {
                    // Paste element
                    lstCTRecords[nRow++] = lstCopiedRecords[nPasted];
                }
                // Restore Grid
                ctable2Grid();
                m_isCtModified = true;
            }
        }
        else  {
            m_szMsg = tr("The Copy Buffer Excedes System Variables Limit. Rows not copied");
            warnUser(this, szTitle, m_szMsg);
        }
    }
    m_szMsg = tr("Rows Pasted: %1") .arg(nPasted);
    displayStatusMessage(m_szMsg);
    lstCopiedRecords.clear();
    enableInterface();
}

void ctedit::insertRows()
// Aggiunta righe in posizione cursore
{
    // Recupera righe selezionate
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();
    CrossTableRecord emptyRecord;
    int             nInserted = 0;
    int             nFirstRow = -1;
    int             nRow = 0;
    int             nCur = 0;
    int             nStart = 0;

    if (selection.count() <= 0 )  {
        return;
    }
    // Controllo di restare nei Bounding delle variabili utente
    if (m_nGridRow + selection.count() < MAX_NONRETENTIVE - 1)  {
        // Append to Undo List
        lstUndo.append(lstCTRecords);
        // Enter in Paste Mode
        m_fCutOrPaste = true;
        // Ricerca del Punto di Inserzione
        for (nCur = 0; nCur < selection.count(); nCur++)  {
            // Reperisce l'Item Row Number dall'elenco degli elementi selezionati
            QModelIndex index = selection.at(nCur);
            nRow = index.row();
            // Remember first row of selection
            if (nFirstRow < 0)  {
                nFirstRow = nRow;
                break;
            }
        }
        // Insert New Recs
        for (nCur = 0; nCur < selection.count(); nCur++)  {
            lstCTRecords.insert(nFirstRow, emptyRecord);
            freeCTrec(nFirstRow);
            nInserted ++;
        }
        // Search the right place 2 remove extra records
        if (nFirstRow >= 0 && nFirstRow < MAX_RETENTIVE - 1)
            nStart = MAX_RETENTIVE - 1;
        else if (nFirstRow >= MIN_NONRETENTIVE -1 && nFirstRow < MAX_NONRETENTIVE - 1)
            nStart = MAX_NONRETENTIVE - 1;
        else    // Should never happen....
            nStart = 0;
        // Remove extra Rec to readjust positions
        for (nCur = 0; nCur < nInserted; nCur++)  {
            lstCTRecords.removeAt(nStart);
        }
        // Refresh Grid
        ctable2Grid();
        m_isCtModified = true;
    }
    else  {
        m_szMsg = tr("Too Many Rows selected, passed limit of User Variables!");
        displayStatusMessage(m_szMsg);
        selection.clear();
        return;
    }
    m_szMsg = tr("Rows Inserted: %1") .arg(selection.count());
    displayStatusMessage(m_szMsg);
    enableInterface();
}
void ctedit::emptySelected()
// Cancellazione delle righe correntemente selezionate
// (solo svuotamento senza Shift in alto delle righe)
{
    // Recupera righe selezionate
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();
    int             nRow = 0;
    int             nCur = 0;
    int             nRemoved = 0;
    int             nFirstRow = -1;

    // Check Modif. and append data to Undo List
    if (selection.isEmpty() || m_nGridRow >= MIN_SYSTEM - 1)  {
        m_szMsg = tr("Can't remove rows in System Area");
        displayStatusMessage(m_szMsg);
        selection.clear();
        return;
    }
    lstUndo.append(lstCTRecords);
    // Compile Selected Row List
    m_fCutOrPaste = true;
    for (nCur = 0; nCur < selection.count(); nCur++)  {
        // Reperisce l'Item Row Number dall'elenco degli elementi selezionati
        QModelIndex index = selection.at(nCur);
        nRow = index.row();
        // Remember first row of selection
        if (nFirstRow < 0)
            nFirstRow = nRow;
        // Free Row
        if (nRow < MAX_NONRETENTIVE)  {
            freeCTrec(nRow);
            nRemoved++;
        }
    }
    // Set Current index Row to first of Selection
    selection.clear();
    // Refresh Grid
    if (nRemoved)  {
        ctable2Grid();
        m_isCtModified = true;
    }
    // Riposiziona alla riga corrente
    if (nRemoved > 0 && nFirstRow >= 0)  {
        jumpToGridRow(nFirstRow);
    }
    m_szMsg = tr("Rows Removed: %1") .arg(nRemoved);
    displayStatusMessage(m_szMsg);
    // Update Iface
    enableInterface();
}

void ctedit::removeSelected()
// Rimozione delle righe correntemente selezionate
// (svuotamento con Shift in alto delle righe)
{
    // Recupera righe selezionate
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();
    int             nRow = 0;
    int             nCur = 0;
    int             nStart = 0;
    int             nRemoved = 0;
    int             nFirstRow = -1;
    CrossTableRecord emptyRecord;

    // Check Modif. and append data to Undo List
    if (selection.isEmpty() || m_nGridRow >= MIN_SYSTEM - 1)  {
        m_szMsg = tr("Can't remove rows in System Area");
        displayStatusMessage(m_szMsg);
        selection.clear();
        return;
    }
    lstUndo.append(lstCTRecords);
    // Compile Selected Row List
    m_fCutOrPaste = true;
    for (nCur = 0; nCur < selection.count(); nCur++)  {
        // Reperisce l'Item Row Number dall'elenco degli elementi selezionati
        QModelIndex index = selection.at(nCur);
        nRow = index.row();
        // Remember first row of selection
        if (nFirstRow < 0)
            nFirstRow = nRow;
        // Removing Row from list
        if (nRow < MAX_NONRETENTIVE)  {
            lstCTRecords.removeAt(nRow - nRemoved);
            nRemoved++;
        }
    }
    // Refresh Grid
    if (nRemoved)  {
        // Search the right place 2 insert empty records
        if (nFirstRow >= 0 && nFirstRow < MAX_RETENTIVE - 1)
            nStart = MAX_RETENTIVE - nRemoved - 1;
        else if (nFirstRow >= MIN_NONRETENTIVE -1 && nFirstRow < MAX_NONRETENTIVE - 1)
            nStart = MAX_NONRETENTIVE - nRemoved - 1;
        else    // Should never happen....
            nStart = 0;
        // Insert empty Rec to readjust positions
        for (nCur = 0; nCur < nRemoved; nCur++)  {
            lstCTRecords.insert(nStart, emptyRecord);
            freeCTrec(nStart);
        }
        // Refresh Grid
        ctable2Grid();
        m_isCtModified = true;
    }
    m_szMsg = tr("Rows Removed: %1") .arg(nRemoved);
    displayStatusMessage(m_szMsg);
    // Update Iface
    enableInterface();
}
void ctedit::cutSelected()
// Taglia righe in Buffer di copiatura
{
    // Recupera righe selezionate
    QModelIndexList selection = ui->tblCT->selectionModel()->selectedRows();

    if (m_nGridRow >= MIN_SYSTEM - 1)  {
        m_szMsg = tr("Can't remove rows in System Area");
        selection.clear();
        displayStatusMessage(m_szMsg);
        return;
    }
    m_fCutOrPaste = true;
    // Copia Righe
    copySelected(false);
    // Elimina Righe
    if(lstCopiedRecords.count() > 0)
        emptySelected();
    // Result
    m_szMsg = tr("Rows Cutted: %1") .arg(lstCopiedRecords.count());
    displayStatusMessage(m_szMsg);
    // qDebug() << m_szMsg;
}
bool ctedit::isFormEmpty()
// Controllo Form Editing vuoto
{
    int nFilled = 0;

    nFilled += (ui->cboPriority->currentIndex() >= 0);
    nFilled += (ui->cboUpdate->currentIndex() >= 0);
    nFilled += (! ui->txtName->text().trimmed().isEmpty());
    nFilled += (ui->cboType->currentIndex() >= 0);
    nFilled += (! ui->txtDecimal->text().trimmed().isEmpty());
    nFilled += (ui->cboProtocol->currentIndex() >= 0);
    nFilled += (! ui->txtIP->text().trimmed().isEmpty());
    nFilled += (! ui->txtPort->text().trimmed().isEmpty());
    nFilled += (! ui->txtNode->text().trimmed().isEmpty());
    nFilled += (! ui->txtRegister->text().trimmed().isEmpty());
    // nFilled += (ui->txtBlock->text().trimmed() != ui->tblCT->item(m_nGridRow, colBlock)->text().trimmed());
    // nFilled += (ui->txtBlockSize->text().trimmed() != ui->tblCT->item(m_nGridRow, colBlockSize)->text().trimmed());
    nFilled += (! ui->txtComment->text().trimmed().isEmpty());
    nFilled += (ui->cboBehavior->currentIndex() >= 0);
    if (ui->cboBehavior->currentIndex() >= behavior_alarm)  {
        nFilled += (ui->cboVariable1->currentIndex() >= 0);
        nFilled += (ui->cboCondition->currentIndex() >= 0);
        nFilled += (ui->cboVariable2->currentIndex() >= 0);
        nFilled += (! ui->txtFixedValue->text().trimmed().isEmpty());
    }
    // Return Value
    // qDebug() << "isFormEmpty(): N.Row:" << m_nGridRow << "Campi definiti:" << nFilled;
    return (nFilled == 0);
}

bool ctedit::isLineModified(int nRow)
// Check se linea corrente Grid è diversa da Form in Editing
{
    int     nModif = 0;

    // Confronto tra Form Editing e riga Grid
    if(nRow >= 0 && nRow < lstCTRecords.count())  {
        nModif += (ui->cboPriority->currentText().trimmed() != ui->tblCT->item(nRow, colPriority)->text().trimmed());
        nModif += (ui->cboUpdate->currentText().trimmed() != ui->tblCT->item(nRow, colUpdate)->text().trimmed());
        nModif += (ui->txtName->text().trimmed() != ui->tblCT->item(nRow, colName)->text().trimmed());
        nModif += (ui->cboType->currentText().trimmed() != ui->tblCT->item(nRow, colType)->text().trimmed());
        nModif += (ui->txtDecimal->text().trimmed() != ui->tblCT->item(nRow, colDecimal)->text().trimmed());
        nModif += (ui->cboProtocol->currentText().trimmed() != ui->tblCT->item(nRow, colProtocol)->text().trimmed());
        nModif += (ui->txtIP->text().trimmed() != ui->tblCT->item(nRow, colIP)->text().trimmed());
        nModif += (ui->txtPort->text().trimmed() != ui->tblCT->item(nRow, colPort)->text().trimmed());
        nModif += (ui->txtNode->text().trimmed() != ui->tblCT->item(nRow, colNodeID)->text().trimmed());
        nModif += (ui->txtRegister->text().trimmed() != ui->tblCT->item(nRow, colRegister)->text().trimmed());
        // nModif += (ui->txtBlock->text().trimmed() != ui->tblCT->item(nRow, colBlock)->text().trimmed());
        // nModif += (ui->txtBlockSize->text().trimmed() != ui->tblCT->item(nRow, colBlockSize)->text().trimmed());
        nModif += (ui->txtComment->text().trimmed() != ui->tblCT->item(nRow, colComment)->text().trimmed());
        nModif += (ui->cboBehavior->currentText().trimmed() != ui->tblCT->item(nRow, colBehavior)->text().trimmed());
        // Frame Allarmi
        if (ui->cboBehavior->currentIndex() >= behavior_alarm)  {
            nModif += (ui->cboVariable1->currentText().trimmed() != ui->tblCT->item(nRow, colSourceVar)->text().trimmed());
            nModif += (ui->cboCondition->currentText().trimmed() != ui->tblCT->item(nRow, colCondition)->text().trimmed());
            if (ui->optFixedVal->isChecked())
                nModif += (ui->txtFixedValue->text().trimmed() != ui->tblCT->item(nRow, colCompare)->text().trimmed());
            else
                nModif += (ui->cboVariable2->currentText().trimmed() != ui->tblCT->item(nRow, colCompare)->text().trimmed());
        }
    }
    // qDebug() << "Modified(): N.Row:" << nRow << "Numero Modifiche:" << nModif;
    return (nModif > 0);
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
    // QStringList lstFields;
    bool fOk;

    // Valori da interfaccia a Lista Stringhe
    // fOk = iface2values(lstFields);
    // Controllo di coerenza sulla riga corrente
    // if (checkFormFields(m_nGridRow, lstFields, true) > 0)
    //     return;
    // Input Dialog per Numero riga
    int nRow = QInputDialog::getInt(this, tr("Row to Jump To"),
                                 tr("Enter Row Number to Jump to:"), m_nGridRow + 1, 1, DimCrossTable, 1, &fOk);
    if (fOk)  {
        nRow--;
        // Se la riga non è visibile chiede conferma se fare ShowAll
        if (lstCTRecords[nRow].UsedEntry == 0 && ! m_fShowAllRows)  {
            m_szMsg = trUtf8("The requested row is not visible. Show all rows?");
            if (queryUser(this, szTitle, m_szMsg, false))  {
                ui->cmdHideShow->setChecked(true);
            }
        }
        jumpToGridRow(nRow);
    }
}
void ctedit::on_cmdSearch_clicked()
// Search Variable by Name
{
    bool fOk;
    int  nRow = 0;
    // QStringList lstFields;

    // Valori da interfaccia a Lista Stringhe
    // fOk = iface2values(lstFields);
    // if (checkFormFields(m_nGridRow, lstFields, true) > 0)
    //     return;
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
    // ui->tblCT->scrollToItem(ui->tblCT->currentItem(), QAbstractItemView::PositionAtCenter);
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
    QByteArray  baCompErr;
    QString     szCompErr;
    QProcess    procCompile;
    int         nExitCode = 0;

    // Controllo presenza di Errori
    if (globalChecks())
        return;
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
    // qDebug() << szCommand << lstArguments;
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
    baCompErr = procCompile.readAllStandardError();
    nExitCode = procCompile.exitCode();
    if (nExitCode != 0)  {
        m_szMsg = tr("Exit Code of Cross Table Compiler: %1\n") .arg(nExitCode);
        szCompErr = QString::fromAscii(baCompErr.data());
        m_szMsg.append(szCompErr);
        warnUser(this, szTitle, m_szMsg);
        // TODO: Analisi errore del Cross Compiler
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
                // qDebug() << tr("Model Line: %1") .arg(szLine);
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
    // qDebug() << tr("Current Model: %1") .arg(szModel);
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
    ui->cmdPLC->setEnabled(! m_isCtModified);
    ui->fraCondition->setEnabled(true);
    ui->tblCT->setEnabled(true);
    m_fCutOrPaste = false;
}
QStringList ctedit::getPortsFromModel(QString szModel, QString szProtocol)
// Calocolo Porte abilitate in funzione di Modello e protocollo
{
    QStringList lstValues;
    int nModel = lstProductNames.indexOf(szModel);
    int nProtocol = lstProtocol.indexOf(szProtocol);

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
    int nModel = lstProductNames.indexOf(szModel);

    lstBusEnabler.clear();
    // Abilita di default tutti i Protocolli
    for (nCur = 0; nCur < lstProtocol.count(); nCur++)  {
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
    for (nCur = 0; nCur < lstProtocol.count(); nCur++)  {
        if (lstBusEnabler[nCur])
            enableComboItem(ui->cboProtocol, nCur);
        else
            disableComboItem(ui->cboProtocol, nCur);
    }
}
void ctedit::on_cboBehavior_currentIndexChanged(int index)
{
    // Abilitazione o meno del frame condizioni allarmi/eventi
    if (index > behavior_readwrite) {
        ui->fraCondition->setVisible(true);
    } else
        ui->fraCondition->setVisible(false);
}
void ctedit::fillErrorMessage(int nRow, int nCol, int nErrCode, QString szVarName, QString szValue, QChar severity, Err_CT *errCt)
{
    errCt->cSeverity = severity;
    errCt->nRow = nRow;
    errCt->nCol = nCol;
    errCt->nCodErr = nErrCode;
    errCt->szErrMessage = lstErrorMessages[nErrCode];
    errCt->szVarName = szVarName;
    errCt->szValue = szValue;
}
int ctedit::globalChecks()
// Controlli complessivi su tutta la CT
{
    int         nRow = 0;
    int         nErrors = 0;
    bool        fRecOk = false;
    QStringList lstFields;
    QString     szTemp;
    Err_CT      errCt;
    // Form per Display Errori
    cteErrorList    *errWindow;

    lstCTErrors.clear();
    lstUniqueVarNames.clear();
    // Ciclo Globale su tutti gli Items di CT
    for (nRow = 0; nRow < lstCTRecords.count(); nRow++)  {
        // Controlla solo righe utilizzate
        if (lstCTRecords[nRow].Enable)  {
            // Controllo univocità di nome
            szTemp = QString::fromAscii(lstCTRecords[nRow].Tag).trimmed();
            if (lstUniqueVarNames.indexOf(szTemp) > 0)  {
                fillErrorMessage(nRow, colName, errCTDuplicateName, szTemp, szTemp, chSeverityError, &errCt);
                lstCTErrors.append(errCt);
                nErrors++;
            }
            else  {
                lstUniqueVarNames.append(szTemp);
            }
        // Controlli specifici di Riga
        fRecOk = recCT2List(lstFields, nRow);
        if (fRecOk)
            nErrors += checkFormFields(nRow, lstFields, false);
        }
    }
    // Display finestra errore
    if(nErrors)  {
        qDebug() << "Found Errors:" << nErrors;
        errWindow = new cteErrorList(this);
        errWindow->setModal(true);
        errWindow->lstErrors2Grid(lstCTErrors);
        if (errWindow->exec() == QDialog::Accepted)  {
            nRow = errWindow->currentRow();
            if (nRow >= 0 && nRow < DimCrossTable)
                jumpToGridRow(nRow);
        }
        delete errWindow;
    }
    return nErrors;
}
bool ctedit::isValidVarName(QString szName)
{
    bool    fRes = true;
    char    anyCh;
    int     i = 0;

    if (!szName.isEmpty())  {
        // Controllo che la variabile non cominci con un carattere numerico
        for (i = 0; i < szName.length(); i++)  {
            anyCh = szName.at(i).toAscii();
            // First Ch is Number
            if (i == 0 && (anyCh <= '9' && anyCh >= '0'))  {
                fRes = false;
                break;
            }
            // Others char must be Digit, Printable Chars or '_'
            if (! ((anyCh >= '0' && anyCh <= '9') ||
                   (anyCh >= 'A' && anyCh <= 'Z') ||
                   (anyCh >= 'a' && anyCh <= 'z') ||
                   (anyCh == '_')))  {
                fRes = false;
                break;
            }
        }
    }
    else  {
        fRes = false;
    }
    // Return value
    return fRes;
}
int ctedit::fillVarList(QStringList &lstVars, QList<int> &lstTypes, QList<int> &lstUpdates)
// Fill sorted List of Variables Names for Types in lstTypes and Update Type in lstUpdates
{
    bool    fTypeFilter = lstTypes.count() > 0;
    bool    fUpdateFilter = lstUpdates.count() > 0;
    int     nRow = 0;
    bool    f2Add = false;
    bool    fUpdateOk = false;

    lstVars.clear();

    for (nRow = 0; nRow < lstCTRecords.count(); nRow++)  {
        if (lstCTRecords[nRow].Enable)  {
            // Filter on Var Type
            if (fTypeFilter)  {
                f2Add = lstTypes.indexOf(lstCTRecords[nRow].VarType) >= 0 ? true : false;
            }
            else  {
                f2Add = true;
            }
            // Filter on Update Type
            if (f2Add && fUpdateFilter)  {
                fUpdateOk = lstUpdates.indexOf(lstCTRecords[nRow].Update) >= 0 ? true : false;
            }
            else {
                fUpdateOk = f2Add;
            }

            // If Var is defined and of a correct type, insert in list
            if (f2Add && fUpdateOk)  {
                lstVars.append(QString::fromAscii(lstCTRecords[nRow].Tag));
            }
        }
    }
    // Ordimanento Alfabetico della Lista
    lstVars.sort();
    // Return value
    // qDebug() << "Items Added to List:" << lstVars.count();
    return lstVars.count();
}

int ctedit::fillComboVarNames(QComboBox *comboBox, QList<int> &lstTypes, QList<int> &lstUpdates)
// Caricamento ComboBox con Nomi Variabili filtrate in funzione del Tipo e della Persistenza
{
    QStringList lstVars;
    int         nItem = 0;
    bool        oldState = comboBox->blockSignals(true);

    lstVars.clear();
    comboBox->setCurrentIndex(-1);
    comboBox->clear();
    if (fillVarList(lstVars, lstTypes, lstUpdates) > 0)
    {
        for (nItem = 0; nItem < lstVars.count(); nItem++)  {
            comboBox->addItem(lstVars[nItem], lstVars[nItem]);
        }
        comboBox->setCurrentIndex(-1);
    }
    comboBox->blockSignals(oldState);
    return lstVars.count();
}
int ctedit::checkFormFields(int nRow, QStringList &lstValues, bool fSingleLine)
// Controlli formali sulla riga a termine editing o ciclicamente durante controllo globale valori
{
    int         nErrors = 0;
    int         nJumpRow = 0;
    int         nPos = -1;
    int         nPriority = -1;
    int         nType = -1;
    int         nUpdate = -1;
    int         nVal = 0;
    int         nProtocol = -1;
    varTypes    nTypeVar1 = UNKNOWN;
    bool        fOk = false;
    Err_CT      errCt;
    QString     szTemp;
    QString     szVarName;
    QString     szIP;
    QString     szVar1;

    // Form per Display Errori
    cteErrorList    *errWindow;

    // Clear Error List if single line show
    if (fSingleLine)
        lstCTErrors.clear();
    // Controllo Variable Name
    szVarName = lstValues[colName];
    // Controllo cboPriority
    szTemp = lstValues[colPriority];
    nPriority = szTemp.isEmpty() ? -1 : lstPriority.indexOf(szTemp);
    if (nPriority < 0)  {
        fillErrorMessage(nRow, colPriority, errCTNoPriority, szVarName, szTemp, chSeverityError, &errCt);
        lstCTErrors.append(errCt);
        nErrors++;
    }
    // Controllo Update
    szTemp = lstValues[colUpdate];
    nUpdate = szTemp.isEmpty() ? -1 : lstUpdateNames.indexOf(szTemp);
    if (nUpdate < 0)  {
        fillErrorMessage(nRow, colUpdate, errCTNoUpdate, szVarName, szTemp, chSeverityError, &errCt);
        lstCTErrors.append(errCt);
        nErrors++;
    }
    // Controllo Variable Name    
    if (! isValidVarName(szVarName))  {
        fillErrorMessage(nRow, colName, errCTNoName, szVarName, szVarName, chSeverityError, &errCt);
        lstCTErrors.append(errCt);
        nErrors++;
    }
    // Controllo Type
    szTemp = lstValues[colType];
    nType = szTemp.isEmpty() ? -1 : lstTipi.indexOf(szTemp);
    if (nType < 0)  {
        fillErrorMessage(nRow, colUpdate, errCTNoType, szVarName, szTemp, chSeverityError, &errCt);
        lstCTErrors.append(errCt);
        nErrors++;
    }
    // Controllo Decimal
    szTemp = lstValues[colDecimal];
    if (szTemp.isEmpty())  {
        fillErrorMessage(nRow, colDecimal, errCTNoDecimals, szVarName, szTemp, chSeverityError, &errCt);
        lstCTErrors.append(errCt);
        nErrors++;
    }
    else  {
        // Numero Decimali
        nVal = szTemp.toInt(&fOk);
        nVal = fOk ? nVal : 0;
        // Decimali a 0 per tipo Bit
        if (nType == BIT && nVal > 0)  {
            fillErrorMessage(nRow, colDecimal, errCTNoDecimalZero, szVarName, szTemp, chSeverityError, &errCt);
            lstCTErrors.append(errCt);
            nErrors++;
        }
        else if (nType == BYTE_BIT) {
            if (nVal < 1 or nVal > 8)  {
                fillErrorMessage(nRow, colDecimal, errCTWrongDecimals, szVarName, szTemp, chSeverityError, &errCt);
                lstCTErrors.append(errCt);
                nErrors++;
            }
        }
        else if (nType == WORD_BIT) {
            if (nVal < 1 or nVal > 16)  {
                fillErrorMessage(nRow, colDecimal, errCTWrongDecimals, szVarName, szTemp, chSeverityError, &errCt);
                lstCTErrors.append(errCt);
                nErrors++;
            }
        }
        else if (nType == DWORD_BIT) {
            if (nVal < 1 or nVal > 32)  {
                fillErrorMessage(nRow, colDecimal, errCTWrongDecimals, szVarName, szTemp, chSeverityError, &errCt);
                lstCTErrors.append(errCt);
                nErrors++;
            }
        }
        // Numero Decimali > 4 ===> Variable (per tipi differenti da Bit in tutte le versioni possibili)
        else if (nVal >= 4 && nType != BYTE_BIT && nType == WORD_BIT && nType == DWORD_BIT)  {
            // Controlla che il numero indicato punti ad una variabile del tipo necessario a contenere il numero di decimali
            if (nVal > DimCrossTable || ! lstCTRecords[nVal].Enable ||
                    (lstCTRecords[nVal].VarType != UINT8 &&  lstCTRecords[nVal].VarType != UINT16 && lstCTRecords[nVal].VarType != UINT16BA &&
                     lstCTRecords[nVal].VarType != UDINT &&  lstCTRecords[nVal].VarType != UDINTDCBA && lstCTRecords[nVal].VarType != UDINTCDAB &&
                     lstCTRecords[nVal].VarType != UDINTBADC ) )   {
                fillErrorMessage(nRow, colDecimal, errCTNoVarDecimals, szVarName, szTemp, chSeverityError, &errCt);
                lstCTErrors.append(errCt);
                nErrors++;
            }
        }
    }
    // Controllo Protocol
    szTemp = lstValues[colProtocol];
    nProtocol = szTemp.isEmpty() ? -1 : lstProtocol.indexOf(szTemp);
    if (nProtocol < 0)  {
        fillErrorMessage(nRow, colProtocol, errCTNoProtocol, szVarName, szTemp, chSeverityError, &errCt);
        lstCTErrors.append(errCt);
        nErrors++;
    }
    // Controllo Ip Address
    szIP = lstValues[colIP].trimmed();
    if (szIP.isEmpty() &&
            (nProtocol == TCP || nProtocol == TCPRTU || nProtocol == TCP_SRV || nProtocol == TCPRTU_SRV))  {

        fillErrorMessage(nRow, colIP, errCTNoIP, szVarName, szIP, chSeverityError, &errCt);
        lstCTErrors.append(errCt);
        nErrors++;
    }
    // Controlli per gestione Allarmi/Eventi
    szTemp = lstValues[colBehavior];
    nPos = szTemp.isEmpty() ? -1 : lstBehavior.indexOf(szTemp);
    if (nPos < 0 || nPos >= lstBehavior.count())  {
        fillErrorMessage(nRow, colBehavior, errCTNoBehavior, szVarName, szTemp, chSeverityError, &errCt);
        lstCTErrors.append(errCt);
        nErrors++;
    }
    // Controlli specifici per Allarmi/Eventi
    if (nPos >= behavior_alarm && nPos <= behavior_event)  {
        // Controllo che la variabile Alarm/Event sia di tipo BIT
        if (nType != BIT)  {
            fillErrorMessage(nRow, colType, errCTNoBit, szVarName, szVarName, chSeverityError, &errCt);
            lstCTErrors.append(errCt);
            nErrors++;
        }
        // Controllo che la variabile impostata come Alarm/Event abbia priority > 0 e non sia Update=H
        if (nPriority <= 0 || nUpdate <= Htype)  {
            fillErrorMessage(nRow, colType, errCTBadPriorityUpdate, szVarName, szVarName, chSeverityError, &errCt);
            lstCTErrors.append(errCt);
            nErrors++;
        }
        // Controllo che la variabile selezionata come Var1 sia NON H
        QStringList lstAlarmVars;
        fillVarList(lstAlarmVars, lstAllVarTypes, lstNoHUpdates);
        // Variable 1
        szVar1 = lstValues[colSourceVar];
        nPos = szVar1.isEmpty() ? -1 : lstAlarmVars.indexOf(szVar1);
        if (nPos < 0)  {
            fillErrorMessage(nRow, colSourceVar, errCTNoVar1, szVarName, szVar1, chSeverityError, &errCt);
            lstCTErrors.append(errCt);
            nErrors++;
        }
        // Ricerca della Variabile 1 per estrarre il Tipo
        if (! szVar1.isEmpty())  {
            nPos = varName2Row(szVar1, lstCTRecords);
            if (nPos >= 0 && nPos < lstCTRecords.count())
                nTypeVar1 = lstCTRecords[nPos].VarType;
        }
        // Controllo sull'operatore di comparazione
        szTemp = lstValues[colCondition];
        if (nPos < 0)  {
            fillErrorMessage(nRow, colCondition, errCTNoCondition, szVarName, szTemp, chSeverityError, &errCt);
            lstCTErrors.append(errCt);
            nErrors++;
        }
        // Controllo sulla parte DX espressione
        // Operatore Rising/Falling
        if (nPos >= oper_rising && nPos <= oper_falling)  {
            lstValues[colCompare].clear();
            if (! (nTypeVar1 == BIT || nTypeVar1 == BYTE_BIT || nTypeVar1 == WORD_BIT || nTypeVar1 == DWORD_BIT))  {
                fillErrorMessage(nRow, colSourceVar, errCTRiseFallNotBit, szVarName, szTemp, chSeverityError, &errCt);
                lstCTErrors.append(errCt);
                nErrors++;
            }
        }
        // Altri Operatori
        else if (nPos >= 0 && nPos < oper_rising)  {
            // Espressione vuota
            szTemp = lstValues[colCompare];
            if (szTemp.isEmpty())  {
                fillErrorMessage(nRow, colCompare, errCTEmptyCondExpression, szVarName, szTemp, chSeverityError, &errCt);
                lstCTErrors.append(errCt);
                nErrors++;
            }
            else  {
                QChar c = szTemp.at(0);
                if (! c.isLetter())  {
                    // Numero
                    bool fOk;
                    double dblVal = szTemp.toDouble(&fOk);
                    if (!fOk)  {
                        // Invalid Number
                        fillErrorMessage(nRow, colCompare, errCTInvalidNum, szVarName, szTemp, chSeverityError, &errCt);
                        lstCTErrors.append(errCt);
                        nErrors++;
                    }
                }
                else  {
                    // Variabile
                    // Ricerca nome variabile in Var NO H
                    nPos = lstAlarmVars.indexOf(szTemp);
                    if (nPos < 0 )  {
                        // Variabile non definita
                        fillErrorMessage(nRow, colCompare, errCTNoVar2, szVarName, szTemp, chSeverityError, &errCt);
                        lstCTErrors.append(errCt);
                        nErrors++;
                    }
                    nPos = varName2Row(szTemp, lstCTRecords);
                    // Verifica di Compatibilità di tipo
                    if (nPos >= 0 && nPos < lstCTRecords.count())  {
                        varTypes tipoVar2 = lstCTRecords[nPos].VarType;
                        QList<int> lstCompatTypes;
                        // Ricerca dei tipi compatibili con Var1
                        fillCompatibleTypesList(nTypeVar1, lstCompatTypes);
                        if (lstCompatTypes.indexOf(tipoVar2) < 0)  {
                            // Variabile 2 non compatibile
                            fillErrorMessage(nRow, colCompare, errCTIncompatibleVar, szVarName, szTemp, chSeverityError, &errCt);
                            lstCTErrors.append(errCt);
                            nErrors++;

                        }
                    }
                }
            }
        }
    }
    //
    // TODO: Ulteriori controlli formali....
    //
    // qDebug() << "Found Errors:" << nErrors;
    // Form visualizzazione errori se richiesto
    if (fSingleLine && nErrors)  {
        errWindow = new cteErrorList(this);
        errWindow->setModal(true);
        errWindow->lstErrors2Grid(lstCTErrors);
        if (errWindow->exec() == QDialog::Accepted)  {
            nJumpRow = errWindow->currentRow();
            if (nJumpRow >= 0 && nJumpRow < DimCrossTable)
                jumpToGridRow(nJumpRow);
        }
        delete errWindow;
    }
    // Return Value
    return nErrors;
}

void ctedit::on_cboVariable1_currentIndexChanged(int index)
{
    QString szVarName;
    int     nRow = -1;
    QList<int> lstVTypes;
    QString szRightVar;

    lstVTypes.clear();
    ui->lblTypeVar1->setText(szEMPTY);
    m_vtAlarmVarType = UNKNOWN;
    if (index >= 0)  {
        szRightVar.clear();
        szVarName = ui->cboVariable1->currentText();
        if (!szVarName.isEmpty())  {
            nRow = varName2Row(szVarName, lstCTRecords);
        }
        if (nRow >= 0 && nRow < lstCTRecords.count())  {
            // Recupera il tipo della Variabile a SX dell'espressione Allarme/Evento
            m_vtAlarmVarType = lstCTRecords[nRow].VarType;
            qDebug() << "Row First Variable in Alarm (Row - Name - nType - Type):" << nRow << szVarName << m_vtAlarmVarType << QString::fromAscii(varTypeName[m_vtAlarmVarType]);
            QString szVar1Type = QString::fromAscii(varTypeName[m_vtAlarmVarType]);
            szVar1Type.prepend(QString::fromAscii("["));
            szVar1Type.append(QString::fromAscii("]"));
            ui->lblTypeVar1->setText(szVar1Type);
            // Disabilita le voci per Rising and falling
            if (m_vtAlarmVarType == BIT || m_vtAlarmVarType == BYTE_BIT || m_vtAlarmVarType == WORD_BIT || m_vtAlarmVarType == DWORD_BIT)  {
                qDebug() << "Condition Enabled";
                enableComboItem(ui->cboCondition, oper_rising);
                enableComboItem(ui->cboCondition, oper_falling);
            }
            else  {
                qDebug() << "Condition is Disabled";
                disableComboItem(ui->cboCondition, oper_rising);
                disableComboItem(ui->cboCondition, oper_falling);
            }
            // Salva il nome della Var DX se già specificato
            if (ui->cboVariable2->count() > 0 && ui->cboVariable2->currentIndex() >= 0)  {
                szRightVar = ui->cboVariable2->currentText();
            }
            // Fill Var Type List with compatible types
            fillCompatibleTypesList(m_vtAlarmVarType, lstVTypes);
            // Fill Right Var Combo List
            fillComboVarNames(ui->cboVariable2, lstVTypes, lstNoHUpdates);
            // Reset Index Variable
            ui->cboVariable2->setCurrentIndex(-1);
            // Search Left variable in Right List to remove it
            nRow = ui->cboVariable2->findText(szVarName, Qt::MatchExactly);
            if (nRow >= 0 && nRow < ui->cboVariable2->count())
                ui->cboVariable2->removeItem(nRow);
            // Search original var in combo if available
            if (! szRightVar.isEmpty())  {
                nRow = ui->cboVariable2->findText(szRightVar, Qt::MatchExactly);
                if (nRow >= 0 && nRow < ui->cboVariable2->count())  {
                    ui->cboVariable2->setCurrentIndex(nRow);
                }
            }
        }
    }
}

void ctedit::on_cboCondition_currentIndexChanged(int index)
{
    if (index >= oper_rising)  {
        ui->cboVariable2->setCurrentIndex(-1);
        ui->txtFixedValue->setText(szEMPTY);
        ui->fraSelector->setEnabled(false);
        ui->fraRight->setEnabled(false);
    }
    else  {
        ui->fraSelector->setEnabled(true);
        ui->fraRight->setEnabled(true);
    }
}

int ctedit::varName2Row(QString &szVarName, QList<CrossTableRecord> &lstCTRecs)
// Search in Cross Table the index of szVarName
{
    int nRow = -1;
    char searchTag[MAX_IDNAME_LEN];

    if (! szVarName.isEmpty())  {
        strcpy(searchTag, szVarName.toAscii().data());
        for (nRow = 0; nRow < lstCTRecs.count(); nRow++)  {
            if (lstCTRecs[nRow].UsedEntry)  {
                if (strcmp(searchTag, lstCTRecs[nRow].Tag) == 0)
                    break;
            }
        }
        // Check Failed Search
        if (nRow == lstCTRecs.count())
            nRow = -1;
    }
    return nRow;
}

void ctedit::on_optFixedVal_toggled(bool checked)
{
    if (checked)  {
        ui->txtFixedValue->setEnabled(true);
        ui->cboVariable2->setEnabled(false);
    }
}

void ctedit::on_optVariableVal_toggled(bool checked)
{
    if (checked)  {
        ui->txtFixedValue->setEnabled(false);
        ui->cboVariable2->setEnabled(true);
    }
}
int  ctedit::fillCompatibleTypesList(varTypes nTypeVar, QList<int> &lstTypes)
// Riempie la lista dei tipi compatibili tra loro
{
    // Pulizia lista di destinazione
    lstTypes.clear();
    if (nTypeVar >= BIT && nTypeVar < TYPE_TOTALS) {
        switch (nTypeVar) {
            // Vari tipi di BIT
            case BIT:
            case BYTE_BIT:
            case WORD_BIT:
            case DWORD_BIT:
                lstTypes.append(BIT);
                lstTypes.append(BYTE_BIT);
                lstTypes.append(WORD_BIT);
                lstTypes.append(DWORD_BIT);
                break;
            // Vari tipi di SIGNED INT
            case INT16:
            case INT16BA:
            case DINT:
            case DINTDCBA:
            case DINTCDAB:
            case DINTBADC:
                lstTypes.append(INT16);
                lstTypes.append(INT16BA);
                lstTypes.append(DINT);
                lstTypes.append(DINTDCBA);
                lstTypes.append(DINTCDAB);
                lstTypes.append(DINTBADC);
                break;
            // Vari tipi di UNSIGNED INT
            case UINT8:
            case UINT16:
            case UINT16BA:
            case UDINT:
            case UDINTDCBA:
            case UDINTCDAB:
            case UDINTBADC:
                lstTypes.append(UINT8);
                lstTypes.append(UINT16);
                lstTypes.append(UINT16BA);
                lstTypes.append(UDINT);
                lstTypes.append(UDINTDCBA);
                lstTypes.append(UDINTCDAB);
                lstTypes.append(UDINTBADC);
                break;
            // Vari tipi di REAL
            case REAL:
            case REALDCBA:
            case REALCDAB:
            case REALBADC:
                lstTypes.append(REAL);
                lstTypes.append(REALDCBA);
                lstTypes.append(REALCDAB);
                lstTypes.append(REALBADC);
                break;
            default:
                lstTypes.append(UNKNOWN);
        }
    }
    return lstTypes.count();
}


void ctedit::on_cmdPLC_clicked()
{
    QString     szPathPLCApplication;
    QStringList lstEnv;
    QString     szCommand;
    QStringList lstArguments;
    QString     szTemp;
    QProcess    procPLC;
    qint64      pidPLC;

    // Lista delle variabili d'ambiente
    lstEnv = QProcessEnvironment::systemEnvironment().toStringList();
    qDebug() << "Current Environment:";
    int i = 0;
    for (i=0; i<lstEnv.count(); i++)  {
        qDebug() << i << lstEnv[i];
    }
    // Ricerca della variabile specifica per il lancio del PLC
    szPathPLCApplication = QProcessEnvironment::systemEnvironment().value(szPLCEnvVar, szEMPTY);
    // Search Path of PLC Application
    if (! szPathPLCApplication.isEmpty())  {
        // To be modified with specifics of PLC Application
        szTemp = QString::fromAscii("%1");
        qDebug() << szTemp;
        szPathPLCApplication.remove(szTemp, Qt::CaseInsensitive);
        szPathPLCApplication.append(QString::fromAscii("/bin/linguist"));
        // Build PLC Editor Application command
        szCommand = szPathPLCApplication;
        // First parameter: File 4cp
        szTemp = m_szCurrentProjectName;
        szTemp.remove(szProExt, Qt::CaseInsensitive);
        szTemp.append(szPLCExt);
        szTemp.prepend(m_szCurrentPLCPath);
        lstArguments.append(szTemp);
        // Imposta come Directory corrente di esecuzione la directory del File PLC
        procPLC.setWorkingDirectory(m_szCurrentPLCPath);
        // Esecuzione Comando
        qDebug() << szCommand << lstArguments;
        if (! procPLC.startDetached(szCommand, lstArguments, m_szCurrentPLCPath, &pidPLC))  {
            m_szMsg = tr("Error Starting PLC Compiler!\n");
            m_szMsg.append(szCommand);
            warnUser(this, szTitle, m_szMsg);
        }
    }
    else  {
        m_szMsg = tr("Referencer to Application PLC Compiler %1 Not Found!\n") .arg(szPLCEnvVar);
        m_szMsg.append(szCommand);
        warnUser(this, szTitle, m_szMsg);
    }
}
