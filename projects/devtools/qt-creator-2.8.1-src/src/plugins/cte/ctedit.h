#ifndef CTEDIT_H
#define CTEDIT_H

#include <QTableView>
#include <QModelIndex>
#include <QModelIndexList>
#include <QDialog>
#include <QList>

namespace Ui {
class ctedit;
}

class ctedit : public QDialog
{
    Q_OBJECT

public:
    explicit ctedit(QWidget *parent = 0);
    ~ctedit();
    bool    selectCTFile();
    bool    loadCTFile();
    bool    ctable2Iface();

signals:

public slots:


private slots:
    void itemClicked(QModelIndex gridItem);         // Singolo Click su Item in griglia
    void itemDoubleClicked(QModelIndex gridItem);   // Doppio Click su Item in griglia
    void on_cmdHideShow_clicked(bool checked);

private:
    //---------------------------------------------------------------------
    // Funzioni locali al modulo
    //---------------------------------------------------------------------
    bool recCT2List(QStringList &lstValues, int nPos);
    bool values2Iface(QStringList &lstValues);

    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    Ui::ctedit *ui;
    int         m_nGridRow;
    QString     m_CurrentCTFile;
    QStringList lstHeadCols;
    QStringList lstPLC;
    QStringList lstTipi;
    QStringList lstBusType;
    QStringList lstValues;
};

#endif // CTEDIT_H
