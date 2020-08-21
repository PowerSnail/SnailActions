#pragma once
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>

#include <QDir>
#include <exception>

namespace util
{

template <typename... T> void panic(const char *msg, T... args)
{
    printf(msg, args...);
    printf("\n");
    std::terminate();
}

QDir EnsureConfigDir();

rapidjson::Document DefaultConfig();

void SaveConfig(const rapidjson::Document &doc, const char *path);

rapidjson::Document LoadConfig(const char *path);

} // namespace util
