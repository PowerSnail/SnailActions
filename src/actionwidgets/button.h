#pragma once

#include "src/actionwidgets/actionwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <string>

class Button : public ActionWidget
{
    Q_OBJECT

  public:
    Button(const char *command, QWidget *parent = nullptr);

  private:
    std::string mCommand;
};
