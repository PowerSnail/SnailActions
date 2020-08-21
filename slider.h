#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QWidget>
#include <string>

#include "action.h"

class Slider : public ActionWidget
{
    Q_OBJECT

  public:
    Slider(const QIcon &icon, const QString &title, int maximum, int minimum, const char *command,
           const char *commandGetter, QWidget *parent = nullptr);
    void showEvent(QShowEvent *e) override;

  private:
    std::string command;
    std::string commandGetter;
};
