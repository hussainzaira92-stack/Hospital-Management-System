#ifndef PATIENT_H
#define PATIENT_H
#include"person.h"
#include<iostream>
class patient:public person
{
protected:
	
	int age;
	char gender;
	char mobile[12];
	float balance;
public:
	patient();
	patient(int id, const char* name,  const char* password, int age, char gender, const char* mobile, float balance);
	void display()const;
	int getID()const;
	void deductBalance(float);
	void addBalance(float);
	int getAge()const;
	const char* getName() const;
	const char* getPassword()const;
	char getGender()const;
	const char* getMobile() const;
	float getBalance() const;
	/*void display()const;*/
	void menu() ;
	void operator+=(float amount);
	void operator-=(float amount);
	bool operator==(const patient& obj);
	friend std::ostream& operator<<(std::ostream&, const patient&obj );

};
#endif

