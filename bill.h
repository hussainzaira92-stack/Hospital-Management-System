#ifndef BILL_H
#define BILL_H
#include <iostream>
class bill
{
private:
    int billID;
    int patientID;
    int appointmentID;
    float amount;
    char status[20];
    char date[11];
public:
    bill();
    bill(int bID, int pID, int aID,float am,  const char* status,  const char* date);
    int getID() const;
    int getPatientID() const;
    int getAppointmentID() const;
    float getAmount() const;
    const char* getStatus() const;
    const char* getDate() const;
    void setStatus(const char*);
    friend std::ostream& operator<<(std::ostream&, const bill&);
};

#endif
