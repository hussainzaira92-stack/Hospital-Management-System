#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdint>
#include "hospitalSystem.h"
#include "fileHandler.h"
#include "validator.h"
#include "stringHelper.h"
enum class Screen {
    Splash, MainMenu,
    PatientLogin, DoctorLogin, AdminLogin,
    PatientDashboard, DoctorDashboard, AdminDashboard,
    BookAppointmentSpec,          
    BookAppointmentPick,          
    CancelAppointment, ViewAppointments,
    ViewMedicalRecords, ViewBills, PayBill, TopUpBalance,
    ViewTodayAppointments, MarkComplete, MarkNoShow,
    WritePrescription,
    ViewPatientHistoryInput,      
    ViewPatientHistoryResult,     
    AddDoctor,
    RemoveDoctor,                 
    AddPatient, RemovePatient,
    ViewAllPatients, ViewAllDoctors, ViewAllAppointments,
    ViewUnpaidBills, ViewSecurityLog, GenerateDailyReport
};

struct Button {
    sf::RectangleShape shape;
    sf::Text*          label   = nullptr;
    const sf::Font*    font    = nullptr;
    bool               hovered = false;

    Button() = default;
    ~Button() { delete label; }
    Button(const Button&)            = delete;
    Button& operator=(const Button&) = delete;
    Button(Button&& o) noexcept;
    Button& operator=(Button&& o) noexcept;

    void init(const sf::Font& f, float x, float y, float w, float h,
              const char* text, unsigned int fontSize = 16,
              sf::Color fill    = sf::Color(122,92,90),
              sf::Color textCol = sf::Color(255,255,255));
    void setHover(bool h);
    void draw(sf::RenderWindow& win) const;
    bool contains(sf::Vector2f pos) const;
};

struct InputField {
    sf::RectangleShape box;
    sf::Text*          display    = nullptr;
    const sf::Font*    font       = nullptr;
    char               buffer[200]{};
    int                len        = 0;
    bool               active     = false;
    bool               isPassword = false;

    InputField() = default;
    ~InputField() { delete display; }
    InputField(const InputField&)            = delete;
    InputField& operator=(const InputField&) = delete;
    InputField(InputField&& o) noexcept;
    InputField& operator=(InputField&& o) noexcept;

    void init(const sf::Font& f, float x, float y, float w, float h, bool pw = false);
    void clear();
    void updateDisplay();
    void draw(sf::RenderWindow& win) const;
};

struct Banner {
    sf::RectangleShape bg;
    sf::Text*          msg      = nullptr;
    bool               visible  = false;
    bool               isError  = false;
    sf::Clock          timer;
    float              duration = 3.0f;

    Banner()  = default;
    ~Banner() { delete msg; }
    Banner(const Banner&)            = delete;
    Banner& operator=(const Banner&) = delete;

    void show(const char* text, bool error,
              const sf::Font& font, float winW, float winH);
    void update();
    void draw(sf::RenderWindow& win);
};

struct TextArea {
    struct Line {
        sf::Text* text = nullptr;
        Line() = default;
        ~Line() { delete text; }
        Line(const Line&) = delete;
        Line& operator=(const Line&) = delete;
        Line(Line&& o) noexcept : text(o.text) { o.text = nullptr; }
        Line& operator=(Line&& o) noexcept {
            if (this != &o) { delete text; text = o.text; o.text = nullptr; }
            return *this;
        }
    };
    std::vector<Line> lines;
    float scrollOffset = 0.f;

    void clear();
    void addLine(const sf::Font& f, const sf::String& s,
                 unsigned int sz, sf::Color col);
};

class MediCoreGUI {
public:
    MediCoreGUI();
    void run();

private:
    sf::RenderWindow window;
    sf::Font         fontReg;
    sf::Font         fontBold;
    sf::Music        ambientMusic;
    sf::SoundBuffer  clickBuf;
    sf::Sound*       clickSound = nullptr;
    bool             musicOn    = true;   

    Screen         currentScreen = Screen::Splash;
    HospitalSystem hospital;
    patient*       loggedPatient = nullptr;
    doctor*        loggedDoctor  = nullptr;
    admin*         loggedAdmin   = nullptr;
    int            loginAttempts = 0;

    static constexpr float W     = 1280.f;
    static constexpr float H     =  720.f;
    static constexpr float SIDEW =  220.f;
    static constexpr float TOPH  =   56.f;

    static constexpr float CX    = SIDEW + 20.f;   
    static constexpr float CY    = TOPH  + 16.f;   
    static constexpr float CW    = W - SIDEW;      

    sf::Clock          splashClock;
    sf::Text*          splashTitle = nullptr;
    sf::Text*          splashSub   = nullptr;
    sf::RectangleShape splashBg;
    sf::RectangleShape splashLine;

