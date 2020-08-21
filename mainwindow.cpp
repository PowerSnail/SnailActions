#include "mainwindow.h"

#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QIcon>
#include <QLayout>
#include <QScreen>
#include <QSystemTrayIcon>
#include <QFocusEvent>

#include <QtDebug>
#include <qnamespace.h>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), tray(QIcon::fromTheme("SnailActions"))
{
    ui->setupUi(this);
    tray.setToolTip("Snail Actions");
    QObject::connect(&tray, &QSystemTrayIcon::activated, this, [=](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger)
        {
            this->show();
        }
    });
    tray.show();

    QObject::connect(this, &MainWindow::shown, this, [=]() {
        this->setFocus();
        this->resize(1, 1); // As small as possible
        auto cursorPos = QCursor().pos();
        auto screenRect = QGuiApplication::screenAt(cursorPos)->geometry();
        auto rect = this->geometry();

        auto x = std::clamp(cursorPos.x(), screenRect.left(), screenRect.right() - rect.width());
        auto y = std::clamp(cursorPos.y(), screenRect.top(), screenRect.bottom() - rect.height());
        this->move(x, y);
    });

    this->setWindowFlags(Qt::Tool);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addWidget(ActionWidget *widget)
{
    this->centralWidget()->layout()->addWidget(widget);
    QObject::connect(this, &MainWindow::shown, widget, &ActionWidget::shown);
}

void MainWindow::showEvent(QShowEvent *e)
{
    this->QMainWindow::showEvent(e);
    emit this->shown();
}

void MainWindow::focusOutEvent(QFocusEvent *e) {
    qDebug() << "Focus out event reason: " << e->reason();
    // if (e->reason() == Qt::ActiveWindowFocusReason) {
        // this->hide();
    // }
}

