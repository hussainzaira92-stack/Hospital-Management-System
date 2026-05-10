#include "fileHandler.h"
#include <fstream>
#include <iostream>
#include <cstring>
void FileHandler::loadPatients(  Storage<patient>& patients) 
{
    std::ifstream file("patients.txt");
    if (!file)
    {
        std::cout << "patients.txt not found.\n";
        return;
    } 
    int id, age;
    char name[50];
    char gender;
    char contact[12];
    char password[50];
    float balance;
    while (file >> id) 
    {
        file.ignore();
        file.getline(name, 50, ',');
        file >> age;
        file.ignore();
        file >> gender;
        file.ignore();
        file.getline(contact, 12, ',');
        file.getline(password, 50, ',');
        file >> balance;
        file.ignore();
        patient p(id, name, password, age, gender, contact, balance);
        patients.add(p);
    }
    file.close();
}
void FileHandler::loadDoctors( Storage<doctor>& doctors) 
{
    std::ifstream file("doctors.txt");
    if (!file) 
    {
        std::cout << "doctors.txt not found.\n";
        return;
    }
    int id;
    char name[50];
    char specialization[50];
    char contact[12];
    char password[50];
    float fee;
    while (file >> id) 
    {

        file.ignore();
        file.getline(name, 50, ',');
        file.getline(specialization, 50, ',');
        file.getline(contact, 12, ',');
        file.getline(password, 50, ',');
        file >> fee;
        file.ignore();
        doctor d(id, name, specialization, contact,password,fee);
        doctors.add(d);
    }
    file.close();
}
void FileHandler::loadAdmins( Storage<admin>& admins)
{
    std::ifstream file("admin.txt");
    if (!file) 
    {
        std::cout << "admin.txt not found.\n";
        return;
    }
    int id;
    char name[50];
    char password[50];
    while (file >> id) 
    {

        file.ignore();
        file.getline(name, 50, ',');
        file.getline(password, 50);
        admin a(id, name, password);
        admins.add(a);
    }
    file.close();
}
void FileHandler::loadAppointments(Storage<appointment>& appointments) 
{
    std::ifstream file("appointments.txt");
    if (!file) 
    {
        std::cout << "appointments.txt not found.\n";
        return;
    }
    int appID;
    int patientID;
    int doctorID;
    char date[11];
    char timeSlot[6];
    char status[20];
    while (file >> appID)
    {
        file.ignore();
        file >> patientID;
        file.ignore();
        file >> doctorID;
        file.ignore();
        file.getline(date, 11, ',');
        file.getline(timeSlot, 6, ',');
        file.getline(status, 20);
        appointment a(appID, patientID, doctorID,   date, timeSlot,  status);
        appointments.add(a);
    }
    file.close();
}
void FileHandler::loadBills( Storage<bill>& bills) 
{
    std::ifstream file("bills.txt");
    if (!file)
    {
        std::cout << "bills.txt not found.\n";
        return;
    }
    int billID;
    int patientID;
    int appointmentID;
    float amount;
    char status[20];
    char date[11];
    while (file >> billID) 
    {
        file.ignore();
        file >> patientID;
        file.ignore();
        file >> appointmentID;
        file.ignore();
        file >> amount;
        file.ignore();
        file.getline(status, 20, ',');
        file.getline(date, 11);
        bill b(billID,  patientID,  appointmentID,  amount,status,  date);
        bills.add(b);
    }
    file.close();
}
void FileHandler::loadPrescriptions( Storage<prescription>& prescriptions) 
{
    std::ifstream file("prescriptions.txt");
    if (!file)
    {
        std::cout << "prescriptions.txt not found.\n";
        return;
    }
    int presID;
    int appID;
    int patientID;
    int doctorID;
    char date[11];
    char medicines[500];
    char notes[300];
    while (file >> presID) 
    {
        file.ignore();
        file >> appID;
        file.ignore();
        file >> patientID;
        file.ignore();
        file >> doctorID;
        file.ignore();
        file.getline(date, 11, ',');
        file.getline(medicines, 500, ',');
        file.getline(notes, 300);
        prescription p(presID, appID, patientID,doctorID,  date,  medicines, notes);
        prescriptions.add(p);
    }
    file.close();
}
void FileHandler::appendPatient( const patient& p) 
{
    std::ofstream file( "patients.txt", std::ios::app);
    file << p.getID() << ","
        << p.getName() << ","
        << p.getAge() << ","
        << p.getGender() << ","
        << p.getMobile() << ","
        << p.getPassword() << ","
        << p.getBalance()
        << "\n";
    file.close();
}
void FileHandler::appendDoctor(
    const doctor& d) {

    std::ofstream file(
        "doctors.txt",
        std::ios::app
    );

    file << d.getID() << ","
        << d.getName() << ","
        << d.getSpec() << ","
        << d.getContact() << ","
        << d.getPassword() << ","
        << d.getFee()
        << "\n";

    file.close();
}
void FileHandler::appendBill(  const bill& b) 
{

    std::ofstream file(
        "bills.txt",
        std::ios::app
    );

    file << b.getID() << ","
        << b.getPatientID() << ","
        << b.getAppointmentID() << ","
        << b.getAmount() << ","
        << b.getStatus() << ","
        << b.getDate()
        << "\n";

    file.close();
}
void FileHandler::appendPrescription( const prescription& p) 
{

    std::ofstream file(
        "prescriptions.txt",
        std::ios::app
    );

    file << p.getID() << ","
        << p.getAppointmentID() << ","
        << p.getPatientID() << ","
        << p.getDoctorID() << ","
        << p.getDate() << ","
        << p.getMedicines() << ","
        << p.getNotes()
        << "\n";

    file.close();
}
void FileHandler::appendAppointment(
    const appointment& a) 
{
    std::ofstream file( "appointments.txt", std::ios::app);
    file << a.getID() << ","
        << a.getPatientID() << ","
        << a.getDoctorID() << ","
        << a.getDate() << ","
        << a.getTimeSlot() << ","
        << a.getStatus()
        << "\n";

    file.close();
}
void FileHandler::updatePatients(
    const Storage<patient>& patients) 
{
    std::ofstream file("patients.txt");
    const  patient* data = patients.getAll();
    for (int i = 0; i < patients.size(); i++) 
    {

        file << data[i].getID() << ","
            << data[i].getName() << ","
            << data[i].getAge() << ","
            << data[i].getGender() << ","
            << data[i].getMobile() << ","
            << data[i].getPassword() << ","
            << data[i].getBalance()
            << "\n";
    }

    file.close();
}
void FileHandler::updateDoctors(  const Storage<doctor>& doctors) 
{

    std::ofstream file("doctors.txt");

    const doctor* data = doctors.getAll();

    for (int i = 0; i < doctors.size(); i++)
    {

        file << data[i].getID() << ","
            << data[i].getName() << ","
            << data[i].getSpec() << ","
            << data[i].getContact() << ","
            << data[i].getPassword() << ","
            << data[i].getFee()
            << "\n";
    }

    file.close();
}
void FileHandler::updateAppointments(
    const Storage<appointment>& appointments) 
{

    std::ofstream file("appointments.txt");

    const appointment* data =
        appointments.getAll();

    for (int i = 0; i < appointments.size(); i++) {

        file << data[i].getID() << ","
            << data[i].getPatientID() << ","
            << data[i].getDoctorID() << ","
            << data[i].getDate() << ","
            << data[i].getTimeSlot() << ","
            << data[i].getStatus()
            << "\n";
    }

    file.close();
}

