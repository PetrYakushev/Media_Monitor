#pragma once

#include "FileScanner.h"
#include <string>
#include <filesystem>

class JsonWriter
{
public:
    string toJson(FileScanner::MediaMap& mediaFiles);

    void writeToFile(
        FileScanner::MediaMap& mediaFiles,filesystem::path& filePath);
};