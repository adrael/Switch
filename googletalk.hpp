#ifndef GOOGLETALK_HPP
#define GOOGLETALK_HPP

/** --------------------------------------------------------------------------------------------------------------- **/

#include <qdir.h>
#include <qmovie.h>
#include <qlabel.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qprogressbar.h>
#include <qstackedwidget.h>

/** --------------------------------------------------------------------------------------------------------------- **/

//#include <qxmpp/QXmppClient.h>
//#include "qxmpp/QXmppPresence.h"
//#include "qxmpp/QXmppMessage.h"
//#include "qxmpp/QXmppUtils.h"
//#include "qxmpp/QXmppReconnectionManager.h"
//#include "qxmpp/QXmppVCardManager.h"

/** --------------------------------------------------------------------------------------------------------------- **/

#include "manager.hpp"
#include "lineedit.hpp"

/** --------------------------------------------------------------------------------------------------------------- **/

class GoogleTalk : public QWidget
{
    Q_OBJECT

public:
    explicit GoogleTalk(const QString & path = "", QWidget * parent = 0);

signals:

public slots:

private slots:
    void signIn();
    void cancelSignIn();

private:
    QStackedWidget *  stack;
    QLabel         *  loader;
    QPushButton    *  launcher,
                   *  canceller;
    QCheckBox      *  memorizer;
//    QXmppClient       m_xmppClient;

    LineEdit       *  login,
                   *  password;

};

/** --------------------------------------------------------------------------------------------------------------- **/

#endif // GOOGLETALK_HPP
