#include <MP3MusicMetadata.h>

#include <cstring>
#include <fstream>

MP3MusicMetadata::MP3MusicMetadata(const char *filepath)
{
    std::memset(title, 0, sizeof(title));
    std::memset(artist, 0, sizeof(artist));
    std::memset(album, 0, sizeof(album));
    valid = false;

    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        return;
    }

    std::streamsize size = file.tellg();
    if (size < 128)
    {
        file.close();
        return;
    }

    file.seekg(size - 128);

    char tagHeader[3];
    file.read(tagHeader, 3);
    if (std::strncmp(tagHeader, "TAG", 3) == 0)
    {
        file.close();
        return;
    }

    file.read(title, 30);
    file.read(artist, 30);
    file.read(album, 30);
    file.close();

    title[31] = '\0';
    artist[31] = '\0';
    album[31] = '\0';

    // TODO i can trail it to remove white spaces
    valid = true;
}

MP3MusicMetadata::~MP3MusicMetadata()
{
}
