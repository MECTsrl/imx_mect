#ifndef CTE_ERRDEF_H
#define CTE_ERRDEF_H

#include <QString>
#include <QChar>

const QChar szSeverityError = QChar::fromAscii('E');
const QChar szSeverityWarning = QChar::fromAscii('W');

// Struttura definizione Errore in CT
enum errorMessages_e
{
    errCTNoError = 0,
    errCTDuplicateName,
    errCTNoPriority,
    errCTNoUpdate,
    errCTNoName,
    errCTNoType,
    errCTNoDecimals,
    errCTNoVarDecimals,
    errCTNoProtocol,
    errCTNoIP,
    errCTBadIP,
    errCTNoPort,
    errCTNoNode,
    errCTNoRegister,
    errCTTotals
};

const int nErrCols = 5;
enum errorCols_e
{
    colSeverity = 0,
    colRow,
    colColumn,
    colVarName,
    colErrCode,
    colErrMsg,
    colErrTotals
};

// Struttura per memorizzazione errori
struct Err_CT {
    QChar           cSeverity;              // Livello Errore
    int             nRow;                   // Riga errore
    int             nCol;                   // Colonna Errore
    QString         szVarName;              // Nome della Variabile associata
    int             nCodErr;                // Codice errore
    QString         szErrMessage;           // Error Message
};

#endif // CTE_ERRDEF_H
