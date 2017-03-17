#ifndef CTEERRORLIST_H
#define CTEERRORLIST_H

#include <QDialog>
#include <QItemSelection>

#include "cteerrdef.h"

namespace Ui {
class cteErrorList;
}

class cteErrorList : public QDialog
{
    Q_OBJECT

public:
    explicit cteErrorList(QWidget *parent = 0);
    ~cteErrorList();
    int     currentRow();
    int lstErrors2Grid(const QList<Err_CT> &lstErrors);      // Fill Error Grid with errors

private slots:
    void on_cmdLine_clicked();
    void on_cmdExit_clicked();
    void tableItemChanged(const QItemSelection & selected, const QItemSelection & deselected);

private:
    QString list2CellValue(int nCol, const Err_CT &recErr);

    Ui::cteErrorList *ui;
    QStringList     lstCols;                            // Prompt Colonne
    int             m_nGridRow;                         // Riga corrente sul Grid;
};

#endif // CTEERRORLIST_H
