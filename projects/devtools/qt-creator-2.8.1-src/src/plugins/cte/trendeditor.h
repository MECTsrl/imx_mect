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
    void updateVarLists(const QStringList &lstTrendVars);

private slots:

    void on_cmdColor_1_clicked();
    void on_cmdColor_2_clicked();
    void on_cmdColor_3_clicked();
    void on_cmdColor_4_clicked();

private:
    //---------------------------------------------------------------------
    // Funzioni locali al modulo
    //---------------------------------------------------------------------
    bool    getNewColor(int nTrack);                        // Show Color dialog to select new Track color
    bool    trendFile2Iface(const QString &szFileTrend);    // Load a trends file in Interface Fields
    bool    iface2TrendFile(const QString &szFileTrend);    // Write Interface Fields to a trends file
    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    Ui::TrendEditor *ui;
    // Liste varie di supporto all'interfaccia
    QHash<QString, QString> mapOrientation;
    QStringList lstLoggedVars;
};

#endif // TRENDEDITOR_H
