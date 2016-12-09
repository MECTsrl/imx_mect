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

#define MAXCOLS = 13

enum colonne_e
{
    colRow = 0,
    colPriority,
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
    colNReg,
    colComment,
    colTotals
};



extern int LoadXTable(char *crossTableFile);
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
    szEmpty = QString::fromAscii("");
    for (nCol = 0; nCol < colTotals; nCol++)  {
        lstHeadCols.append(szEmpty);
        lstValues.append(szEmpty);
    }
    // Riempimento liste
    // Titoli colonne
    lstHeadCols[colRow] = trUtf8("Row");
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
    lstHeadCols[colNReg] = trUtf8("N.Reg");
    lstHeadCols[colComment] = trUtf8("Comment");
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
    // Caricamento delle varie Combos
    // Combo Priority
    for  (nCol=1; nCol<4; nCol++)   {
        ui->cboPriority->addItem(QString::number(nCol), QString::number(nCol));
    }
    // Combo Update
    for  (nCol=0; nCol<lstPLC.count(); nCol++)   {
        ui->cboUpdate->addItem(lstPLC[nCol], lstPLC[nCol]);
    }
    // Combo Tipo
    for  (nCol=0; nCol<lstTipi.count(); nCol++)   {
        ui->cboType->addItem(lstTipi[nCol], lstTipi[nCol]);
    }
    // Combo Tipo
    for  (nCol=0; nCol<lstBusType.count(); nCol++)   {
        ui->cboProtocol->addItem(lstBusType[nCol], lstBusType[nCol]);
    }
    // Combo Decimals
    for  (nCol=0; nCol<4; nCol++)   {
        ui->cboDecimal->addItem(QString::number(nCol), QString::number(nCol));
    }
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
}

ctedit::~ctedit()
{
    delete ui;
}

