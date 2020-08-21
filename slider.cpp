#include "slider.h"

#include <fmt/core.h>
#include <qnamespace.h>
#include <qslider.h>

#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QObject>
#include <QProcess>
#include <QSlider>
#include <QWidget>
#include <cstdlib>

Slider::Slider(const QIcon &icon, const QString &title, int maximum, int minimum, const char *command,
               const char *commandGetter, QWidget *parent)
    : ActionWidget(parent), command(command), commandGetter(commandGetter)
{

    auto iconLabel = new QLabel();
    iconLabel->setPixmap(icon.pixmap(32, 32));

    auto titleLabel = new QLabel();
    titleLabel->setText(title);

    auto slider = new QSlider();
    slider->setMaximum(maximum);
    slider->setMinimum(minimum);
    slider->setOrientation(Qt::Horizontal);
    slider->setTracking(false);

    auto layout = new QHBoxLayout();
    layout->addWidget(iconLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(slider);

    this->setLayout(layout);

    QObject::connect(slider, &QSlider::valueChanged, this, [=](int value) {
        std::string command = fmt::format(this->command, fmt::arg("value", value));
        QProcess p;
        p.start("sh", QStringList() << "-c" << command.c_str());
        p.waitForFinished(-1);
    });

    QObject::connect(this, &Slider::shown, this, [=]() {
        QProcess p;
        p.start("sh", QStringList() << "-c" << this->commandGetter.c_str());
        p.waitForFinished(-1);
        auto output = p.readAllStandardOutput().toInt();
        slider->setValue(output);
    });
}

void Slider::showEvent(QShowEvent *e)
{
    emit shown();
}
