#pragma once
#include <SDL_mixer.h>
#include <iostream>
// ������
class Sound
{
public:
    Sound();
    ~Sound();
    void          Play();       // �Đ�
    void          Stop();       // �X�g�b�v
    bool          LoadSound(const std::string& fileName); // �T�E���h�t�@�C���ǂݍ���
    bool          IsPlaying();  // ���ݍĐ������H

private:
    Mix_Chunk* mChunk;        // �T�E���h�f�[�^
    int           mChannel;      // �Đ��`�����l��

};

