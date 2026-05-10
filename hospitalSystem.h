// ========================= HOSPITALSYSTEM.H =========================

#ifndef HOSPITALSYSTEM_H
#define HOSPITALSYSTEM_H

#include "storage.h"

#include "patient.h"
#include "doctor.h"
#include "admin.h"

#include "appointment.h"
#include "bill.h"
#include "prescription.h"

class HospitalSystem {

private:

    Storage<patient> patients;

    Storage<doctor> doctors;

    Storage<admin> admins;

    Storage<appointment> appointments;

    Storage<bill> bills;

    Storage<prescription> prescriptions;

public:

    HospitalSystem();

    void start();

    // MAIN MENU
    void mainMenu();
 
    // LOGIN
    void logSecurityAttempt(
        const char* role,
        int id
    );
    patient* patientLogin();

    doctor* doctorLogin();


    admin* adminLogin();
    //getters
    Storage<patient>& getPatients();
    Storage<admin>& getAdmins();

    Storage<doctor>& getDoctors();

    Storage<appointment>& getAppointments();

    Storage<bill>& getBills();

    Storage<prescription>& getPrescriptions();

    // MENUS
    void patientMenu(patient*);

    void doctorMenu(doctor*);

    void adminMenu(admin*);

    // PATIENT FUNCTIONS
    void topUpBalance(patient*);

    void viewAppointments(patient*);
    void bookAppointment(
        patient*
    );

    void cancelAppointment(
        patient*
    );

    void viewMedicalRecords(
        patient*
    );

    void viewBills(
        patient*
    );

    void payBill(
        patient*
    );

    // DOCTOR FUNCTIONS
    void viewTodayAppointments(doctor*);
    void markAppointmentComplete(
        doctor*
    );

    void markAppointmentNoShow(
        doctor*
    );

    void writePrescription(
        doctor*
    );

    void viewPatientHistory(
        doctor*
    );

    // ADMIN FUNCTIONS
    void addDoctor();

    void removeDoctor();

    void addPatient();

    void removePatient();

    void viewUnpaidBills();

    void dischargePatient();

    void viewSecurityLog();

    void generateDailyReport();

    void viewAllPatients();

    void viewAllDoctors();

    void viewAllAppointments();
};

#endif