    // ---- Main menu ----
    sf::RectangleShape mainBg;
    sf::RectangleShape mainPanel;
    sf::Text*          mainTitle      = nullptr;
    sf::Text*          mainSub        = nullptr;
    sf::Text*          mainWelcome    = nullptr;
    sf::Text*          mainWelcomeSub = nullptr;
    Button             mainRoleBtns[3];

    // ---- Login ----
    sf::Text*          loginTitle   = nullptr;
    sf::Text*          loginSub     = nullptr;
    sf::Text*          loginIDLbl   = nullptr;
    sf::Text*          loginPassLbl = nullptr;
    InputField         loginID;
    InputField         loginPass;
    Button             loginSubmit;
    Button             loginBack;
    sf::RectangleShape loginCard;   

    // ---- Dashboard chrome ----
    sf::RectangleShape sidebar;
    sf::RectangleShape sideUserCard;
    sf::RectangleShape topBar;
    sf::RectangleShape topAccent;
    sf::Text*          sideLogoText  = nullptr;
    sf::Text*          userInfoName  = nullptr;
    sf::Text*          userInfoRole  = nullptr;
    sf::Text*          userInfoExtra = nullptr;
    sf::Text*          contentTitle  = nullptr;
    Button             sidebarBtns[12];
    int                sidebarCount  = 0;
    Button             musicBtn;     

    
    InputField formFields[6];
    sf::Text*  formLabels[6]{};
    int        formFieldCount = 0;
    Button     formSubmitBtn;
    Button     formClearBtn;

    TextArea           rightPanel;
    bool               rightPanelVisible = false;
    sf::RectangleShape rightPanelBg;   

    char bookSpec[50]{};   

    TextArea contentArea;
    Banner   banner;

    void loadAssets();
    void setupSplash();
    void setupMainMenu();
    void setupLogin(Screen role);
    void setupDashboard(Screen dash);
    void setupForm(Screen s);                    
    void setupSplitForm(Screen s);                

    void handleEvents();
    void update();
    void render();

    void renderSplash();
    void renderMainMenu();
    void renderLogin();
    void renderDashboardBase();   
    void renderContentLines();    
    void renderDashboard();       
    void renderForm();           
    void renderSplitScreen();     

    void buildSidebar(const char* labels[], int count);
    int  sidebarHit(sf::Vector2f pos);

    void handlePatientAction(int idx);
    void handleDoctorAction(int idx);
    void handleAdminAction(int idx);

    void submitBookSpec();           
    void submitBookAppointment();    
    void submitCancelAppointment();
    void submitTopUp();
    void submitPayBill();
    void submitAddDoctor();
    void submitRemoveDoctor();
    void submitAddPatient();
    void submitRemovePatient();
    void submitWritePrescription();
    void submitViewPatientHistory(); 
    void submitMarkComplete();
    void submitMarkNoShow();

    void displayAppointments();
    void displayMedicalRecords();
    void displayBills();
    void displayTodayAppointments();
    void displayAllPatients();
    void displayAllDoctors();
    void displayAllAppointments();
    void displayUnpaidBills();
    void displaySecurityLog();
    void displayDailyReport();

    void populateRightPanelDoctors(const char* spec);
    void populateRightPanelBills();
    void populateRightPanelAllDoctors();

    void handleTextInput(uint32_t unicode);
    void renderInputField(InputField& f);
    void showBanner(const char* msg, bool err);
    void playClick();
    void clearForm();
    void hoverBtns(Button* btns, int n, sf::Vector2f mouse);
    bool strEq(const char* a, const char* b);
    void ftos(float v, char* buf, int sz);
    void itos(int v,   char* buf, int sz);

    sf::Text* makeText(const sf::Font& f, const sf::String& s,
                       unsigned int sz, sf::Color col,
                       float x = 0.f, float y = 0.f);
    void centreText(sf::Text* t, float cx, float cy);

    static sf::Color cBg()      { return {250,245,244}; }
    static sf::Color cSide()    { return { 44, 35, 37}; }
    static sf::Color cRose()    { return {230,200,198}; }
    static sf::Color cAccent()  { return {122, 92, 90}; }
    static sf::Color cText()    { return { 30, 20, 20}; }
    static sf::Color cMuted()   { return {156,126,124}; }
    static sf::Color cSuccess() { return { 74,124, 89}; }
    static sf::Color cError()   { return {139, 58, 58}; }
    static sf::Color cSideBtn() { return { 60, 48, 50}; }
    static sf::Color cSideHov() { return {122, 92, 90}; }
    static sf::Color cWhite()   { return {255,255,255}; }
};
