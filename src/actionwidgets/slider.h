#pragma once

#include "actionwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QWidget>
#include <string>

class Slider : public ActionWidget
{
    Q_OBJECT

  public:
    Slider(int maximum, int minimum, const char *command, const char *commandGetter, QWidget *parent = nullptr);
    void showEvent(QShowEvent *e) override;

  private:
    std::string mCommand;
    std::string mCommandGetter;
};
