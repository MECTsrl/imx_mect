#include "trendeditor.h"
#include "ui_trendeditor.h"

TrendEditor::TrendEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrendEditor)
{
    ui->setupUi(this);
    // Filling Fixed Combos
}

TrendEditor::~TrendEditor()
{
    delete ui;
}
