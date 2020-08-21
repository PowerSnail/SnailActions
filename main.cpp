#include <QApplication>
#include <QDir>
#include <QIcon>
#include <QStandardPaths>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "action.h"
#include "button.h"
#include "mainwindow.h"
#include "slider.h"
#include "util.h"

ActionWidget *BuildButton(const rapidjson::Value &config)
{
    auto btn = new Button(QIcon::fromTheme(config["icon_name"].GetString()), // icon
                          config["title"].GetString(),                       // title
                          config["callback"].GetString()                     // command
    );
    return btn;
}

ActionWidget *BuildSlider(const rapidjson::Value &config)
{
    auto slider = new Slider(QIcon::fromTheme(config["icon_name"].GetString()), // icon
                             config["title"].GetString(),                       // title
                             config["max"].GetInt(),                            // maximum
                             config["min"].GetInt(),                            // minimum
                             config["callback"].GetString(),                    // command
                             config["value_getter"].GetString()                 // commandGetter
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
        util::panic("App Icon is Null");
    }
    QApplication::setWindowIcon(appIcon);

    auto configDir = util::EnsureConfigDir();
    const auto config = (configDir.exists("action.json"))
                            ? util::LoadConfig(configDir.filePath("action.json").toStdString().c_str())
                            : util::DefaultConfig();

    if (!config.IsArray())
    {
        util::panic("Error parsing the config.");
    }

    MainWindow w;

    for (auto &v : config.GetArray())
    {
        auto type = std::string(v["widget"].GetString(), v["widget"].GetStringLength());
        if (type == "Button")
        {
            w.addWidget(BuildButton(v));
        }
        else if (type == "Slider")
        {
            w.addWidget(BuildSlider(v));
        }
    }

    auto result = a.exec();
    util::SaveConfig(config, configDir.filePath("action.json").toStdString().c_str());
    return result;
}
