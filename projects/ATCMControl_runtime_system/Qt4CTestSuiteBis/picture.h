#ifndef PICTURE_H
#define PICTURE_H

#include <QWidget>

namespace Ui {
    class Picture;
}

class Picture : public QWidget
{
    Q_OBJECT

public:
    explicit Picture(QWidget *parent = 0);
    ~Picture();

private slots:
	void on_pushButton_clicked();

private:
    Ui::Picture *ui;
};

#endif // PICTURE_H
