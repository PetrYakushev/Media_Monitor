#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stdexcept>

using namespace std;

class FileScanner
{
public:
    using MediaMap = unordered_map<string, vector<string>>;

    MediaMap scan(filesystem::path& root);

private:
    static string toLower(string value);
    static string getCategory(filesystem::path path);
    static void sortResults(MediaMap& result);

    static unordered_set<string> kAudioExtensions;
    static unordered_set<string> kVideoExtensions;
    static unordered_set<string> kImageExtensions;
};