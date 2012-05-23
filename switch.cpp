#include "switch.hpp"

/** --------------------------------------------------------------------------------------------------------------- **/

Switch::Switch(QWidget * parent) :
    QMainWindow(parent),
    centralWidget(new QWidget(this)),
    stack(new QStackedWidget(centralWidget)),
    signalMapper(new QSignalMapper(centralWidget)),
    toolsMapper(new QSignalMapper(centralWidget)),
    appPath(QDir().homePath() + "/Documents/Dropbox/Switch")
{
    Manager::setLocation(appPath + "/utils");
    Manager::openDatabase();
    Manager::store("Facebook", "test", "test");

    QGroupBox * switchBox(new QGroupBox("", centralWidget));
    switchBox->setFixedWidth(190);
    switchLayout = new QVBoxLayout(switchBox);

    switchNames << "GTalk"
                << "Facebook"
                << "Twitter"
                << "Skype"
                << "WindowsLiveMessenger";

    switchTtips << "Google Talk"
                << "Facebook"
                << "Twitter"
                << "Skype"
                << "Windows Live Messenger";

    switchIcons << appPath + "/utils/icons/gtalk.png"
                << appPath + "/utils/icons/facebook.png"
                << appPath + "/utils/icons/twitter.png"
                << appPath + "/utils/icons/skype.png"
                << appPath + "/utils/icons/wlm.png";

    switchWidth << 120 // GTalk
                << 120 // Facebook
                << 150 // Twitter
                << 150 // Skype
                << 150;// WLM

    switchHeight<< 40  // GTalk
                << 50  // Facebook
                << 50  // Twitter
                << 40  // Skype
                << 50; // WLM

    bool check;
    for (int i(0); i < switchNames.size(); ++i) {
        QPushButton * button(new QPushButton(QIcon(switchIcons[i]), "", centralWidget));
        button->setIconSize(QSize(switchWidth[i], switchHeight[i]));
        button->setToolTip(switchTtips[i]);
        button->setObjectName(switchNames[i]);
        button->setFixedSize(170, 40);
        button->setFlat(true);
        button->setCheckable(true);
        if(switchNames[i] == "GTalk") {
            button->setChecked(true);
            currentCheckedButton = "GTalk";
        }
        check = connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        Q_ASSERT(check);
        signalMapper->setMapping(button, switchNames[i]);
        switchLayout->addStretch();
        switchLayout->addWidget(button);
        presMap.insert(switchNames[i], 0);
    }

    check = connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(switchWindow(const QString &)));
    Q_ASSERT(check);

    check = connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(switchButton(const QString &)));
    Q_ASSERT(check);

    switchPresenceLayout = new QHBoxLayout;

    switchPresenceIcons << appPath + "/utils/icons/green.png"
                        << appPath + "/utils/icons/red.png"
                        << appPath + "/utils/icons/orange.png"
                        << appPath + "/utils/icons/gray.png";

    switchPresenceTtips << tr("Apparaitre en ligne pour toutes les sessions")
                        << tr("Apparaitre en occupé(e) pour toutes les sessions")
                        << tr("Apparaitre en absent(e) pour toutes les sessions")
                        << tr("Apparaitre en hors ligne pour toutes les sessions");

    for (int i(0); i < switchPresenceIcons.size(); ++i) {
        QPushButton * button(new QPushButton(QIcon(switchPresenceIcons[i]), "", centralWidget));
        button->setToolTip(switchPresenceTtips[i]);
        button->setIconSize(QSize(20, 20));
        button->setObjectName(QString(i));
        button->setFixedSize(20, 20);
        button->setFlat(true);
        button->setCheckable(true);
        if(i == 0) {
            button->setChecked(true);
            currentCheckedState = 0;
        }
        check = connect(button, SIGNAL(clicked()), toolsMapper, SLOT(map()));
        Q_ASSERT(check);
        toolsMapper->setMapping(button, i);
        switchPresenceLayout->addWidget(button);
        switchPresenceLayout->addStretch();
    }

    check = connect(toolsMapper, SIGNAL(mapped(const int &)), this, SLOT(switchState   (const int &)));
    Q_ASSERT(check);

    check = connect(toolsMapper, SIGNAL(mapped(const int &)), this, SLOT(switchPresence(const int &)));
    Q_ASSERT(check);

    QPushButton * toolButton(new QPushButton(QIcon(appPath + "/utils/icons/tools.png"), "", centralWidget));
    toolButton->setToolTip(tr("Paramètres"));
    toolButton->setIconSize(QSize(40, 40));
    toolButton->setFixedSize(40, 40);
    toolButton->setFlat(true);

    QPushButton * addButton(new QPushButton(QIcon(appPath + "/utils/icons/add.png"), "", centralWidget));
    addButton->setToolTip(tr("Ajouter un contact à la session courante"));
    addButton->setIconSize(QSize(40, 40));
    addButton->setFixedSize(40, 40);
    addButton->setFlat(true);

    QHBoxLayout * switchToolsLayout(new QHBoxLayout);
    switchToolsLayout->addWidget(addButton);
    switchToolsLayout->addStretch();
    switchToolsLayout->addWidget(toolButton);

    switchLayout->addLayout(switchPresenceLayout);
    switchLayout->addLayout(switchToolsLayout);

    switchBox->setLayout(switchLayout);

    stack->addWidget(new GoogleTalk          (appPath, centralWidget));
    stack->addWidget(new Facebook            (appPath, centralWidget));
    stack->addWidget(new Twitter             (appPath, centralWidget));
    stack->addWidget(new Skype               (appPath, centralWidget));
    stack->addWidget(new WindowsLiveMessenger(appPath, centralWidget));

    QHBoxLayout * centralLayout(new QHBoxLayout(centralWidget));
    centralLayout->addWidget(switchBox);
    centralLayout->addWidget(stack);

    centralWidget->setLayout(centralLayout);

    setCentralWidget(centralWidget);
    setWindowIcon(QIcon(appPath + "/utils/icons/icon.png"));
    layout()->setSizeConstraint(QLayout::SetFixedSize);

