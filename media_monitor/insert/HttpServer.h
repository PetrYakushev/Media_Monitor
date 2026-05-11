#pragma once

#include <filesystem>
#include <string>

using namespace std;

class HttpServer{
public:
    explicit HttpServer(filesystem::path filePath);
    void start(int port);
private:
    filesystem::path filePath_;
};