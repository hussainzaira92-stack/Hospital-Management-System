
#include "hospitalSystem.h"
#include "fileHandler.h"
#include "validator.h"
#include <iostream>
#include"stringHelper.h"
#include <fstream>
#include<cstring>
// ========================= CONSTRUCTOR =========================

HospitalSystem::HospitalSystem() {

    FileHandler::loadPatients(patients);

    FileHandler::loadDoctors(doctors);

    FileHandler::loadAdmins(admins);

    FileHandler::loadAppointments(
        appointments);

    FileHandler::loadBills(bills);

    FileHandler::loadPrescriptions(
        prescriptions);
}

// ========================= START =========================

void HospitalSystem::start() 
{

    mainMenu();
}

// ========================= MAIN MENU =========================

void HospitalSystem::mainMenu()
{

    int choice;

    while (true) {

        std::cout
            << "\n===== MediCore Hospital =====\n";

        std::cout
            << "1. Patient\n";

        std::cout
            << "2. Doctor\n";

        std::cout
            << "3. Admin\n";

        std::cout
            << "4. Exit\n";

        std::cout
            << "Enter choice: ";

        std::cin >> choice;

        switch (choice) {

        case 1: {

            patient* p = patientLogin();

            if (p != nullptr) {

                patientMenu(p);
            }

            break;
        }

        case 2: {

            doctor* d = doctorLogin();

            if (d != nullptr) {

                doctorMenu(d);
            }

            break;
        }

        case 3: {

            admin* a = adminLogin();

            if (a != nullptr) {

                adminMenu(a);
            }

            break;
        }

        case 4:

            return;

        default:

            std::cout
                << "Invalid choice.\n";
        }
    }
}
void HospitalSystem::logSecurityAttempt(
    const char* role,
    int id
) {

    std::ofstream file(
        "security_log.txt",
        std::ios::app
    );

    file << "LOCKED ACCOUNT -> ";

    file << "Role: "
        << role
        << " | ID: "
        << id
        << "\n";

    file.close();
}

// ========================= PATIENT LOGIN =========================

patient* HospitalSystem::patientLogin() {

    int attempts = 0;

    while (attempts < 3) {

        int id;

        char password[50];

        std::cout
            << "\nEnter Patient ID: ";

        std::cin >> id;

        std::cout
            << "Enter Password: ";

        std::cin >> password;

        patient* p =
            patients.findByID(id);

        if (p != nullptr &&
            StringHelper::compare(
                p->getPassword(),
                password
            )) {

            return p;
        }

        attempts++;

        std::cout
            << "Invalid login.\n";

        std::cout
            << "Attempts left: "
            << 3 - attempts
            << "\n";
    }

    std::cout
        << "\nAccount locked. Contact admin.\n";

    logSecurityAttempt(
        "Patient",
        -1
    );

    return nullptr;
}
// ========================= DOCTOR LOGIN =========================

doctor* HospitalSystem::doctorLogin() {

    int attempts = 0;

    while (attempts < 3) {

        int id;

        char password[50];

        std::cout
            << "\nEnter Doctor ID: ";

        std::cin >> id;

        std::cout
            << "Enter Password: ";

        std::cin >> password;

        doctor* d =
            doctors.findByID(id);

        if (d != nullptr &&
            StringHelper::compare(
                d->getPassword(),
                password
            )) {

            return d;
        }

        attempts++;

        std::cout
            << "Invalid login.\n";

        std::cout
            << "Attempts left: "
            << 3 - attempts
            << "\n";
    }

    std::cout
        << "\nAccount locked. Contact admin.\n";

    logSecurityAttempt(
        "Doctor",
        -1
    );

    return nullptr;
}

// ========================= ADMIN LOGIN =========================
admin* HospitalSystem::adminLogin() {

    int attempts = 0;

    while (attempts < 3) {

        int id;

        char password[50];

        std::cout
            << "\nEnter Admin ID: ";

        std::cin >> id;

        std::cout
            << "Enter Password: ";

        std::cin >> password;

        admin* a =
            admins.findByID(id);

        if (a != nullptr &&
            StringHelper::compare(
                a->getPassword(),
                password
            )) {

            return a;
        }

        attempts++;

        std::cout
            << "Invalid login.\n";

        std::cout
            << "Attempts left: "
            << 3 - attempts
            << "\n";
    }

    std::cout
        << "\nAccount locked. Contact admin.\n";

    logSecurityAttempt(
        "Admin",
        -1
    );

    return nullptr;
}

