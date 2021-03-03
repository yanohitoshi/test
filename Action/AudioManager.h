#pragma once
#include "SDL.h"
#include <unordered_map>    


#define AUDIO AudioManager::GetInstance()

class Sound;
class Music;
// ������
class AudioManager
{
public:

    /*
    @brief  �C���X�^���X���擾����
    @return AudioManager�N���X�̃C���X�^���X
    */
    static AudioManager* GetInstance() { return audio; }
    /*
    @brief  �C���X�^���X���쐬����
    */
    static void CreateInstance();

    /*
    @brief  �C���X�^���X���폜����
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

    //�����̃C���X�^���X
    static AudioManager* audio;


    std::unordered_map<std::string, class Sound*> mSounds;
    std::unordered_map<std::string, class Music*> mMusics;

};

