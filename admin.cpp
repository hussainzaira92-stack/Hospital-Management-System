#include<iostream>
#include "admin.h";
using namespace std;
admin::admin() :person() {};
admin::admin(int id, const char* name, const char* password) :person(id, name, password) {};
void admin::display() const
{
	cout << "\n======ADMIN DETAILS======" << endl;
	cout << "Name: " << name << endl << "ID: " << id << endl;
}
int admin::getID()
{
    return id;
}
void admin::menu() 
{
   cout << "\nAdmin Panel — MediCore\n";
    cout << "1. Add Doctor\n";
   cout << "2. Remove Doctor\n";
   cout << "3. View All Patients\n";
    cout << "4. View All Doctors\n";
  cout << "5. View All Appointments\n";
    cout << "6. View Unpaid Bills\n";
   cout << "7. Discharge Patient\n";
    cout << "8. View Security Log\n";
  cout << "9. Generate Daily Report\n";
  cout << "10. Logout\n";
}
ostream& operator<<(ostream& out, const admin& obj)
{
    out << "Admin ID: " << obj.id
        << ", Name: " << obj.name;
    return out;
}
