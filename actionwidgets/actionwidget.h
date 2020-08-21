#pragma once

#include <QWidget>

class ActionWidget : public QWidget
{
    Q_OBJECT

  public:
    ActionWidget(QWidget *parent);

  signals:
    void shown();
};
