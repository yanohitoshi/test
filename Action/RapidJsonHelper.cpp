#include "RapidJsonHelper.h"

/*
@fn  json�t�@�C���̃I�[�v�� 
@param _inputDocument rapidJson�I�u�W�F�N�g
@param _inFileName �I�[�v��������Json�t�@�C���p�X
return �t�@�C�����J�����Ƃ��ł�����
*/
bool openJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName)
{
	// json�t�@�C���J���邩�H
	std::ifstream file(_inFileName);
	if (!file.is_open())
	{
		return false;
	}

	// filestream�Ƀt�@�C���������荞��
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();

	// �t�@�C���������JSon������ɕϊ�
	rapidjson::StringStream jsonStr(contents.c_str());
	// �t�@�C���X�g���[������
	file.close();

	// ��̓I�u�W�F�N�g�쐬
	_inputDocument.ParseStream(jsonStr);

	// JSonObject�Ƃ��ēǂ߂����H
	if (!_inputDocument.IsObject())
	{
		return false;
	}
	return true;
}

/*
@fn  Doc���ɂ��̃����o�[�͑��݂��邩�H
@param _inDocument rapidJson�I�u�W�F�N�g
@param _memberName �����o��
@return Document�Ƀ����o�����܂܂�Ă������ǂ���
*/
bool IsExistMember(const rapidjson::Document& _inDocument, const char* _memberName)
{
	rapidjson::Value::ConstMemberIterator iter;
	iter = _inDocument.FindMember(_memberName);

	if (iter == _inDocument.MemberEnd())
	{
		return false;
	}
	return true;
}

/*
@fn ���̃����o�[�����݂��A���l����v���邩�H
@param _inDocument �h�L�������g
@param _menberName �����o�[��
@param _matchValue ���ׂ��������o�[���Ƀ}�b�`����l
@return  memberName�ɑΉ�����l��matchValue�������Ƃ��̂�true��Ԃ� 
*/
bool IsExistMemberAndValue(const rapidjson::Document& _inDocument, const char* _menberName, const char* _matchValue)
{
	if (!IsExistMember(_inDocument, _menberName))
	{
		return false;
	}

	std::string findValueString;
	findValueString = std::string(_matchValue);

	if (findValueString != _inDocument[_menberName].GetString())
	{
		return false;
	}
	return true;
}

/*
@param _inDocument
@param _menberName 
@return Document���Ƀ����o�����܂܂�邩
*/
bool IsExistArrayName(const rapidjson::Document& _inDocument, const char* _menberName)
{
	rapidjson::Value::ConstMemberIterator iter;
	iter = _inDocument.FindMember(_menberName);
	if (iter == _inDocument.MemberEnd())
	{
		return false;
	}
	return _inDocument[_menberName].IsArray();
}


// JSON�l����e��int�ł������I��float �l�Ƃ��Ď擾
float ForceGetFloat(const rapidjson::Value& val)
{
	std::string tmp;
	tmp = val.GetString();

	return static_cast<float>(atof(tmp.c_str()));
}
