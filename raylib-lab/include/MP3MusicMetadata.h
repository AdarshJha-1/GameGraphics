#ifndef MP3_MUSIC_METADATA_H
#define MP3_MUSIC_METADATA_H

class MP3MusicMetadata
{
public:
    char title[31];
    char artist[31];
    char album[31];
    bool valid = false;

    MP3MusicMetadata(const char *filepath);
    ~MP3MusicMetadata();
};

#endif // MP3_MUSIC_METADATA_H
