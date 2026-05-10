#include "GUI.h"
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
Button::Button(Button&& o) noexcept
    : shape(std::move(o.shape)), label(o.label), font(o.font), hovered(o.hovered)
{ o.label = nullptr; o.font = nullptr; }

Button& Button::operator=(Button&& o) noexcept {
    if (this != &o) {
        delete label;
        shape   = std::move(o.shape);
        label   = o.label;  o.label = nullptr;
        font    = o.font;   o.font  = nullptr;
        hovered = o.hovered;
    }
    return *this;
}

void Button::init(const sf::Font& f, float x, float y, float w, float h,
                  const char* text, unsigned int fontSize,
                  sf::Color fill, sf::Color textCol)
{
    font = &f;
    delete label;
    label = new sf::Text(f, sf::String(text), fontSize);
    shape.setPosition({x, y});
    shape.setSize({w, h});
    shape.setFillColor(fill);
    label->setFillColor(textCol);
    sf::FloatRect tb = label->getLocalBounds();
    label->setOrigin({ tb.position.x + tb.size.x / 2.f,
                       tb.position.y + tb.size.y / 2.f });
    label->setPosition({ x + w / 2.f, y + h / 2.f });
}

void Button::setHover(bool h) {
    hovered = h;
    shape.setFillColor(h ? sf::Color(230,200,198) : sf::Color(122,92,90));
    if (label) label->setFillColor(h ? sf::Color(30,20,20) : sf::Color(255,255,255));
}

void Button::draw(sf::RenderWindow& win) const {
    win.draw(shape);
    if (label) win.draw(*label);
}

bool Button::contains(sf::Vector2f pos) const {
    return shape.getGlobalBounds().contains(pos);
}

InputField::InputField(InputField&& o) noexcept
    : box(std::move(o.box)), display(o.display), font(o.font),
      len(o.len), active(o.active), isPassword(o.isPassword)
{
    memcpy(buffer, o.buffer, 200);
    o.display = nullptr; o.font = nullptr;
}

InputField& InputField::operator=(InputField&& o) noexcept {
    if (this != &o) {
        delete display;
        box        = std::move(o.box);
        display    = o.display;  o.display = nullptr;
        font       = o.font;     o.font    = nullptr;
        len        = o.len;
        active     = o.active;
        isPassword = o.isPassword;
        memcpy(buffer, o.buffer, 200);
    }
    return *this;
}

void InputField::init(const sf::Font& f, float x, float y, float w, float h, bool pw) {
    font = &f;  isPassword = pw;
    len = 0; buffer[0] = '\0'; active = false;
    box.setPosition({x,y}); box.setSize({w,h});
    box.setFillColor({255,255,255});
    box.setOutlineColor({230,200,198}); box.setOutlineThickness(2.f);
    delete display;
    display = new sf::Text(f, sf::String(""), 14);
    display->setFillColor({30,20,20});
    display->setPosition({x+10.f, y+h/2.f-9.f});
}

void InputField::clear() {
    len = 0; buffer[0] = '\0';
    if (display) display->setString("");
}

void InputField::updateDisplay() {
    if (!display) return;
    if (isPassword) {
        sf::String s; for (int i=0;i<len;i++) s+='*';
        display->setString(s);
    } else {
        display->setString(sf::String(buffer));
    }
}

void InputField::draw(sf::RenderWindow& win) const {
    win.draw(box);
    if (display) win.draw(*display);
}

void Banner::show(const char* text, bool error,
                  const sf::Font& font, float winW, float winH)
{
    isError = error; visible = true; timer.restart();
    bg.setSize({winW, 44.f}); bg.setPosition({0.f, winH-44.f});
    bg.setFillColor(error ? sf::Color(139,58,58,230) : sf::Color(74,124,89,230));
    delete msg;
    msg = new sf::Text(font, sf::String(text), 15);
    msg->setFillColor(sf::Color::White);
    sf::FloatRect tb = msg->getLocalBounds();
    msg->setOrigin({tb.position.x+tb.size.x/2.f, tb.position.y+tb.size.y/2.f});
    msg->setPosition({winW/2.f, winH-22.f});
}
void Banner::update() {
    if (visible && timer.getElapsedTime().asSeconds()>duration) visible=false;
}
void Banner::draw(sf::RenderWindow& win) {
    if (!visible) return;
    win.draw(bg); if (msg) win.draw(*msg);
}

void TextArea::clear() { lines.clear(); scrollOffset=0.f; }
void TextArea::addLine(const sf::Font& f, const sf::String& s,
                       unsigned int sz, sf::Color col)
{
    Line l; l.text = new sf::Text(f,s,sz); l.text->setFillColor(col);
    lines.push_back(std::move(l));
}

bool MediCoreGUI::strEq(const char* a, const char* b) {
    if (!a||!b) return false;
    while (*a&&*b){ if(*a!=*b) return false; a++;b++; }
    return *a==*b;
}
void MediCoreGUI::ftos(float v,char*buf,int sz){snprintf(buf,sz,"%.2f",v);}
void MediCoreGUI::itos(int v,  char*buf,int sz){snprintf(buf,sz,"%d",  v);}
void MediCoreGUI::playClick(){ if(clickSound) clickSound->play(); }
void MediCoreGUI::showBanner(const char* msg,bool err){
    banner.show(msg,err,fontBold,W,H);
}
sf::Text* MediCoreGUI::makeText(const sf::Font& f,const sf::String& s,
                                 unsigned int sz,sf::Color col,float x,float y){
    sf::Text* t=new sf::Text(f,s,sz);
    t->setFillColor(col); t->setPosition({x,y}); return t;
}
void MediCoreGUI::centreText(sf::Text* t,float cx,float cy){
    if(!t) return;
    sf::FloatRect b=t->getLocalBounds();
    t->setOrigin({b.position.x+b.size.x/2.f, b.position.y+b.size.y/2.f});
    t->setPosition({cx,cy});
}
void MediCoreGUI::clearForm(){
    for(int i=0;i<formFieldCount;i++) formFields[i].clear();
}
void MediCoreGUI::hoverBtns(Button* btns,int n,sf::Vector2f mouse){
    for(int i=0;i<n;i++) btns[i].setHover(btns[i].contains(mouse));
}

MediCoreGUI::MediCoreGUI()
    : window(sf::VideoMode({1280u,720u}),
             "MediCore Hospital Management System",
             sf::Style::Titlebar | sf::Style::Close)
{
    window.setFramerateLimit(60);
    loadAssets();
    setupSplash();
}
void MediCoreGUI::loadAssets(){
    fontReg.openFromFile("assets/fonts/Lato-Regular.ttf");
    fontBold.openFromFile("assets/fonts/Lato-Bold.ttf");
    if(clickBuf.loadFromFile("assets/sounds/click.ogg")){
        clickSound=new sf::Sound(clickBuf); clickSound->setVolume(70.f);
    }
    if(ambientMusic.openFromFile("assets/sounds/ambient.ogg")){
        ambientMusic.setLooping(true); ambientMusic.setVolume(18.f); ambientMusic.play();
    }
}


void MediCoreGUI::setupSplash(){
    splashBg.setSize({W,H}); splashBg.setFillColor({44,35,37});
    splashLine.setSize({400.f,3.f}); splashLine.setFillColor(cRose());
    splashLine.setPosition({W/2.f-200.f, H/2.f+40.f});
    delete splashTitle;
    splashTitle=makeText(fontBold,"MediCore",64,cRose());
    centreText(splashTitle,W/2.f,H/2.f-14.f);
    delete splashSub;
    splashSub=makeText(fontReg,"Hospital Management System",18,cMuted());
    centreText(splashSub,W/2.f,H/2.f+52.f);
    splashClock.restart();
}