// ========================= PATIENT MENU =========================

void HospitalSystem::patientMenu(
    patient* patient
) {

    int choice;

    while (true) {

        std::cout
            << "\nWelcome, "
            << patient->getName()
            << "\n";

        std::cout
            << "Balance: PKR "
            << patient->getBalance()
            << "\n";

        std::cout
            << "========================\n";

        std::cout
            << "1. Book Appointment\n";

        std::cout
            << "2. Cancel Appointment\n";

        std::cout
            << "3. View My Appointments\n";

        std::cout
            << "4. View My Medical Records\n";

        std::cout
            << "5. View My Bills\n";

        std::cout
            << "6. Pay Bill\n";

        std::cout
            << "7. Top Up Balance\n";

        std::cout
            << "8. Logout\n";

        std::cout
            << "Enter choice: ";

        std::cin >> choice;

        switch (choice) {

        case 1:

            bookAppointment(
                patient
            );

            break;

        case 2:

            cancelAppointment(
                patient
            );

            break;

        case 3:

            viewAppointments(
                patient
            );

            break;

        case 4:

            viewMedicalRecords(
                patient
            );

            break;

        case 5:

            viewBills(
                patient
            );

            break;

        case 6:

            payBill(
                patient
            );

            break;

        case 7:

            topUpBalance(
                patient
            );

            break;

        case 8:

            return;

        default:

            std::cout
                << "Invalid choice.\n";
        }
    }
}

// ========================= DOCTOR MENU =========================

void HospitalSystem::doctorMenu(
    doctor* doctor
) {

    int choice;

    while (true) {

        std::cout
            << "\nWelcome, Dr. "
            << doctor->getName();

        std::cout
            << " | Specialization: "
            << doctor->getSpec()
            << "\n";

        std::cout
            << "====================================\n";

        std::cout
            << "1. View  Appointments\n";

        std::cout
            << "2. Mark Appointment Complete\n";

        std::cout
            << "3. Mark Appointment No-Show\n";

        std::cout
            << "4. Write Prescription\n";

        std::cout
            << "5. View Patient Medical History\n";

        std::cout
            << "6. Logout\n";

        std::cout
            << "Enter choice: ";

        std::cin >> choice;

        switch (choice) {

        case 1:

            viewTodayAppointments(
                doctor
            );

            break;

        case 2:

            markAppointmentComplete(
                doctor
            );

            break;

        case 3:

            markAppointmentNoShow(
                doctor
            );

            break;

        case 4:

            writePrescription(
                doctor
            );

            break;

        case 5:

            viewPatientHistory(
                doctor
            );

            break;

        case 6:

            return;

        default:

            std::cout
                << "Invalid choice.\n";
        }
    }
}
// ========================= ADMIN MENU =========================

