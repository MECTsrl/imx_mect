#ifndef CTEDIT_H
#define CTEDIT_H

#include "parser.h"
#include <QTableView>
#include <QModelIndex>
#include <QModelIndexList>
#include <QItemSelection>
#include <QDialog>
#include <QList>
#include <QComboBox>
#include <QPoint>
#include <QColor>

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
    bool    saveCTFile();


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
    void on_cmdImport_clicked();                    // Import Rows from Another CT File
    void on_cmdGotoRow_clicked();                   // Goto Row n
    void on_cmdSearch_clicked();                    // Search Variable by Name

private:
    //---------------------------------------------------------------------
    // Funzioni locali al modulo
    //---------------------------------------------------------------------
    // Lettura e scrittura dati da e per strutture di appoggio
    bool    ctable2Grid();                          // Lettura di tutta la CT in Grid
    bool    grid2CTable();                          // Dump di tutto il Grid in lista di CT Records
    bool    list2GridRow(QStringList &lstRecValues, int nRow);  // Inserimento o modifica elemento in Grid (valori -> GRID)
    bool    list2CTrec(QStringList &lstRecValues, int nRow);// Conversione da Lista Stringhe a CT Record (Grid -> REC SINGOLO)
    bool    recCT2List(QStringList &lstRecValues, int nRow);// Conversione da CT Record a Lista Stringhe per Interfaccia (REC -> Grid)
    void    listClear(QStringList &lstRecValues);   // Svuotamento e pulizia Lista Stringhe per passaggio dati Interfaccia <---> Record CT
    bool    values2Iface(QStringList &lstRecValues);// Copia Lista Stringhe convertite da CT Record a Zona di Editing
    bool    iface2values(QStringList &lstRecValues);// Copia da Zona Editing a Lista Stringhe per Grid e Record CT
    void    freeCTrec(int nRow);                    // Marca il Record della CT come inutilizzato
    bool    loadCTFile(QString szFileCT, QList<CrossTableRecord> &lstCtRecs, bool fLoadGrid);
    // Gestione interfaccia
    void    showGroupVars(int nRow);                 // Imposta in interfaccia il gruppo di appartenenza di una variabile (Ritentivo, NR, System)
    void    enableFields();                         // Abilitazione dei campi form in funzione di Protocollo
    bool    checkFields();                          // Primi controlli formali sulla riga a termine editing
    bool    isLineModified();                       // Check su modifica record corrente
    bool    riassegnaBlocchi();                     // Riassegnazione blocchi variabili
    void    showAllRows(bool fShowAll);              // Visualizza o nascondi tutte le righe
    void    setRowColor(int nRow, int nAlternate);  // Imposta il colore di sfondo di una riga
    void    jumpToGridRow(int nRow);                    // Salto alla riga nRow del Grid
    // Utilità
    int     searchCombo(QComboBox *Combo, QString szValue);
    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    Ui::ctedit *ui;
    int         m_nGridRow;                         // Riga corrente sul Grid
    QString     m_szCurrentCTFile;                  // File Cross Table corrente (completo di Path)
    QString     m_szCurrentProjectPath;             // Project Path corrente
    QString     m_szFormatDate;                     // Format Masks per Date e tempo
    QString     m_szFormatTime;
    QString     m_szMsg;                            // Variabile di servizio per Messaggi
    // Liste varie per prompt colonne e valori Combo Box (per traduzioni)
    QStringList lstHeadCols;
    QStringList lstPriority;
    QStringList lstPLC;
    QStringList lstTipi;
    QStringList lstBusType;
    QStringList lstBehavior;
    QStringList lstCondition;

    QStringList lstUsedVarNames;                    // Lista contenente i nomi delle variabili
    // Valori per stringa vuota e Zero (creati così per problemi di classe QString in compilazione sotto Qt
    QString     szEMPTY;
    QString     szZERO;
    // Colori per sfondi grid
    QColor      colorRetentive[2];
    QColor      colorNonRetentive[2];
    QColor      colorSystem[2];
    // Record CrossTable
    QList<CrossTableRecord> lstCopiedRecords;       // Lista di Record per copia/incolla
    QList<CrossTableRecord> lstCTRecords;           // Lista completa di record per tabella
    CrossTableRecord        CrossTable[1 + DimCrossTable];	 // campi sono riempiti a partire dall'indice 1
    // Variabili di stato ad uso globale
    bool        m_isCtModified;
    bool        m_fShowAllRows;                     // Vero se sono visualizzate tutte le righe
};

#endif // CTEDIT_H
