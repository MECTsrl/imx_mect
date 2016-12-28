#include "ctedit.h"
#include "ui_ctedit.h"

#include "parser.h"

#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
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
#include <QMenu>

/* ----  Local Defines:   ----------------------------------------------------- */
#define _TRUE  1
#define _FALSE 0
#define MAXBLOCKSIZE 64
#define MIN_RETENTIVE 1
#define MAX_RETENTIVE 192
#define MIN_NONRETENTIVE 193
#define MAX_NONRETENTIVE 4999
#define MIN_SYSTEM 5000
#define EMPTY_IP "0.0.0.0"
#define DEF_IP_PORT "502"

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

extern int LoadXTable(char *crossTableFile);
extern int SaveXTable(char *crossTableFile);
extern char *ipaddr2str(uint32_t ipaddr, char *buffer);

ctedit::ctedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ctedit)
{
    int     nCol = 0;
    int     nValMin = 0;
    int     nValMax = 9999;
    int     nValMaxInt16 = 65535;
    QString szEmpty;

    ui->setupUi(this);
    // Header Colonne
    lstHeadCols.clear();
    lstValues.clear();
    lstPLC.clear();
    lstBusType.clear();
    lstBehavior.clear();
    szEmpty = QString::fromAscii("");
    for (nCol = 0; nCol < colTotals; nCol++)  {
        lstHeadCols.append(szEmpty);
        lstValues.append(szEmpty);
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
    // Lista PLC
    lstPLC
            << trUtf8("H")
            << trUtf8("P")
            << trUtf8("S")
            << trUtf8("F")
            << trUtf8("V")
            << trUtf8("X")
        ;

    lstTipi
            << trUtf8("BIT")
            << trUtf8("BYTE_BIT")
            << trUtf8("WORD_BIT")
            << trUtf8("DWORD_BIT")
            << trUtf8("UINT16")
            << trUtf8("UINT16BA")
            << trUtf8("INT16")
            << trUtf8("INT16BA")
            << trUtf8("REAL")
            << trUtf8("REALDCBA")
            << trUtf8("REALCDAB")
            << trUtf8("REALBADC")
            << trUtf8("UDINT")
            << trUtf8("UDINTDCBA")
            << trUtf8("UDINTCDAB")
            << trUtf8("UDINTBADC")
            << trUtf8("DINT")
            << trUtf8("DINTDCBA")
            << trUtf8("DINTCDAB")
            << trUtf8("DINTBADC")
            << trUtf8("UNKNOWN")
        ;
    lstBusType
            << trUtf8("PLC")
            << trUtf8("RTU")
            << trUtf8("TCP")
            << trUtf8("TCP_RTU")
            << trUtf8("CANOPEN")
            << trUtf8("MECT")
            << trUtf8("RTU_SRV")
            << trUtf8("TCP_SRV")
            << trUtf8("TCPRTU SRV")
        ;
    lstBehavior
            << trUtf8("READ")
            << trUtf8("READ/WRITE")
            << trUtf8("ALARM")
            << trUtf8("EVENT")
        ;
    // Caricamento delle varie Combos
    // Combo Priority
    for  (nCol=0; nCol<4; nCol++)   {
        ui->cboPriority->addItem(QString::number(nCol), QString::number(nCol));
    }
    // Combo Update
    for  (nCol=0; nCol<lstPLC.count(); nCol++)   {
        ui->cboUpdate->addItem(lstPLC[nCol], lstPLC[nCol]);
    }
    // Combo TipoCrossTable
    for  (nCol=0; nCol<lstTipi.count(); nCol++)   {
        ui->cboType->addItem(lstTipi[nCol], lstTipi[nCol]);
    }
    // Combo Tipo Bus
    for  (nCol=0; nCol<lstBusType.count(); nCol++)   {
        ui->cboProtocol->addItem(lstBusType[nCol], lstBusType[nCol]);
    }
    // Combo Decimals
    //for  (nCol=0; nCol<4; nCol++)   {
    //    ui->cboDecimal->addItem(QString::number(nCol), QString::number(nCol));
    //}
    // Combo Behavior
    for  (nCol=0; nCol<lstBehavior.count(); nCol++)   {
        ui->cboBehavior->addItem(lstBehavior[nCol], lstBehavior[nCol]);
    }
    // Init Valori
    m_szCurrentCTFile.clear();
    m_szCurrentProjectPath.clear();
    m_nGridRow = 0;
    lstCopiedRows.clear();
    m_fRowChanged = false;
    // Connessione Segnali - Slot
    ui->tblCT->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tblCT, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(displayUserMenu(const QPoint &)));
    // connect(ui->tblCT, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));
    connect(ui->tblCT->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            SLOT(tableItemChanged(const QItemSelection &, const QItemSelection & ) ));
    // Validator per Interi per campi txtPort txtNodeId
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
    // Campi sempre locked
    ui->txtRow->setEnabled(false);
    ui->fraOptions->setEnabled(false);
    ui->txtBlock->setEnabled(false);
    ui->txtBlockSize->setEnabled(false);
    // Stringhe generiche per gestione dei formati di Data e ora
    m_szFormatDate = QString::fromAscii("yyyy.MM.dd");
    m_szFormatTime = QString::fromAscii("hh:mm:ss");
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
    QFileInfo   ctFileInfo(szFileCT);
    QString     szFile;

    if (ctFileInfo.exists() && ctFileInfo.isFile()) {
        szFile = szFileCT;
    }
    else {
        szFile = QFileDialog::getOpenFileName(this, tr("Open Cross Table File"), szFileCT, tr("Cross Table File (*.csv)"));
    }
    // Tries to Open CT File
    if (! szFile.isEmpty())   {
        m_szCurrentCTFile = szFile;
        return loadCTFile();
    }
    else  {
        m_szCurrentCTFile.clear();
        return false;
    }
}
bool    ctedit::loadCTFile()
// Load the current CT File
{
    int nRes = 0;

    if (m_szCurrentCTFile.isEmpty())
        return false;
    // Opening File
    nRes = LoadXTable(m_szCurrentCTFile.toAscii().data());
    // Return value is the result of Parsing C structure to C++ Objects
    if (nRes == 0)
        return ctable2Iface();
    else
        return false;
}
bool    ctedit::ctable2Iface()
{
    bool        fRes = true;
    int         nCur = 0;
    int         nCol = 0;
    int         nRowCount = 0;
    QString     szTemp;
    QTableWidgetItem    *tItem;

    ui->tblCT->setEnabled(false);
    ui->tblCT->clearSelection();
    ui->tblCT->setRowCount(0);
    ui->tblCT->setColumnCount(colTotals);
    for (nCur = 1; nCur <= DimCrossTable+1; ++nCur)  {
        // Covert CT Record 2 User Values
        fRes = recCT2List(lstValues, nCur);
        // If Ok add row to Table Vie
        if (fRes)  {
            ui->tblCT->insertRow(nRowCount);
            // Insert Items at Row, Col
            for (nCol = 0; nCol < colTotals; nCol++)  {
                szTemp = lstValues[nCol];
                tItem = new QTableWidgetItem(szTemp);
                if (nCol == colName || nCol == colComment)
                    // Item Allineato a Sx
                    tItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                else
                    // Item Centrato in Cella
                    tItem->setTextAlignment(Qt::AlignCenter);
                // Rende il valore non Editabile
                tItem->setFlags(tItem->flags() ^ Qt::ItemIsEditable);
                // Aggiunta al Grid
                ui->tblCT->setItem(nRowCount, nCol, tItem);
                // Flag Marcatore della riga
                if (CrossTable[nCur].UsedEntry > 0)
                    ui->tblCT->showRow(nRowCount);
                else
                    ui->tblCT->hideRow(nRowCount);
            }
            nRowCount++;
        }
    }
    // Impostazione parametri TableView
    ui->tblCT->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblCT->setHorizontalHeaderLabels(lstHeadCols);
    // ui->tblCT->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblCT->setEnabled(true);
    // Return value
    return fRes;
}
bool ctedit::recCT2List(QStringList &lstRecValues, int nPos)
{
    int     nCol = 0;
    QString szTemp;
    char ip[MAX_IPADDR_LEN];

    if (nPos <= 0 || nPos > DimCrossTable + 1)
        return false;
    szTemp.clear();
    for (nCol = 0; nCol < lstRecValues.count(); nCol++)  {
        lstRecValues[nCol] = szTemp;
    }
    // Recupero informazioni da Record CT
    // Abilitazione riga
    if (CrossTable[nPos].UsedEntry > 0)  {
        // Priority
        lstRecValues[colPriority] = QString::number(CrossTable[nPos].Enable);
        // Campo Update
        if (CrossTable[nPos].Plc >= 0 && CrossTable[nPos].Plc < lstPLC.count())
            lstRecValues[colUpdate] = lstPLC[CrossTable[nPos].Plc];
        // Campo Name
        lstRecValues[colName] = QString::fromAscii(CrossTable[nPos].Tag);
        // Campo Type
        if (CrossTable[nPos].Types >= BIT && CrossTable[nPos].Types <= UNKNOWN)
            lstRecValues[colType] = lstTipi[CrossTable[nPos].Types];
        // Campo Decimal
        lstRecValues[colDecimal] = QString::number(CrossTable[nPos].Decimal);
        // Protocol
        if (CrossTable[nPos].Protocol >= 0 && CrossTable[nPos].Protocol < lstBusType.count())
            lstRecValues[colProtocol] = lstBusType[CrossTable[nPos].Protocol];
        // IP Address
        if (CrossTable[nPos].Protocol == TCP || CrossTable[nPos].Protocol == TCPRTU ||
                CrossTable[nPos].Protocol == TCP_SRV || CrossTable[nPos].Protocol ==TCPRTU_SRV)  {
            ipaddr2str(CrossTable[nPos].IPAddress, ip);
            szTemp = QString::fromAscii(ip);
            lstRecValues[colIP] = szTemp;
        }
        // Port
        lstRecValues[colPort] = QString::number(CrossTable[nPos].Port);
        // Node Id
        lstRecValues[colNodeID] = QString::number(CrossTable[nPos].NodeId);
        // Register
        lstRecValues[colRegister] = QString::number(CrossTable[nPos].Offset);
        // Block
        lstRecValues[colBlock] = QString::number(CrossTable[nPos].Block);
        // N.Registro
        lstRecValues[colBlockSize] = QString::number(CrossTable[nPos].BlockSize);
        // Commento
        lstRecValues[colComment] = QString::fromAscii(CrossTable[nPos].Comment).trimmed();
        // Behavior
        // Caso Read/ReadWrite
        if (CrossTable[nPos].Output == _FALSE)
            lstRecValues[colBehavior] = lstBehavior[bevReadOnly];
        else if (CrossTable[nPos].Output == _TRUE)
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
    int         nCur = 0;
    bool        fVisible = false;
    int         nFirstVisible = -1;

    // Titolo del Bottone
    if (checked)  {
        ui->cmdHideShow->setText(tr("Hide"));
    }
    else  {
        ui->cmdHideShow->setText(tr("Show"));
    }
    // Items del Grid
    for (nCur = 0; nCur < ui->tblCT->rowCount(); nCur++)  {
        // Mostra tutti
        if (checked)  {
            ui->tblCT->showRow(nCur);
        }
        // Nascondi i non abilitati
        else  {
            // Mostra o nascondi le righe se sono abilitate
            if (CrossTable[nCur+1].UsedEntry > 0)
                ui->tblCT->showRow(nCur);
            else
                ui->tblCT->hideRow(nCur);
        }
        // Ricerca della prima riga visibile
        if (nFirstVisible < 0)
            if (CrossTable[nCur+1].UsedEntry > 0)
                nFirstVisible = nCur;
        // Verifica dello stato della riga corrente
        if (nCur == m_nGridRow)
            fVisible = CrossTable[nCur+1].UsedEntry > 0;
    }
    if (! fVisible)
        m_nGridRow = nFirstVisible;
    // Cambia selezione corrente
    ui->tblCT->setCurrentCell(m_nGridRow, 0, QItemSelectionModel::SelectCurrent);
    // ui->tblCT->setSelection(Zone, QItemSelectionModel::SelectCurrent);
}
bool ctedit::values2Iface(QStringList &lstRecValues)
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
    m_fRowChanged = false;
    return true;
}