void HospitalSystem::adminMenu(
    admin* admin
) {

    int choice;

    while (true) {

        std::cout
            << "\nAdmin Panel — MediCore\n";

        std::cout
            << "======================\n";

        std::cout
            << "1. Add Doctor\n";

        std::cout
            << "2. Remove Doctor\n";

        std::cout
            << "3. Add Patient\n";

        std::cout
            << "4. Remove Patient\n";

        std::cout
            << "5. View All Patients\n";

        std::cout
            << "6. View All Doctors\n";

        std::cout
            << "7. View All Appointments\n";

        std::cout
            << "8. View Unpaid Bills\n";

        std::cout
            << "9. Discharge Patient\n";

        std::cout
            << "10. View Security Log\n";

        std::cout
            << "11. Generate Daily Report\n";

        std::cout
            << "12. Logout\n";

        std::cout
            << "Enter choice: ";

        std::cin >> choice;

        switch (choice) {

        case 1:

            addDoctor();

            break;

        case 2:

            removeDoctor();

            break;

        case 3:

            addPatient();

            break;

        case 4:

            removePatient();

            break;

        case 5:

            viewAllPatients();

            break;

        case 6:

            viewAllDoctors();

            break;

        case 7:

            viewAllAppointments();

            break;

        case 8:

            viewUnpaidBills();

            break;

        case 9:

            dischargePatient();

            break;

        case 10:

            viewSecurityLog();

            break;

        case 11:

            generateDailyReport();

            break;

        case 12:

            return;

        default:

            std::cout
                << "Invalid choice.\n";
        }
    }
}
// ========================= VIEW SECURITY LOG =========================
void HospitalSystem::viewSecurityLog() {

    std::ifstream file(
        "security_log.txt"
    );

    char line[200];

    while (

        file.getline(
            line,
            200
        )

        ) {

        std::cout
            << line
            << "\n";
    }

    file.close();
}
// ========================= VIEW DAILY REPRT =========================
void HospitalSystem::
generateDailyReport() {

    // GET CURRENT DATE

    time_t t = time(0);

    tm now;

    localtime_s(&now, &t);

    char today[20];

    sprintf_s(

        today,

        "%02d-%02d-%04d",

        now.tm_mday,

        now.tm_mon + 1,

        now.tm_year + 1900
    );

    int pending = 0;

    int completed = 0;

    int noShow = 0;

    int cancelled = 0;

    float revenue = 0;

    // =========================
    // ALL APPOINTMENTS SO FAR
    // =========================

    for (int i = 0;
        i < appointments.size();
        i++) {

        appointment a =
            appointments.getAll()[i];

        if (

            StringHelper::compare(
                a.getStatus(),
                "scheduled"
            )
            ) {

            pending++;
        }

        else if (

            StringHelper::compare(
                a.getStatus(),
                "completed"
            )
            ) {

            completed++;
        }

        else if (

            StringHelper::compare(
                a.getStatus(),
                "no-show"
            )
            ) {

            noShow++;
        }

        else if (

            StringHelper::compare(
                a.getStatus(),
                "cancelled"
            )
            ) {

            cancelled++;
        }
    }

    // =========================
    // ALL REVENUE SO FAR
    // =========================

    for (int i = 0;
        i < bills.size();
        i++) {

        if (

            StringHelper::compare(

                bills.getAll()[i]
                .getStatus(),

                "paid"
            )
            ) {

            revenue +=
                bills.getAll()[i]
                .getAmount();
        }
    }

    // =========================
    // DISPLAY REPORT
    // =========================

    std::cout
        << "\n========== DAILY REPORT ==========\n";

    std::cout
        << "Generated On: "
        << today
        << "\n\n";

    std::cout
        << "Total appointments so far: "

        << appointments.size()

        << "\n";

    std::cout
        << "(Pending: "
        << pending

        << " Completed: "
        << completed

        << " No-show: "
        << noShow

        << " Cancelled: "
        << cancelled

        << ")\n\n";

    std::cout
        << "Revenue collected so far: PKR "
        << revenue
        << "\n\n";

    // =========================
    // UNPAID BILLS
    // =========================

    std::cout
        << "Patients with outstanding unpaid bills:\n";

    bool unpaidFound = false;

    for (int i = 0;
        i < patients.size();
        i++) {

        float totalOwed = 0;

        for (int j = 0;
            j < bills.size();
            j++) {

            if (

                bills.getAll()[j]
                .getPatientID()

                ==

                patients.getAll()[i]
                .getID()

                &&

                StringHelper::compare(

                    bills.getAll()[j]
                    .getStatus(),

                    "unpaid"
                )
                ) {

                totalOwed +=
                    bills.getAll()[j]
                    .getAmount();
            }
        }

        if (totalOwed > 0) {

            unpaidFound = true;

            std::cout
                << patients
                .getAll()[i]
                .getName()

                << " | PKR "

                << totalOwed

                << "\n";
        }
    }

    if (!unpaidFound) {

        std::cout
            << "None\n";
    }

    // =========================
    // DOCTOR SUMMARY
    // =========================

    std::cout
        << "\nDoctor-wise summary:\n";

    for (int d = 0;
        d < doctors.size();
        d++) {

        int docCompleted = 0;

        int docPending = 0;

        int docNoShow = 0;

        for (int a = 0;
            a < appointments.size();
            a++) {

            appointment app =
                appointments
                .getAll()[a];

            if (

                app.getDoctorID()

                ==

                doctors.getAll()[d]
                .getID()
                ) {

                if (

                    StringHelper::compare(
                        app.getStatus(),
                        "completed"
                    )
                    ) {

                    docCompleted++;
                }

                else if (

                    StringHelper::compare(
                        app.getStatus(),
                        "scheduled"
                    )
                    ) {

                    docPending++;
                }

                else if (

                    StringHelper::compare(
                        app.getStatus(),
                        "no-show"
                    )
                    ) {

                    docNoShow++;
                }
            }
        }

        std::cout
            << doctors
            .getAll()[d]
            .getName()

            << " | Completed: "
            << docCompleted

            << " | Pending: "
            << docPending

            << " | No-show: "
            << docNoShow

            << "\n";
    }
}
// ========================= DISCHARGE PATIENT =========================
void HospitalSystem::dischargePatient()
{

 

    removePatient();
}
// ========================= VIEW UNPAID BILSS =========================
void HospitalSystem::
viewUnpaidBills() {

    bool found = false;

    std::cout
        << "\n===== UNPAID BILLS =====\n";

    for (int i = 0;
        i < bills.size();
        i++) {

        if (

            StringHelper::compare(

                bills.getAll()[i]
                .getStatus(),

                "unpaid"
            )
            ) {

            std::cout
                << bills.getAll()[i]
                << "\n";

            found = true;
        }
    }

    if (!found) {

        std::cout
            << "No unpaid bills.\n";
    }
}
// ========================= REMOVE PATIENT =========================
void HospitalSystem::removePatient() {

    int id;

    std::cout
        << "Enter Patient ID: ";

    std::cin >> id;

    FileHandler::deletePatient(

        id,

        patients,

        appointments,

        bills,

        prescriptions
    );

    std::cout
        << "Patient removed.\n";
}
// ========================= ADD PATIENT =========================
void HospitalSystem::addPatient() {

    int id =
        patients.size() + 1;

    char name[50];

    int age;

    char gender;

    char contact[20];

    char password[50];

    float balance;

    std::cin.ignore();

    std::cout << "Name: ";
    std::cin.getline(name, 50);

    std::cout << "Age: ";
    std::cin >> age;

    std::cout << "Gender(M/F): ";
    std::cin >> gender;

    std::cin.ignore();

    std::cout << "Contact: ";
    std::cin.getline(contact, 20);

    std::cout << "Password: ";
    std::cin.getline(password, 50);

    std::cout << "Balance: ";
    std::cin >> balance;

    patient p(

        id,
        name,
        password,
        age,
        gender,
        contact,
       
        balance
    );

    patients.add(p);

    FileHandler::appendPatient(p);

    std::cout
        << "Patient added.\n";
}
// ========================= DELETE DOCTOR =========================
void HospitalSystem::removeDoctor() {

int id;

std::cout
<< "Enter Doctor ID: ";

std::cin >> id;

FileHandler::deleteDoctor(
    id,
    doctors
);

std::cout
<< "Doctor removed.\n";
}
// ========================= ADD DOCTOR =========================
void HospitalSystem::addDoctor() {

    int id =
        doctors.size() + 1;

    char name[50];

    char spec[50];

    char contact[20];

    char password[50];

    float fee;

    std::cin.ignore();

    std::cout << "Name: ";
    std::cin.getline(name, 50);

    std::cout << "Specialization: ";
    std::cin.getline(spec, 50);

    std::cout << "Contact: ";
    std::cin.getline(contact, 20);

    std::cout << "Password: ";
    std::cin.getline(password, 50);

    std::cout << "Fee: ";
    std::cin >> fee;

    doctor d(

        id,
        name,
        spec,
        contact,
        password,
        fee
    );

    doctors.add(d);

    FileHandler::appendDoctor(d);

    std::cout
        << "Doctor added.\n";
}
// ========================= TOP UP BALANCE =========================

