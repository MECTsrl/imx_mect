#include "trendeditor.h"
#include "ui_trendeditor.h"

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
