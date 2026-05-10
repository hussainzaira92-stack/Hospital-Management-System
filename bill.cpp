#include "bill.h"
#include<iostream>
#include"stringHelper.h"
using namespace std;

bill::bill() 
{
    billID = 0;
    patientID = 0;
    appointmentID = 0;
    amount = 0;
    status[0] = '\0';
    date[0] = '\0';
}

bill::bill(int bID, int pID,  int aID, float am, const char* s,  const char* d ) 
{
    billID = bID;
    patientID = pID;
    appointmentID = aID;
    amount = am;
    StringHelper::copy(status, s);
    StringHelper::copy(date, d);

}

int bill::getID() const
{
    return billID;
}

int bill::getPatientID() const 
{
    return patientID;
}

int bill::getAppointmentID() const
{
    return appointmentID;
}

float bill::getAmount() const
{
    return amount;
}

const char* bill::getStatus() const
{
    return status;
}

const char* bill::getDate() const
{
    return date;
}

void bill::setStatus(const char* s) 
{
    StringHelper::copy(status, s);
}

ostream& operator<<(ostream& out, const bill& obj)
{

    out << "Bill ID: " << obj.billID
        << " | Patient ID: " << obj.patientID
        << " | Appointment ID: " << obj.appointmentID
        << " | Amount: PKR " << obj.amount
        << " | Status: " << obj.status
        << " | Date: " << obj.date;
    return out;
}