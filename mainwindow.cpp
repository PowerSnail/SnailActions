#include "mainwindow.h"

#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>
#include <QFocusEvent>
#include <QGridLayout>
#include <QGuiApplication>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QScreen>
#include <QSystemTrayIcon>
#include <QtDebug>
#include <QtGlobal>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), mTray(QIcon::fromTheme("SnailActions")), mContextMenu()
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Sheet);

    auto exitAction = mContextMenu.addAction("E&xit");
    mTray.setContextMenu(&mContextMenu);
    mTray.setToolTip("Snail Actions");
    mTray.show();

    QObject::connect(&mTray, &QSystemTrayIcon::activated, this, &MainWindow::TrayTriggered);
    QObject::connect(exitAction, &QAction::triggered, QApplication::instance(), &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddWidget(const QString iconName, const QString title, ActionWidget *widget)
{
    auto iconLabel = new QLabel();
    iconLabel->setPixmap(QIcon::fromTheme(iconName).pixmap(32, 32));

    auto titleLabel = new QLabel();
    titleLabel->setText(title);

    auto layout = static_cast<QGridLayout *>(this->centralWidget()->layout());
    auto row = layout->rowCount();

    layout->addWidget(iconLabel, row, 0);
    layout->addWidget(titleLabel, row, 1);
    layout->addWidget(widget, row, 2);
    QObject::connect(this, &MainWindow::Shown, widget, &ActionWidget::Shown);
}

void MainWindow::TrayTriggered(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        this->show();
        this->resize(1, 1); // As small as possible
        auto cursorPos = QCursor().pos();
        auto screenRect = QGuiApplication::screenAt(cursorPos)->geometry();
        auto rect = this->geometry();

        auto x = std::clamp(cursorPos.x(), screenRect.left(), screenRect.right() - rect.width());
        auto y = std::clamp(cursorPos.y(), screenRect.top(), screenRect.bottom() - rect.height());
        this->move(x, y);
        this->setFocus();
        emit this->Shown();
    }
}

void MainWindow::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::ActivationChange && !this->isActiveWindow())
    {
        this->hide();
    }
}
