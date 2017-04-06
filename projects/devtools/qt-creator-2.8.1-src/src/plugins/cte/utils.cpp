/***************************************************************
 * Name:      Utils.cpp
 * Purpose:
 * Author:    AS ()
 * Created:   2012.04.02
 * Copyright: AS ()
 * License:
 **************************************************************/
#include <QByteArray>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QList>
#include <QLocale>
#include <QProcess>
#include <QStringList>
#include <QDesktopServices>
#include <QUrl>
#include <QChar>
#include <QLatin1Char>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QBrush>
#include <math.h>
#include <QCoreApplication>
#include "utils.h"

const  char         cDoubleQuote = 34;      // Carattere "
const  char         cSingleQuote = 39;      // '
const  char         cSpace = 32;            // Blank
const  char         cZero = 48;             // Zero

QString szSpace(int nSpaces)
// Ritorna una stringa di nSpaces Spazio o vuota se nSpaces <= 0
{
    QString     szTemp;

    szTemp.clear();
    if (nSpaces > 0)
        szTemp.fill(QChar(cSpace, 0), nSpaces);
    // Return Value
    return szTemp;
}

void splitFileName(const QString &fileName, QString &szPath, QString &szFile, QString &szSuffisso)
// Spezza un file name nelle sue componentiPath, Nome File, Suffisso
{
    szPath.clear();
    szFile.clear();
    szSuffisso.clear();
    if (fileName.length() > 0)   {
        QFile fWork(fileName);
        if (fWork.exists())  {
            // Isola il Path Corrente dal nome del file
            QFileInfo fileInfo(fileName);
            szPath = fileInfo.absolutePath();
            szFile = fileInfo.completeBaseName();
            szSuffisso = fileInfo.suffix();
        }
    }

}
QString getPathFromFileName(const QString &fileName)
// Estrae il Path assoluto dal File Name ricevuto come parametro
{
    QString szReturn;

    szReturn.clear();
    if (fileName.length() > 0)   {
        QFile fWork(fileName);
        if (fWork.exists())  {
            // Isola il Path Corrente dal nome del file
            QFileInfo pathInfo(fileName);
            szReturn = pathInfo.absolutePath();
        }
    }
    return szReturn;
}
bool fileExists(const QString &szFile)
{
    QFileInfo checkFile(szFile);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}
bool fileBackUp(const QString &szFile)
// Crea una copia di BackUp di un file
{
    QFile   sourceFile(szFile);
    QString szFileDest(szFile);
    bool    fRes = false;

    if (fileExists(szFile))  {
        szFileDest.append(QString::fromAscii(".bak"));
        fRes = sourceFile.copy(szFileDest);
    }
    // Return Value
    return fRes;
}

bool queryUser(QWidget * parent, const QString &szTitle, const QString &szQueryMessage, bool fDefault)
// Domanda all'Utente se procedere, return True se Ok
{
    bool        fRes = false;
    QMessageBox::StandardButton         nDefButton = QMessageBox::No;

    if (fDefault)
        nDefButton = QMessageBox::Yes;
    else
        nDefButton = QMessageBox::No;

    QMessageBox::StandardButton ret = QMessageBox::Yes;

    // Prompt Message Box
    ret = QMessageBox::question(parent, szTitle, szQueryMessage, QMessageBox::Yes | QMessageBox::No, nDefButton);
    // Return Value
    fRes = (ret == QMessageBox::Yes);
    return fRes;
}
void notifyUser(QWidget * parent, const QString &szTitle, const QString &szMessage)
// Notifica all'Utente il messaggio con solo il tasto Ok
{
    QMessageBox::StandardButton ret = QMessageBox::Ok;

    // Prompt Message Box
    ret = QMessageBox::information(parent, szTitle, szMessage);
}
void warnUser(QWidget * parent, const QString &szTitle, const QString &szMessage)
// Notifica all'Utente il messaggio con solo il tasto Ok e Icona Warning
{
    QMessageBox::StandardButton ret = QMessageBox::Ok;

    // Prompt Message Box
    ret = QMessageBox::critical(parent, szTitle, szMessage);
}

