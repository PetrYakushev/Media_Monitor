#include "../insert/FileScanner.h"
#include "../insert/JsonWriter.h"
#include "../insert/Scheduler.h"
#include "../insert/HttpServer.h"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    try{
        filesystem::path root = filesystem::current_path();
        chrono::seconds interval(5);

        if (argc >= 2)
            root = argv[1];

        if (argc >= 3)
            interval = chrono::seconds(stoi(argv[2]));

        filesystem::path output = filesystem::path(getenv("HOME")) / ".media_files";

        FileScanner scanner;
        JsonWriter writer;
        Scheduler scheduler;
        HttpServer server(output);

        thread httpThread([&](){
            server.start(1234);
        });

        scheduler.run(
            [&]()
            {
                auto mediaFiles = scanner.scan(root);
                writer.writeToFile(mediaFiles, output);

                cout << "Updated: " << output << "\n";
            },
            interval);

        httpThread.join();
    }
    catch (const std::exception& e){
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}