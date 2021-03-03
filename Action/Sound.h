#pragma once
#include <SDL_mixer.h>
#include <iostream>
// 未実装
class Sound
{
public:
    Sound();
    ~Sound();
    void          Play();       // 再生
    void          Stop();       // ストップ
    bool          LoadSound(const std::string& fileName); // サウンドファイル読み込み
    bool          IsPlaying();  // 現在再生中か？

private:
    Mix_Chunk* mChunk;        // サウンドデータ
    int           mChannel;      // 再生チャンネル

};