QString num2Hex(int nValue, int nLen)
// Converte un numero in stringa Hex, con padding a 0 a Sx per nLen Chars
{
    QString szTemp;
    QString szFiller;

    szTemp = QString::number(nValue, 16);
    szTemp = szTemp.trimmed();
    szFiller.clear();
    if (nLen > 0)  {
        szFiller.fill(QChar(cZero, 0), nLen);
        if (szTemp.length() < nLen) {
            szTemp = szTemp.prepend(szFiller);
            szTemp = szTemp.right(nLen);
        }
    }
    // Conversione in Maiuscole
    szTemp = szTemp.toUpper();
    return szTemp;
}
QString int2PaddedString(int nValue, int nLen, int nBase)
// Converte un numero in stringa, con padding a 0 a Sx per nLen Chars
// La base di default per la conversione è 10
{
    QString szTemp;
    QString szFiller;

    szTemp = szTemp.number(nValue, nBase);
    szTemp = szTemp.trimmed();
    szFiller.clear();
    if (nLen > 0)  {
        szFiller.fill(QChar(cZero, 0), nLen);
        if (szTemp.length() < nLen) {
            szTemp = szTemp.prepend(szFiller);
            szTemp = szTemp.right(nLen);
        }
    }
    // Conversione in Maiuscole
    szTemp = szTemp.toUpper();
    return szTemp;
}
QString long2PaddedString(quint64 nValue, int nLen, int nBase)
// Converte un numero long in stringa Dec/Hex, con padding a 0 a Sx per nLen Chars
// La base di default per la conversione è 10
{
    QString szTemp;
    QString szFiller;

    szTemp = szTemp.number(nValue, nBase);
    szTemp = szTemp.trimmed();
    szFiller.clear();
    if (nLen > 0)  {
        szFiller.fill(QChar(cZero, 0), nLen);
        if (szTemp.length() < nLen) {
            szTemp = szTemp.prepend(szFiller);
            szTemp = szTemp.right(nLen);
        }
    }
    // Conversione in Maiuscole
    szTemp = szTemp.toUpper();
    return szTemp;
}
QString parseQuote(const QString &szFieldValue)
// Controlla gli eventuali Quote in una stringa prima di passarli ad uno Statement SQL
{
    QString szReturn;
    int nPos = 0;

    // Start Values
    szReturn = szFieldValue;
    // Ricerca del Singolo Apice
    nPos = szReturn.indexOf(QChar(cSingleQuote, 0), nPos);
    while (nPos >= 0)  {
        // Aggiunge un nuovo cSingleQuote
        szReturn = szReturn.left(nPos + 1) + QChar(cSingleQuote, 0) + szReturn.mid(nPos + 1);
        // Ricerca del successivo cSingleQuote
        nPos = szReturn.indexOf(QChar(cSingleQuote, 0), nPos + 2);
    }
    // Ricerca del Doppio Apice
    nPos = szReturn.indexOf(QChar(cDoubleQuote, 0), nPos);
    while (nPos >= 0)  {
        // Aggiunge un nuovo cSingleQuote
        szReturn = szReturn.left(nPos + 1) + QChar(cDoubleQuote, 0) + szReturn.mid(nPos + 1);
        // Ricerca del successivo cSingleQuote
        nPos = szReturn.indexOf(QChar(cDoubleQuote, 0), nPos + 2);
    }
    // Return Value
    return szReturn;
}
QString addQuote(const QString &szFieldValue)
// Aggiunge Single Quote ad un campo
{
    QString szReturn;

    // Start Values
    szReturn = szFieldValue;
    // Rimuovi spazi aggiuntivi
    szReturn.trimmed();
    szReturn.prepend(QChar(cSingleQuote, 0));
    szReturn.append(QChar(cSingleQuote, 0));
    // Return Value
    return szReturn;

}
QString addDoubleQuote(const QString &szStringValue)
// Aggiunge Doppio Quote ad una stringa
{
    QString szReturn;

    // Start Values Rimuovi spazi aggiuntivi
    szReturn = szStringValue.trimmed();
    szReturn.prepend(QChar(cDoubleQuote, 0));
    szReturn.append(QChar(cDoubleQuote, 0));
    // return Value
    return szReturn;

}

