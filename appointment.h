#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include<iostream>
#include"person.h"
class appointment 
{

    private:
        int appointmentID;
        int patientID;
        int doctorID;
        char date[11];      
        char time[6];   
        char status[20];

    public:
        appointment();
        appointment(int pId, int dId, int aId, const char* date, const char* time, const char* status);
        int getID() const;
        int getPatientID() const;
        int getDoctorID() const;
        const char* getDate() const;
        const char* getTimeSlot() const;
        const char* getStatus() const;
        void setStatus(const char*);
        bool operator==(const appointment&) const;
        friend std::ostream& operator<<(std::ostream&, const appointment&);
    };

#endif

