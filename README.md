# Media Monitor

Media Monitor — приложение на C++20 под Linux для периодического сканирования каталога и поиска мультимедийных файлов.

Программа:

- рекурсивно обходит указанный каталог;
- ищет аудио, видео и изображения;
- формирует JSON-файл `~/.media_files`;
- предоставляет HTTP API;
- отображает HTML-страницу с автоматическим обновлением данных.

---

## Поддерживаемые форматы

### Audio
- `.mp3`
- `.wav`
- `.flac`
- `.ogg`
- `.aac`

### Video
- `.mp4`
- `.avi`
- `.mkv`
- `.mov`
- `.mpeg`
- `.mpg`

### Images
- `.jpg`
- `.jpeg`
- `.png`
- `.gif`
- `.bmp`
- `.webp`

---

## Формат JSON

```json
{
  "audio": [
    "music/song.mp3"
  ],
  "video": [
    "videos/movie.mkv"
  ],
  "images": [
    "images/photo.jpg"
  ]
}
```

## Запуск

В папке `build`:

Базовый запуск (текущая директория)

`./media_monitor`

Запуск с параметрами

`./media_monitor <path_to_scan> <interval_seconds>`

Пример:

`./media_monitor /home/user 5`


## Доступ к приложению

После запуска:

JSON API

`http://localhost:1234/media_files`

Web-интерфейс

`http://localhost:1234/`

## Завершение работы

Остановка приложения:

`Ctrl + C`

## Выходной файл

Результаты сохраняются в:

`~/.media_files`
