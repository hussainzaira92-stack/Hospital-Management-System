
#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "Storage.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
class FileHandler 
{
public:
    static void loadPatients(Storage<patient>&);
    static void loadDoctors(Storage<doctor>&);
    static void loadAdmins(Storage<admin>&);
    static void loadAppointments(Storage<appointment>&);
    static void loadBills(Storage<bill>&);
    static void loadPrescriptions(Storage<prescription>&);
    static void appendPatient(const patient&);
    static void appendDoctor(const doctor&);
    static void appendAppointment(const appointment&);
    static void appendBill(const bill&);
    static void appendPrescription(const prescription&);
    static void updatePatients(const Storage<patient>&);
    static void updateDoctors(const Storage<doctor>&);
    static void updateAppointments( const Storage<appointment>&);
    static void updateBills(const Storage<bill>&);
    static void updatePrescriptions( const Storage<prescription>&);
    static void deletePatient(int, Storage<patient>&, Storage<appointment>&, Storage<bill>&, Storage<prescription>&);
    static void deleteDoctor(  int, Storage<doctor>&);
    static void deleteAppointment( int,Storage<appointment>&);
    static void deleteBill( int,  Storage<bill>&);
    static void deletePrescription( int,Storage<prescription>&);
    static void dischargePatient(int patientID, Storage<patient>&, Storage<appointment>&, Storage<bill>&, Storage<prescription>&);
    
};

#endif
