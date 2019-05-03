#include <fstream>
#include <iostream>
#include <string>

#include "Token.h"
#include "Environment.h"
#include "STAutoreleasePool.h"
#include "StoneState.h"

using namespace std;
USING_NS_STONE;

std::unique_ptr<char> getUniqueDataFromFile(const std::string& filename);
Value print(Environment* env);

int main() {
	auto uniquePtr = std::move(getUniqueDataFromFile("1.txt"));
	if (uniquePtr == nullptr)
	{
		cout << "文件打开失败" << endl;
		return 1;
	}
	StoneState* stone = new StoneState();
	stone->init(uniquePtr.get());
	uniquePtr.reset();
	//加入方法
	const char* params[] = { "value" };
	stone->putNative("print", print, params, 1);

	while (stone->hasNext())
	{
		/*Value* value = stone->execute();
		if (value != nullptr)
			cout << value->asString() << endl;
			*/
		stone->execute();
	}

	delete stone;
	AutoreleasePool::purge();
	delete Token::TOKEN_EOF;

	return 0;
}

std::unique_ptr<char> getUniqueDataFromFile(const std::string& filename) 
{
	std::unique_ptr<char> points;
	std::ifstream in;
	in.open(filename);

	//打开文件失败
	if (!in.is_open()) {
		return points;
	}
	//定位到文件的末尾
	in.seekg(0, std::ios::end);
	//获取总长度
	int size = (int)in.tellg();

	char* buffer = new char[size + 1];
	memset(buffer, '\0', size + 1);
	
	//读取
	in.seekg(0, std::ios::beg);
	in.read(buffer, size);
	//关闭文件
	in.close();

	points = std::unique_ptr<char>(buffer);
	return points;
}

Value print(Environment* env)
{
	//获取参数
	const Value* value = env->get("value");
	std::cout << value->asString() << std::endl;

	return *value;
}