void FileHandler::updateBills(
    const Storage<bill>& bills) {

    std::ofstream file("bills.txt");

    const bill* data = bills.getAll();

    for (int i = 0; i < bills.size(); i++) {

        file << data[i].getID() << ","
            << data[i].getPatientID() << ","
            << data[i].getAppointmentID() << ","
            << data[i].getAmount() << ","
            << data[i].getStatus() << ","
            << data[i].getDate()
            << "\n";
    }

    file.close();
}
void FileHandler::updatePrescriptions(
    const Storage<prescription>& prescriptions) {

    std::ofstream file("prescriptions.txt");

    const prescription* data =
        prescriptions.getAll();

    for (int i = 0; i < prescriptions.size(); i++) {

        file << data[i].getID() << ","
            << data[i].getAppointmentID() << ","
            << data[i].getPatientID() << ","
            << data[i].getDoctorID() << ","
            << data[i].getDate() << ","
            << data[i].getMedicines() << ","
            << data[i].getNotes()
            << "\n";
    }

    file.close();
}

void FileHandler::deletePatient( int id, Storage<patient>& patients, Storage<appointment>& appointments, Storage<bill>& bills, Storage<prescription>& prescriptions) {

    // REMOVE PATIENT

    patients.removeByID(id);

    // REMOVE RELATED APPOINTMENTS

    for (int i = 0;
        i < appointments.size();
        i++) {

        if (

            appointments
            .getAll()[i]
            .getPatientID()

            == id
            ) {

            appointments.removeByID(

                appointments
                .getAll()[i]
                .getID()
            );

            i--;
        }
    }

    // REMOVE RELATED BILLS

    for (int i = 0;
        i < bills.size();
        i++) {

        if (

            bills
            .getAll()[i]
            .getPatientID()

            == id
            ) {

            bills.removeByID(

                bills
                .getAll()[i]
                .getID()
            );

            i--;
        }
    }

    // REMOVE PRESCRIPTIONS

    for (int i = 0;
        i < prescriptions.size();
        i++) {

        if (

            prescriptions
            .getAll()[i]
            .getPatientID()

            == id
            ) {

            prescriptions.removeByID(

                prescriptions
                .getAll()[i]
                .getID()
            );

            i--;
        }
    }

    // UPDATE FILES

    updatePatients(patients);

    updateAppointments(
        appointments
    );

    updateBills(bills);

    updatePrescriptions(
        prescriptions
    );
}
void FileHandler::deleteDoctor(  int id, Storage<doctor>& doctors) 
{

    doctors.removeByID(id);

    updateDoctors(doctors);
}
void FileHandler::deleteAppointment(
    int id,
    Storage<appointment>& appointments) {

    appointments.removeByID(id);

    updateAppointments(appointments);
}