void MediCoreGUI::setupMainMenu(){
    mainBg.setSize({W,H}); mainBg.setFillColor(cBg());
    mainPanel.setSize({350.f,H}); mainPanel.setFillColor(cSide()); mainPanel.setPosition({0,0});
    delete mainTitle; mainTitle=makeText(fontBold,"MediCore",44,cRose(),40.f,174.f);
    delete mainSub;   mainSub  =makeText(fontReg,"Hospital Management\nSystem",16,cMuted(),42.f,234.f);
    delete mainWelcome;    mainWelcome   =makeText(fontBold,"Welcome Back",28,cText(),470.f,194.f);
    delete mainWelcomeSub; mainWelcomeSub=makeText(fontReg,"Please select your role to continue",13,cMuted(),470.f,228.f);
    const char* lbls[3]={"Login as Patient","Login as Doctor","Login as Admin"};
    float bx=470.f,by=268.f,bw=300.f,bh=52.f;
    for(int i=0;i<3;i++) mainRoleBtns[i].init(fontBold,bx,by+i*72.f,bw,bh,lbls[i],16);
}


void MediCoreGUI::setupLogin(Screen role){
    const char* title=
        role==Screen::PatientLogin?"Patient Login":
        role==Screen::DoctorLogin ?"Doctor Login" :"Admin Login";

    // Card: 520 wide x 400 tall, centred
    float cardW=520.f, cardH=400.f;
    float cardX=W/2.f-cardW/2.f, cardY=H/2.f-cardH/2.f;

    loginCard.setSize({cardW,cardH});
    loginCard.setPosition({cardX,cardY});
    loginCard.setFillColor(cWhite());
    loginCard.setOutlineColor(cRose()); loginCard.setOutlineThickness(2.f);

    float fx=cardX+40.f, fw=cardW-80.f;
    float fy=cardY+30.f;

    delete loginTitle;
    loginTitle=makeText(fontBold,title,26,cText(),fx,fy);
    delete loginSub;
    loginSub  =makeText(fontReg,"Enter your credentials to continue",13,cMuted(),fx,fy+36.f);

    delete loginIDLbl;
    loginIDLbl=makeText(fontReg,"User ID",13,cMuted(),fx,fy+84.f);
    loginID.init(fontReg,fx,fy+102.f,fw,40.f,false);
    loginID.active=true;

    delete loginPassLbl;
    loginPassLbl=makeText(fontReg,"Password",13,cMuted(),fx,fy+158.f);
    loginPass.init(fontReg,fx,fy+176.f,fw,40.f,true);

    loginSubmit.init(fontBold,fx,fy+238.f,fw,44.f,"Login",16);
    loginBack  .init(fontBold,fx,fy+292.f,fw,38.f,"Back",14,sf::Color(200,185,183),cText());

    loginAttempts=0; loginID.clear(); loginPass.clear();
}

void MediCoreGUI::setupDashboard(Screen dash){
    sidebar     .setSize({SIDEW,H});   sidebar.setFillColor(cSide()); sidebar.setPosition({0,0});
    sideUserCard.setSize({SIDEW,110.f});sideUserCard.setFillColor({60,48,50}); sideUserCard.setPosition({0,0});
    topBar      .setSize({W-SIDEW,TOPH}); topBar.setFillColor(cRose()); topBar.setPosition({SIDEW,0});
    topAccent   .setSize({W-SIDEW,2.f});  topAccent.setFillColor(cAccent()); topAccent.setPosition({SIDEW,TOPH});

    delete sideLogoText;
    sideLogoText=makeText(fontBold,"MediCore",16,cRose(),14.f,H-36.f);

    delete userInfoName; delete userInfoRole; delete userInfoExtra;

    if(dash==Screen::PatientDashboard){
        userInfoName =makeText(fontBold,sf::String(loggedPatient->getName()),15,cRose(),14.f,14.f);
        userInfoRole =makeText(fontReg,"Patient",12,cMuted(),14.f,38.f);
        char bal[80]; snprintf(bal,80,"Bal: PKR %.2f",loggedPatient->getBalance());
        userInfoExtra=makeText(fontReg,sf::String(bal),12,cMuted(),14.f,54.f);
        const char* lbls[]={"Book Appointment","Cancel Appointment","My Appointments",
                             "Medical Records","My Bills","Pay Bill","Top Up Balance","Logout"};
        buildSidebar(lbls,8);
    } else if(dash==Screen::DoctorDashboard){
        char dname[60]="Dr. "; strncat_s(dname,60,loggedDoctor->getName(),55);
        userInfoName =makeText(fontBold,sf::String(dname),15,cRose(),14.f,14.f);
        userInfoRole =makeText(fontReg,sf::String(loggedDoctor->getSpec()),12,cMuted(),14.f,38.f);
        userInfoExtra=makeText(fontReg,"",12,cMuted(),14.f,54.f);
        const char* lbls[]={"Today's Appointments","Mark Complete","Mark No-Show",
                             "Write Prescription","Patient History","Logout"};
        buildSidebar(lbls,6);
    } else {
        userInfoName =makeText(fontBold,"Administrator",15,cRose(),14.f,14.f);
        userInfoRole =makeText(fontReg,"Admin  MediCore",12,cMuted(),14.f,38.f);
        userInfoExtra=makeText(fontReg,"",12,cMuted(),14.f,54.f);
        const char* lbls[]={"Add Doctor","Remove Doctor","Add Patient","Remove Patient",
                             "All Patients","All Doctors","All Appointments",
                             "Unpaid Bills","Security Log","Daily Report","Logout"};
        buildSidebar(lbls,11);
    }

    delete contentTitle;
    contentTitle=makeText(fontBold,"Welcome to MediCore",18,cText(),SIDEW+24.f,TOPH/2.f-10.f);

    const char* mlbl = musicOn ? "Music: ON" : "Music: OFF";
    musicBtn.init(fontReg, W-110.f, 8.f, 100.f, 40.f, mlbl, 13,
                  sf::Color(100,75,73), cWhite());

    contentArea.clear();
    contentArea.addLine(fontReg,"Select an option from the sidebar to get started.",14,cMuted());
    rightPanelVisible=false;
}

void MediCoreGUI::buildSidebar(const char* labels[],int count){
    sidebarCount=count;
    float sy=120.f, bh=40.f, gap=5.f;
    for(int i=0;i<count;i++)
        sidebarBtns[i].init(fontReg,8.f,sy+i*(bh+gap),SIDEW-16.f,bh,labels[i],12,cSideBtn(),cRose());
}
int MediCoreGUI::sidebarHit(sf::Vector2f pos){
    for(int i=0;i<sidebarCount;i++) if(sidebarBtns[i].contains(pos)) return i;
    return -1;
}

