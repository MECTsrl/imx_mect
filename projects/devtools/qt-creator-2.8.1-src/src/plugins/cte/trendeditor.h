#ifndef TRENDEDITOR_H
#define TRENDEDITOR_H

#include <QWidget>

namespace Ui {
class TrendEditor;
}

class TrendEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TrendEditor(QWidget *parent = 0);
    ~TrendEditor();

private:
    Ui::TrendEditor *ui;
    QStringList lstOrientation;
};

#endif // TRENDEDITOR_H
