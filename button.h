#pragma once

#include "action.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <string>

class Button : public ActionWidget
{
    Q_OBJECT

  public:
    Button(const QIcon &icon, const QString &title, const char *command, QWidget *parent = nullptr);

  private:
    std::string command;
};
