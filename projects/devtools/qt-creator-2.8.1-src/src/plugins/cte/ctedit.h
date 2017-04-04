#ifndef CTEDIT_H
#define CTEDIT_H


#include "parser.h"
#include "cteerrdef.h"

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
    void emptySelected();                           // Cancellazione delle righe correntemente selezionate
    void removeSelected();                          // Rimozione delle righe correntemente selezionate
    void copySelected(bool fClearSelection);                            // Copia delle righe selezionate in Buffer di Copiatura
    void pasteSelected();                           // Incolla righe da Buffer di copiatura a Riga corrente
    void cutSelected();                             // Taglia righe in Buffer di copiatura
    void on_cmdHideShow_clicked(bool checked);      // Bottone Hide/Show righe vuote
    void on_cmdBlocchi_clicked();                   // Riordino Blocchi
    void on_cmdSave_clicked();                      // Salvataggio file
    void displayUserMenu(const QPoint &pos);        // Menu contestuale Grid
    void on_cboProtocol_currentIndexChanged(int index);
    void tableItemChanged(const QItemSelection & selected, const QItemSelection & deselected);
    void clearEntryForm();                          // Svutamento elementi Form Data Entry
    void clearStatusMessage();                      // Clear message in ui->lblMessage
    void tabSelected(int nTab);                     // Change current Tab
    void on_cboType_currentIndexChanged(int index);
    void on_cmdImport_clicked();                    // Import Rows from Another CT File
    void on_cmdGotoRow_clicked();                   // Goto Row n
    void on_cmdSearch_clicked();                    // Search Variable by Name
    void on_cmdCompile_clicked();                   // Generate Compiled Files
    void on_cmdUndo_clicked();                      // Retrieve a CT Block from Undo List

    void on_cboBehavior_currentIndexChanged(int index);

    void on_cboVariable1_currentIndexChanged(int index);

    void on_cboCondition_currentIndexChanged(int index);

    void on_optFixedVal_toggled(bool checked);

    void on_optVariableVal_toggled(bool checked);

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
    void    showGroupVars(int nRow);                // Imposta in interfaccia il gruppo di appartenenza di una variabile (Ritentivo, NR, System)
    void    enableFields();                         // Abilitazione dei campi form in funzione di Protocollo
    bool    isLineModified(int nRow);               // Check se linea corrente Grid è diversa da Form in Editing
    bool    riassegnaBlocchi();                     // Riassegnazione blocchi variabili
    void    showAllRows(bool fShowAll);             // Visualizza o nascondi tutte le righe
    void    setRowColor(int nRow, int nAlternate);  // Imposta il colore di sfondo di una riga
    void    jumpToGridRow(int nRow);                // Salto alla riga nRow del Grid
    void    displayStatusMessage(QString szMessage, int nSeconds = 0);// Show message in ui->lblMessage
    void    enableInterface();                      // Abilita l'interfaccia in funzione dello stato del sistema
    int     fillVarList(QStringList &lstVars, QList<int> &lstTypes, QList<int> &lstUpdates); // Fill sorted List of Variables Names for Types in lstTypes and Update Type in lstUpdates
    int     fillComboVarNames(QComboBox *comboBox, QList<int> &lstTypes, QList<int> &lstUpdates);   // Caricamento ComboBox con Nomi Variabili filtrate in funzione del Tipo and Update Type in lstUpdates
    int     varName2Row(QString &szVarName, QList<CrossTableRecord> &lstCTRecs);        // Search in Cross Table Record List the index of szVarName
    // Gestione Controlli
    int     checkFormFields(int nRow, QStringList &lstValues, bool fSingleLine = true);   // Controlli formali sulla riga a termine editing
    int     globalChecks();                                 // Controlli complessivi su tutta la CT
    bool    isFormEmpty();                          // Controllo Form Editing vuoto
    bool    isValidVarName(QString szName);         // Controllo del Nome Variabile
    void    fillErrorMessage(int nRow, int nCol, int nErrCode, QString szVarName, QString szValue, QChar severity, Err_CT *errCt);
    // Gestione Configurazione Progetto
    QString getModelName();                         // Lettura del file template.pri per determinare il modello di TPAC
    // Calcolo valori in funzione del Modello e del Protocollo
    QStringList getPortsFromModel(QString szModel, QString szProtocol);      // Calocolo Porte in funzione di Modello e protocollo
    void    enableProtocolsFromModel(QString szModel);  // Abilita i Protocolli in funzione del Modello corrente
    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    Ui::ctedit *ui;
    int         m_nGridRow;                         // Riga corrente sul Grid
    QString     m_szCurrentCTFile;                  // File Cross Table corrente (completo di Path)
    QString     m_szCurrentCTPath;                  // Path del file Cross Table corrente
    QString     m_szCurrentCTName;                  // Nome del file Cross Table (senza Path)
    QString     m_szCurrentProjectPath;             // Project Path corrente
    QString     m_szCurrentModel;                   // Modello TPAC del progetto
    // Liste varie per prompt colonne e valori Combo Box (per traduzioni)
    QStringList lstHeadCols;
    QStringList lstPriority;
    QStringList lstUpdateNames;
    QStringList lstTipi;
    QStringList lstProtocol;
    QList<bool> lstBusEnabler;
    QStringList lstBehavior;
    QStringList lstCondition;
    QStringList lstProductNames;
    // Variabili di servizio
    QString     m_szFormatDate;                     // Format Masks per Date e tempo
    QString     m_szFormatTime;
    QString     m_szMsg;                            // Variabile di servizio per Messaggi
    // Valori per stringa vuota e Zero (creati così per problemi di classe QString in compilazione sotto Qt
    QString     szEMPTY;
    QString     szZERO;
    // Colori per sfondi grid
    QColor      colorRetentive[2];
    QColor      colorNonRetentive[2];
    QColor      colorSystem[2];
    QString     szColorRet[2];
    QString     szColorNonRet[2];
    QString     szColorSystem[2];

    // Record CrossTable
    QList<CrossTableRecord> lstCopiedRecords;       // Lista di Record per copia/incolla
    QList<CrossTableRecord> lstCTRecords;           // Lista completa di record per tabella
    QList<QList<CrossTableRecord> > lstUndo;        // Lista degli Undo di elementi di Cross Table Editor
    CrossTableRecord        CrossTable[1 + DimCrossTable];	 // campi sono riempiti a partire dall'indice 1
    // Controllo e Gestione  Errori
    QList<int>              lstAllUpdates;          // Lista contenente tutti i tipi di Update (per filtro su Nomi variabili)
    QList<int>              lstNoHUpdates;          // Lista contenente tutti i tipi di Update tranne H (per Allarmi)
    QList<int>              lstAllVarTypes;         // Lista contenente tutti i tipi di Variabili definiti
    QStringList             lstUsedVarNames;        // Lista contenente i nomi delle variabili (per Search)
    QList<Err_CT>           lstCTErrors;
    QStringList             lstUniqueVarNames;      // Lista per controllo univocità identificatori
    QStringList             lstErrorMessages;       // Lista dei messaggi di errore
    // Variabili di stato ad uso globale
    int         m_nCurTab;                          // Tab corrente in interfaccia
    bool        m_isCtModified;
    bool        m_fShowAllRows;                     // Vero se sono visualizzate tutte le righe
    bool        m_fCutOrPaste;                      // Vero se è in corso un Cut or Paste
    bool        m_fEmptyForm;                       // Vero se il Form di Data Entry risulta vuoto
};

#endif // CTEDIT_H
