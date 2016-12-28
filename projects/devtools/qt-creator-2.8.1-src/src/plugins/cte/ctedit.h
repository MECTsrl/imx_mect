#ifndef CTEDIT_H
#define CTEDIT_H

#include <QTableView>
#include <QModelIndex>
#include <QModelIndexList>
#include <QItemSelection>
#include <QDialog>
#include <QList>
#include <QComboBox>
#include <QPoint>

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
    bool    iface2Ctable();


signals:

public slots:
    void    setProjectPath(QString szProjectPath);

private slots:
    void copySelected();                            // Copia delle righe selezionate in Buffer di Copiatura
    void pasteSelected();                           // Incolla righe da Buffer di copiatura a Riga corrente
    void on_cmdHideShow_clicked(bool checked);
    void on_cmdBlocchi_clicked();                   // Riordino Blocchi
    void on_cmdSave_clicked();                      // Salvataggio file
    void displayUserMenu(const QPoint &pos);        // Menu contestuale Grid
    void on_cboProtocol_currentIndexChanged(int index);
    void tableItemChanged(const QItemSelection & selected, const QItemSelection & deselected);
    void clearForm();                               // Svutamento elementi Form Data Entry

private:
    //---------------------------------------------------------------------
    // Funzioni locali al modulo
    //---------------------------------------------------------------------
    void    setGroupVars(int nRow);                 // Imposta il gruppo di appartenenza di una variabile
    void    enableFields();                         // Abilitazione dei campi form
    bool    recCT2List(QStringList &lstRecValues, int nPos);
    bool    list2CTrec(QStringList &lstRecValues, int nPos);
    bool    values2Iface(QStringList &lstRecValues);
    int     searchCombo(QComboBox *Combo, QString szValue);
    bool    riassegnaBlocchi();                       // Riassegnazione blocchi variabili
    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    Ui::ctedit *ui;
    int         m_nGridRow;
    bool        m_fRowChanged;
    QString     m_szCurrentCTFile;
    QString     m_szCurrentProjectPath;
    QString     m_szFormatDate;
    QString     m_szFormatTime;
    QStringList lstHeadCols;
    QStringList lstPLC;
    QStringList lstTipi;
    QStringList lstBusType;
    QStringList lstBehavior;
    QStringList lstValues;
    QList<int>  lstCopiedRows;
};

#endif // CTEDIT_H
