#include "trendeditor.h"
#include "ui_trendeditor.h"
#include "utils.h"

#include <QColor>
#include <QColorDialog>
#include <QPalette>
#include <QDebug>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QValidator>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QMessageBox>

const int nTrk1 = 1;
const int nTrk2 = 2;
const int nTrk3 = 3;
const int nTrk4 = 4;



const QString szTREND1FILE = QString::fromAscii("trend1.csv");
const QString szTRENDMASK =  QString::fromAscii("trend*.csv");
const QString szDEFCOLOR = QString::fromAscii("palegreen");
const QString szPORTRAIT = QString::fromAscii("P");
const QString szLANDSCAPE = QString::fromAscii("L");

enum trendFields
{   nTrendVisible = 0,
    nTrendVarName,
    nTrendColor,
    nTrendMin,
    nTrendMax,
    nTrendDescr,
    nTrendTotal
};


TrendEditor::TrendEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrendEditor)
{
    ui->setupUi(this);
    // Filling Fixed Combos
    // Combo Orientation
    mapOrientation.insert(szPORTRAIT, trUtf8("Portrait"));
    mapOrientation.insert(szLANDSCAPE, trUtf8("Landscape"));
    ui->cboOrientation->addItems(mapOrientation.values());
    ui->cboOrientation->setCurrentIndex(-1);
    // Validators
    ui->txtMin_1->setValidator(new QDoubleValidator(this));
    ui->txtMin_2->setValidator(new QDoubleValidator(this));
    ui->txtMin_3->setValidator(new QDoubleValidator(this));
    ui->txtMin_4->setValidator(new QDoubleValidator(this));
    ui->txtMax_1->setValidator(new QDoubleValidator(this));
    ui->txtMax_2->setValidator(new QDoubleValidator(this));
    ui->txtMax_3->setValidator(new QDoubleValidator(this));
    ui->txtMax_4->setValidator(new QDoubleValidator(this));
    // Path & file infos
    m_szTrendFile.clear();
    m_szTrendPath.clear();
}

TrendEditor::~TrendEditor()
{
    delete ui;
}

void TrendEditor::updateVarLists(const QStringList &lstTrendVars)
{
    int         nCur;
    int         nPos = -1;
    QString      szCurVar;
    QComboBox   *cboVar = 0;

    for (nCur = nTrk1; nCur <= nTrk4; nCur++)  {
        if (nCur == nTrk1)  {
            cboVar = ui->cboVariable_1;
        }
        else if (nCur == nTrk2)  {
            cboVar = ui->cboVariable_2;
        }
        else if (nCur == nTrk3)  {
            cboVar = ui->cboVariable_3;
        }
        else if (nCur == nTrk4)  {
            cboVar = ui->cboVariable_4;
        }
        // qDebug() << tr("Updated Variables Combo: %1") .arg(nCur);
        // Retrieve Current Item selected if Any
        szCurVar = cboVar->currentText();
        // Update Varlist
        cboVar->clear();
        cboVar->addItems(lstTrendVars);
        // Fetch previous value
        nPos = -1;
        if (!szCurVar.isEmpty())  {
            nPos = lstTrendVars.indexOf(szCurVar);
        }
        cboVar->setCurrentIndex(nPos);
    }
}

void TrendEditor::on_cmdColor_1_clicked()
{
    getNewColor(nTrk1);
}

void TrendEditor::on_cmdColor_2_clicked()
{
    getNewColor(nTrk2);
}

void TrendEditor::on_cmdColor_3_clicked()
{
    getNewColor(nTrk3);
}

