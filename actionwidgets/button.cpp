#include "button.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QObject>
#include <QProcess>
#include <QPushButton>
#include <QStringList>
#include <QWidget>
#include <cstdlib>

Button::Button(const char *command, QWidget *parent) : ActionWidget(parent), mCommand(command)
{
    auto button = new QPushButton();
    button->setIcon(QIcon::fromTheme("media-play"));
    auto policy = button->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    button->setSizePolicy(policy);

    QObject::connect(button, &QPushButton::clicked, this, [=]() {
        QProcess p;
        p.start("sh", QStringList() << "-c" << this->mCommand.c_str());
        p.waitForFinished(-1);
    });

    auto layout = new QHBoxLayout();
    layout->addWidget(button);

    this->setLayout(layout);
}
