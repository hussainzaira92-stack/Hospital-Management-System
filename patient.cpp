#include"patient.h"
#include"stringHelper.h"
using namespace std;



	patient::patient():person()
	{
		
		this->age = 0;
		this->gender = '0';
		mobile[0] = '\0';
		balance = 0;

	}
	patient::patient(int id, const char* name,  const char* password, int age, char gender, const char* mobile, float balance):person(id, name,password)
	{
		this->age = age;
		this-> gender = gender;
		StringHelper::copy(this->mobile, mobile);
		this->balance = balance;
	}
	void patient::display()const
	{
		cout << "\n======PATIENT DETAILS======" << endl;
		cout << "Patient: " << name << endl << "ID: " << id << endl << "Gender: " << gender << endl << "Mobile: " << mobile << endl << "Balance: " << balance << endl;
	}
	void patient::addBalance(
		float amount
	) {

		balance += amount;
	}
	void patient::menu()
	{

		cout << "\n========PATINET MENU========" << endl;
		
	}
	void patient::deductBalance(
		float amount
	) {

		if (amount <= balance) {

			balance -= amount;
		}
	}
	float patient::getBalance() const
	{
		return balance;
	}
	void patient::operator+=(float amount)
	{
		balance = balance + amount;
	}
	int patient::getID()const
	{
		return id;
	}
	int  patient::getAge()const
	{
		return age;
	}
	const char* patient:: getName() const
	{
		return name;
	}
	const char* patient::getPassword()const
	{
		return password;
	}
	char patient::getGender()const
	{
		return gender;
	}
	const char* patient::getMobile()const
	{
		return mobile;
	}
	void patient::operator-=(float amount)
	{
		balance = balance - amount;
	}
	bool patient:: operator==(const patient& obj)
	{
		return this->id == obj.id;
	}
	ostream& operator<<(ostream& out, const patient& obj)
	{
		out << "ID: " << obj.id << ", Name: " << obj.name
			<< ", Balance: " << obj.balance;
		return out;
	}



