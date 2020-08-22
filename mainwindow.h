#pragma once

#include "actionwidgets/actionwidget.h"
#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void AddWidget(const QString iconName, const QString title, ActionWidget *widget);

    void changeEvent(QEvent *e) override;

  signals:
    void shown();

  public slots:
    void TrayTriggered(QSystemTrayIcon::ActivationReason reason);

  private:
    Ui::MainWindow *ui;
    QSystemTrayIcon tray;
    QMenu contextMenu;
};