QString string2CamelCase(const QString szValue)
// Conversione di una stringa a Camel Case [Prima iniziale di ogni parola maiuscola]
{
    QString     szTemp;
    QString     szToken;
    QString     szResult;
    int         i = 0;
    // Conversione stringa a Lower Case
    szTemp = szValue;
    szTemp = szTemp.toLower();
    // Split della
    QStringList szList = szTemp.split(QChar(cSpace, 0), QString::SkipEmptyParts);
    szTemp.clear();
    for (i = 0; i < szList.count(); i++)  {
        szTemp = szList[i].trimmed();
        szToken = szTemp.left(1).toUpper();
        szToken = szToken + szTemp.mid(1);
        szList[i] = szToken;
    }
    szResult = szList.join(QChar(cSpace, 0));
    return szResult;
}
double myRound(double dblVal, unsigned decPlaces)
// Arrotondamento a n Cifre Decimali di un double
// Metodo Matematico: Si prende un numero, si moltiplica per 10^decPlaces, si somma + 0.5 per arrotondare, e si ridivide per 10^decPlaces
// Metodo String Based: Con la stessa logica di Clipper si converte un Double in una stringa con il numero di decimali richiesto
// E poi si riconverte nuovamente in double. Se tutto fila liscio (ovvero fOk = true) si ritorna il nuovo
// valore, diversamente il valore di partenza. E' un modo per toglere di mezzo decimali strani in 10 posizione...
// Restano comunque dei decimali in posizione molto bassa legati alla precisione dei floating point
{
    // double  dblTemp = 0.0;
    double  dblFloor = 0.0;
    // bool    fOk = false;
    // QString szTemp;

    // Metodo Matematico di arrotondamento (Produce gli stessi effetti del metodo string based ma è più veloce)
    dblFloor =  floor(dblVal * pow(10., decPlaces) + .5) / pow(10., decPlaces);
    // Metodo String based di arrotondamento
    // szTemp = QLocale::system().toString(dblVal,'f', decPlaces);
    // dblTemp = QLocale::system().toDouble(szTemp, &fOk);
    // dblTemp = fOk ? dblTemp : dblVal;
    // Return Value
    return dblFloor;

}

void setCellEnabled(QTableWidgetItem *tItem, bool fEnabled)
// Abilita o disabilita una cella di un QTableWidget
{
    int nFlags;

    if (tItem != 0)  {
        nFlags = tItem->flags();
        // Abilita la Cella (OR con Flag Abilitazione)
        nFlags = nFlags | Qt::ItemIsEnabled;
        // Disabilita la Cella (XOR con Flag Abilitazione, sicuramente Bit Spento)
        if (! fEnabled)
            nFlags = nFlags ^ Qt::ItemIsEnabled;
        // Impostazione Flag
        tItem->setFlags((Qt::ItemFlags) nFlags);
    }
}
void setCellEditable(QTableWidgetItem *tItem, bool fEnabled)
// Permette Editing diretto su cella di un QTableWidget
{
    int nFlags;

    if (tItem != 0)  {
        nFlags = tItem->flags();
        // Abilita Editing Cella (OR con Flag Abilitazione)
        nFlags = nFlags | Qt::ItemIsEditable;
        // Disabilita Editing Cella (XOR con Flag Abilitazione, sicuramente Bit Spento)
        if (! fEnabled)
            nFlags = nFlags ^ Qt::ItemIsEditable;
        // Impostazione Flag
        tItem->setFlags((Qt::ItemFlags) nFlags);
    }
}
void setCellSelectable(QTableWidgetItem *tItem, bool fEnabled)
// Permette la selezione della Cella
{
    int nFlags;

    if (tItem != 0)  {
        nFlags = tItem->flags();
        // Abilita Selezione Cella (OR con Flag Abilitazione)
        nFlags = nFlags | Qt::ItemIsSelectable;
        // Disabilita Editing Cella (XOR con Flag Abilitazione, sicuramente Bit Spento)
        if (! fEnabled)
            nFlags = nFlags ^ Qt::ItemIsSelectable;
        // Impostazione Flag
        tItem->setFlags((Qt::ItemFlags) nFlags);
    }
}
void setTableRowEnabled(QTableWidget * tTable, int nRow, bool fEnabled)
// Blocca/Sblocca completamente la Riga della Tabella
{
    int nCol = 0;
    QTableWidgetItem    *tItem;

    if (nRow < tTable->rowCount())  {
        for (nCol = 0; nCol < tTable->columnCount(); nCol++)  {
            tItem = tTable->item(nRow, nCol);
            if (tItem != 0)  {
                setCellSelectable(tItem, fEnabled);
                setCellEditable(tItem, fEnabled);
                setCellEnabled(tItem, fEnabled);
            }
        }
    }
}

