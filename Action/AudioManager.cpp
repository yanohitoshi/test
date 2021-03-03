#include "AudioManager.h"
#include "Music.h"
#include "Sound.h"

AudioManager* AudioManager::audio = nullptr;

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
    if (mSounds.size() > 0 || mMusics.size() > 0)
    {
        ShutDown();
    }
}


/*
@brief  インスタンスを作成する
*/
void AudioManager::CreateInstance()
{
    if (audio == nullptr)
    {
        audio = new AudioManager();
    }
}

/*
@brief  インスタンスを削除する
*/
void AudioManager::DeleteInstance()
{
    if (audio != nullptr)
    {
        delete audio;
        audio = nullptr;
    }
}

// サウンド取得
Sound* AudioManager::GetSound(const std::string& fileName)
{
    Sound* sound = nullptr;//サウンドクラスのポインタ(初期化)
    auto iter = mSounds.find(fileName);//ファイル名の検索
    // サウンドファイル登録されているか？
    if (iter != mSounds.end())//サウンド検索が成功したのか
    {
        sound = iter->second;//サウンドが見つかった
    }
    else
    {
        // 登録なかったら新規サウンド読み込み
        sound = new Sound();
        if (sound->LoadSound(fileName))
        {
            mSounds.emplace(fileName, sound);//実質mSounds[fileName] = sound;をしている
        }
        else
        {
            printf("%s 読み込み失敗\n", fileName.c_str());
            delete sound;
            sound = nullptr;
        }
    }
    return sound;
}

void AudioManager::RemoveSound(const std::string& fileName)
{
    // サウンドファイルを削除
    auto iter = mSounds.find(fileName);
    if (iter != mSounds.end())
    {
        printf("release: %s\n", iter->first.c_str());
        delete iter->second;
        mSounds.erase(iter);
    }
}

void AudioManager::PlaySound(const std::string& fileName)
{
    //サウンド鳴らす
    mSounds[fileName]->Play();
}

void AudioManager::StopSound(const std::string& fileName)
{
    mSounds[fileName]->Stop();
}

bool AudioManager::IsPlayingSound(const std::string& fileName)
{
    return mSounds[fileName]->IsPlaying();
}

Music* AudioManager::GetMusic(const std::string& fileName)
{
    Music* music = nullptr;//初期化
    auto iter = mMusics.find(fileName);//ファイル名の検索
    //ミュージックファイル登録されているか？
    if (iter != mMusics.end())//ミュージック検索が成功したのか
    {
        music = iter->second;//ミュージックが見つかった
    }
    else
    {
        //登録がなかったら新規ミュージック読み込み
        music = new Music();
        if (music->LoadMusic(fileName))
        {
            mMusics.emplace(fileName, music);
        }
        else
        {
            printf("%s読み込み失敗\n", fileName.c_str());
            delete music;
            music = nullptr;
        }
    }
    return nullptr;
}

void AudioManager::RemoveMusic(const std::string& fileName)
{
    //ミュージックファイルを削除
    auto iter = mMusics.find(fileName);
    if (iter != mMusics.end())
    {
        printf("release: %s\n", iter->first.c_str());
        delete iter->second;
        mMusics.erase(iter);
    }
}

void AudioManager::PlayFadeInMusic(const std::string& fileName, int fadeInTime)
{
    mMusics[fileName]->FadeInMusic(fadeInTime);
}

void AudioManager::PlayMusic(const std::string& fileName)
{
    //ミュージックを鳴らす
    mMusics[fileName]->Play();
}

void AudioManager::FadeOutMusic(int fadeOutTime)
{
    Music::FadeOutMusic(fadeOutTime);
}

void AudioManager::StopMusic()
{
    Music::Stop();
}

bool AudioManager::IsPlayingMusic()
{
    return Music::IsPlaying();
}

void AudioManager::ShutDown()
{
    //サウンド破棄
    for (auto i : mSounds)
    {
        printf("release : %s\n", i.first.c_str());
        delete i.second;
    }
    mSounds.clear();
    //ミュージック破棄コードをここに書く
    for (auto i : mMusics)
    {
        printf("release : %s\n", i.first.c_str());
        delete i.second;
    }
    mMusics.clear();
}