#ifndef __Stone_StoneState_H__
#define __Stone_StoneState_H__

#include <string>
#include <iostream>

#include "StoneMarcos.h"
#include "Value.h"
#include "Environment.h"

NS_STONE_BEGIN

class Lexer;
class NestedEnv;
class EvalVisitor;
class ArrayParser;

class StoneState
{
public:
	StoneState();
	~StoneState();

	bool init(const char* text);
	//ִ�нű���䣬������ֵ
	Value* execute();
	//�Ƿ񻹴������
	bool hasNext();

	void putNative(const std::string& name, const nativeFunc& callback, const char** params, int len);
private:
	Lexer* _lexer;
	NestedEnv* _environment;
	EvalVisitor* _visitor;
	ArrayParser* _parser;
};
NS_STONE_END
#endif