void TrendEditor::on_cmdColor_4_clicked()
{
    getNewColor(nTrk4);
}
bool    TrendEditor::getNewColor(int nTrack)
// Show Color dialog to select new Track color
{
    QString     szColor;
    QColor      cColor;
    QColor      newColor;
    QLabel      *destLabel = 0;
    bool        fRes = false;

    // Retrieve Colors and start color dialog
    if (nTrack == nTrk1)  {
        szColor = ui->lblColor_1->text();
        destLabel = ui->lblColor_1;
    }
    else if (nTrack == nTrk2)  {
        szColor = ui->lblColor_2->text();
        destLabel = ui->lblColor_2;
    }
    else if (nTrack == nTrk3)  {
        szColor = ui->lblColor_3->text();
        destLabel = ui->lblColor_3;
    }
    else if (nTrack == nTrk4)  {
        szColor = ui->lblColor_4->text();
        destLabel = ui->lblColor_4;
    }
    // Analisi del contenuto della label
    if (! szColor.isEmpty())  {
        szColor.prepend(szSHARP);
        if (QColor::isValidColor(szColor))  {
            cColor.setNamedColor(szColor);
            // qDebug() << tr("Color valid: %1") .arg(szColor);
        }
        else {
            cColor = QColor(szDEFCOLOR);
            // qDebug() << tr("Color invalid: %1 forced to: %2") .arg(szColor) .arg(cColor.name());
        }
    }
    if (! cColor.isValid()) {
        cColor = QColor(szDEFCOLOR);
    }
    // Open Color Dialog to select New Color
    newColor = QColorDialog::getColor(cColor, this, tr("Select Track %1 Color") .arg(nTrack));
    // Set New Color to Label
    if (newColor.isValid() && destLabel != 0)  {
        setLabelColor(destLabel, newColor);
        fRes = true;
    }
    return fRes;
}
bool TrendEditor::tokens2Iface(const QStringList &lstTokens, int nRow)
// Da CSV Tokens ad interfaccia
{
    // Puntatori ad oggetto interfaccia del Trend corrente
    QCheckBox       *chkVisible = 0;
    QComboBox       *cboVariable = 0;
    QLabel          *lblColor = 0;
    QLineEdit       *txtMin = 0;
    QLineEdit       *txtMax = 0;
    QLineEdit       *txtComment = 0;
    // Variabili di supporto per verifica valori
    QString         szTemp;
    double          dblVal = 0.0;
    int             nVal = 0;
    bool            fOK = false;
    QColor          cColTrend;
    bool            fRes = true;


    // Assegnazione delle caselle di lavoro
    if (nRow == nTrk1)  {
        chkVisible = ui->chkVisible_1;
        cboVariable = ui->cboVariable_1;
        lblColor = ui->lblColor_1;
        txtMin = ui->txtMin_1;
        txtMax = ui->txtMax_1;
        txtComment = ui->txtComment_1;
    } 
    else if (nRow == nTrk2)  {
        chkVisible = ui->chkVisible_2;
        cboVariable = ui->cboVariable_2;
        lblColor = ui->lblColor_2;
        txtMin = ui->txtMin_2;
        txtMax = ui->txtMax_2;
        txtComment = ui->txtComment_2;
    } 
    else if (nRow == nTrk3)  {
        chkVisible = ui->chkVisible_3;
        cboVariable = ui->cboVariable_3;
        lblColor = ui->lblColor_3;
        txtMin = ui->txtMin_3;
        txtMax = ui->txtMax_3;
        txtComment = ui->txtComment_3;
    } 
    else if (nRow == nTrk4)  {        
        chkVisible = ui->chkVisible_4;
        cboVariable = ui->cboVariable_4;
        lblColor = ui->lblColor_4;
        txtMin = ui->txtMin_4;
        txtMax = ui->txtMax_4;
        txtComment = ui->txtComment_4;
    }
    // Check Visible
    nVal = lstTokens[nTrendVisible].toInt(&fOK);
    if (fOK)  {
        fOK = nVal == 1;
        chkVisible->setChecked(fOK);
    }
    else
        chkVisible->setChecked(false);
    // Var Name
    nVal = cboVariable->findText(lstTokens[nTrendVarName]);
    if (nVal >= 0 && nVal < cboVariable->count())
        cboVariable->setCurrentIndex(nVal);
    else
        cboVariable->setCurrentIndex(-1);
    // Color Trend
    szTemp = lstTokens[nTrendColor];
    if (!szTemp.isEmpty())  {
        szTemp.prepend(szSHARP);
        if (QColor::isValidColor(szTemp))  {
            cColTrend.setNamedColor(szTemp);
        }
    }
    if (! cColTrend.isValid())
        cColTrend.setNamedColor(szDEFCOLOR);
    setLabelColor(lblColor, cColTrend);
    // MinValue
    dblVal = lstTokens[nTrendMin].toDouble(&fOK);
    dblVal = fOK ? dblVal : 0.0;
    szTemp = QString::number(dblVal, 'f', 3);
    txtMin->setText(szTemp);
    // MaxValue
    dblVal = lstTokens[nTrendMax].toDouble(&fOK);
    dblVal = fOK ? dblVal : 0.0;
    szTemp = QString::number(dblVal, 'f', 3);
    txtMax->setText(szTemp);
    // Comment
    txtComment->setText(lstTokens[nTrendDescr]);
    // Return value
    return fRes;
}
bool TrendEditor::iface2Tokens(QStringList &lstTokens, int nRow)
// Da Interfaccia a List per scrittura CSV
{
    bool            fRes = true;
    // Puntatori ad oggetto interfaccia del Trend corrente
    QCheckBox       *chkVisible = 0;
    QComboBox       *cboVariable = 0;
    QLabel          *lblColor = 0;
    QLineEdit       *txtMin = 0;
    QLineEdit       *txtMax = 0;
    QLineEdit       *txtComment = 0;


    // Assegnazione delle caselle di lavoro
    if (nRow == nTrk1)  {
        chkVisible = ui->chkVisible_1;
        cboVariable = ui->cboVariable_1;
        lblColor = ui->lblColor_1;
        txtMin = ui->txtMin_1;
        txtMax = ui->txtMax_1;
        txtComment = ui->txtComment_1;
    }
    else if (nRow == nTrk2)  {
        chkVisible = ui->chkVisible_2;
        cboVariable = ui->cboVariable_2;
        lblColor = ui->lblColor_2;
        txtMin = ui->txtMin_2;
        txtMax = ui->txtMax_2;
        txtComment = ui->txtComment_2;
    }
    else if (nRow == nTrk3)  {
        chkVisible = ui->chkVisible_3;
        cboVariable = ui->cboVariable_3;
        lblColor = ui->lblColor_3;
        txtMin = ui->txtMin_3;
        txtMax = ui->txtMax_3;
        txtComment = ui->txtComment_3;
    }
    else if (nRow == nTrk4)  {
        chkVisible = ui->chkVisible_4;
        cboVariable = ui->cboVariable_4;
        lblColor = ui->lblColor_4;
        txtMin = ui->txtMin_4;
        txtMax = ui->txtMax_4;
        txtComment = ui->txtComment_4;
    }
    // Salvataggio dei valori su Lista Tokens
    lstTokens.clear();
    int nCol = 0;
    for (nCol = 0; nCol < nTrendTotal; nCol++)  {
        lstTokens.append(szEMPTY);
    }
    // Check Box Visible
    lstTokens[nTrendVisible] = (chkVisible->isChecked() ? szTRUE : szFALSE);
    // Variabile Name
    lstTokens[nTrendVarName] = cboVariable->currentText().trimmed();
    // Color Name
    lstTokens[nTrendColor] = lblColor->text().trimmed();
    // Trend Min
    lstTokens[nTrendMin] = txtMin->text().trimmed();
    // Trend Max
    lstTokens[nTrendMax] = txtMax->text().trimmed();
    // Trend Descriprion
    lstTokens[nTrendDescr] = txtComment->text().trimmed();
    // Return value
    return fRes;
}
bool TrendEditor::trendFile2Iface(const QString &szFileTrend)
// Load a trends file in Interface Fields
{
    bool            fRes = false;
    QFile           fSource(szFileTrend);
    QString         szLine;
    QStringList     lstTokens;
    int             nPos = -1;
    int             nRow = 1;

    if (fSource.exists())  {
        fSource.open(QIODevice::ReadOnly | QIODevice::Text);
        if (fSource.isOpen())  {
            QTextStream txtTrend(&fSource);
            // Legge la prima riga per l'orientamento del Trend
            if (!txtTrend.atEnd())  {
                szLine = txtTrend.readLine().trimmed();
                if (! szLine.isEmpty())  {
                    if (mapOrientation.contains(szLine))  {
                        szLine = mapOrientation.value(szLine);
                        nPos = ui->cboOrientation->findText(szLine, Qt::MatchFixedString);
                    }
                }
            }
            if (nPos >= 0 && nPos < ui->cboOrientation->count())
                ui->cboOrientation->setCurrentIndex(nPos);
            else
                ui->cboOrientation->setCurrentIndex(-1);
            // Cerca nel file le altre 4 righe 1 per ogni trend
            while(! txtTrend.atEnd() && nRow <= nTrk4) {
                szLine = txtTrend.readLine().trimmed();
                // Divide la riga letta in Tokens
                lstTokens = szLine.split(szSEMICOL);
                if (lstTokens.count() >= nTrendTotal)  {
                    // Trim dei Tokens
                    for (nPos = 0; nPos < lstTokens.count(); nPos++)
                        lstTokens[nPos] = lstTokens[nPos].trimmed();
                    // Tokens ad elementi interfaccia
                    fRes = tokens2Iface(lstTokens, nRow);
                }
                else
                    fRes = false;
                if (! fRes)
                    break;
                // Next Line
                nRow++;
            }
            // Close File
            fSource.close();
        }
    }
    // Return value
    return fRes;
}
bool TrendEditor::iface2TrendFile(const QString &szFileTrend)
// Write Interface Fields to a trends file
{
    bool            fOk = false;
    QFile           fDest(szFileTrend);
    QString         szLine;
    QStringList     lstTokens;
    int             nRow = 1;

    // Apertura del File in modalità scrittura troncata
    fDest.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    if (fDest.isOpen())  {
        QTextStream txtTrend(&fDest);
        // Trend Orientation
        szLine = mapOrientation.key(ui->cboOrientation->currentText());
        if (szLine.isEmpty())
            szLine = szLANDSCAPE;
        txtTrend << szLine << endl;
        // Trend Fields
        for (nRow = nTrk1; nRow <= nTrk4; nRow++)  {
            fOk = iface2Tokens(lstTokens, nRow);
            if (fOk)  {
                szLine = lstTokens.join(szSEMICOL);
                txtTrend << szLine << endl;
            }
            else
                break;
        }
        txtTrend.flush();
        fDest.close();
    }
    // Return value
    return fOk;
}