void FileHandler::deleteBill(
    int id,
    Storage<bill>& bills) {

    bills.removeByID(id);

    updateBills(bills);
}

void FileHandler::deletePrescription(
    int id,
    Storage<prescription>& prescriptions) {

    prescriptions.removeByID(id);

    updatePrescriptions(prescriptions);
}
void FileHandler::dischargePatient(
    int patientID, Storage<patient>& patients, Storage<appointment>& appointments, Storage<bill>& bills, Storage<prescription>& prescriptions)
{
    patients.removeByID(patientID);
    for (int i = 0; i < appointments.size(); i++) 
    {

        if (appointments.getAll()[i]
            .getPatientID() == patientID) 
        {

            appointments.removeByID(
                appointments.getAll()[i].getID()
            );

            i--;
        }
    }
    for (int i = 0; i < bills.size(); i++) 
    {

        if (bills.getAll()[i]
            .getPatientID() == patientID)
        {

            bills.removeByID(
                bills.getAll()[i].getID()
            );

            i--;
        }
    }
    for (int i = 0; i < prescriptions.size(); i++) 
    {

        if (prescriptions.getAll()[i]
            .getPatientID() == patientID)
        {

            prescriptions.removeByID(
                prescriptions.getAll()[i].getID()
            );

            i--;
        }
    }
    updatePatients(patients);

    updateAppointments(appointments);

    updateBills(bills);

    updatePrescriptions(prescriptions);
}