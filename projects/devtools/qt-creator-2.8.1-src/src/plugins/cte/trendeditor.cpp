#include "trendeditor.h"
#include "ui_trendeditor.h"
#include "utils.h"

#include <QColor>
#include <QColorDialog>

const int nTrk1 = 1;
const int nTrk2 = 2;
const int nTrk3 = 3;
const int nTrk4 = 4;

TrendEditor::TrendEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrendEditor)
{
    int     nCur = 0;

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
// get and set color for track nTrack
{
    QString     szColor;
    QColor      cColor;

    // Retrieve Colors and start color dialog
    if (nTrack == nTrk1)
        szColor = ui->lblColor_1->text();
    else if (nTrack == nTrk2)
        szColor = ui->lblColor_2->text();
    else if (nTrack == nTrk3)
        szColor = ui->lblColor_3->text();
    else if (nTrack == nTrk4)
        szColor = ui->lblColor_4->text();
    if (! szColor.isEmpty())  {
        szColor.prepend(szDOUBLEQUOTE);
    }
    else {
        cColor = QColor(QString::fromAscii("palegreen"));
    }
}
