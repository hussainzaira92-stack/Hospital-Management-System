#include "doctor.h"
#include"stringHelper.h"
using namespace std;
doctor::doctor():person()
{
	spec[0] = '\0';
	contact[0] = '\0';
	fee = 0.0;
}

doctor::doctor(int id, const char* name,  const char* spec, const char* contact, const char* password, float fee) :person(id, name, password)
{
	StringHelper::copy(this->spec, spec);
	StringHelper::copy(this->contact, contact);
	this->fee = fee;
}
int doctor::getID()const
{
	return id;
}
void doctor::setSpec(const char* spec)
{
	StringHelper::copy(this->spec, spec);
}
const char* doctor::getSpec()const
{
	return spec;
}
void doctor::setContact(const char* conatct)
{
	StringHelper::copy(this->contact, contact);
}
const char* doctor::getContact()const
{
	return contact;
}
void doctor:: setFee(float amount)
{
	this->fee = amount;
}
float doctor::getFee()const 
{
	return fee;
}

const char* doctor::getName()const
{
	return name;
}
const char* doctor::getPassword()const
{
	return password;
}
void doctor::menu()
{
	cout << "\n======DOCTOR'S MENU======" << endl;
}
bool doctor::operator==(const doctor& obj)
{
	return this->id == obj.id;
}
void doctor::display() const {

    std::cout
        << "Doctor ID: "
        << id
        << " | Name: "
        << name
        << " | Specialization: "
        << spec
        << " | Fee: "
        << fee;
}

std::ostream& operator<<(
    std::ostream& out,
    const doctor& d
    ) {

    out
        << "Doctor ID: "
        << d.id
        << " | Name: "
        << d.name
        << " | Specialization: "
        << d.spec
        << " | Fee: "
        << d.fee;

    return out;
}