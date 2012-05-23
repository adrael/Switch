#include "twitter.hpp"

Twitter::Twitter(const QString & path, QWidget * parent) : QWidget(parent)
{
    QGroupBox * connection(new QGroupBox("Twitter", this));

    login    = new LineEdit(this, "Login",    path + "/utils/icons", "user.png");
    password = new LineEdit(this, "Password", path + "/utils/icons", "key.png", QLineEdit::Password);

    QPushButton * launch(new QPushButton("Connect to Twitter", this));
    launch->setMaximumWidth(200);
    launch->setMinimumWidth(100);

    QGridLayout * connectLayout(new QGridLayout);
    connectLayout->addWidget(login,    1, 0, 1, 0, Qt::AlignCenter);
    connectLayout->addWidget(password, 2, 0, 1, 0, Qt::AlignCenter);
    connectLayout->addWidget(launch,   3, 0, 1, 0, Qt::AlignCenter);

    connection->setLayout(connectLayout);

    stack = new QStackedWidget(this);
    stack->addWidget(connection);

    connection->setMinimumSize(250, 300);
    connection->setMaximumSize(450, 300);

    QVBoxLayout * layout(new QVBoxLayout);
    layout->addWidget(stack);

    setLayout(layout);
    setObjectName("TwitterWidget");
}
