#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H
#include <iostream>
class prescription 
{
private:
    int prescriptionID;
    int appointmentID;
    int patientID;
    int doctorID;
    char date[11];
    char medicines[500];
    char notes[300];

public:
    prescription();
    prescription(int, int, int, int,  const char*, const char*,   const char*);
    int getID() const;
    int getAppointmentID() const;
    int getPatientID() const;
    int getDoctorID() const;
    const char* getDate() const;
    const char* getMedicines() const;
    const char* getNotes() const;
    friend std::ostream& operator<<(std::ostream&,  const prescription&);
};

#endif