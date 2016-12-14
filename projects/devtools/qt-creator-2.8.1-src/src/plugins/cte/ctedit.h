#ifndef CTEDIT_H
#define CTEDIT_H

#include <QTableView>
#include <QModelIndex>
#include <QModelIndexList>
#include <QDialog>
#include <QList>
#include <QComboBox>

namespace Ui {
class ctedit;
}

class ctedit : public QDialog
{
    Q_OBJECT

public:
    explicit ctedit(QWidget *parent = 0);
    ~ctedit();
    bool    selectCTFile(QString szFileCT);
    bool    loadCTFile();
    bool    ctable2Iface();
    bool    saveCTFile();


signals:

public slots:
    void    setProjectPath(QString szProjectPath);

private slots:
    void itemClicked(QModelIndex gridItem);         // Singolo Click su Item in griglia
    void itemDoubleClicked(QModelIndex gridItem);   // Doppio Click su Item in griglia
    void on_cmdHideShow_clicked(bool checked);
    void on_cmdBlocchi_clicked();                   // Riordino Blocchi
    void on_cmdSave_clicked();                      // Salvataggio file

private:
    //---------------------------------------------------------------------
    // Funzioni locali al modulo
    //---------------------------------------------------------------------
    bool    recCT2List(QStringList &lstRecValues, int nPos);
    bool    values2Iface(QStringList &lstRecValues);
    int     searchCombo(QComboBox *Combo, QString szValue);
    bool    riassegnaBlocchi();                       // Riassegnazione blocchi variabili
    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    Ui::ctedit *ui;
    int         m_nGridRow;
    QString     m_szCurrentCTFile;
    QString     m_szCurrentProjectPath;
    QStringList lstHeadCols;
    QStringList lstPLC;
    QStringList lstTipi;
    QStringList lstBusType;
    QStringList lstBehavior;
    QStringList lstValues;
};

#endif // CTEDIT_H