void MediCoreGUI::setupForm(Screen s){
    formFieldCount=0; clearForm(); contentArea.clear(); rightPanelVisible=false;
    for(int i=0;i<6;i++){delete formLabels[i];formLabels[i]=nullptr;}

    float fx=CX+10.f, fw=380.f, fh=38.f, gy=58.f, sy=CY+10.f;
    auto addF=[&](int i,const char* lbl,bool pw=false){
        formLabels[i]=makeText(fontReg,lbl,13,cMuted(),fx,sy+i*gy);
        formFields[i].init(fontReg,fx,sy+i*gy+18.f,fw,fh,pw);
        formFieldCount++;
    };

    const char* ctitle="Form";
    if      (s==Screen::BookAppointmentSpec){  
        ctitle="Book Appointment - Step 1";
        addF(0,"Enter Specialization (e.g. Cardiology)");
    }
    else if (s==Screen::CancelAppointment){ ctitle="Cancel Appointment"; addF(0,"Appointment ID"); }
    else if (s==Screen::TopUpBalance)     { ctitle="Top Up Balance";     addF(0,"Amount (PKR)"); }
    else if (s==Screen::AddDoctor)        { ctitle="Add Doctor";
        addF(0,"Name"); addF(1,"Specialization"); addF(2,"Contact (11 digits)");
        addF(3,"Password (min 6 chars)",true); addF(4,"Consultation Fee (PKR)"); }
    else if (s==Screen::AddPatient)       { ctitle="Add Patient";
        addF(0,"Name"); addF(1,"Age"); addF(2,"Gender (M/F)");
        addF(3,"Contact (11 digits)"); addF(4,"Password (min 6 chars)",true);
        addF(5,"Initial Balance (PKR)"); }
    else if (s==Screen::RemovePatient)    { ctitle="Remove Patient"; addF(0,"Patient ID"); }
    else if (s==Screen::WritePrescription){ ctitle="Write Prescription";
        addF(0,"Appointment ID"); addF(1,"Medicines (e.g. Paracetamol 500mg)"); addF(2,"Notes"); }
    else if (s==Screen::ViewPatientHistoryInput){ ctitle="Patient History"; addF(0,"Patient ID"); }
    else if (s==Screen::MarkComplete)     { ctitle="Mark Complete"; addF(0,"Appointment ID"); }
    else if (s==Screen::MarkNoShow)       { ctitle="Mark No-Show"; addF(0,"Appointment ID"); }

    delete contentTitle;
    contentTitle=makeText(fontBold,ctitle,18,cText(),SIDEW+24.f,TOPH/2.f-10.f);
    formFields[0].active=true;

    float submitY=sy+formFieldCount*gy+14.f;
    formSubmitBtn.init(fontBold,fx,submitY,160.f,40.f,"Submit",15);
    formClearBtn .init(fontBold,fx+180.f,submitY,110.f,40.f,"Clear",15,sf::Color(200,185,183),cText());
}

void MediCoreGUI::setupSplitForm(Screen s){
    formFieldCount=0; clearForm();
    for(int i=0;i<6;i++){delete formLabels[i];formLabels[i]=nullptr;}

    float fx=CX+10.f, fw=300.f, fh=38.f, gy=60.f, sy=CY+14.f;
    auto addF=[&](int i,const char* lbl,bool pw=false){
        formLabels[i]=makeText(fontReg,lbl,13,cMuted(),fx,sy+i*gy);
        formFields[i].init(fontReg,fx,sy+i*gy+18.f,fw,fh,pw);
        formFieldCount++;
    };

    const char* ctitle="Form";
    if(s==Screen::BookAppointmentPick){
        ctitle="Book Appointment - Step 2";
        addF(0,"Doctor ID (from list)");
        addF(1,"Date (DD-MM-YYYY)");
        addF(2,"Time Slot (09:00 – 16:00)");
    } else if(s==Screen::PayBill){
        ctitle="Pay Bill";
        addF(0,"Bill ID (from list)");
    } else if(s==Screen::RemoveDoctor){
        ctitle="Remove Doctor";
        addF(0,"Doctor ID (from list)");
    }

    delete contentTitle;
    contentTitle=makeText(fontBold,ctitle,18,cText(),SIDEW+24.f,TOPH/2.f-10.f);
    formFields[0].active=true;

    float submitY=sy+formFieldCount*gy+14.f;
    formSubmitBtn.init(fontBold,fx,submitY,160.f,40.f,"Submit",15);
    formClearBtn .init(fontBold,fx+180.f,submitY,110.f,40.f,"Clear",15,sf::Color(200,185,183),cText());

    float rpX=SIDEW+CW*0.42f, rpW=CW*0.55f-10.f;
    rightPanelBg.setPosition({rpX, TOPH+4.f});
    rightPanelBg.setSize({rpW, H-TOPH-8.f});
    rightPanelBg.setFillColor({255,255,255});
    rightPanelBg.setOutlineColor(cRose()); rightPanelBg.setOutlineThickness(1.5f);

    rightPanelVisible=true;
}

void MediCoreGUI::displayAppointments(){
    contentArea.clear();
    if(contentTitle) contentTitle->setString("My Appointments");
    bool found=false;
    for(int i=0;i<hospital.getAppointments().size();i++){
        appointment& a=hospital.getAppointments().getAll()[i];
        if(a.getPatientID()==loggedPatient->getID()){
            char line[300];
            snprintf(line,300,"ID:%-4d  Doc:%-4d  %s  %s  [%s]",
                a.getID(),a.getDoctorID(),a.getDate(),a.getTimeSlot(),a.getStatus());
            contentArea.addLine(fontReg,sf::String(line),13,cText()); found=true;
        }
    }
    if(!found) contentArea.addLine(fontReg,"No appointments found.",13,cMuted());
}

void MediCoreGUI::displayMedicalRecords(){
    contentArea.clear();
    if(contentTitle) contentTitle->setString("Medical Records");
    bool found=false;
    for(int i=0;i<hospital.getPrescriptions().size();i++){
        prescription& p=hospital.getPrescriptions().getAll()[i];
        if(p.getPatientID()==loggedPatient->getID()){
            char line[512];
            snprintf(line,512,"Date: %s  |  %s  |  %s",p.getDate(),p.getMedicines(),p.getNotes());
            contentArea.addLine(fontReg,sf::String(line),13,cText()); found=true;
        }
    }
    if(!found) contentArea.addLine(fontReg,"No medical records found.",13,cMuted());
}

void MediCoreGUI::displayBills(){
    contentArea.clear();
    if(contentTitle) contentTitle->setString("My Bills");
    float total=0.f; bool found=false;
    for(int i=0;i<hospital.getBills().size();i++){
        bill& b=hospital.getBills().getAll()[i];
        if(b.getPatientID()==loggedPatient->getID()){
            char line[300];
            snprintf(line,300,"Bill %-4d  Appt %-4d  PKR %8.2f  %-10s  %s",
                b.getID(),b.getAppointmentID(),b.getAmount(),b.getStatus(),b.getDate());
            contentArea.addLine(fontReg,sf::String(line),13,cText());
            if(strEq(b.getStatus(),"unpaid")) total+=b.getAmount();
            found=true;
        }
    }
    if(!found){ contentArea.addLine(fontReg,"No bills found.",13,cMuted()); return; }
    contentArea.addLine(fontReg,"",6,cText());
    char tot[80]; snprintf(tot,80,"Total outstanding (unpaid): PKR %.2f",total);
    contentArea.addLine(fontBold,sf::String(tot),14,cAccent());
}

void MediCoreGUI::displayTodayAppointments(){
    contentArea.clear();
    if(contentTitle) contentTitle->setString("Today's Appointments");
    bool found=false;
    for(int i=0;i<hospital.getAppointments().size();i++){
        appointment& a=hospital.getAppointments().getAll()[i];
        if(a.getDoctorID()==loggedDoctor->getID()){
            char line[256];
            snprintf(line,256,"ID:%-4d  Patient:%-4d  Slot:%-6s  [%s]",
                a.getID(),a.getPatientID(),a.getTimeSlot(),a.getStatus());
            contentArea.addLine(fontReg,sf::String(line),13,cText()); found=true;
        }
    }
    if(!found) contentArea.addLine(fontReg,"No appointments for today.",13,cMuted());
}

void MediCoreGUI::displayAllPatients(){
    contentArea.clear();
    if(contentTitle) contentTitle->setString("All Patients");
    for(int i=0;i<hospital.getPatients().size();i++){
        patient& p=hospital.getPatients().getAll()[i];
        char line[256];
        snprintf(line,256,"ID:%-4d  %-22s  Age:%-3d  Gender:%c  PKR %.2f",
            p.getID(),p.getName(),p.getAge(),p.getGender(),p.getBalance());
        contentArea.addLine(fontReg,sf::String(line),13,cText());
    }
    if(hospital.getPatients().size()==0) contentArea.addLine(fontReg,"No patients.",13,cMuted());
}

void MediCoreGUI::displayAllDoctors(){
    contentArea.clear();
    if(contentTitle) contentTitle->setString("All Doctors");
    for(int i=0;i<hospital.getDoctors().size();i++){
        doctor& d=hospital.getDoctors().getAll()[i];
        char line[256];
        snprintf(line,256,"ID:%-4d  Dr. %-20s  %-20s  Fee: PKR %.2f",
            d.getID(),d.getName(),d.getSpec(),d.getFee());
        contentArea.addLine(fontReg,sf::String(line),13,cText());
    }
    if(hospital.getDoctors().size()==0) contentArea.addLine(fontReg,"No doctors.",13,cMuted());
}

