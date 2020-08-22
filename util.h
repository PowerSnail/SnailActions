#pragma once
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>

#include <QDir>
#include <exception>

namespace util
{

template <typename... T> void Panic(const char *msg, T... args)
{
    printf(msg, args...);
    printf("\n");
    std::terminate();
}

QDir EnsureConfigDir();

rapidjson::Document MakeDefaultConfig(const char *path);

void SaveConfig(const rapidjson::Document &doc, const char *path);

rapidjson::Document LoadConfig(const char *path);

} // namespace util
