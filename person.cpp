#include "person.h"
#include"stringHelper.h"
using namespace std;
person::person()
{
	id = 0;
	name[0] = '\0';
	password[0] = '\0';
}
person::person(int id, const char* name, const char* password)
{
	this->id = id;
	StringHelper::copy(this->name, name);
	StringHelper::copy(this->password, password);
}
void person::setID(int id)
{
	this->id = id;
}
int person::getID()
{
	return id;
}
void person::setName(const char* name)
{
	StringHelper::copy(this->name, name);
}
const char* person::getName()
{
	return name;
}
void person::setPassword(const char* password)
{
	StringHelper::copy(this->password, password);
}
const char* person::getPassword()
{
	return password;
}

person::~person()
{

}
