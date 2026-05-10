#include "../insert/JsonWriter.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

string JsonWriter::toJson(FileScanner::MediaMap& mediaFiles){
    json j;

    j["audio"] = mediaFiles.contains("audio")
        ? mediaFiles.at("audio")
        : vector<string>{};

    j["video"] = mediaFiles.contains("video")
        ? mediaFiles.at("video")
        : vector<string>{};

    j["images"] = mediaFiles.contains("images")
        ? mediaFiles.at("images")
        : vector<string>{};

    return j.dump(4);
}

void JsonWriter::writeToFile(FileScanner::MediaMap& mediaFiles,filesystem::path& filePath)
{
    string tmpPath = filePath.string() + ".tmp";

    ofstream out(tmpPath, ios::out | ios::trunc);
    if (!out.is_open()){
        throw runtime_error("Failed to open temp file");
    }
    out << toJson(mediaFiles);
    out.close();
    error_code ec;
    filesystem::rename(tmpPath, filePath, ec);

    if (ec){
        throw runtime_error("Failed to rename temp file");
    }
}