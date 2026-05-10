#include<iostream>
#include<cstring>
using namespace std;
#include"appointment.h"
#include"stringHelper.h"
appointment::appointment()
{
	patientID = 0;
		doctorID = 0;
		appointmentID = 0;
		time[0] = '\0';
		status[0] = '\0';
		date[0] = '\0';
}
appointment::appointment(int aId, int pId, int dId, const char* date, const char* time, const char* status)
{
	patientID = pId;
	doctorID = dId;
	appointmentID = aId;
	StringHelper::copy(this->time, time);
	StringHelper::copy(this->date, date);
StringHelper::copy(this->status, status);
}

int appointment::getID() const 
{
	return appointmentID;
}

int appointment::getPatientID() const
{
	return patientID;
}

int appointment::getDoctorID() const 
{
	return doctorID;
}

const char* appointment::getDate() const
{
	return date;
}

const char* appointment::getTimeSlot() const 
{
	return time;
}

const char* appointment::getStatus() const 
{
	return status;
}

void appointment::setStatus(const char* s) 
{
	StringHelper::copy(status, s);
}
bool appointment::operator==(const appointment& obj) const
{
	if(StringHelper::compare(status, "cancelled") == 0 ||StringHelper::compare(obj.status, "cancelled") == 0) 
		return false;
	bool flag = (doctorID == obj.doctorID && StringHelper::compare(date, obj.date) == 0 && StringHelper::compare(time, obj.time) == 0);
	return flag;
}
ostream& operator<<(std::ostream& out,const appointment& obj) 
{

	out << "Appointment ID: "<< obj.appointmentID<< " | Patient ID: "	<< obj.patientID<< " | Doctor ID: "<< obj.doctorID
		<< " | Date: "<< obj.date<< " | Time: "<< obj.time<< " | Status: "<< obj.status;
	return out;
}
