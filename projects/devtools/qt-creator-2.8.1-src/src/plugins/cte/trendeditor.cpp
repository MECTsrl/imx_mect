#include "trendeditor.h"
#include "ui_trendeditor.h"
#include "utils.h"

#include <QColor>
#include <QColorDialog>
#include <QPalette>
#include <QDebug>
#include <QLabel>
#include <QComboBox>

const int nTrk1 = 1;
const int nTrk2 = 2;
const int nTrk3 = 3;
const int nTrk4 = 4;

TrendEditor::TrendEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrendEditor)
{
    ui->setupUi(this);
    // Filling Fixed Combos
    // Combo Orientation
    mapOrientation.insert(QString::fromAscii("P"), trUtf8("Portrait"));
    mapOrientation.insert(QString::fromAscii("L"), trUtf8("Landscape"));
    ui->cboOrientation->addItems(mapOrientation.values());
    /*
    for (nCur = 0; nCur < mapOrientation.count(); nCur++)  {
        ui->cboOrientation->addItem(mapOrientation.value(i));
    }
    */
    // Combo Colori ???

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
            qDebug() << tr("Color valid: %1") .arg(szColor);
        }
        else {
            cColor = QColor(QString::fromAscii("crimson"));
            qDebug() << tr("Color invalid: %1 forced to: %2") .arg(szColor) .arg(cColor.name());
        }
    }
    if (! cColor.isValid()) {
        cColor = QColor(QString::fromAscii("palegreen"));
    }
    // Open Color Dialog to select New Color
    newColor = QColorDialog::getColor(cColor, this, tr("Select Track %1 Color") .arg(nTrack));
    // Set New Color to Label
    if (newColor.isValid() && destLabel != 0)  {
        QPalette    palLabel = destLabel->palette();
        palLabel.setColor(destLabel->backgroundRole(), newColor);
        destLabel->setAutoFillBackground(true);
        destLabel->setPalette(palLabel);
        // Update Label content
        szColor = newColor.name();
        szColor.remove(szSHARP);
        destLabel->setText(szColor);
        fRes = true;
    }
    return fRes;
}
bool TrendEditor::trendFile2Iface(const QString &szFileTrend)
// Load a trends file in Interface Fields
{
    bool fRes = false;

    // Return value
    return fRes;
}
bool TrendEditor::iface2TrendFile(const QString &szFileTrend)
// Write Interface Fields to a trends file
{
    bool fRes = false;

    // Return value
    return fRes;
}
