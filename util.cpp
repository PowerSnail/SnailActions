#include "util.h"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>

#include <QDir>
#include <QStandardPaths>
#include <QString>

QDir util::EnsureConfigDir()
{
    auto configPathList = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);
    if (configPathList.isEmpty())
    {
        util::panic("Failed to get platform config directory");
    }

    QDir configDir(configPathList[0]);
    if (!configDir.mkpath("."))
    {
        util::panic("Failed to make the config directory");
    }

    return configDir;
}

rapidjson::Document util::MakeDefaultConfig(const char* path)
{
    rapidjson::Document d;

    d.SetArray();
    auto &allocator = d.GetAllocator();

    {
        rapidjson::Value v;
        v.SetObject();
        v.AddMember("title", "kwin replace", allocator);
        v.AddMember("icon_name", "kwin", allocator);
        v.AddMember("widget", "Button", allocator);
        v.AddMember("callback", "kwin_x11 --replace &", allocator);
        d.PushBack(v, allocator);
    }
    {
        rapidjson::Value v;
        v.SetObject();
        v.AddMember("title", "Brightness", allocator);
        v.AddMember("icon_name", "monitor", allocator);
        v.AddMember("widget", "Slider", allocator);
        v.AddMember("max", 100, allocator);
        v.AddMember("min", 5, allocator);
        v.AddMember("callback", "ddcutil setvcp 10 {value}", allocator);
        v.AddMember("value_getter", "ddcutil -t getvcp 10 | cut --fields=4 --delimiter=' '", allocator);
        d.PushBack(v, allocator);
    }

    util::SaveConfig(d, path);
    return d;
}

void util::SaveConfig(const rapidjson::Document &doc, const char *path)
{
    FILE *fp = fopen(path, "w");
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

    doc.Accept(writer);
    fclose(fp);
}

rapidjson::Document util::LoadConfig(const char *path)
{
    FILE *fp = fopen(path, "r");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    rapidjson::Document d;
    d.ParseStream(is);
    fclose(fp);

    return d;
}
