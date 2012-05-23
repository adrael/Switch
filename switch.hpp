#ifndef SWITCH_HPP
#define SWITCH_HPP

/** --------------------------------------------------------------------------------------------------------------- **/

#include <qmap.h>
#include <qlayout.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qmainwindow.h>
#include <qapplication.h>
#include <qnetworkproxy.h>
#include <qsignalmapper.h>
#include <qstackedwidget.h>

#include <qdebug.h>

/** --------------------------------------------------------------------------------------------------------------- **/

#include "wlm.hpp"
#include "skype.hpp"
#include "twitter.hpp"
#include "facebook.hpp"
#include "googletalk.hpp"

/** --------------------------------------------------------------------------------------------------------------- **/

class CloseHandler: public QObject
{
private:
    bool flag;
protected:
    bool eventFilter(QObject * obj, QEvent * event) {
        if(obj->isWidgetType()) {
            switch(event->type()) {
            case QEvent::Close:
                if(flag){
                    event->ignore();
                    return true;
                }
                break;
            case QEvent::KeyPress:
                if(((QKeyEvent *)event)->key() == Qt::Key_F4 || (((QKeyEvent *)event)->modifiers() == Qt::AltModifier))
                    flag = true;
                else if(((QKeyEvent *)event)->key() == Qt::Key_Escape) {
                    event->ignore();
                    return true;
                }
                break;
            case QEvent::MouseButtonPress:
            case QEvent::MouseButtonRelease:
            case QEvent::MouseMove:
            case QEvent::Leave:
                flag = false;
            default: break;
            }
        }
        return QObject::eventFilter(obj, event);
    }
};

/** --------------------------------------------------------------------------------------------------------------- **/

class Switch : public QMainWindow
{
    Q_OBJECT

public:
    Switch(QWidget * parent = 0);
    ~Switch();

private slots:
    void switchWindow(const QString &);
    void switchButton(const QString &);

    void switchState    (const int &);
    void switchPresence (const int &);

    void getHash();

private:
    void firstLaunch();

    QWidget        *   centralWidget;
    QStackedWidget *   stack;
    QSignalMapper  *   signalMapper,
                   *   toolsMapper;
    QVBoxLayout    *   switchLayout;
    QHBoxLayout    *   switchPresenceLayout;
    QStringList        switchNames,
                       switchTtips,
                       switchIcons,
                       switchPresenceIcons,
                       switchPresenceTtips;
    QList<int>         switchWidth,
                       switchHeight;
    QString            appPath,
                       currentCheckedButton;
    QLabel         *   passError;
    QDialog        *   logWindow;

    QMap<QString, int> presMap;

    LineEdit       *   login,
                   *   password;

    int                currentCheckedState;
};

/** --------------------------------------------------------------------------------------------------------------- **/

#endif // SWITCH_HPP
