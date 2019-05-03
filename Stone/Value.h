#ifndef __Stone_Value_H__
#define __Stone_Value_H__

#include<string>
#include<cstring>
#include<vector>
#include<unordered_map>
#include<cstdlib>
#include<sstream>

#include "StoneMarcos.h"

NS_STONE_BEGIN

class Value;
class Function;

typedef std::vector<Value> ValueVector;
typedef std::unordered_map<std::string, Value> ValueMap;
typedef std::unordered_map<int, Value> ValueMapIntKey;

class Value
{
public:
	static const Value Null;
public:
	enum class Type
	{
		NONE = 0,
		BYTE,
		INTEGER,
		FLOAT,
		DOUBLE,
		BOOLEAN,
		STRING,
		FUNCTION,
		VECTOR,
		MAP,
		INT_KEY_MAP
	};
private:
	Type _type;
	union
	{
		unsigned char byteVal;
		int intVal;
		float floatVal;
		double doubleVal;
		bool boolVal;
		std::string* stringVal;
		Function* functionVal;
		ValueVector* vectorVal;
		ValueMap* mapVal;
		ValueMapIntKey* intKeyMapVal;
	}_field;
public:
	Value();
	explicit Value(unsigned char v);
	explicit Value(int v);
	explicit Value(float v);
	explicit Value(double v);
	explicit Value(bool v);
	explicit Value(const char* v);
	explicit Value(const std::string& v);
	explicit Value(Function* function);
	explicit Value(const ValueVector& v);
	explicit Value(const ValueMap& v);
	explicit Value(const ValueMapIntKey& v);
	//���ƹ��캯��
	Value(const Value& v);
	~Value();
	//����=�����
	Value& operator=(const Value& v);

	Value& operator=(unsigned char v);
	Value& operator=(int v);
	Value& operator=(float v);
	Value& operator=(double v);
	Value& operator=(bool v);
	Value& operator=(const char* v);
	Value& operator=(const std::string& v);
	Value& operator=(Function* func);
	Value& operator=(const ValueVector& v);
	Value& operator=(const ValueMap& v);
	Value& operator=(const ValueMapIntKey& v);
	// == !=
	bool operator==(const Value& v)const;
	bool operator!=(const Value& v);
	//
	unsigned char asByte()const;
	int asInt()const;
	float asFloat()const;
	double asDouble()const;
	bool asBool()const;
	std::string asString()const;
	Function* asFunction() const;
	ValueVector &asValueVector()const;
	ValueMap &asValueMap()const;
	ValueMapIntKey &asValueIntKey()const;
	//�Ƿ�Ϊ��
	bool isNull()const { return _type == Type::NONE; }
	Type getType()const { return _type; }
private:
	void clear();
	void reset(Type type);
};
NS_STONE_END
#endif