void MediCoreGUI::displayAllAppointments(){
    contentArea.clear();
    if(contentTitle) contentTitle->setString("All Appointments");
    for(int i=0;i<hospital.getAppointments().size();i++){
        appointment& a=hospital.getAppointments().getAll()[i];
        char line[300];
        snprintf(line,300,"ID:%-4d  P:%-4d  D:%-4d  %s  %-6s  [%s]",
            a.getID(),a.getPatientID(),a.getDoctorID(),
            a.getDate(),a.getTimeSlot(),a.getStatus());
        contentArea.addLine(fontReg,sf::String(line),13,cText());
    }
    if(hospital.getAppointments().size()==0) contentArea.addLine(fontReg,"No appointments.",13,cMuted());
}

void MediCoreGUI::displayUnpaidBills(){
    contentArea.clear();
    if(contentTitle) contentTitle->setString("Unpaid Bills");
    bool found=false;
    for(int i=0;i<hospital.getBills().size();i++){
        bill& b=hospital.getBills().getAll()[i];
        if(strEq(b.getStatus(),"unpaid")){
            char line[256];
            snprintf(line,256,"Bill %-4d  Patient %-4d  Appt %-4d  PKR %8.2f  %s",
                b.getID(),b.getPatientID(),b.getAppointmentID(),b.getAmount(),b.getDate());
            contentArea.addLine(fontReg,sf::String(line),13,cText()); found=true;
        }
    }
    if(!found) contentArea.addLine(fontReg,"No unpaid bills.",13,cMuted());
}

void MediCoreGUI::displaySecurityLog(){
    contentArea.clear();
    if(contentTitle) contentTitle->setString("Security Log");
    std::ifstream f("security_log.txt"); char line[200]; bool found=false;
    while(f.getline(line,200)){ contentArea.addLine(fontReg,sf::String(line),13,cText()); found=true; }
    f.close();
    if(!found) contentArea.addLine(fontReg,"No security events logged.",13,cMuted());
}

void MediCoreGUI::displayDailyReport(){
    contentArea.clear();
    if(contentTitle) contentTitle->setString("Daily Report");
    int pend=0,comp=0,nos=0,canc=0; float rev=0.f;
    for(int i=0;i<hospital.getAppointments().size();i++){
        const char* st=hospital.getAppointments().getAll()[i].getStatus();
        if(strEq(st,"scheduled")) pend++;
        else if(strEq(st,"completed")) comp++;
        else if(strEq(st,"no-show")) nos++;
        else if(strEq(st,"cancelled")) canc++;
    }
    for(int i=0;i<hospital.getBills().size();i++)
        if(strEq(hospital.getBills().getAll()[i].getStatus(),"paid"))
            rev+=hospital.getBills().getAll()[i].getAmount();
    char line[256];
    snprintf(line,256,"Total:%d  Pending:%d  Completed:%d  No-show:%d  Cancelled:%d",
        hospital.getAppointments().size(),pend,comp,nos,canc);
    contentArea.addLine(fontReg,sf::String(line),13,cText());
    snprintf(line,256,"Revenue Collected: PKR %.2f",rev);
    contentArea.addLine(fontBold,sf::String(line),14,cAccent());
    contentArea.addLine(fontReg,"",6,cText());
    contentArea.addLine(fontBold,"Doctor Summary:",13,cText());
    for(int d=0;d<hospital.getDoctors().size();d++){
        int dc=0,dp=0,dn=0,did=hospital.getDoctors().getAll()[d].getID();
        for(int a=0;a<hospital.getAppointments().size();a++){
            appointment& ap=hospital.getAppointments().getAll()[a];
            if(ap.getDoctorID()==did){
                if(strEq(ap.getStatus(),"completed")) dc++;
                else if(strEq(ap.getStatus(),"scheduled")) dp++;
                else if(strEq(ap.getStatus(),"no-show")) dn++;
            }
        }
        snprintf(line,256,"Dr. %-20s  Done:%-3d  Pending:%-3d  No-show:%d",
            hospital.getDoctors().getAll()[d].getName(),dc,dp,dn);
        contentArea.addLine(fontReg,sf::String(line),13,cText());
    }
}

void MediCoreGUI::populateRightPanelDoctors(const char* spec){
    rightPanel.clear();
    rightPanel.addLine(fontBold,sf::String("Doctors - ")+sf::String(spec),14,cAccent());
    rightPanel.addLine(fontReg,"",6,cMuted());
    bool found=false;
    for(int i=0;i<hospital.getDoctors().size();i++){
        doctor& d=hospital.getDoctors().getAll()[i];
        char dspec[80],qspec[80];
        strncpy_s(dspec,80,d.getSpec(),79);
        strncpy_s(qspec,80,spec,79);
        for(int c=0;dspec[c];c++) if(dspec[c]>='A'&&dspec[c]<='Z') dspec[c]+=32;
        for(int c=0;qspec[c];c++) if(qspec[c]>='A'&&qspec[c]<='Z') qspec[c]+=32;
        if(strstr(dspec,qspec)){
            char line[200];
            snprintf(line,200,"ID:%-4d  Dr. %s",d.getID(),d.getName());
            rightPanel.addLine(fontBold,sf::String(line),13,cText());
            snprintf(line,200,"  %-20s  Fee: PKR %.2f",d.getSpec(),d.getFee());
            rightPanel.addLine(fontReg,sf::String(line),12,cMuted());
            rightPanel.addLine(fontReg,"",4,cMuted());
            found=true;
        }
    }
    if(!found) rightPanel.addLine(fontReg,"No doctors found for that specialization.",13,cError());
}

void MediCoreGUI::populateRightPanelBills(){
    rightPanel.clear();
    rightPanel.addLine(fontBold,"Your Bills",14,cAccent());
    rightPanel.addLine(fontReg,"",6,cMuted());
    float total=0.f; bool found=false;
    for(int i=0;i<hospital.getBills().size();i++){
        bill& b=hospital.getBills().getAll()[i];
        if(b.getPatientID()==loggedPatient->getID()){
            char line[200];
            snprintf(line,200,"Bill %-4d  Appt %-4d  PKR %.2f",
                b.getID(),b.getAppointmentID(),b.getAmount());
            rightPanel.addLine(fontBold,sf::String(line),13,cText());
            snprintf(line,200,"  Status: %-10s  %s",b.getStatus(),b.getDate());
            rightPanel.addLine(fontReg,sf::String(line),12,cMuted());
            rightPanel.addLine(fontReg,"",4,cMuted());
            if(strEq(b.getStatus(),"unpaid")) total+=b.getAmount();
            found=true;
        }
    }
    if(!found){ rightPanel.addLine(fontReg,"No bills found.",13,cMuted()); return; }
    char tot[80]; snprintf(tot,80,"Outstanding: PKR %.2f",total);
    rightPanel.addLine(fontBold,sf::String(tot),14,cAccent());
}
void MediCoreGUI::populateRightPanelAllDoctors(){
    rightPanel.clear();
    rightPanel.addLine(fontBold,"All Doctors",14,cAccent());
    rightPanel.addLine(fontReg,"",6,cMuted());
    for(int i=0;i<hospital.getDoctors().size();i++){
        doctor& d=hospital.getDoctors().getAll()[i];
        char line[200];
        snprintf(line,200,"ID:%-4d  Dr. %s",d.getID(),d.getName());
        rightPanel.addLine(fontBold,sf::String(line),13,cText());
        snprintf(line,200,"  %-20s  Fee: PKR %.2f",d.getSpec(),d.getFee());
        rightPanel.addLine(fontReg,sf::String(line),12,cMuted());
        rightPanel.addLine(fontReg,"",4,cMuted());
    }
    if(hospital.getDoctors().size()==0) rightPanel.addLine(fontReg,"No doctors.",13,cMuted());
}

