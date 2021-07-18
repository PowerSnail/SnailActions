#include "src/actionwidgets/slider.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QObject>
#include <QProcess>
#include <QSlider>
#include <QWidget>
#include <QtGlobal>
#include <fmt/core.h>

Slider::Slider(int maximum, int minimum, const char *command, const char *commandGetter, QWidget *parent)
    : ActionWidget(parent), mCommand(command), mCommandGetter(commandGetter), mSlider(), lock()
{
    mSlider.setMaximum(maximum);
    mSlider.setMinimum(minimum);
    mSlider.setOrientation(Qt::Horizontal);
    mSlider.setTracking(false);

    auto layout = new QHBoxLayout();
    layout->addWidget(&mSlider);

    this->setLayout(layout);

    QObject::connect(&mSlider, &QSlider::valueChanged, this, &Slider::SliderValueChanged);
    QObject::connect(this, &Slider::Shown, this, &Slider::GetValue);
}

void Slider::showEvent(QShowEvent *e)
{
    emit Shown();
}

void Slider::GetValue()
{
    lock.lock();
    mSlider.setEnabled(false);
    blockSignals(true);
    auto *p = new QProcess(this);
    p->start("sh", QStringList() << "-c" << this->mCommandGetter.c_str());
    connect(p, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [p, this](int, QProcess::ExitStatus) {
        auto output = p->readAllStandardOutput().toInt();
        this->mSlider.setValue(output);
        this->mSlider.setEnabled(true);
        p->setParent(nullptr);
        delete p;
        blockSignals(false);
        lock.unlock();
    });
}

void Slider::SliderValueChanged(int value)
{
    if (!lock.try_lock()) {
        return;
    }

    std::string command = fmt::format(this->mCommand, fmt::arg("value", value));
    auto *p = new QProcess(this);
    p->start("sh", QStringList() << "-c" << command.c_str());
    connect(p, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [p, this](int, QProcess::ExitStatus) {
        p->setParent(nullptr);
        delete p;
        lock.unlock();
    });
}
