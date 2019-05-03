#ifndef __Stone_Token_H__
#define __Stone_Token_H__

#include <string>

#include "StoneMarcos.h"

NS_STONE_BEGIN
/*
	���ʣ��б�ʶ�������ֺ��ַ���
*/
class Token
{
public:
	enum class Type
	{
		None,
		Identifier,//��ʶ��
		Number,	   //����
		String,	   //�ַ���
	};
public:
	Token(int line);
	~Token();
	//��ȡ�к�
	int getLineNumber() const { return _line; }
	//��ȡ���ʵ�����
	Type getType() const { return _type; }
	//��ȡ�ı�
	virtual std::string asString() const { return ""; }
	//��ȡ����
	virtual int asInt() const { return 0; }
protected:
	int _line;
	Type _type;
public:
	//end of file
	static Token* const TOKEN_EOF;
	//end of line
	static const char* TOKEN_EOL;
};

/*
	NumToken ����
*/
class NumToken: public Token
{
public:
	NumToken(int line, int value);
	virtual std::string asString() const;
	virtual int asInt() const;
private:
	int _value;
};

/*
	��ʶ��
*/
class IdToken : public Token
{
public:
	IdToken(int line, const std::string& id);
	virtual std::string asString() const;
private:
	std::string _text;
};

/*
	�ַ���StrToken
*/
class StrToken : public Token
{
public:
	StrToken(int line, const std::string& str);
	virtual std::string asString() const;
private:
	std::string _literal;
};
NS_STONE_END
#endif