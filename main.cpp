#include <QApplication>
#include <QDir>
#include <QIcon>
#include <QStandardPaths>

#include "actionwidgets/actionwidget.h"
#include "actionwidgets/button.h"
#include "actionwidgets/slider.h"
#include "mainwindow.h"
#include "util.h"

ActionWidget *BuildButton(const rapidjson::Value &config)
{
    auto btn = new Button(config["callback"].GetString());
    return btn;
}

ActionWidget *BuildSlider(const rapidjson::Value &config)
{
    auto slider = new Slider(config["max"].GetInt(),            // maximum
                             config["min"].GetInt(),            // minimum
                             config["callback"].GetString(),    // command
                             config["value_getter"].GetString() // commandGetter
    );
    return slider;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << ":icons");
    auto appIcon = QIcon::fromTheme("SnailActions");
    if (appIcon.isNull())
    {
        util::Panic("App Icon is Null");
    }
    QApplication::setWindowIcon(appIcon);

    auto configDir = util::EnsureConfigDir();
    auto configPath = configDir.filePath("action.json").toStdString();
    const auto config = (configDir.exists("action.json")) ? util::LoadConfig(configPath.c_str())
                                                          : util::MakeDefaultConfig(configPath.c_str());

    if (!config.IsArray())
    {
        util::Panic("Error parsing the config.");
    }

    MainWindow w;

    for (auto &v : config.GetArray())
    {
        auto type = std::string(v["widget"].GetString(), v["widget"].GetStringLength());
        if (type == "Button")
        {
            w.AddWidget(v["icon_name"].GetString(), v["title"].GetString(), BuildButton(v));
        }
        else if (type == "Slider")
        {
            w.AddWidget(v["icon_name"].GetString(), v["title"].GetString(), BuildSlider(v));
        }
    }

    auto result = a.exec();
    return result;
}