void MediCoreGUI::submitBookSpec(){
    if(formFields[0].buffer[0]=='\0'){
        showBanner("Please enter a specialization.",true); return;
    }
    strncpy_s(bookSpec,50,formFields[0].buffer,49);
    currentScreen=Screen::BookAppointmentPick;
    setupSplitForm(Screen::BookAppointmentPick);
    populateRightPanelDoctors(bookSpec);
    showBanner("Doctors listed. Enter Doctor ID, Date and Time, then Submit.",false);
}

void MediCoreGUI::submitBookAppointment(){
    int docID=atoi(formFields[0].buffer);
    char date[20],slot[20];
    strncpy_s(date,20,formFields[1].buffer,19);
    strncpy_s(slot,20,formFields[2].buffer,19);

    doctor* d=hospital.getDoctors().findByID(docID);
    if(!d){ showBanner("Doctor not found.",true); return; }

    char dspec[80],qspec[80];
    strncpy_s(dspec,80,d->getSpec(),79);
    strncpy_s(qspec,80,bookSpec,79);
    for(int c=0;dspec[c];c++) if(dspec[c]>='A'&&dspec[c]<='Z') dspec[c]+=32;
    for(int c=0;qspec[c];c++) if(qspec[c]>='A'&&qspec[c]<='Z') qspec[c]+=32;
    if(!strstr(dspec,qspec)){
        showBanner("That doctor's specialization doesn't match. Check the list.",true); return;
    }

    if(!Validator::validateDate(date)){ showBanner("Invalid date. Use DD-MM-YYYY.",true); return; }
    const char slots[8][10]={"09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00"};
    bool validSlot=false;
    for(int s=0;s<8;s++) if(strEq(slot,slots[s])){validSlot=true;break;}
    if(!validSlot){ showBanner("Invalid time slot. Use HH:00 from 09:00-16:00.",true); return; }

    for(int i=0;i<hospital.getAppointments().size();i++){
        appointment& a=hospital.getAppointments().getAll()[i];
        if(a.getDoctorID()==docID&&strEq(a.getDate(),date)&&
           strEq(a.getTimeSlot(),slot)&&!strEq(a.getStatus(),"cancelled")){
            showBanner("That slot is already taken.",true); return;
        }
    }
    if(loggedPatient->getBalance()<d->getFee()){
        showBanner("Insufficient balance.",true); return;
    }

    int apptID=hospital.getAppointments().size()+1;
    appointment app(apptID,loggedPatient->getID(),docID,date,slot,"scheduled");
    hospital.getAppointments().add(app);
    FileHandler::appendAppointment(app);

    int billID=hospital.getBills().size()+1;
    bill b(billID,loggedPatient->getID(),apptID,d->getFee(),"unpaid",date);
    hospital.getBills().add(b);
    FileHandler::appendBill(b);

    char bal[80]; snprintf(bal,80,"Bal: PKR %.2f",loggedPatient->getBalance());
    if(userInfoExtra) userInfoExtra->setString(sf::String(bal));
    showBanner("Appointment booked successfully!",false);
    currentScreen=Screen::BookAppointmentSpec;
    setupForm(Screen::BookAppointmentSpec);
}

void MediCoreGUI::submitCancelAppointment(){
    int id=atoi(formFields[0].buffer);
    appointment* a=hospital.getAppointments().findByID(id);
    if(!a||a->getPatientID()!=loggedPatient->getID()){
        showBanner("Appointment not found or not yours.",true); return;
    }
    if(strEq(a->getStatus(),"cancelled")){ showBanner("Already cancelled.",true); return; }
    a->setStatus("cancelled");
    for(int i=0;i<hospital.getBills().size();i++){
        bill* b=&hospital.getBills().getAll()[i];
        if(b->getAppointmentID()==a->getID()){
            if(strEq(b->getStatus(),"paid")){ loggedPatient->addBalance(b->getAmount()); b->setStatus("refunded"); }
            else b->setStatus("cancelled"); break;
        }
    }
    FileHandler::updateAppointments(hospital.getAppointments());
    FileHandler::updateBills(hospital.getBills());
    FileHandler::updatePatients(hospital.getPatients());
    showBanner("Appointment cancelled successfully.",false); clearForm();
}

void MediCoreGUI::submitTopUp(){
    float amount=(float)atof(formFields[0].buffer);
    if(!Validator::validatePositiveFloat(amount)){
        showBanner("Enter a valid positive amount.",true); return;
    }
    *loggedPatient+=amount;
    FileHandler::updatePatients(hospital.getPatients());
    char msg[80]; snprintf(msg,80,"Balance updated. New: PKR %.2f",loggedPatient->getBalance());
    showBanner(msg,false);
    char bal[80]; snprintf(bal,80,"Bal: PKR %.2f",loggedPatient->getBalance());
    if(userInfoExtra) userInfoExtra->setString(sf::String(bal));
    clearForm();
}

void MediCoreGUI::submitPayBill(){
    int id=atoi(formFields[0].buffer);
    bill* b=hospital.getBills().findByID(id);
    if(!b||b->getPatientID()!=loggedPatient->getID()){
        showBanner("Bill not found or not yours.",true); return;
    }
    if(strEq(b->getStatus(),"paid")){ showBanner("Bill already paid.",true); return; }
    if(loggedPatient->getBalance()<b->getAmount()){ showBanner("Insufficient balance.",true); return; }
    loggedPatient->deductBalance(b->getAmount());
    b->setStatus("paid");
    FileHandler::updateBills(hospital.getBills());
    FileHandler::updatePatients(hospital.getPatients());
    char msg[80]; snprintf(msg,80,"Bill paid. Remaining: PKR %.2f",loggedPatient->getBalance());
    showBanner(msg,false);
    char bal[80]; snprintf(bal,80,"Bal: PKR %.2f",loggedPatient->getBalance());
    if(userInfoExtra) userInfoExtra->setString(sf::String(bal));
    clearForm();
    populateRightPanelBills();  
}

void MediCoreGUI::submitAddDoctor(){
    char name[50],spec[50],contact[20],password[50];
    strncpy_s(name,50,formFields[0].buffer,49);
    strncpy_s(spec,50,formFields[1].buffer,49);
    strncpy_s(contact,20,formFields[2].buffer,19);
    strncpy_s(password,50,formFields[3].buffer,49);
    float fee=(float)atof(formFields[4].buffer);
    if(name[0]=='\0'){ showBanner("Name cannot be empty.",true); return; }
    if(spec[0]=='\0'){ showBanner("Specialization cannot be empty.",true); return; }
    if(!Validator::validateContact(contact)){ showBanner("Contact must be 11 digits.",true); return; }
    if(!Validator::validatePassword(password)){ showBanner("Password must be 6+ chars.",true); return; }
    if(!Validator::validatePositiveFloat(fee)){ showBanner("Fee must be positive.",true); return; }
    int maxID=0;
    for(int i=0;i<hospital.getDoctors().size();i++){
        int did=hospital.getDoctors().getAll()[i].getID();
        if(did>maxID) maxID=did;
    }
    int id=maxID+1;
    doctor d(id,name,spec,contact,password,fee);
    hospital.getDoctors().add(d);
    FileHandler::appendDoctor(d);
    char msg[80]; snprintf(msg,80,"Doctor added. ID: %d",id);
    showBanner(msg,false); clearForm();
}

void MediCoreGUI::submitRemoveDoctor(){
    int id=atoi(formFields[0].buffer);
    if(id==0){ showBanner("Enter a valid Doctor ID.",true); return; }
    FileHandler::deleteDoctor(id,hospital.getDoctors());
    showBanner("Doctor removed.",false); clearForm();
    populateRightPanelAllDoctors();   
}

