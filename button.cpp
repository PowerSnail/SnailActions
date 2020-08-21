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

Button::Button(const QIcon &icon, const QString &title, const char *command, QWidget *parent)
    : ActionWidget(parent), command(command)
{

    auto iconLabel = new QLabel();
    iconLabel->setPixmap(icon.pixmap(32, 32));

    auto titleLabel = new QLabel();
    titleLabel->setText(title);

    auto button = new QPushButton();
    auto policy = button->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    button->setSizePolicy(policy);

    QObject::connect(button, &QPushButton::clicked, this, [=]() {
        QProcess p;
        p.start("sh", QStringList() << "-c" << this->command.c_str());
        p.waitForFinished(-1);
    });

    auto layout = new QHBoxLayout();
    layout->addWidget(iconLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(button);

    this->setLayout(layout);
}
