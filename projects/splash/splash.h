#ifndef SPLASH_H
#define SPLASH_H

#include <QWidget>

extern char picture[256];
extern char text[256];
extern char fontname[256];
extern char fontsize[256];
extern char color[256];
extern char bgcolor[256];

namespace Ui {
class splash;
}

class splash : public QWidget
{
    Q_OBJECT
    
public:
    explicit splash(QWidget *parent = 0);
    ~splash();
    
private slots:
    void on_pushButtonQuit_clicked();

private:
    Ui::splash *ui;
};

#endif // SPLASH_H
