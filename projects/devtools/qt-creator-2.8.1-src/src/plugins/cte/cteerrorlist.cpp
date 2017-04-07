#include "cteerrorlist.h"
#include "ui_cteerrorlist.h"

#include <QDebug>

cteErrorList::cteErrorList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cteErrorList)
{
    int nCol = 0;

    ui->setupUi(this);
    lstCols.clear();
    for (nCol = colErrSeverity ; nCol < colErrTotals; nCol++)  {
        lstCols.append(QString::fromAscii(""));
    }
    // Riempimento liste
    // Titoli colonne  colSeverity
    lstCols[colErrSeverity] = trUtf8("Level");
    lstCols[colErrRow] = trUtf8("Row");
    lstCols[colErrColumn] = trUtf8("Column");
    lstCols[colErrVarName] = trUtf8("Variable Name");
    lstCols[colErrValue] = trUtf8("Value");
    lstCols[colErrCodeErr] = trUtf8("Error Code");
    lstCols[colErrMsgErr] = trUtf8("Error Message");
    // Impostazione parametri TableView
    ui->tblErrors->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblErrors->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblErrors->setHorizontalHeaderLabels(lstCols);
    ui->tblErrors->setEnabled(true);
    // Riga corrente
    m_nGridRow = -1;
    // Segnali - Slots
    connect(ui->tblErrors->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            SLOT(tableItemChanged(const QItemSelection &, const QItemSelection & ) ));
}

cteErrorList::~cteErrorList()
{
    delete ui;
}
void cteErrorList::on_cmdExit_clicked()
{
    this->reject();
}

void cteErrorList::on_cmdLine_clicked()
{
    this->accept();
}
int cteErrorList::currentRow()
{
    return m_nGridRow;
}
void cteErrorList::tableItemChanged(const QItemSelection & selected, const QItemSelection & deselected)
{
    int     nRow = -1;
    QString szTemp;
    bool    fOk;

    // Estrae il numero di riga dal modello
    nRow  = selected.indexes().at(0).row();
    // Recupera il valore riga dalla colonna colRow
    szTemp = ui->tblErrors->item(nRow, colErrRow)->text();
    // Conversione in Int
    nRow = szTemp.toInt(&fOk);
    m_nGridRow = fOk ? nRow - 1 : -1;
    qDebug() << "Grid Row:" << m_nGridRow;

}
int cteErrorList::lstErrors2Grid(const QList<Err_CT>  &lstErrors)
// Fill Error Grid with errors
{
    int     nRow = 0;
    int     nCol = 0;
    bool    fAdd = false;
    QString szTemp;
    QTableWidgetItem    *tItem;

    this->setCursor(Qt::WaitCursor);
    // Empty Grid
    ui->tblErrors->setEnabled(false);
    ui->tblErrors->clearSelection();
    ui->tblErrors->setRowCount(0);
    ui->tblErrors->clear();
    ui->tblErrors->setColumnCount(colErrTotals);
    ui->tblErrors->setSortingEnabled(false);
    // Reload Error Grid
    if (lstErrors.count() > 0)  {
        for (nRow = 0; nRow < lstErrors.count(); nRow ++)  {
            // Inserimento riga
            ui->tblErrors->insertRow(nRow);
            // Voci di Errore
            for (nCol = colErrSeverity; nCol < colErrTotals; nCol++)  {
                szTemp = list2CellValue(nCol, lstErrors[nRow]);
                tItem = ui->tblErrors->item(nRow, nCol);
                if (tItem == NULL)  {
                    fAdd = true;
                    tItem = new QTableWidgetItem(szTemp);
                }
                else  {
                    fAdd = false;
                    tItem->setText(szTemp);
                }
                // Adjust Alignment
                if (nCol == colErrMsgErr || nCol == colErrVarName)  {
                    // Item Allineato a Sx
                    tItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                }
                else  {
                    // Item Centrato in Cella
                    tItem->setTextAlignment(Qt::AlignCenter);
                }
                // Rende il valore non Editabile
                tItem->setFlags(tItem->flags() ^ Qt::ItemIsEditable);
                // Aggiunta al Grid
                if (fAdd)  {
                    ui->tblErrors->setItem(nRow, nCol, tItem);
                }
            }
        }

        ui->tblErrors->selectRow(0);
    }
    // Column and Selection Mode
    ui->tblErrors->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblErrors->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblErrors->setHorizontalHeaderLabels(lstCols);
    ui->tblErrors->horizontalHeader()->setSortIndicator(colErrRow, Qt::AscendingOrder);
    ui->tblErrors->setSortingEnabled(true);
    ui->tblErrors->horizontalHeader()->setResizeMode(colErrVarName, QHeaderView::Stretch);
    ui->tblErrors->horizontalHeader()->setResizeMode(colErrMsgErr, QHeaderView::Stretch);
    ui->tblErrors->setAlternatingRowColors(true);
    ui->tblErrors->setEnabled(true);
    this->setCursor(Qt::ArrowCursor);
    // Return Value
    return nRow;
}
QString cteErrorList::list2CellValue(int nCol, const Err_CT &recErr)
{
    QString     szTemp;

    if (nCol == colErrSeverity)  {
        szTemp = QString(recErr.cSeverity);
    }
    else if (nCol == colErrRow)  {
        szTemp = QString::number(recErr.nRow + 1);
    }
    else if (nCol == colErrColumn)  {
        szTemp = QString::number(recErr.nCol + 1);
    }
    else if (nCol == colErrVarName)  {
        szTemp =  recErr.szVarName;
    }
    else if (nCol == colErrValue)  {
        szTemp =  recErr.szValue;
    }
    else if (nCol == colErrCodeErr)  {
        szTemp = QString::number(recErr.nCodErr);
    }
    else if (nCol == colErrMsgErr)  {
        szTemp = recErr.szErrMessage;
    }
    // Return Value
    return  szTemp;
}
