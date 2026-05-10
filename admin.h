#ifndef ADMIN_H
#define ADMIN_H
#include<iostream>
#include "person.h"
class admin: public person
{public:
	admin();
	admin(int id, const char* name, const char* password);
	void display() const;
	void menu();
	int getID();
	friend std::ostream& operator<<(std::ostream&, const admin&);

};
#endif
