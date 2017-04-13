#ifndef TRENDEDITOR_H
#define TRENDEDITOR_H

#include "parser.h"

#include <QWidget>
#include <QString>
#include <QHash>
#include <QStringList>

namespace Ui {
class TrendEditor;
}

class TrendEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TrendEditor(QWidget *parent = 0);
    ~TrendEditor();

signals:

public slots:

private slots:


private:
    //---------------------------------------------------------------------
    // Funzioni locali al modulo
    //---------------------------------------------------------------------

    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    Ui::TrendEditor *ui;
    // Liste varie di supporto all'interfaccia
    QHash<QString, QString> mapOrientation;
    QStringList lstLoggedVars;
};

#endif // TRENDEDITOR_H
