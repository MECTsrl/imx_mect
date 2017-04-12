#ifndef MECTSETTINGS_H
#define MECTSETTINGS_H

#include "parser.h"

#include <QWidget>
#include <QHash>
#include <QString>

namespace Ui {
class MectSettings;
}

class MectSettings : public QWidget
{
    Q_OBJECT

public:
    explicit MectSettings(QWidget *parent = 0);
    ~MectSettings();
    bool loadProjectFiles(const QString &szFileSettings, const QString szFilePro, const QString &szProjectPath, const int nModel);

signals:

public slots:
    void    setModel(const int nModel);

private slots:

    void on_cmdSave_clicked();

private:
    //---------------------------------------------------------------------
    // Funzioni locali al modulo
    //---------------------------------------------------------------------
    void save_all();
    bool checkFields();
    void enablePortsFromModel(int nModel);
    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    QHash<QString, QString> LanguageMap;
    Ui::MectSettings *ui;
    QString m_szFileSettings;
    QString m_szProjectPath;
    QString m_szFilePro;
    QString m_szModel;
    int     m_nModel;
    bool    m_tabEnabled[tabTotals];
};

#endif // MECTSETTINGS_H
