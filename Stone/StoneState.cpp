#include "StoneState.h"
#include "Lexer.h"
#include "NestedEnv.h"
#include "EvalVisitor.h"
#include "ArrayParser.h"
#include "STAutoreleasePool.h"
#include "Token.h"
#include "ASTree.h"
#include "ParseException.h"
#include "StoneException.h"
#include "NullStmnt.h"

NS_STONE_BEGIN

StoneState::StoneState()
	:_lexer(nullptr)
	,_environment(nullptr)
	,_visitor(nullptr)
	,_parser(nullptr)
{
}

StoneState::~StoneState()
{
	delete _parser;
	delete _visitor;
	delete _environment;
	delete _lexer;

	AutoreleasePool::getInstance()->clear();
}

bool StoneState::init(const char* text)
{
	_lexer = new Lexer(text);
	_environment = new NestedEnv();
	_visitor = new EvalVisitor();
	_parser = new ArrayParser();

	return true;
}

Value* StoneState::execute()
{
	try 
	{
		ASTree* t = _parser->parse(_lexer);
		//����NullStmnt,������nullptr
		if (t->getTreeID() == NullStmnt::TREE_ID)
		{
			return nullptr;
		}
		t->accept(_visitor, _environment);
	}
	catch (ParseException& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (StoneException& e)
	{
		std::cout << e.what() << std::endl;
	}
	//����Ҫ�ֶ��ͷ��ڴ�
	AutoreleasePool::getInstance()->clear();

	return _visitor->result;
}

bool StoneState::hasNext()
{
	return _lexer->peek(0) != Token::TOKEN_EOF;
}

void StoneState::putNative(const std::string& name, const nativeFunc& callback, const char** params, int len)
{
	_environment->putNative(name, callback, params, len);
}
NS_STONE_END