void TrendEditor::on_cmdLoad_clicked()
{
    QString szSourceFile;

    szSourceFile = QFileDialog::getOpenFileName(this, tr("Open Trend File"),
                                              m_szTrendFile, tr("Trends Files (trend*.csv)"));
    if (! szSourceFile.isEmpty())  {
        QFile fTrend(szSourceFile);
        if (fTrend.exists())  {
            if (trendFile2Iface(szSourceFile))  {
                m_szTrendFile = szSourceFile;
                ui->txtTrendName->setText(szSourceFile);
            }
        }
    }
}

void TrendEditor::on_cmdSave_clicked()
{
    QString szDestFile;

    // Checking interface Values
    if (! checkFields())
        return;
    // Ask Dialog file name
    szDestFile = QFileDialog::getSaveFileName(this, tr("Save Trend File"),
                                              m_szTrendFile, tr("Trends Files (trend*.csv)"));
    if (! szDestFile.isEmpty())  {
        // Copia di salvataggio
        fileBackUp(szDestFile);
        // Scrittura nuovi valori
        if (iface2TrendFile(szDestFile))  {
            m_szTrendFile = szDestFile;
            ui->txtTrendName->setText(szDestFile);
        }
    }
}
void TrendEditor::setTrendsPath(const QString &szTrendsPath)
{
    QString         szNewTrendFile;

    m_szTrendPath = szTrendsPath;
    if (m_szTrendFile.isEmpty())  {
        szNewTrendFile = m_szTrendPath;
        szNewTrendFile.append(szTREND1FILE);
        QFile fTrend(szNewTrendFile);
        if (fTrend.exists())  {
            if (trendFile2Iface(szNewTrendFile))  {
                m_szTrendFile = szNewTrendFile;
                ui->txtTrendName->setText(szNewTrendFile);
            }
        }
    }
}
void TrendEditor::setLabelColor(QLabel *destLabel, QColor newColor)
// Imposta background e foreground di una label con il colore newColor
{
    QString     szColor;
    QColor      cTextColor;

    if (destLabel != 0 && newColor.isValid())  {
        QPalette    palLabel = destLabel->palette();
        palLabel.setColor(destLabel->backgroundRole(), newColor);
        // Calcola un colore opportuno per il Testo della Label
        cTextColor = getIdealTextColor(newColor);
        palLabel.setColor(destLabel->foregroundRole(), cTextColor);
        destLabel->setAutoFillBackground(true);        
        destLabel->setPalette(palLabel);
        // Update Label content
        szColor = newColor.name();
        szColor.remove(szSHARP);
        szColor = szColor.toUpper();
        destLabel->setText(szColor);
    }
}
bool TrendEditor::checkFields()
// Controllo del contenuto dei campi
{
    bool            fRes = false;
    bool            fOk = false;
    bool            fVisible = false;
    int             nRow = 0;
    QStringList     lstTokens;
    double          dblMin = 0;
    double          dblMax = 0;

    // Combo Orientation
    if(ui->cboOrientation->currentIndex() < 0)
    {
        QMessageBox::critical(0,trUtf8("Error"),trUtf8("'Orientation' must be selected"));
        goto exitCheck;
    }
    for (nRow = nTrk1; nRow <= nTrk4; nRow++)  {
        fOk = iface2Tokens(lstTokens, nRow);
        // Acquisizione valore check Visible
        fVisible = lstTokens[nTrendVisible] == szTRUE;
        // Variable Name
        if (fVisible && lstTokens[nTrendVarName].isEmpty())  {
            m_szMsg = tr("Track: %1. If Visible associated Variable must be selected") .arg(nRow);
            QMessageBox::critical(0,trUtf8("Error"),m_szMsg);
            goto exitCheck;
        }
        // Trend Color
        if (fVisible && lstTokens[nTrendColor].isEmpty())  {
            m_szMsg = tr("Track: %1. If Visible associated Display Color must be selected") .arg(nRow);
            QMessageBox::critical(0,trUtf8("Error"),m_szMsg);
            goto exitCheck;
        }
        // Trend Min
        dblMin = lstTokens[nTrendMin].toDouble(&fOk);
        if (fVisible && ! fOk)  {
            m_szMsg = tr("Track: %1. If Visible associated Min Value must be specified") .arg(nRow);
            QMessageBox::critical(0,trUtf8("Error"),m_szMsg);
            goto exitCheck;
        }
        // Trend Max
        dblMax = lstTokens[nTrendMax].toDouble(&fOk);
        if (fVisible && ! fOk)  {
            m_szMsg = tr("Track: %1. If Visible associated Max Value must be specified") .arg(nRow);
            QMessageBox::critical(0,trUtf8("Error"),m_szMsg);
            goto exitCheck;
        }
        // Trend Min > Trend Max
        if (fVisible && dblMin >= dblMax)  {
            m_szMsg = tr("Track: %1. If Visible associated Max Value must be greater than Min Value") .arg(nRow);
            QMessageBox::critical(0,trUtf8("Error"),m_szMsg);
            goto exitCheck;
        }
    }
    //------------------------
    // All check are Ok, return true
    //------------------------
    fRes = true;

exitCheck:
    return fRes;

}
