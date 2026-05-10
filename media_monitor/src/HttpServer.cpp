#include "../insert/HttpServer.h"
#include "httplib.h"

#include <fstream>
#include <sstream>

HttpServer::HttpServer(filesystem::path filePath): filePath_(move(filePath)){
}

void HttpServer::start(int port)
{
    httplib::Server server;
    server.Get("/media_files",[&](const httplib::Request&, httplib::Response& res)
    {
        ifstream file(filePath_);

        if (!file.is_open())
        {
            res.status = 500;
            res.set_content("{\"error\":\"file not found\"}", "application/json");
            return;
        }
        stringstream buffer;
        buffer << file.rdbuf();

        res.set_content(buffer.str(), "application/json");
    });

    server.Get("/", [&](const httplib::Request&, httplib::Response& res)
    {
        const char* html = R"HTML(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Media Monitor</title>
    <style>
        body {
            font-family: Arial;
            margin: 20px;
            background: #0f172a;
            color: #e2e8f0;
        }
        h1 { color: #38bdf8; }
        pre {
            background: #1e293b;
            padding: 15px;
            border-radius: 8px;
            overflow-x: auto;
        }
        .box {
            margin-bottom: 20px;
            padding: 10px;
            background: #111827;
            border-radius: 10px;
        }
    </style>
</head>
<body>

<h1>Media Monitor</h1>

<div class="box">
    <h3>Audio</h3>
    <ul id="audio"></ul>
</div>

<div class="box">
    <h3>Video</h3>
    <ul id="video"></ul>
</div>

<div class="box">
    <h3>Images</h3>
    <ul id="images"></ul>
</div>

<script>
async function loadData() {
    try {
        const res = await fetch('/media_files');
        const data = await res.json();

        function fill(id, arr) {
            const el = document.getElementById(id);
            el.innerHTML = '';
            arr.forEach(f => {
                const li = document.createElement('li');
                li.textContent = f;
                el.appendChild(li);
            });
        }

        fill('audio', data.audio || []);
        fill('video', data.video || []);
        fill('images', data.images || []);

    } catch (e) {
        console.error(e);
    }
}

loadData();
setInterval(loadData, 3000);
</script>

</body>
</html>
)HTML";

        res.set_content(html, "text/html");
    });

    server.listen("0.0.0.0", port);
}