#ifndef FACEBOOK_HPP
#define FACEBOOK_HPP

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

class Facebook : public QWidget
{
    Q_OBJECT

public:
    explicit Facebook(const QString & path = "", QWidget * parent = 0);

signals:

public slots:

private:
    QStackedWidget * stack;
    LineEdit * login, * password;

};

/** --------------------------------------------------------------------------------------------------------------- **/

#endif // FACEBOOK_HPP
