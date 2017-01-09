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
    bool    iface2Ctable();                         // Dump di tutto il Grid in lista di CT Records


signals:

public slots:
    void    setProjectPath(QString szProjectPath);

private slots:
    void insertRows();                              // Aggiunta righe in posizione cursore
    void removeSelected();                          // Rimozione delle righe correntemente selezionate
    void copySelected();                            // Copia delle righe selezionate in Buffer di Copiatura
    void pasteSelected();                           // Incolla righe da Buffer di copiatura a Riga corrente
    void cutSelected();                             // Taglia righe in Buffer di copiatura
    void on_cmdHideShow_clicked(bool checked);      // Bottone Hide/Show righe vuote
    void on_cmdBlocchi_clicked();                   // Riordino Blocchi
    void on_cmdSave_clicked();                      // Salvataggio file
    void displayUserMenu(const QPoint &pos);        // Menu contestuale Grid
    void on_cboProtocol_currentIndexChanged(int index);
    void tableItemChanged(const QItemSelection & selected, const QItemSelection & deselected);
    void clearEntryForm();                          // Svutamento elementi Form Data Entry


    void on_cboType_currentIndexChanged(int index);

private:
    //---------------------------------------------------------------------
    // Funzioni locali al modulo
    //---------------------------------------------------------------------
    void    setGroupVars(int nRow);                 // Imposta in interfaccia il gruppo di appartenenza di una variabile
    void    enableFields();                         // Abilitazione dei campi form in funzione di Protocollo
    bool    checkFields();                          // Primi controlli formali sulla riga a termine editing
    bool    isLineModified();                       // Check su modifica record corrente
    void    clearCTrec(int nRow);                   // Marca il Record della CT come inutilizzato
    bool    recCT2List(QStringList &lstRecValues, int nRow);// Conversione da CT Record a Lista Stringhe per Interfaccia (REC -> Grid)
    bool    list2CTrec(QStringList &lstRecValues, int nRow);// Conversione da Lista Stringhe a CT Record (Grid -> REC)
    bool    values2Iface(QStringList &lstRecValues);// Copia Lista Stringhe convertite da CT Record a Zona di Editing
    bool    iface2values(QStringList &lstRecValues);
    int     searchCombo(QComboBox *Combo, QString szValue);
    bool    riassegnaBlocchi();                       // Riassegnazione blocchi variabili
    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    Ui::ctedit *ui;
    int         m_nGridRow;
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
    QString     szEMPTY;
    QString     szZERO;

};

#endif // CTEDIT_H
