/****************************************************************************
*  Copyright (C) 2011 Raphaël MARQUES <work.rmarques@gmail.com>
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

/** --------------------------------------------------------------------------------------------------------------- **/

#ifndef LINEEDIT_HPP
#define LINEEDIT_HPP

/** --------------------------------------------------------------------------------------------------------------- **/

#include <qcoreapplication.h>
#include <qtoolbutton.h>
#include <qevent.h>
#include <qlineedit.h>
#include <qstyle.h>

/** --------------------------------------------------------------------------------------------------------------- **/

class LineEdit : public QLineEdit {

    Q_OBJECT

public:

    LineEdit(QWidget * lineParent = 0, const QString & lineText = "", const QString & iconPath = "", const QString & icon = "", const EchoMode & mode = QLineEdit::Normal) :
        QLineEdit(lineText, lineParent),
        clearButton(new QToolButton(this)),
        iconButton(new QToolButton(this)),
        myText(lineText) {


        QPalette palette = this->palette();
        palette.setColor(QPalette::Text, QColor(128, 128, 128));
        setPalette(palette);

        clearButton->setIcon(QIcon(iconPath + "/clear.png"));
        clearButton->setIconSize(QSize(16, 16));
        clearButton->setCursor(Qt::PointingHandCursor);
        clearButton->setStyleSheet("QToolButton {border: none; padding: 0px;}");
        clearButton->hide();
        clearButton->setToolTip(tr("Clear searchbar"));

        iconButton->setIcon(QIcon(iconPath + "/" + icon));
        iconButton->setIconSize(QSize(16, 16));
        iconButton->setStyleSheet("QToolButton {border: none; padding: 0px;}");

        connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
        connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(updateClearButton(const QString &)));

        int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
        setStyleSheet(QString("QLineEdit {padding-right: %1px; padding-left: %1px;} ").arg(clearButton->sizeHint().width() + frameWidth + 5));

        QSize miniSize = minimumSizeHint();

        setMinimumSize(qMax(miniSize.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2),
                               qMax(miniSize.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));

        setAcceptDrops(false);
        setEchoMode(mode);
        setMinimumWidth(200);
        setMaximumWidth(400);
    }

    ~LineEdit() {}

    void mousePressEvent(QMouseEvent * event) {
        if (event->button() == Qt::RightButton) event->accept();
        else  QLineEdit::mousePressEvent(event);
    }

    void contextMenuEvent(QContextMenuEvent * event) {
        event->ignore();
        return;
    }

    void noResult(bool result = false) {
        QPalette palette = this->palette();
        if(result) palette.setColor(QPalette::Text, QColor(255, 0, 0));
        else palette.setColor(QPalette::Text, QColor(0, 0, 0));
        setPalette(palette);
    }

protected:

    void resizeEvent(QResizeEvent * event) {
        QSize size = clearButton->sizeHint();
        int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
        clearButton->move(rect().right() - frameWidth - size.width(), (rect().bottom() + 1 - size.height()) / 2);
        iconButton->move(5, (rect().bottom() + 1 - size.height()) / 2);
    }


private slots:

    void updateClearButton(const QString & text) {
        clearButton->setVisible(!text.isEmpty());
    }

private:

    QToolButton * clearButton, * iconButton;
    QString myText;

    void focusInEvent(QFocusEvent * event) {
        if(text() == myText) {
            clear();
            QPalette palette = this->palette();
            palette.setColor(QPalette::Text, QColor(0, 0, 0));
            setPalette(palette);
        }
        event->accept();
    }

    void focusOutEvent(QFocusEvent * e) {
        if(text().isEmpty()) {
            QPalette palette = this->palette();
            palette.setColor(QPalette::Text, QColor(128, 128, 128));
            setPalette(palette);
            setText(myText);
            clearButton->setVisible(false);
            QCoreApplication::processEvents();
            QCoreApplication::flush();
        }
        e->accept();
    }
};

/** --------------------------------------------------------------------------------------------------------------- **/

#endif // LINEEDIT_HPP