void HospitalSystem::topUpBalance(
    patient* patient) {

    float amount;

    std::cout
        << "Enter amount: ";

    std::cin >> amount;

    if (!Validator::
        validatePositiveFloat(amount)) {

        std::cout
            << "Invalid amount.\n";

        return;
    }

    *patient += amount;

    FileHandler::updatePatients(  patients);

    std::cout
        << "Balance updated.\n";
}

// ========================= VIEW APPOINTMENTS =========================

void HospitalSystem::viewAppointments(
    patient* patient) {

    bool found = false;

    for (int i = 0;
        i < appointments.size();
        i++) {

        if (appointments.getAll()[i]
            .getPatientID()
            == patient->getID()) {

            std::cout
                << appointments
                .getAll()[i]
                << "\n";

            found = true;
        }
    }

    if (!found) {

        std::cout
            << "No appointments found.\n";
    }
}

// ========================= VIEW TODAY APPOINTMENTS =========================

void HospitalSystem::
viewTodayAppointments(
    doctor* doctor) {

    bool found = false;

    for (int i = 0;
        i < appointments.size();
        i++) {

        if (appointments.getAll()[i]
            .getDoctorID()
            == doctor->getID()) {

            std::cout
                << appointments
                .getAll()[i]
                << "\n";

            found = true;
        }
    }

    if (!found) {

        std::cout
            << "No appointments found.\n";
    }
}
// ========================= MARK COMPLETE APPOINTMENTS =========================
void HospitalSystem::
markAppointmentComplete(
    doctor* doctor
) {

    int id;

    std::cout
        << "Enter Appointment ID: ";

    std::cin >> id;

    appointment* a =
        appointments.findByID(id);

    if (a != nullptr &&
        a->getDoctorID()
        == doctor->getID()) {

        a->setStatus(
            "completed"
        );

        FileHandler::
            updateAppointments(
                appointments
            );

        std::cout
            << "Appointment completed.\n";
    }

    else {

        std::cout
            << "Appointment not found.\n";
    }
}
// ========================= MARK APPOINTMENTS NO SHOW =========================
void HospitalSystem::
markAppointmentNoShow(
    doctor* doctor
) {

    int id;

    std::cout
        << "Enter Appointment ID: ";

    std::cin >> id;

    appointment* a =
        appointments.findByID(id);

    if (a != nullptr &&
        a->getDoctorID()
        == doctor->getID()) {

        a->setStatus(
            "no-show"
        );

        FileHandler::
            updateAppointments(
                appointments
            );

        std::cout
            << "Appointment updated.\n";
    }

    else {

        std::cout
            << "Appointment not found.\n";
    }
}