void ctedit::on_cmdBlocchi_clicked()
{
    bool fRes = false;

    fRes = riassegnaBlocchi();
}

void ctedit::on_cmdSave_clicked()
{
    bool fRes = false;

    fRes = saveCTFile();

}
int ctedit::searchCombo(QComboBox *Combo, QString szValue)
// Ricerca del Valore aint16_tll'interno di una Combo scorrendo la parte Qt::UserRole
{
    int         nItem = 0;
    QString     szCurValue;
    int         retValue = -1;
    QVariant    val;

    if (Combo->count() == 0 || szValue.length() == 0)
        return retValue;
    szCurValue.clear();
    for (nItem = 0; nItem < Combo->count(); nItem++)  {
        val = Combo->itemData (nItem,  Qt::UserRole);
        if (val.canConvert<QString>())  {
            szCurValue = val.toString();
            if (szCurValue.contains(szValue, Qt::CaseSensitive))  {
                retValue =  nItem;
                break;
            }
        }
    }
    return retValue;
}
// Riassegnazione blocchi variabili
bool    ctedit::riassegnaBlocchi()
{
    int             nRow = 0;
    bool            fRes = false;
    int             nPrevRow = -1;
    int             nBlockStart = 0;
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
    for (nRow = 1; nRow <= DimCrossTable+1; nRow++)  {
        // Ignora le righe con Priority == 0
        if (CrossTable[nRow].Enable > 0)  {
            // Salto riga o condizione di inizio nuovo blocco
            // Inizio nuovo blocco
            if (nPrevRow != nRow - 1 || prevPriority != CrossTable[nRow].Enable || prevType != CrossTable[nRow].Types || prevProtocol !=  CrossTable[nRow].Protocol
                    || prevIpAdr != CrossTable[nRow].IPAddress || prevPort != CrossTable[nRow].Port || prevNodeId != CrossTable[nRow].NodeId
                    || curBSize >= MAXBLOCKSIZE)  {
                // Rinumera block start
                if (nRow - nBlockStart > 1)  {
                    for (j = nBlockStart; j < nRow; j++)  {
                        CrossTable[j].BlockSize = curBSize;
                    }
                }
                // Imposta i valori di confronto correnti
                nBlockStart = nRow;
                prevPriority = CrossTable[nRow].Enable;
                prevProtocol =  CrossTable[nRow].Protocol;
                prevIpAdr = CrossTable[nRow].IPAddress;
                prevPort = CrossTable[nRow].Port;
                prevType = CrossTable[nRow].Types;
                prevNodeId = CrossTable[nRow].NodeId;
                curBlock = (int16_t) nRow;
                curBSize = 1;
            }
            // Prosecuzione Blocco corrente
            else  {
                ++curBSize;
            }
            // Aggiornamento Blocco e Size
            CrossTable[nRow].Block = curBlock;
            CrossTable[nRow].BlockSize = curBSize;
            // Incremento ultima riga significativa
            nPrevRow = nRow;
        }
        else
            CrossTable[nRow].Block = 0;
    }
    // Rinumera ultimo blocco trattato
    for (j = nBlockStart; j < nRow; j++)  {
        CrossTable[j].BlockSize = curBSize;
    }
    // Return value as reload CT
    fRes = ctable2Iface();
    qDebug() << "Reload finished";
    ui->cmdBlocchi->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
    return fRes;
}
bool ctedit::saveCTFile()
{
    int nRes = 0;
    QString szCtFile;

    // Trigo per ora per preparare un File name differente per non perdere l'originale
    // Al momento riscrive (forse) una fotocopia della stuttura C di partenza
    szCtFile = QString(QDate::currentDate().toString(m_szFormatDate));
    szCtFile.prepend(QString::fromAscii("_"));
    szCtFile.append(QString::fromAscii("_"));
    szCtFile.append(QString(QTime::currentTime().toString(m_szFormatTime)));
    szCtFile.prepend(m_szCurrentCTFile);
    // Saving File
    nRes = SaveXTable(szCtFile.toAscii().data());
    // Return Value
    return nRes == 0;
}
bool ctedit::iface2Ctable()
{
    bool        fRes = true;
    int         nCur = 0;
    int         nCol = 0;
    int         nRowCount = 0;
    QString     szTemp;
    QTableWidgetItem    *tItem;

    // Ciclo sugli elementi di Grid
    for (nCur = 1; nCur <= ui->tblCT->rowCount(); ++nCur)  {
        lstValues.clear();
        // Insert Items at Row, Col
        for (nCol = 1; nCol < colTotals; nCol++)  {
            tItem = ui->tblCT->item(nCur, nCol);
            szTemp = tItem->text();
            // Aggiunta alla Lista
            lstValues.append(szTemp);
        }
        // Covert back User Values 2 CT Record
        fRes = list2CTrec(lstValues, nCur);
    }
    // Return Value
    return fRes;
}
bool ctedit::list2CTrec(QStringList &lstRecValues, int nPos)
{
    bool        fRes = true;

    // Return Value
    return fRes;
}
void ctedit::enableFields()
// Abilitazione dei campi form in funzione del tipo di variabile
{
    // Frame tipo Vars
    setGroupVars(m_nGridRow);
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
        else if (ui->cboProtocol->currentIndex() == MECT)  {
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
void ctedit::setGroupVars(int nRow)
// Imposta il gruppo di appartenenza di una variabile
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


void ctedit::on_cboProtocol_currentIndexChanged(int index)
{
    QString     szTemp;
    QString     szEmpty;

    // qDebug() << "Protocol Index changed to:" << index;
    szEmpty.clear();
    szTemp.clear();
    // No Index
    if (index == -1)  {
        ui->txtIP->setText(szEmpty);
        ui->txtPort->setText(szEmpty);
        ui->txtNode->setText(szEmpty);
        ui->txtRegister->setText(szEmpty);
    }
    // PLC
    else if (index == PLC)  {
        // All Data Entry Cleared
        ui->txtIP->setText(szEmpty);
        ui->txtPort->setText(szEmpty);
        ui->txtNode->setText(szEmpty);
        ui->txtRegister->setText(szEmpty);
    }
    // RTU
    else if (index == RTU)  {
        ui->txtIP->setText(szEmpty);
        szTemp = ui->txtPort->text();
        if (szTemp.isEmpty())  {
            szTemp = QString::fromAscii("1");
            ui->txtPort->setText(szTemp);
        }

    }
    // TCP, TCPRTU,
    else if (index == TCP || index == TCPRTU)  {
        szTemp = QString::fromAscii(DEF_IP_PORT);
        ui->txtPort->setText(szTemp);
    }
    // TCP_SRV, TCPRTU_SRV
    else if (index == TCP_SRV || index == TCPRTU_SRV)  {
        szTemp = QString::fromAscii(DEF_IP_PORT);
        ui->txtPort->setText(szTemp);
        szTemp = QString::fromAscii(EMPTY_IP);
        ui->txtIP->setText(szTemp);
    }
    // CANOPEN
    else if (index == CANOPEN)  {
        ui->txtIP->setText(szEmpty);
        szTemp = QString::fromAscii("1");
        ui->txtPort->setText(szTemp);
    }
    // MECT
    else if (index == MECT)  {
        ui->txtIP->setText(szEmpty);
        szTemp = QString::fromAscii("0");
        ui->txtPort->setText(szTemp);
    }
    // RTU_SRV
    else if (index == RTU_SRV)  {
        ui->txtIP->setText(szEmpty);
        szTemp = QString::fromAscii("0");
        ui->txtPort->setText(szTemp);
    }
    // Abilitazione del campi di data entry in funzione del Protocollo
    enableFields();
    m_fRowChanged = true;
}
void ctedit::tableItemChanged(const QItemSelection & selected, const QItemSelection & deselected)
// Slot attivato ad ogni cambio di riga in
{
    int     nRow = -1;
    bool    fRes = false;

    if (! deselected.isEmpty())  {
        nRow = deselected.indexes().at(0).row();
        qDebug() << "Previous Row: " << nRow;
        // szPrevID = modelSearch->index(nRow, 0).data().toString().trimmed();
    }
    if (! selected.isEmpty())  {
        // Estrae il numero di riga del modello
        nRow = selected.indexes().at(0).row();
        qDebug() << "New Row: " << nRow;
        if (nRow >= 0)  {
            m_nGridRow = nRow;
            // Covert CT Record 2 User Values
            fRes = recCT2List(lstValues, nRow +1);
            if (fRes)
                fRes = values2Iface(lstValues);
        }
    }
    else  {
        clearForm();
    }

}
void ctedit::displayUserMenu(const QPoint &pos)
// Menu contestuale Grid
{
    int         nRow = ui->tblCT->rowAt(pos.y());

    // Aggiornamento numero riga
    if (nRow >= 0)  {
        m_nGridRow = nRow;
    }
    // Oggetto menu contestuale
    QMenu gridMenu(this);
    // Items del Menu contestuale
    QAction *copyRows = gridMenu.addAction(trUtf8("Copia righe"));
    QAction *pasteRows = gridMenu.addAction(trUtf8("Incolla righe"));
    // Abilitazione delle voci di Menu
    pasteRows->setEnabled(lstCopiedRows.count() > 0 && m_nGridRow < MIN_SYSTEM);
    // Esecuzione del Menu
    QAction *actMenu = gridMenu.exec(ui->tblCT->viewport()->mapToGlobal(pos));
    // Controllo dell'Azione selezionata
    if (actMenu == copyRows)  {
        copySelected();
    }
    else if (actMenu == pasteRows)  {
        // tabView->clearSelection();
    }

}
void ctedit::copySelected()
// Copia delle righe selezionate in Buffer di Copiatura
{
    QTableWidgetItem    *tItem;
    int                 nRow = 0;

    // Clear Copied Items Rows
    lstCopiedRows.clear();
    // Compile Selected Row List
    for (nRow = 0; nRow < MAX_NONRETENTIVE - 1; nRow++)  {
        // Si utilizza la colonna 0 per capire se l'item è selezionato
        tItem = ui->tblCT->item(nRow, 0);
        if (tItem->isSelected())  {
            lstCopiedRows.append(nRow);
        }
    }
    qDebug() << "Copied: " << lstCopiedRows.count() << lstCopiedRows;
}
void ctedit::pasteSelected()
// Incolla righe da Buffer di copiatura a Riga corrente
{
    QTableWidgetItem    *tItem;
    int                 nRow = ui->tblCT->currentRow();
    int                 nCur = 0;
    int                 nSourceElement = 0;

    // Paste Rows
    if (nRow >= 0 && nRow < MAX_NONRETENTIVE - 1 && lstCopiedRows.count() > 0)  {
        // Compile Selected Row List
        for (nCur = 0; nCur < lstCopiedRows.count(); nCur ++)  {
            // Retrieve element
            nSourceElement = lstCopiedRows[nCur];
            // check if Dest Element is in User Area
            if (nRow < MAX_NONRETENTIVE - 1)  {
                // if ()
            }
        }

    }
    lstCopiedRows.clear();
    qDebug() << "Pasted: " << lstCopiedRows.count() << lstCopiedRows;
}

void ctedit::clearForm()
// Svutamento elementi Form Data Entry
{
    QString     szEmpty;

    szEmpty.clear();
    ui->cboPriority->setCurrentIndex(-1);
    ui->cboUpdate->setCurrentIndex(-1);
    ui->txtName->setText(szEmpty);
    ui->cboType->setCurrentIndex(-1);
    ui->txtDecimal->setText(szEmpty);
    ui->cboProtocol->setCurrentIndex(-1);
    ui->txtIP->setText(szEmpty);
    ui->txtPort->setText(szEmpty);
    ui->txtNode->setText(szEmpty);
    ui->txtRegister->setText(szEmpty);
    ui->txtBlock->setText(szEmpty);
    ui->txtBlockSize->setText(szEmpty);
    ui->txtComment->setText(szEmpty);
    ui->cboBehavior->setCurrentIndex(-1);
    m_fRowChanged = false;
}
