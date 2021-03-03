#pragma once
#include <SDL_mixer.h>
#include <iostream>
// 未実装
class Music
{
public:
    Music();
    ~Music();
    void        Play();                                 // ミュージック再生
    void        FadeInMusic(int fadeInTime);            // ミュージックフェードイン
    bool        LoadMusic(const std::string& fileName); // ミュージック読み込み

    static void Stop();                                 // ミュージックフェードアウト
    static void FadeOutMusic(int fadeOutTime);          // 再生中のミュージックをフェードアウト
    static bool IsPlaying();                            // 現在ミュージックは再生中か？

private:
    Mix_Music* mMusic;                                 // 音源データ

};

