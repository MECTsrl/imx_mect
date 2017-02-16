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
    bool    loadCTFile();
    bool    ctable2Grid();                         // Lettura di tutta la CT in Grid
    bool    saveCTFile();
    bool    grid2CTable();                         // Dump di tutto il Grid in lista di CT Records


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
    void    freeCTrec(int nRow);                    // Marca il Record della CT come inutilizzato
    bool    recCT2List(QStringList &lstRecValues, int nRow);// Conversione da CT Record a Lista Stringhe per Interfaccia (REC -> Grid)
    bool    list2CTrec(QStringList &lstRecValues, int nRow);// Conversione da Lista Stringhe a CT Record (Grid -> REC)
    bool    values2Iface(QStringList &lstRecValues);// Copia Lista Stringhe convertite da CT Record a Zona di Editing
    bool    iface2values(QStringList &lstRecValues);// Copia da Zona Editing a Lista Stringhe per Grid e Record CT
    int     searchCombo(QComboBox *Combo, QString szValue);
    bool    riassegnaBlocchi();                     // Riassegnazione blocchi variabili
    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    Ui::ctedit *ui;
    int         m_nGridRow;                         // Riga corrente sul Grid
    QString     m_szCurrentCTFile;                  // File Cross Table corrente (completo di Path)
    QString     m_szCurrentProjectPath;             // Project Path corrente
    QString     m_szFormatDate;                     // Format Masks per Date e tempo
    QString     m_szFormatTime;
    // Liste varie per prompt colonne e valori Combo Box (per traduzioni)
    QStringList lstHeadCols;
    QStringList lstPriority;
    QStringList lstPLC;
    QStringList lstTipi;
    QStringList lstBusType;
    QStringList lstBehavior;

    QStringList lstValues;                          // Buffer di Recod da Grid a Form e viceversa

    // Valori per stringa vuota e Zero (creati così per problemi di classe QString in compilazione sotto Qt
    QString     szEMPTY;
    QString     szZERO;
    // Colori per sfondi grid
    QColor      colorRetentive;
    QColor      colorNonRetentive;
    QColor      colorSystem;
    // Variabili di stato ad uso globale
    bool        ctModified;

};

#endif // CTEDIT_H
