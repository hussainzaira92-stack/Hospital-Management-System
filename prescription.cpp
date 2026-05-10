#include "prescription.h"
#include"stringHelper.h"
#include <iostream>
using namespace std;
prescription::prescription() 
{

    prescriptionID = 0;
    appointmentID = 0;
    patientID = 0;
    doctorID = 0;
    date[0] = '\0';
    medicines[0] = '\0';
    notes[0] = '\0';
}
prescription::prescription(

    int id,

    int appointmentID,

    int patientID,

    int doctorID,

    const char* date,

    const char* medicines,

    const char* notes

) {

    this->prescriptionID = id;

    this->appointmentID =
        appointmentID;

    this->patientID =
        patientID;

    this->doctorID =
        doctorID;

    StringHelper::copy(
        this->date,
        date
    );

    StringHelper::copy(
        this->medicines,
        medicines
    );

    StringHelper::copy(
        this->notes,
        notes
    );
}

int prescription::getID() const
{
    return prescriptionID;
}

int prescription::getAppointmentID() const 
{
    return appointmentID;
}

int prescription::getPatientID() const 
{
    return patientID;
}

int prescription::getDoctorID() const 
{
    return doctorID;
}

const char* prescription::getDate() const 
{
    return date;
}

const char* prescription::getMedicines() const
{
    return medicines;
}

const char* prescription::getNotes() const 
{
    return notes;
}

ostream& operator<<(ostream& out,const prescription& obj) 
{
    out << "Prescription ID: " << obj.prescriptionID  << " | Appointment ID: "  << obj.appointmentID
        << " | Patient ID: " << obj.patientID << " | Doctor ID: "<< obj.doctorID
        << " | Date: "  << obj.date << " | Medicines: " << obj.medicines << " | Notes: "  << obj.notes;
    return out;
}