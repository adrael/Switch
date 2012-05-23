#include "googletalk.hpp"

GoogleTalk::GoogleTalk(const QString & path, QWidget * parent) : QWidget(parent)
{
    QGroupBox * connection(new QGroupBox("GoogleTalk", this));
    connection->setMinimumSize(250, 300);
    connection->setMaximumSize(450, 300);

    login    = new LineEdit(this, "Login",    path + "/utils/icons", "user.png");
    password = new LineEdit(this, "Password", path + "/utils/icons", "key.png", QLineEdit::Password);

    loader = new QLabel(this);
    loader->setMovie(new QMovie(path + "/utils/icons/loader.gif"));

    launcher = new QPushButton("Connect to GTalk", this);
    launcher->setMaximumWidth(200);
    launcher->setMinimumWidth(100);

    canceller = new QPushButton("Cancel", this);
    canceller->setMaximumWidth(100);
    canceller->setMinimumWidth(100);
    canceller->setEnabled(false);

    memorizer = new QCheckBox("Remember user", this);

    QGridLayout * connectLayout(new QGridLayout);
    connectLayout->addWidget(login,     1, 0, 1, 0, Qt::AlignCenter);
    connectLayout->addWidget(password,  2, 0, 1, 0, Qt::AlignCenter);
    connectLayout->addWidget(memorizer, 3, 0, 1, 0, Qt::AlignCenter);
    connectLayout->addWidget(loader,    4, 0, 1, 0, Qt::AlignCenter);
    connectLayout->addWidget(launcher,  5, 0);
    connectLayout->addWidget(canceller, 5, 1);

    connection->setLayout(connectLayout);

    stack = new QStackedWidget(this);
    stack->addWidget(connection);

    QVBoxLayout * layout(new QVBoxLayout);
    layout->addWidget(stack);

    bool check = connect(launcher, SIGNAL(clicked()), this, SLOT(signIn()));
    Q_ASSERT(check);

    check = connect(canceller, SIGNAL(clicked()), this, SLOT(cancelSignIn()));
    Q_ASSERT(check);

    setLayout(layout);
    setObjectName("GTalkWidget");
}

/** --------------------------------------------------------------------------------------------------------------- **/

void GoogleTalk::signIn()
{
    Manager::store("GTALK", login->text(), password->text());

    login->setEnabled(false);
    password->setEnabled(false);
    launcher->setEnabled(false);
    canceller->setEnabled(true);
    loader->setVisible(true);
    loader->movie()->start();

//    m_xmppClient.configuration().setJid(login->text());
//    m_xmppClient.configuration().setPassword(password->text());

//    qDebug() << m_xmppClient.configuration().jid();

    // Connect to google
}

/** --------------------------------------------------------------------------------------------------------------- **/

void GoogleTalk::cancelSignIn()
{
    login->setEnabled(true);
    password->setEnabled(true);
    launcher->setEnabled(true);
    canceller->setEnabled(false);
    loader->setVisible(false);
    loader->movie()->stop();
}

/** --------------------------------------------------------------------------------------------------------------- **/