void MediCoreGUI::submitAddPatient(){
    char name[50],contact[20],password[50];
    strncpy_s(name,50,formFields[0].buffer,49);
    int age=atoi(formFields[1].buffer);
    char gender=formFields[2].buffer[0];
    strncpy_s(contact,20,formFields[3].buffer,19);
    strncpy_s(password,50,formFields[4].buffer,49);
    float balance=(float)atof(formFields[5].buffer);
    if(!Validator::validateAge(age)){ showBanner("Invalid age.",true); return; }
    if(!Validator::validateGender(gender)){ showBanner("Gender must be M or F.",true); return; }
    if(!Validator::validateContact(contact)){ showBanner("Contact must be 11 digits.",true); return; }
    if(!Validator::validatePassword(password)){ showBanner("Password must be 6+ chars.",true); return; }
    if(!Validator::validatePositiveFloat(balance)){ showBanner("Balance must be positive.",true); return; }
    int maxID=0;
    for(int i=0;i<hospital.getPatients().size();i++){
        int pid=hospital.getPatients().getAll()[i].getID();
        if(pid>maxID) maxID=pid;
    }
    int id=maxID+1;
    patient p(id,name,password,age,gender,contact,balance);
    hospital.getPatients().add(p);
    FileHandler::appendPatient(p);
    char msg[60]; snprintf(msg,60,"Patient added. ID: %d",id);
    showBanner(msg,false); clearForm();
}

void MediCoreGUI::submitRemovePatient(){
    int id=atoi(formFields[0].buffer);
    FileHandler::deletePatient(id,hospital.getPatients(),
        hospital.getAppointments(),hospital.getBills(),hospital.getPrescriptions());
    showBanner("Patient removed.",false); clearForm();
}

void MediCoreGUI::submitWritePrescription(){
    int apptID=atoi(formFields[0].buffer);
    appointment* a=hospital.getAppointments().findByID(apptID);
    if(!a||a->getDoctorID()!=loggedDoctor->getID()){
        showBanner("Appointment not found or not yours.",true); return;
    }
    if(!strEq(a->getStatus(),"completed")){
        showBanner("Appointment must be completed first.",true); return;
    }
    int newID=hospital.getPrescriptions().size()+1;
    prescription p(newID,apptID,a->getPatientID(),loggedDoctor->getID(),
        "10-05-2026",formFields[1].buffer,formFields[2].buffer);
    hospital.getPrescriptions().add(p);
    FileHandler::appendPrescription(p);
    showBanner("Prescription saved.",false); clearForm();
}

void MediCoreGUI::submitViewPatientHistory(){
    int pid=atoi(formFields[0].buffer);
    contentArea.clear();
    patient* pt=hospital.getPatients().findByID(pid);
    if(pt){
        char hdr[80]; snprintf(hdr,80,"History for: %s (ID: %d)",pt->getName(),pid);
        contentArea.addLine(fontBold,sf::String(hdr),15,cAccent());
        contentArea.addLine(fontReg,"",6,cMuted());
    }
    bool found=false;
    for(int i=0;i<hospital.getPrescriptions().size();i++){
        prescription& p=hospital.getPrescriptions().getAll()[i];
        if(p.getPatientID()==pid){
            char line[512];
            snprintf(line,512,"Date: %s  |  Medicines: %s  |  Notes: %s",
                p.getDate(),p.getMedicines(),p.getNotes());
            contentArea.addLine(fontReg,sf::String(line),13,cText()); found=true;
        }
    }
    if(!found){
        contentArea.addLine(fontReg,"No prescription records found for this patient.",13,cMuted());
        showBanner("No records found.",true);
    } else {
        showBanner("Patient history loaded.",false);
    }
    currentScreen=Screen::ViewPatientHistoryResult;
    delete contentTitle;
    contentTitle=makeText(fontBold,"Patient History",18,cText(),SIDEW+24.f,TOPH/2.f-10.f);
    formFieldCount=0;   
    rightPanelVisible=false;
}

void MediCoreGUI::submitMarkComplete(){
    int id=atoi(formFields[0].buffer);
    appointment* a=hospital.getAppointments().findByID(id);
    if(!a||a->getDoctorID()!=loggedDoctor->getID()){
        showBanner("Appointment not found or not yours.",true); return;
    }
    a->setStatus("completed");
    FileHandler::updateAppointments(hospital.getAppointments());
    showBanner("Appointment marked as completed.",false); clearForm();
}

void MediCoreGUI::submitMarkNoShow(){
    int id=atoi(formFields[0].buffer);
    appointment* a=hospital.getAppointments().findByID(id);
    if(!a||a->getDoctorID()!=loggedDoctor->getID()){
        showBanner("Appointment not found or not yours.",true); return;
    }
    a->setStatus("no-show");
    for(int i=0;i<hospital.getBills().size();i++){
        bill* b=&hospital.getBills().getAll()[i];
        if(b->getAppointmentID()==a->getID()){ b->setStatus("cancelled"); break; }
    }
    FileHandler::updateAppointments(hospital.getAppointments());
    FileHandler::updateBills(hospital.getBills());
    showBanner("Marked as no-show.",false); clearForm();
}

void MediCoreGUI::handlePatientAction(int idx){
    switch(idx){
    case 0: 
        currentScreen=Screen::BookAppointmentSpec;
        setupForm(Screen::BookAppointmentSpec);
        break;
    case 1: currentScreen=Screen::CancelAppointment; setupForm(Screen::CancelAppointment); break;
    case 2: currentScreen=Screen::ViewAppointments;  displayAppointments();  break;
    case 3: currentScreen=Screen::ViewMedicalRecords;displayMedicalRecords(); break;
    case 4: currentScreen=Screen::ViewBills;         displayBills();          break;
   
    case 5:
        currentScreen=Screen::PayBill;
        setupSplitForm(Screen::PayBill);
        populateRightPanelBills();
        delete contentTitle;
        contentTitle=makeText(fontBold,"Pay Bill",18,cText(),SIDEW+24.f,TOPH/2.f-10.f);
        break;
    case 6: currentScreen=Screen::TopUpBalance; setupForm(Screen::TopUpBalance); break;
    case 7: loggedPatient=nullptr; currentScreen=Screen::MainMenu; setupMainMenu(); break;
    }
}

void MediCoreGUI::handleDoctorAction(int idx){
    switch(idx){
    case 0: currentScreen=Screen::ViewTodayAppointments; displayTodayAppointments(); break;
    case 1: currentScreen=Screen::MarkComplete;          setupForm(Screen::MarkComplete); break;
    case 2: currentScreen=Screen::MarkNoShow;            setupForm(Screen::MarkNoShow);   break;
    case 3: currentScreen=Screen::WritePrescription;     setupForm(Screen::WritePrescription); break;
    case 4: 
        currentScreen=Screen::ViewPatientHistoryInput;
        setupForm(Screen::ViewPatientHistoryInput);
        break;
    case 5: loggedDoctor=nullptr; currentScreen=Screen::MainMenu; setupMainMenu(); break;
    }
}

void MediCoreGUI::handleAdminAction(int idx){
    switch(idx){
    case 0:  currentScreen=Screen::AddDoctor;    setupForm(Screen::AddDoctor);    break;
 
    case 1:
        currentScreen=Screen::RemoveDoctor;
        setupSplitForm(Screen::RemoveDoctor);
        populateRightPanelAllDoctors();
        delete contentTitle;
        contentTitle=makeText(fontBold,"Remove Doctor",18,cText(),SIDEW+24.f,TOPH/2.f-10.f);
        break;
    case 2:  currentScreen=Screen::AddPatient;   setupForm(Screen::AddPatient);   break;
    case 3:  currentScreen=Screen::RemovePatient;setupForm(Screen::RemovePatient); break;
    case 4:  currentScreen=Screen::ViewAllPatients;     displayAllPatients();     break;
    case 5:  currentScreen=Screen::ViewAllDoctors;      displayAllDoctors();      break;
    case 6:  currentScreen=Screen::ViewAllAppointments; displayAllAppointments(); break;
    case 7:  currentScreen=Screen::ViewUnpaidBills;     displayUnpaidBills();     break;
    case 8:  currentScreen=Screen::ViewSecurityLog;     displaySecurityLog();     break;
    case 9:  currentScreen=Screen::GenerateDailyReport; displayDailyReport();     break;
    case 10: loggedAdmin=nullptr; currentScreen=Screen::MainMenu; setupMainMenu(); break;
    }
}