void  setTableColEnabled(QTableWidget * tTable, int nCol, bool fEnabled)
// Blocca/Sblocca completamente la Colonna della Tabella
{
    int nRow = 0;
    QTableWidgetItem    *tItem;

    if (nCol < tTable->columnCount())  {
        for (nRow = 0; nRow < tTable->rowCount(); nRow++)  {
            tItem = tTable->item(nRow, nCol);
            if (tItem != 0)  {
                setCellSelectable(tItem, fEnabled);
                setCellEditable(tItem, fEnabled);
                setCellEnabled(tItem, fEnabled);
            }
        }
    }
}
bool showFile(QString szFileName)
// Utilizza i DeskTop Sevices per mostrare un File (es. PDF)
{
    bool    fRes = false;
    QUrl    urlObj;

    // Controllo Esistenza File
    if (! fileExists(szFileName))
        return fRes;
    // Gestione dei Path di tipo UNC
    if (szFileName.startsWith(QString::fromLatin1("\\\\")) || szFileName.startsWith(QString::fromLatin1("//")))  {
        QString szFile;
        szFile = QDir::toNativeSeparators(szFileName);
        urlObj.setUrl(szFile);
    }
    else
        urlObj = QUrl::fromLocalFile(szFileName);
    urlObj.setScheme(QString::fromLatin1("file"));
    fRes = QDesktopServices::openUrl(urlObj);
    // Return Value
    return fRes;
}
void setRowBackground(const QBrush& brush, QAbstractItemModel* model, int row, const QModelIndex& parent)
{
    if(!model || row<0)
        return;
    if(row>=model->rowCount(parent))
        return;
    if(parent.isValid()){
        if(parent.model() != model)
            return;
    }
    for(int i=0; i < model->columnCount(parent); ++i)
        model->setData(model->index(row,i,parent),brush,Qt::BackgroundRole);
}
void doEvents()
{
    QCoreApplication::processEvents();
}
void enableComboItem(QComboBox *Combo, int nItemIndex)
// Riabilita la voce nItemIndex della Combo
{
    if (nItemIndex >= 0 && nItemIndex < Combo->count())
        Combo->setItemData(nItemIndex, 33, Qt::UserRole - 1);
}
void disableComboItem(QComboBox *Combo, int nItemIndex)
// Disabilita la voce nItemIndex della Combo
{
    if (nItemIndex >= 0 && nItemIndex < Combo->count())
        Combo->setItemData(nItemIndex, 0, Qt::UserRole - 1);
}
bool disableAndBlockSignals(QWidget *widget)
// Disabilita e blocca segnali di un oggetto QWidget*
{
    widget->setDisabled(true);
    return widget->blockSignals(true);
}
bool enableAndUnlockSignals(QWidget *widget)
// Riabilita e sblocca segnali di un oggetto QWidget*
{
    widget->setEnabled(true);
    return widget->blockSignals(false);
}