// ========================= WRITE PRESCRIPTIONS =========================
void HospitalSystem::
writePrescription(
    doctor* doctor
) {

    int appID;

    char medicines[500];

    char notes[300];

    std::cout
        << "Enter Appointment ID: ";

    std::cin >> appID;

    std::cin.ignore();

    std::cout
        << "Medicines: ";

    std::cin.getline(
        medicines,
        500
    );

    std::cout
        << "Notes: ";

    std::cin.getline(
        notes,
        300
    );

    appointment* a =
        appointments.findByID(appID);

    if (a == nullptr) {

        std::cout
            << "Appointment not found.\n";

        return;
    }

    int newID =
        prescriptions.size() + 1;

    prescription p(

        newID,

        appID,

        a->getPatientID(),

        doctor->getID(),

        "10-05-2026",

        medicines,

        notes
    );

    prescriptions.add(p);

    FileHandler::
        appendPrescription(p);

    std::cout
        << "Prescription added.\n";
}
// ========================= VIEW PATIENT HISTORT =========================
void HospitalSystem::
viewPatientHistory(
    doctor* doctor
) {

    int patientID;

    std::cout
        << "Enter Patient ID: ";

    std::cin >> patientID;

    bool found = false;

    for (int i = 0;
        i < prescriptions.size();
        i++) {

        if (prescriptions
            .getAll()[i]
            .getPatientID()
            == patientID) {

            std::cout
                << prescriptions
                .getAll()[i]
                << "\n";

            found = true;
        }
    }

    if (!found) {

        std::cout
            << "No history found.\n";
    }
}

// ========================= VIEW ALL PATIENTS =========================

void HospitalSystem::viewAllPatients() {

    for (int i = 0;
        i < patients.size();
        i++) {

        std::cout
            << patients.getAll()[i]
            << "\n";
    }
}

// ========================= VIEW ALL DOCTORS =========================

void HospitalSystem::viewAllDoctors() {

    for (int i = 0;
        i < doctors.size();
        i++) {

        std::cout
            << doctors.getAll()[i]
            << "\n";
    }
}

// ========================= VIEW ALL APPOINTMENTS =========================