bool    ctedit::selectCTFile()
// Select a current CT File
{
    QString szFile;
    QFile   ctFile;

    szFile = QString::fromAscii("/home/emiliano/mect_suite/Test/BiotecHMI_rev4/config/Crosstable.csv");

    if (! ctFile.exists(szFile))
        szFile = QFileDialog::getOpenFileName(this, tr("Open Cross Table File"), szFile, tr("Cross Table File (*.csv)"));
    if (! szFile.isEmpty())   {
        m_CurrentCTFile = szFile;
        return true;
    }
    else  {
        m_CurrentCTFile.clear();
        return false;
    }
}
bool    ctedit::loadCTFile()
// Load the current CT File
{
    int nRes = 0;

    if (m_CurrentCTFile.isEmpty())
        return false;
    // Opening File
    nRes = LoadXTable(m_CurrentCTFile.toAscii().data());
    // Return value
    return nRes == 0;
}
bool    ctedit::ctable2Iface()
{
    bool        fRes = true;
    int         nCur = 0;
    int         nCol = 0;
    int         nRowCount = 0;
    QString     szTemp;
    QTableWidgetItem    *tItem;

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
    // Return value
    return fRes;
}
bool ctedit::recCT2List(QStringList &lstValues, int nPos)
{
    int     nCol = 0;
    QString szTemp;
    char ip[MAX_IPADDR_LEN];

    if (nPos <= 0 || nPos > DimCrossTable + 1)
        return false;
    szTemp.clear();
    for (nCol = 0; nCol < lstValues.count(); nCol++)  {
        lstValues[nCol] = szTemp;
    }
    // Numero riga corrente
    lstValues[colRow] = QString::number(nPos);
    // Recupero informazioni da Record CT
    // Campo Priority abilita la riga
    if (CrossTable[nPos].Enable > 0)  {
        if (CrossTable[nPos].Enable > 0)
            lstValues[colPriority] = QString::number(CrossTable[nPos].Enable);
        // Campo Update
        if (CrossTable[nPos].Plc >= 0 && CrossTable[nPos].Plc < lstPLC.count())
            lstValues[colUpdate] = lstPLC[CrossTable[nPos].Plc];
        // Campo Name
        lstValues[colName] = QString::fromAscii(CrossTable[nPos].Tag);
        // Campo Type
        if (CrossTable[nPos].Types >= BIT && CrossTable[nPos].Types <= UNKNOWN)
            lstValues[colType] = lstTipi[CrossTable[nPos].Types];
        // Campo Decimal
        lstValues[colDecimal] = QString::number(CrossTable[nPos].Decimal);
        // Protocol
        if (CrossTable[nPos].Protocol >= 0 && CrossTable[nPos].Protocol < lstBusType.count())
            lstValues[colProtocol] = lstBusType[CrossTable[nPos].Protocol];
        // IP Address
        if (CrossTable[nPos].IPAddress > 0)  {
            ipaddr2str(CrossTable[nPos].IPAddress, ip);
            szTemp = QString::fromAscii(ip);
            lstValues[colIP] = szTemp;
        }
        // Port
        lstValues[colPort] = QString::number(CrossTable[nPos].Port);
        // Node Id
        lstValues[colNodeID] = QString::number(CrossTable[nPos].NodeId);
        // Register
        lstValues[colRegister] = QString::number(CrossTable[nPos].Offset);
        // Block
        lstValues[colBlock] = QString::number(CrossTable[nPos].Block);
        // N.Registro
        lstValues[colNReg] = QString::number(CrossTable[nPos].BlockSize);
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
bool ctedit::values2Iface(QStringList &lstValues)
{
    QString szTemp;
    int     nPos = 0;

    // Priority
    szTemp = lstValues[colPriority].trimmed();
    ui->cboPriority->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = ui->cboPriority->findText(szTemp, Qt::MatchFixedString);
        if (nPos >= 0 && nPos < ui->cboPriority->count())
            ui->cboPriority->setCurrentIndex(nPos);
    }
    // Update
    szTemp = lstValues[colUpdate].trimmed();
    ui->cboUpdate->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = ui->cboUpdate->findText(szTemp, Qt::MatchFixedString);
        if (nPos >= 0 && nPos < ui->cboUpdate->count())
            ui->cboUpdate->setCurrentIndex(nPos);
    }
    // Name
    szTemp = lstValues[colName].trimmed();
    ui->txtName->setText(szTemp);
    // Type
    szTemp = lstValues[colType].trimmed();
    ui->cboType->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = ui->cboType->findText(szTemp, Qt::MatchFixedString);
        if (nPos >= 0 && nPos < ui->cboType->count())
            ui->cboType->setCurrentIndex(nPos);
    }
    // Decimal
    szTemp = lstValues[colDecimal].trimmed();
    ui->cboDecimal->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = ui->cboDecimal->findText(szTemp, Qt::MatchFixedString);
        if (nPos >= 0 && nPos < ui->cboDecimal->count())
            ui->cboDecimal->setCurrentIndex(nPos);
    }
    // Protocol
    szTemp = lstValues[colProtocol].trimmed();
    ui->cboProtocol->setCurrentIndex(-1);
    if (! szTemp.isEmpty())  {
        nPos = ui->cboProtocol->findText(szTemp, Qt::MatchFixedString);
        if (nPos >= 0 && nPos < ui->cboProtocol->count())
            ui->cboProtocol->setCurrentIndex(nPos);
    }
    // IP
    szTemp = lstValues[colIP].trimmed();
    ui->txtIP->setText(szTemp);
    // Port
    szTemp = lstValues[colPort].trimmed();
    ui->txtPort->setText(szTemp);
    // Node ID
    szTemp = lstValues[colNodeID].trimmed();
    ui->txtNode->setText(szTemp);
    // Register
    szTemp = lstValues[colRegister].trimmed();
    ui->txtRegister->setText(szTemp);
    // Block
    szTemp = lstValues[colBlock].trimmed();
    ui->txtBlock->setText(szTemp);
    // N° Registro
    szTemp = lstValues[colNReg].trimmed();
    ui->txtBlockSize->setText(szTemp);
    // Comment
    szTemp = lstValues[colComment].trimmed();
    ui->txtComment->setText(szTemp);
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