void MediCoreGUI::handleTextInput(uint32_t unicode){
    InputField* target=nullptr;
    if(currentScreen==Screen::PatientLogin||
       currentScreen==Screen::DoctorLogin ||
       currentScreen==Screen::AdminLogin){
        if(loginID.active)   target=&loginID;
        if(loginPass.active) target=&loginPass;
    } else {
        for(int i=0;i<formFieldCount;i++)
            if(formFields[i].active){ target=&formFields[i]; break; }
    }
    if(!target) return;
    if(unicode==8){ if(target->len>0){ target->len--; target->buffer[target->len]='\0'; } }
    else if(unicode>=32&&unicode<127&&target->len<198){
        target->buffer[target->len++]=(char)unicode;
        target->buffer[target->len]='\0';
    }
    target->updateDisplay();
}

void MediCoreGUI::renderInputField(InputField& f){
    f.box.setOutlineColor(f.active?cAccent():cRose());
    f.box.setOutlineThickness(f.active?2.5f:2.f);
    f.draw(window);
    if(f.active&&f.display){
        static sf::Clock cur;
        if((int)(cur.getElapsedTime().asSeconds()*2)%2==0){
            sf::RectangleShape cursor({1.5f,16.f});
            sf::FloatRect tb=f.display->getGlobalBounds();
            cursor.setPosition({tb.position.x+tb.size.x+2.f,
                                 f.box.getPosition().y+f.box.getSize().y/2.f-8.f});
            cursor.setFillColor(cAccent()); window.draw(cursor);
        }
    }
}

void MediCoreGUI::handleEvents(){
    sf::Vector2f mouse(sf::Mouse::getPosition(window));

    while(auto ev=window.pollEvent()){
        if(ev->is<sf::Event::Closed>()){ window.close(); return; }

        if(const auto* te=ev->getIf<sf::Event::TextEntered>())
            handleTextInput(te->unicode);

        if(const auto* mc=ev->getIf<sf::Event::MouseButtonPressed>()){
            if(mc->button!=sf::Mouse::Button::Left) continue;
            sf::Vector2f pos(mc->position);

            if(currentScreen==Screen::Splash){
                currentScreen=Screen::MainMenu; setupMainMenu(); continue;
            }

            if(currentScreen==Screen::MainMenu){
                for(int i=0;i<3;i++){
                    if(mainRoleBtns[i].contains(pos)){
                        playClick();
                        Screen s=(i==0)?Screen::PatientLogin:(i==1)?Screen::DoctorLogin:Screen::AdminLogin;
                        currentScreen=s; setupLogin(s); break;
                    }
                }
                continue;
            }

            if(currentScreen==Screen::PatientLogin||
               currentScreen==Screen::DoctorLogin ||
               currentScreen==Screen::AdminLogin){
                loginID.active  =loginID  .box.getGlobalBounds().contains(pos);
                loginPass.active=loginPass.box.getGlobalBounds().contains(pos);

                if(loginBack.contains(pos)){
                    playClick(); currentScreen=Screen::MainMenu; setupMainMenu(); continue;
                }
                if(loginSubmit.contains(pos)){
                    playClick();
                    int id=atoi(loginID.buffer);
                    auto lockOut=[&](const char* role){
                        loginAttempts++;
                        if(loginAttempts>=3){
                            showBanner("Account locked. Contact admin.",true);
                            std::ofstream lf("security_log.txt",std::ios::app);
                            lf<<"LOCKED -> Role: "<<role<<" | ID: "<<id<<"\n";
                            lf.close();
                            currentScreen=Screen::MainMenu; setupMainMenu();
                        } else {
                            char msg[80];
                            snprintf(msg,80,"Invalid credentials. Attempts left: %d",3-loginAttempts);
                            showBanner(msg,true);
                        }
                    };
                    if(currentScreen==Screen::PatientLogin){
                        patient* p=hospital.getPatients().findByID(id);
                        if(p&&strEq(p->getPassword(),loginPass.buffer)){
                            loggedPatient=p; currentScreen=Screen::PatientDashboard;
                            setupDashboard(Screen::PatientDashboard);
                        } else lockOut("Patient");
                    } else if(currentScreen==Screen::DoctorLogin){
                        doctor* d=hospital.getDoctors().findByID(id);
                        if(d&&strEq(d->getPassword(),loginPass.buffer)){
                            loggedDoctor=d; currentScreen=Screen::DoctorDashboard;
                            setupDashboard(Screen::DoctorDashboard);
                        } else lockOut("Doctor");
                    } else {
                        admin* a=hospital.getAdmins().findByID(id);
                        if(a&&strEq(a->getPassword(),loginPass.buffer)){
                            loggedAdmin=a; currentScreen=Screen::AdminDashboard;
                            setupDashboard(Screen::AdminDashboard);
                        } else lockOut("Admin");
                    }
                    continue;
                }
                continue;
            }

            bool hasSidebar=(loggedPatient||loggedDoctor||loggedAdmin);
            if(hasSidebar && musicBtn.contains(pos)){
                playClick();
                musicOn=!musicOn;
                if(musicOn){ ambientMusic.play(); musicBtn.label->setString("Music: ON"); }
                else        { ambientMusic.pause(); musicBtn.label->setString("Music: OFF"); }
                continue;
            }

            int si=sidebarHit(pos);
            if(si>=0){
                playClick();
                if(loggedPatient)     handlePatientAction(si);
                else if(loggedDoctor) handleDoctorAction(si);
                else if(loggedAdmin)  handleAdminAction(si);
                continue;
            }

            for(int i=0;i<formFieldCount;i++)
                formFields[i].active=formFields[i].box.getGlobalBounds().contains(pos);

            if(formFieldCount>0){
                if(formSubmitBtn.contains(pos)){
                    playClick();
                    switch(currentScreen){
                    case Screen::BookAppointmentSpec:  submitBookSpec();           break;
                    case Screen::BookAppointmentPick:  submitBookAppointment();    break;
                    case Screen::CancelAppointment:    submitCancelAppointment();  break;
                    case Screen::TopUpBalance:         submitTopUp();              break;
                    case Screen::PayBill:              submitPayBill();            break;
                    case Screen::AddDoctor:            submitAddDoctor();          break;
                    case Screen::RemoveDoctor:         submitRemoveDoctor();       break;
                    case Screen::AddPatient:           submitAddPatient();         break;
                    case Screen::RemovePatient:        submitRemovePatient();      break;
                    case Screen::WritePrescription:    submitWritePrescription();  break;
                    case Screen::ViewPatientHistoryInput: submitViewPatientHistory(); break;
                    case Screen::MarkComplete:         submitMarkComplete();       break;
                    case Screen::MarkNoShow:           submitMarkNoShow();         break;
                    default: break;
                    }
                }
                if(formClearBtn.contains(pos)){
                    playClick(); clearForm();
                   
                    rightPanel.scrollOffset=0.f;
                }
            }
        }

        if(const auto* sw=ev->getIf<sf::Event::MouseWheelScrolled>()){
            
            if(rightPanelVisible && mouse.x > SIDEW+CW*0.42f)
                rightPanel.scrollOffset-=sw->delta*22.f;
            else
                contentArea.scrollOffset-=sw->delta*22.f;
            if(contentArea.scrollOffset<0.f) contentArea.scrollOffset=0.f;
            if(rightPanel.scrollOffset<0.f)  rightPanel.scrollOffset =0.f;
        }
    }
    if(currentScreen==Screen::MainMenu) hoverBtns(mainRoleBtns,3,mouse);

    bool hasSidebar=(loggedPatient||loggedDoctor||loggedAdmin);
    if(hasSidebar){
        for(int i=0;i<sidebarCount;i++){
            bool h=sidebarBtns[i].contains(mouse);
            sidebarBtns[i].hovered=h;
            sidebarBtns[i].shape.setFillColor(h?cSideHov():cSideBtn());
            if(sidebarBtns[i].label) sidebarBtns[i].label->setFillColor(h?cWhite():cRose());
        }
        // Music button hover
        musicBtn.setHover(musicBtn.contains(mouse));
        if(!musicBtn.hovered) musicBtn.shape.setFillColor({100,75,73});

        if(formFieldCount>0){
            formSubmitBtn.setHover(formSubmitBtn.contains(mouse));
            formClearBtn.setHover(formClearBtn.contains(mouse));
            if(!formClearBtn.hovered){
                formClearBtn.shape.setFillColor({200,185,183});
                if(formClearBtn.label) formClearBtn.label->setFillColor(cText());
            }
        }
    }
    if(currentScreen==Screen::PatientLogin||
       currentScreen==Screen::DoctorLogin ||
       currentScreen==Screen::AdminLogin){
        loginSubmit.setHover(loginSubmit.contains(mouse));
        loginBack.setHover(loginBack.contains(mouse));
        if(!loginBack.hovered){
            loginBack.shape.setFillColor({200,185,183});
            if(loginBack.label) loginBack.label->setFillColor(cText());
        }
    }
}

