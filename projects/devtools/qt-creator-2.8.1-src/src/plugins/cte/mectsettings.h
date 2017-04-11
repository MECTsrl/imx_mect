#ifndef MECTSETTINGS_H
#define MECTSETTINGS_H

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
    bool loadProjectFiles(const QString &szFileSettings, const QString szFilePro, const QString &szProjectPath);

signals:

public slots:
    void    setModel(const QString &szModel);

private slots:

    void on_cmdSave_clicked();

private:
    //---------------------------------------------------------------------
    // Funzioni locali al modulo
    //---------------------------------------------------------------------
    void save_all();
    bool checkFields();
    //---------------------------------------------------------------------
    // Variabili varie
    //---------------------------------------------------------------------
    QHash<QString, QString> LanguageMap;
    Ui::MectSettings *ui;
    QString m_szFileSettings;
    QString m_szProjectPath;
    QString m_szFilePro;
    QString m_szModel;
};

#endif // MECTSETTINGS_H