//    firstLaunch();
//    qDebug() << Manager::getKey();
}

/** --------------------------------------------------------------------------------------------------------------- **/

Switch::~Switch()
{
    Manager::closeDatabase();
}

/** --------------------------------------------------------------------------------------------------------------- **/

void Switch::firstLaunch() {
    CloseHandler closeHandlerWindow;
    logWindow  = new QDialog(this, Qt::Dialog);
    logWindow->setModal(true);
    logWindow->setWindowIcon(QIcon(appPath + "/utils/icons/icon.png"));
    logWindow->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint| Qt::WindowSystemMenuHint);
    logWindow->setWindowTitle("Switch - Set your account");
    logWindow->installEventFilter(&closeHandlerWindow);

    QLabel * passInfo(new QLabel("You have to choose a login and a password for the application.\n"
                                 "Write them down somewhere because there is no way to retrieve\n"
                                 "them once you lost them.\n"
                                 "Then, you just have to set your social accounts once.\n"
                                 "It is secure, powerful and free. Enjoy!\n", logWindow));

    passError  = new QLabel(logWindow);
    passError->setStyleSheet("QLabel {color: red; font-weight: bold;}");
    passError->setVisible(false);

    login      = new LineEdit(logWindow, "Login",    appPath + "/utils/icons", "user.png");
    login->setMaximumWidth(200);

    password   = new LineEdit(logWindow, "Password", appPath + "/utils/icons", "key.png", QLineEdit::Password);
    password->setMaximumWidth(200);

    QPushButton * button = new QPushButton("Save", logWindow);
    button->setMaximumWidth(100);
    bool check = connect(button, SIGNAL(clicked()), this, SLOT(getHash()));
    Q_ASSERT(check);

    QVBoxLayout * layout = new QVBoxLayout(logWindow);
    layout->setSpacing(20);
    layout->addWidget(passInfo,  0, Qt::AlignCenter);
    layout->addWidget(passError, 0, Qt::AlignCenter);
    layout->addWidget(login,     0, Qt::AlignCenter);
    layout->addWidget(password,  0, Qt::AlignCenter);
    layout->addWidget(button,    0, Qt::AlignCenter);

    logWindow->setLayout(layout);
    logWindow->layout()->setSizeConstraint(QLayout::SetFixedSize);
    logWindow->exec();
}

/** --------------------------------------------------------------------------------------------------------------- **/

void Switch::getHash() {
    if((login->text().isEmpty() || login->text() == "Login") && (password->text().isEmpty() || password->text() == "Password")) {
        passError->setText("ERROR: The login and the password are unvalid.");
        passError->setVisible(true);
    } else if(login->text().isEmpty() || login->text() == "Login") {
        passError->setText("ERROR: The login is unvalid.");
        passError->setVisible(true);
    } else if(password->text().isEmpty() || password->text() == "Password") {
        passError->setText("ERROR: The password is unvalid.");
        passError->setVisible(true);
    } else {
        Manager::setKey(Manager::getHash(login->text() + ":@:" + password->text()));
        logWindow->close();
        delete logWindow;
    }
}

/** --------------------------------------------------------------------------------------------------------------- **/

void Switch::switchWindow(const QString & title) {
    if(currentCheckedButton == title)
        return;
    else {
        currentCheckedButton = title;
        for(int i(0); i < stack->count(); ++i) {
            stack->setCurrentIndex(i);
            if (QWidget * myWidget = dynamic_cast<QWidget *>(stack->currentWidget()))
                if(myWidget->objectName() == (title + "Widget")) {
                    switchPresence(presMap.value(currentCheckedButton));
                    break;
                }
        }
    }
}

/** --------------------------------------------------------------------------------------------------------------- **/

void Switch::switchButton(const QString & title) {
    for(int j(0); j < switchLayout->count(); ++j) {
        if(QWidgetItem * widget = dynamic_cast<QWidgetItem *>(switchLayout->itemAt(j))) {
            QPushButton * button = qobject_cast<QPushButton *>(widget->widget());
            if(button->objectName() != title)
                button->setChecked(false);
            else button->setChecked(true);
        }
    }
}

/** --------------------------------------------------------------------------------------------------------------- **/

void Switch::switchPresence(const int & state) {
    presMap.insert(currentCheckedButton, state);
    for(int j(0); j < switchPresenceLayout->count(); ++j) {
        if(QWidgetItem * widget = dynamic_cast<QWidgetItem *>(switchPresenceLayout->itemAt(j))) {
            QPushButton * button = qobject_cast<QPushButton *>(widget->widget());
            if(button->objectName() != QString(state))
                button->setChecked(false);
            else button->setChecked(true);
        }
    }
}

/** --------------------------------------------------------------------------------------------------------------- **/

void Switch::switchState(const int & state) {
    if(currentCheckedState == state)
        return;
    else {
        currentCheckedState = state;
        QString presence("");
        switch(state) {
        case 0:
            presence = "online";
            break;
        case 1:
            presence = "busy";
            break;
        case 2:
            presence = "away";
            break;
        case 3:
            presence = "offline";
            break;
        default:
            presence = "online";
        }
        qDebug() << "Switching to " << presence;
    }
}

/** --------------------------------------------------------------------------------------------------------------- **/
/** --------------------------------------------------------------------------------------------------------------- **/
