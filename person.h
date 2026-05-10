#pragma once
#include<iostream>
class person
{
protected:
	int id;
	char name[50];
	char password[50];
public:
	person();
	person(int id, const char* name, const char* password);
	void setID(int id);
	int getID();
	void setName(const char* name);
	const char* getName();
	void setPassword(const char* password);
	const char* getPassword();
	virtual void display() const = 0;
	virtual void menu() = 0;
	~person();


};