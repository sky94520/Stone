#include "NullStmnt.h"

NS_STONE_BEGIN
const std::string NullStmnt::TREE_ID = "NullStmnt";
NullStmnt::NullStmnt()
{
	ASTree::init(TREE_ID);
}
NS_STONE_END