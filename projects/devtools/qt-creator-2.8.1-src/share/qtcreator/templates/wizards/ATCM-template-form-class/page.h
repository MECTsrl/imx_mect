/**
 * @file
 * @author Emiliano Bergamaschini <ebergamaschini@mect.it>
 *
 * @section LICENSE
 * Copyright Mect s.r.l. 2013
 *
 * @brief Main page
 */
#ifndef %ClassName:u%_H
#define %ClassName:u%_H

#include "pagebrowser.h"

namespace Ui {
class %ClassName%;
}

class %ClassName% : public page
{
    Q_OBJECT
    
public:
    explicit %ClassName%(QWidget *parent = 0);
    ~%ClassName%();
    virtual void reload(void);
    virtual void updateData();

private slots:
    void changeEvent(QEvent * event);

private:
    Ui::%ClassName% *ui;
};

#endif // %ClassName:u%_H
