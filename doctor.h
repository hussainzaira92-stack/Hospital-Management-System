#ifndef DOCTOR_H
#define DOCTOR_H
#include "person.h"
#include<iostream>
class doctor :public person
{
private:
	char spec[50];
	char contact[12];
	float fee;
public:
	doctor();
	doctor(int id, const char* name,  const char* spec, const char* contact, const char* password, float fee);
	void setSpec(const char* spec);
	const char* getSpec()const;
	void setContact(const char* conatct);
	const char* getContact()const;
	void setFee(float amount);
	int getID()const;
	float getFee()const;
	void display() const;
	const char* getName()const;
	const char* getPassword()const;
	void menu();
	bool operator==(const doctor& obj);
	friend std::ostream& operator<<(std::ostream& out, const doctor& obj);
};
#endif