void HospitalSystem::
viewAllAppointments() {

    for (int i = 0;
        i < appointments.size();
        i++) {

        std::cout
            << appointments
            .getAll()[i]
            << "\n";
    }
}
// ========================= BOOK APPOINTMENTS =========================
void HospitalSystem::bookAppointment(
    patient* patient
) {

    char specialization[50];

    int doctorID;

    char date[20];

    char slot[20];

    // SPECIALIZATION INPUT

    std::cin.ignore();

    std::cout
        << "\nEnter Specialization: ";

    std::cin.getline(
        specialization,
        50
    );

    // SHOW MATCHING DOCTORS

    bool doctorFound = false;

    std::cout
        << "\n===== Available Doctors =====\n";

    for (int i = 0;
        i < doctors.size();
        i++) {

        if (

            StringHelper::compare(

                doctors.getAll()[i]
                .getSpec(),

                specialization
            )
            ) {

            std::cout
                << doctors.getAll()[i]
                << "\n";

            doctorFound = true;
        }
    }

    if (!doctorFound) {

        std::cout
            << "No doctors found.\n";

        return;
    }

    // SELECT DOCTOR

    std::cout
        << "\nEnter Doctor ID: ";

    std::cin >> doctorID;

    doctor* d =
        doctors.findByID(
            doctorID
        );

    if (d == nullptr) {

        std::cout
            << "Doctor not found.\n";

        return;
    }

    // DATE INPUT

    std::cout
        << "Enter Date (DD-MM-YYYY): ";

    std::cin >> date;

    // DATE VALIDATION

    if (

        !Validator::validateDate(
            date
        )
        ) {

        std::cout
            << "Invalid or old date.\n";

        return;
    }

    // SHOW AVAILABLE SLOTS

    const char slots[8][10] = {

        "09:00",
        "10:00",
        "11:00",
        "12:00",
        "13:00",
        "14:00",
        "15:00",
        "16:00"
    };

    std::cout
        << "\n===== Available Slots =====\n";

    bool anyAvailable = false;

    for (int s = 0;
        s < 8;
        s++) {

        bool occupied = false;

        for (int i = 0;
            i < appointments.size();
            i++) {

            appointment a =
                appointments
                .getAll()[i];

            if (

                a.getDoctorID()
                == doctorID

                &&

                StringHelper::compare(
                    a.getDate(),
                    date
                )

                &&

                StringHelper::compare(
                    a.getTimeSlot(),
                    slots[s]
                )

                &&

                !StringHelper::compare(
                    a.getStatus(),
                    "cancelled"
                )
                ) {

                occupied = true;

                break;
            }
        }

        if (!occupied) {

            std::cout
                << slots[s]
                << "\n";

            anyAvailable = true;
        }
    }

    if (!anyAvailable) {

        std::cout
            << "No slots available.\n";

        return;
    }

    // USER SLOT INPUT

    std::cout
        << "\nEnter Time Slot: ";

    std::cin >> slot;
    bool validSlot = false;

    for (int s = 0;
        s < 8;
        s++) {

        if (

            StringHelper::compare(
                slot,
                slots[s]
            )
            ) {

            validSlot = true;

            break;
        }
    }

    if (!validSlot) {

        std::cout
            << "Invalid slot selected.\n";

        return;
    }

    // FINAL SLOT CHECK

    for (int i = 0;
        i < appointments.size();
        i++) {

        appointment a =
            appointments
            .getAll()[i];

        if (

            a.getDoctorID()
            == doctorID

            &&

            StringHelper::compare(
                a.getDate(),
                date
            )

            &&

            StringHelper::compare(
                a.getTimeSlot(),
                slot
            )

            &&

            !StringHelper::compare(
                a.getStatus(),
                "cancelled"
            )
            ) {

            std::cout
                << "Slot unavailable.\n";

            return;
        }
    }

    // BALANCE CHECK

    if (

        patient->getBalance()
        < d->getFee()
        ) {

        std::cout
            << "Insufficient balance.\n";

        return;
    }

    // CREATE APPOINTMENT

    int appointmentID =
        appointments.size() + 1;

    appointment app(

        appointmentID,

        patient->getID(),

        doctorID,

        date,

        slot,

        "scheduled"
    );

    appointments.add(app);

    FileHandler::
        appendAppointment(app);

    // CREATE BILL

    int billID =
        bills.size() + 1;

    bill b(

        billID,

        patient->getID(),

        appointmentID,

        d->getFee(),

        "unpaid",

        date
    );

    bills.add(b);

    FileHandler::
        appendBill(b);

    std::cout
        << "\nAppointment booked successfully.\n";
}
// ========================= CANCEL APPOINTMENTS =========================
void HospitalSystem::cancelAppointment(
    patient* patient
) {

    int id;

    std::cout
        << "Enter Appointment ID: ";

    std::cin >> id;

    appointment* a =
        appointments.findByID(id);

    if (

        a == nullptr

        ||

        a->getPatientID()
        != patient->getID()
        ) {

        std::cout
            << "Appointment not found.\n";

        return;
    }

    // ALREADY CANCELLED

    if (

        StringHelper::compare(

            a->getStatus(),

            "cancelled"
        )
        ) {

        std::cout
            << "Appointment already cancelled.\n";

        return;
    }

    // CANCEL APPOINTMENT

    a->setStatus(
        "cancelled"
    );

    bool refundIssued = false;

    // FIND RELATED BILL

    for (int i = 0;
        i < bills.size();
        i++) {

        bill* b =
            &bills.getAll()[i];

        if (

            b->getAppointmentID()

            ==

            a->getID()
            ) {

            // REFUND ONLY IF PAID

            if (

                StringHelper::compare(

                    b->getStatus(),

                    "paid"
                )
                ) {

                patient->addBalance(

                    b->getAmount()
                );

                b->setStatus(
                    "refunded"
                );

                refundIssued = true;
            }

            // IF UNPAID

            else if (

                StringHelper::compare(

                    b->getStatus(),

                    "unpaid"
                )
                ) {

                b->setStatus(
                    "cancelled"
                );
            }

            break;
        }
    }

    // UPDATE FILES

    FileHandler::
        updateAppointments(
            appointments
        );

    FileHandler::
        updateBills(
            bills
        );

    FileHandler::
        updatePatients(
            patients
        );

    // DISPLAY MESSAGE

    if (refundIssued) {

        std::cout
            << "Appointment cancelled and refund issued.\n";
    }

    else {

        std::cout
            << "Appointment cancelled.\n";
    }
}
// ========================= VIEW MEDICAL RECORDS =========================
void HospitalSystem::viewMedicalRecords(
    patient* patient
) {

    bool found = false;

    for (int i = 0;
        i < prescriptions.size();
        i++) {

        if (

            prescriptions
            .getAll()[i]
            .getPatientID()

            ==

            patient->getID()
            ) {

            std::cout
                << prescriptions
                .getAll()[i]
                << "\n";

            found = true;
        }
    }

    if (!found) {

        std::cout
            << "No medical records found.\n";
    }
}
// ========================= VIEW BILLS =========================
void HospitalSystem::viewBills(
    patient* patient
) {

    bool found = false;

    for (int i = 0;
        i < bills.size();
        i++) {

        if (

            bills.getAll()[i]
            .getPatientID()

            ==

            patient->getID()
            ) {

            std::cout
                << bills.getAll()[i]
                << "\n";

            found = true;
        }
    }

    if (!found) {

        std::cout
            << "No bills found.\n";
    }
}
// ========================= PAY BILLS =========================
void HospitalSystem::payBill(
patient* patient
) {

    int billID;

    std::cout
        << "Enter Bill ID: ";

    std::cin >> billID;

    bill* b =
        bills.findByID(
            billID
        );

    if (

        b == nullptr

        ||

        b->getPatientID()
        != patient->getID()

        ) {

        std::cout
            << "Bill not found.\n";

        return;
    }

    if (

        StringHelper::compare(
            b->getStatus(),
            "paid"
        )

        ) {

        std::cout
            << "Bill already paid.\n";

        return;
    }

    if (

        patient->getBalance()
        < b->getAmount()

        ) {

        std::cout
            << "Insufficient funds.\n";

        return;
    }

    patient->deductBalance(
        b->getAmount()
    );

    b->setStatus(
        "paid"
    );

    FileHandler::
        updateBills(
            bills
        );

    FileHandler::
        updatePatients(
            patients
        );

    std::cout
        << "Bill paid successfully.\n";
}
// ========================= GETTERS =========================
Storage<patient>&
HospitalSystem::getPatients() {

    return patients;
}

Storage<doctor>&
HospitalSystem::getDoctors() {

    return doctors;
}

Storage<appointment>&
HospitalSystem::getAppointments() {

    return appointments;
}

Storage<bill>&
HospitalSystem::getBills() {

    return bills;
}

Storage<prescription>&
HospitalSystem::getPrescriptions() {

    return prescriptions;
}

Storage<admin>&
HospitalSystem::getAdmins() {

    return admins;
}