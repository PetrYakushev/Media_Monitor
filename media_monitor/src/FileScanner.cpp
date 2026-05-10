#include "../insert/FileScanner.h"
#include <iostream>
#include <algorithm>
#include <system_error>

unordered_set<string> FileScanner::kAudioExtensions = {
    ".mp3",
    ".wav",
    ".flac",
    ".ogg",
    ".aac"
};

unordered_set<string> FileScanner::kVideoExtensions = {
    ".mp4",
    ".avi",
    ".mkv",
    ".mov",
    ".mpeg",
    ".mpg"
};

unordered_set<string> FileScanner::kImageExtensions = {
    ".jpg",
    ".jpeg",
    ".png",
    ".gif",
    ".bmp",
    ".webp"
};

string FileScanner::toLower(string value)
{
    transform(value.begin(),value.end(),value.begin(),[](unsigned char c){
        return static_cast<char>(tolower(c));
    });
    return value;
}

string FileScanner::getCategory(filesystem::path path)
{
    string extension = toLower(path.extension().string());

    if (kAudioExtensions.contains(extension)){
        return "audio";
    }

    if (kVideoExtensions.contains(extension)){
        return "video";
    }

    if (kImageExtensions.contains(extension)){
        return "images";
    }

    return {};
}

void FileScanner::sortResults(MediaMap& result)
{
    for (auto& [category, files] : result)
    {
        std::sort(files.begin(), files.end());
    }
}

FileScanner::MediaMap FileScanner::scan(filesystem::path& root)
{
    MediaMap result{
        {"audio", {}},
        {"video", {}},
        {"images", {}}
    };

    if (!filesystem::exists(root)){
        throw runtime_error("Path does not exist: " + root.string());
    }

    if (!filesystem::is_directory(root)){
        throw runtime_error("Path is not a directory: " + root.string());
    }

    error_code ec;

    auto options = filesystem::directory_options::skip_permission_denied;

    for (filesystem::recursive_directory_iterator it(root, options, ec), end;it != end;it.increment(ec)){
        if (ec){
            ec.clear();
            continue;
        }
        
        if (!it->is_regular_file(ec)){
            ec.clear();
            continue;
        }

        string category = getCategory(it->path());

        if (category.empty())
        {
            continue;
        }
        
        filesystem::path relativePath =filesystem::relative(it->path(), root, ec);

        if (ec){
            ec.clear();
            continue;
        }

        result[category].push_back(relativePath.string());
    }

    sortResults(result);

    return result;
}