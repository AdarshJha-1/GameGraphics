#include <iostream>
#include <unistd.h>
#include <math.h>
#include <raylib.h>
#include <imgui.h>
#include "rlImGui.h"

#include "MP3MusicMetadata.h"

int window_width = 1000;
int window_height = 720;

int main()
{
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(window_width, window_height, "uwu");
    SetTargetFPS(60);

    InitAudioDevice();

    // const char *songName = "./songs/King Gnu - 逆夢 - King Gnu official YouTube channel.mp3";
    const char *songName = "./songs/(PLAYLIST) Late 2000's Early 2010's nightcore!!!!!!.mp3";
    Music music = LoadMusicStream(songName);
    PlayMusicStream(music);

    // i f*ed up, modern mp3 uses ID3v2.X not ID3v1
    MP3MusicMetadata musicMetadata(songName);
    musicMetadata.valid = false; // forced false will implement ID3v2.X or something

    float musicVolumeF = 0.1f;
    bool isMusicPause = false;

    rlImGuiSetup(true);

    while (WindowShouldClose() == false)
    {
        if (IsWindowResized())
        {
            window_width = GetScreenWidth();
            window_height = GetScreenHeight();
        }

        UpdateMusicStream(music);
        SetMusicVolume(music, musicVolumeF);

        BeginDrawing();
        ClearBackground(YELLOW);
        rlImGuiBegin();

        ImGui::Begin("Music Player");

        if (musicMetadata.valid)
        {
            ImGui::Text("Playing: %s", musicMetadata.title);
            ImGui::Text("Artist: %s", musicMetadata.artist);
            ImGui::Text("album: %s", musicMetadata.album);
        }
        else
        {
            ImGui::Text("Playing: %s", songName);
        }

        if (ImGui::Checkbox("Pause", &isMusicPause))
        {
            if (isMusicPause)
            {
                PauseMusicStream(music);
            }
            else
            {
                ResumeMusicStream(music);
            }
        }
        ImGui::SliderFloat("Volume", &musicVolumeF, 0.0f, 1.0f, "%.05f");
        ImGui::Separator();

        float timePlayed = GetMusicTimePlayed(music);
        float totalTime = GetMusicTimeLength(music);

        int currentMins = (int)timePlayed / 60;
        int currentSecs = (int)timePlayed % 60;

        int totalMins = (int)totalTime / 60;
        int totalSecs = (int)totalTime % 60;

        ImGui::Text("Time: %02d:%02d / %02d:%02d", currentMins, currentSecs, totalMins, totalSecs);

        float progressFraction = (totalTime > 0.0f) ? (timePlayed / totalTime) : 0.0f;

        ImGui::ProgressBar(progressFraction, ImVec2(-1.0f, 0.0f), "");

        ImGui::End();

        rlImGuiEnd();
        EndDrawing();
    }
    rlImGuiShutdown();
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}