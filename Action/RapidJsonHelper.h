#pragma once

#include "document.h"
#include "filereadstream.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


/*
@fn  json�t�@�C���̃I�[�v��
@param _inputDocument rapidJson�I�u�W�F�N�g
@param _inFileName �I�[�v��������Json�t�@�C���p�X
return �t�@�C�����J�����Ƃ��ł�����
*/
bool openJsonFile(rapidjson::Document& _inputDocument, const char* inFileName);

/*
@fn  Doc���ɂ��̃����o�[�͑��݂��邩�H
@param _inDocument rapidJson�I�u�W�F�N�g
@param _memberName �����o��
@return Document�Ƀ����o�����܂܂�Ă������ǂ���
*/
bool IsExistMember(const rapidjson::Document& inDoc, const char* memberName);

/*
@fn ���̃����o�[�����݂��A���l����v���邩�H
@param _inDocument �h�L�������g
@param _menberName �����o�[��
@param _matchValue ���ׂ��������o�[���Ƀ}�b�`����l
@return  memberName�ɑΉ�����l��matchValue�������Ƃ��̂�true��Ԃ�
*/
bool IsExistMemberAndValue(const rapidjson::Document& inDoc, const char* memberName, const char* matchValue);

/*
@param _inDocument
@param _menberName
@return Document���Ƀ����o�����܂܂�邩
*/
bool IsExistArrayName(const rapidjson::Document& inDoc, const char* memberName);


// Value�l�������I��Float�l�Ƃ��Ď擾
float ForceGetFloat(const rapidjson::Value& val);

