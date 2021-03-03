#pragma once
#include "SDL.h"
#include <unordered_map>    


#define AUDIO AudioManager::GetInstance()

class Sound;
class Music;
// 未実装
class AudioManager
{
public:

    /*
    @brief  インスタンスを取得する
    @return AudioManagerクラスのインスタンス
    */
    static AudioManager* GetInstance() { return audio; }
    /*
    @brief  インスタンスを作成する
    */
    static void CreateInstance();

    /*
    @brief  インスタンスを削除する
    */
    static void DeleteInstance();

    Sound* GetSound(const std::string& fileName);
    void RemoveSound(const std::string& fileName);
    void PlaySound(const std::string& fileName);
    void StopSound(const std::string& fileName);
    bool IsPlayingSound(const std::string& fileName);

    Music* GetMusic(const std::string& fileName);
    void RemoveMusic(const std::string& fileName);
    void PlayFadeInMusic(const std::string& fileName, int fadeInTime);
    void PlayMusic(const std::string& fileName);
    void FadeOutMusic(int fadeOutTime);
    void StopMusic();
    bool IsPlayingMusic();

    void ShutDown();

private:

    AudioManager();
    ~AudioManager();

    //自分のインスタンス
    static AudioManager* audio;


    std::unordered_map<std::string, class Sound*> mSounds;
    std::unordered_map<std::string, class Music*> mMusics;

};