void MediCoreGUI::update(){
    banner.update();
    if(currentScreen==Screen::Splash&&splashClock.getElapsedTime().asSeconds()>3.f){
        currentScreen=Screen::MainMenu; setupMainMenu();
    }
}

void MediCoreGUI::renderSplash(){
    float t=splashClock.getElapsedTime().asSeconds();
    uint8_t alpha=(uint8_t)std::min(255.f,t*140.f);
    if(splashTitle) splashTitle->setFillColor({230,200,198,alpha});
    if(splashSub)   splashSub  ->setFillColor({156,126,124,alpha});
    splashLine.setFillColor({230,200,198,alpha});
    window.draw(splashBg); window.draw(splashLine);
    if(splashTitle) window.draw(*splashTitle);
    if(splashSub)   window.draw(*splashSub);
}

void MediCoreGUI::renderMainMenu(){
    window.draw(mainBg); window.draw(mainPanel);
    sf::RectangleShape strip({5.f,80.f});
    strip.setFillColor(cRose()); strip.setPosition({30.f,174.f}); window.draw(strip);
    if(mainTitle)      window.draw(*mainTitle);
    if(mainSub)        window.draw(*mainSub);
    if(mainWelcome)    window.draw(*mainWelcome);
    if(mainWelcomeSub) window.draw(*mainWelcomeSub);
    for(int i=0;i<3;i++) mainRoleBtns[i].draw(window);
}

void MediCoreGUI::renderLogin(){
    window.draw(mainBg); window.draw(mainPanel);
    if(mainTitle) window.draw(*mainTitle);
    if(mainSub)   window.draw(*mainSub);
    window.draw(loginCard);
    if(loginTitle)   window.draw(*loginTitle);
    if(loginSub)     window.draw(*loginSub);
    if(loginIDLbl)   window.draw(*loginIDLbl);
    renderInputField(loginID);
    if(loginPassLbl) window.draw(*loginPassLbl);
    renderInputField(loginPass);
    loginSubmit.draw(window); loginBack.draw(window);
}

void MediCoreGUI::renderDashboardBase(){
    
    sf::RectangleShape bg({W-SIDEW,H});
    bg.setFillColor(cBg()); bg.setPosition({SIDEW,0}); window.draw(bg);

   
    window.draw(sidebar); window.draw(sideUserCard);
    sf::RectangleShape div({SIDEW-24.f,1.f});
    div.setFillColor({80,65,67}); div.setPosition({12.f,110.f}); window.draw(div);
    if(userInfoName)  window.draw(*userInfoName);
    if(userInfoRole)  window.draw(*userInfoRole);
    if(userInfoExtra) window.draw(*userInfoExtra);
    if(sideLogoText)  window.draw(*sideLogoText);
    for(int i=0;i<sidebarCount;i++) sidebarBtns[i].draw(window);

    window.draw(topBar); window.draw(topAccent);
    if(contentTitle) window.draw(*contentTitle);

    musicBtn.draw(window);
}

void MediCoreGUI::renderContentLines(){
    float cx=CX, cy=CY, lineH=22.f;
    for(size_t i=0;i<contentArea.lines.size();i++){
        float y=cy+i*lineH-contentArea.scrollOffset;
        if(y<cy-lineH||y>H-50.f) continue;
        if(contentArea.lines[i].text){
            contentArea.lines[i].text->setPosition({cx,y});
            window.draw(*contentArea.lines[i].text);
        }
        sf::RectangleShape sep({W-SIDEW-40.f,1.f});
        sep.setFillColor({230,200,198,45}); sep.setPosition({cx,y+18.f});
        window.draw(sep);
    }
}

void MediCoreGUI::renderDashboard(){
    renderDashboardBase();
    renderContentLines();
}

void MediCoreGUI::renderForm(){
    
    for(int i=0;i<formFieldCount;i++){
        if(formLabels[i]) window.draw(*formLabels[i]);
        renderInputField(formFields[i]);
    }
    if(formFieldCount>0){
        formSubmitBtn.draw(window);
        formClearBtn.draw(window);
    }
}

void MediCoreGUI::renderSplitScreen(){
    renderDashboardBase();

    for(int i=0;i<formFieldCount;i++){
        if(formLabels[i]) window.draw(*formLabels[i]);
        renderInputField(formFields[i]);
    }
    if(formFieldCount>0){
        formSubmitBtn.draw(window);
        formClearBtn.draw(window);
    }
    window.draw(rightPanelBg);

    float rpX=rightPanelBg.getPosition().x+16.f;
    float rpY=rightPanelBg.getPosition().y+14.f;
    float rpMaxY=rightPanelBg.getPosition().y+rightPanelBg.getSize().y-10.f;
    float lineH=20.f;

    for(size_t i=0;i<rightPanel.lines.size();i++){
        float y=rpY+i*lineH-rightPanel.scrollOffset;
        if(y<rpY-lineH||y>rpMaxY) continue;
        if(rightPanel.lines[i].text){
            rightPanel.lines[i].text->setPosition({rpX,y});
            window.draw(*rightPanel.lines[i].text);
        }
    }
}

void MediCoreGUI::render(){
    window.clear(cBg());
    switch(currentScreen){
    case Screen::Splash:    renderSplash();    break;
    case Screen::MainMenu:  renderMainMenu();  break;
    case Screen::PatientLogin:
    case Screen::DoctorLogin:
    case Screen::AdminLogin: renderLogin();    break;

    case Screen::PatientDashboard:
    case Screen::DoctorDashboard:
    case Screen::AdminDashboard:
    case Screen::ViewAppointments:
    case Screen::ViewMedicalRecords:
    case Screen::ViewBills:
    case Screen::ViewTodayAppointments:
    case Screen::ViewAllPatients:
    case Screen::ViewAllDoctors:
    case Screen::ViewAllAppointments:
    case Screen::ViewUnpaidBills:
    case Screen::ViewSecurityLog:
    case Screen::GenerateDailyReport:
    case Screen::ViewPatientHistoryResult:   
        renderDashboard(); break;

    case Screen::BookAppointmentPick:
    case Screen::PayBill:
    case Screen::RemoveDoctor:
        renderSplitScreen(); break;

    default: renderForm(); break;
    }
    banner.draw(window);
    window.display();
}

void MediCoreGUI::run(){
    while(window.isOpen()){ handleEvents(); update(); render(); }
}
