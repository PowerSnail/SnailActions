#pragma once

#include "action.h"
#include <QMainWindow>
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

    void addWidget(ActionWidget *widget);
    void showEvent(QShowEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;

  signals:
    void shown();

  private:
    Ui::MainWindow *ui;
    QSystemTrayIcon tray;
};
