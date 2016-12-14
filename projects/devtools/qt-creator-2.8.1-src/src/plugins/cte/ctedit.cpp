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
#include <QLocale>
#include <QDate>
#include <QTime>

/* ----  Local Defines:   ----------------------------------------------------- */
#define MAXCOLS 13
#define _TRUE  1
#define _FALSE 0
#define MAXBLOCKSIZE 64

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
            << trUtf8("BYTE BIT")
            << trUtf8("WORD BIT")
            << trUtf8("DWORD BIT")
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
            << trUtf8("TCP RTU")
            << trUtf8("CANOPEN")
            << trUtf8("MECT")
            << trUtf8("RTU SRV")
            << trUtf8("TCP SRV")
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
    for  (nCol=1; nCol<4; nCol++)   {
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
    for  (nCol=0; nCol<4; nCol++)   {
        ui->cboDecimal->addItem(QString::number(nCol), QString::number(nCol));
    }
    // Combo Behavior
    for  (nCol=0; nCol<lstBehavior.count(); nCol++)   {
        ui->cboBehavior->addItem(lstBehavior[nCol], lstBehavior[nCol]);
    }
    // Init Valori
    m_szCurrentCTFile.clear();
    m_szCurrentProjectPath.clear();
    m_nGridRow = 0;
    // Connessione Segnali - Slot
    connect(ui->tblCT, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));
    // connect(ui->tblCT, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(itemDoubleClicked(QModelIndex)));
    // Validator per Interi per campi txtPort txtNodeId
    ui->txtPort->setValidator(new QIntValidator(nValMin, nValMax, this));
    ui->txtNode->setValidator(new QIntValidator(nValMin, nValMax, this));
    ui->txtRegister->setValidator(new QIntValidator(nValMin, nValMax, this));
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
    // Return value
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
                tItem->setTextAlignment(Qt::AlignLeft);
                // Rende il valore non Editabile
                tItem->setFlags(tItem->flags() ^ Qt::ItemIsEditable);
                // Aggiunta al Grid
                ui->tblCT->setItem(nRowCount, nCol, tItem);
                if (CrossTable[nCur].Enable > 0)
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
    // Numero riga corrente
    // lstRecValues[colRow] = QString::number(nPos);
    // Recupero informazioni da Record CT
    // Campo Priority abilita la riga
    if (CrossTable[nPos].Enable > 0)  {
        if (CrossTable[nPos].Enable > 0)
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
        // if (CrossTable[nPos].IPAddress > 0)  {
            ipaddr2str(CrossTable[nPos].IPAddress, ip);
            szTemp = QString::fromAscii(ip);
            lstRecValues[colIP] = szTemp;
        // }
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
            if (CrossTable[nCur+1].Enable > 0)
                ui->tblCT->showRow(nCur);
            else
                ui->tblCT->hideRow(nCur);
        }
        // Ricerca della prima riga visibile
        if (nFirstVisible < 0)
            if (CrossTable[nCur+1].Enable > 0)
                nFirstVisible = nCur;
        // Verifica dello stato della riga corrente
        if (nCur == m_nGridRow)
            fVisible = CrossTable[nCur+1].Enable > 0;
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
    ui->cboDecimal->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = searchCombo(ui->cboDecimal, szTemp);
        if (nPos >= 0 && nPos < ui->cboDecimal->count())
            ui->cboDecimal->setCurrentIndex(nPos);
    }
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
    return true;
}

void ctedit::itemClicked(QModelIndex gridItem)
// Doppio Click su Grid
{
    int     nRow = gridItem.row();
    bool    fRes = false;

    if (nRow >= 0)  {
        m_nGridRow = nRow;
        // Covert CT Record 2 User Values
        fRes = recCT2List(lstValues, nRow +1);
        if (fRes)
            fRes = values2Iface(lstValues);
    }


}
void ctedit::itemDoubleClicked(QModelIndex gridItem)
// Doppio Click su Grid
{
    int         nRow = gridItem.row();

    if (nRow >= 0)  {
        m_nGridRow = nRow;
    }
}

void ctedit::on_cmdBlocchi_clicked()
{
    bool fRes = false;

    fRes = riassegnaBlocchi();
}

void ctedit::on_cmdSave_clicked()
{

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
    int     nRow = 0;
    bool    fRes = false;
    int     nPrevRow = -1;
    int     nBlockStart = 0;
    int     j = 0;
    FieldbusType    prevProtocol = (FieldbusType) 0;
    uint32_t        prevIpAdr = 0;
    uint16_t        prevPort = 0;
    varTypes        prevType = (varTypes) 0;
    uint16_t        curBlock = 0;
    int16_t         curBSize = (int16_t) 0;

    ui->cmdBlocchi->setEnabled(false);
    this->setCursor(Qt::WaitCursor);
    for (nRow = 1; nRow <= DimCrossTable+1; nRow++)  {
        // Ignora le righe con Priority == 0
        if (CrossTable[nRow].Enable > 0)  {
            // Salto riga o condizione di inizio nuovo blocco
            // Inizio nuovo blocco
            if (nPrevRow != nRow - 1 || prevProtocol !=  CrossTable[nRow].Protocol || prevIpAdr != CrossTable[nRow].IPAddress ||
                    prevPort != CrossTable[nRow].Port || prevType != CrossTable[nRow].Types || curBSize >= MAXBLOCKSIZE)  {
                // Rinumera block start
                if (nRow - nBlockStart > 1)  {
                    for (j = nBlockStart; j < nRow; j++)  {
                        CrossTable[j].BlockSize = curBSize;
                    }
                }
                // Imposta i valori di confronto correnti
                nBlockStart = nRow;
                prevProtocol =  CrossTable[nRow].Protocol;
                prevIpAdr = CrossTable[nRow].IPAddress;
                prevPort = CrossTable[nRow].Port;
                prevType = CrossTable[nRow].Types;
                curBlock = (int16_t) nRow;
                curBSize = 1;
            }
            else
                ++curBSize;
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

    // Trigo per ora per preparare un File name differente
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
