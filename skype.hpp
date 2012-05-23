#ifndef SKYPE_HPP
#define SKYPE_HPP

/** --------------------------------------------------------------------------------------------------------------- **/

#include <qdir.h>
#include <qlabel.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qprogressbar.h>
#include <qstackedwidget.h>

#include <qgroupbox.h>

/** --------------------------------------------------------------------------------------------------------------- **/

#include "lineedit.hpp"

/** --------------------------------------------------------------------------------------------------------------- **/

class Skype : public QWidget
{
    Q_OBJECT

public:
    explicit Skype(const QString & path = "", QWidget * parent = 0);

signals:

public slots:

private:
    QStackedWidget * stack;
    LineEdit * login, * password;

};

/** --------------------------------------------------------------------------------------------------------------- **/

#endif // SKYPE_HPP
