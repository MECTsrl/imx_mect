#include "trendeditor.h"
#include "ui_trendeditor.h"

TrendEditor::TrendEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrendEditor)
{
    ui->setupUi(this);
}

TrendEditor::~TrendEditor()
{
    delete ui;
}
