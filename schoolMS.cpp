// Dsa Lab Project - Student Management System
#include <iostream>
#include <string>
#include <iomanip> 
#include <limits>  

using namespace std;

// --- CONFIGURATION ---
const int MAX_STUDENTS_PER_CLASS = 60;
const int NUM_SUBJECTS = 5;
const int NUM_DAYS = 30;
const int NUM_CLASSES = 5;

// --- DATA STRUCTURES ---

struct Student
{
    int rollNo;
    string name;
    float marks[NUM_SUBJECTS];
    int attendance[NUM_DAYS]; // -1 (None), 0 (Absent), 1 (Present)
    bool active;

    Student()
    {
        rollNo = 0;
        active = true;
        name = "Undefined";
        for (int i = 0; i < NUM_SUBJECTS; i++) marks[i] = 0.0f;
        for (int i = 0; i < NUM_DAYS; i++) attendance[i] = -1;
    }
};

struct Classroom
{
    int classID;
    Student students[MAX_STUDENTS_PER_CLASS];
    int studentCount;
};
struct Admin
{
    string username;
    string password;
    string fullName;
    string designation;
    bool isActive;

    Admin()
    {
        username = "";
        password = "";
        fullName = "Not Set";
        designation = "Administrator";
        isActive = false;
    }
    
    Admin(string uname, string pwd, string name, string desig)
    {
        username = uname;
        password = pwd;
        fullName = name;
        designation = desig;
        isActive = true;
    }
};
// --- GLOBAL STATE ---
Classroom classes[NUM_CLASSES];
// ** ADMIN SECTION **
const int MAX_ADMINS = 10;
Admin admins[MAX_ADMINS];
int adminCount = 0;
// --- PROTOTYPES ---

// Input Validation
int getValidInt(string prompt, int min = 0, int max = 2147483647);
string getValidString(string prompt);

// Auth & UI
bool performLogin();
void showDashboard();

// Core Utilities
int selectClass();

// Modules
void handleStudentManagement();
void handleAcademicRecords();
void handleAttendance();
void handleAnalytics();

// Student Operations
void addStudent(Classroom &cls);
void deleteStudent(Classroom &cls);
void searchStudent(Classroom &cls);
void displayAllStudents(Classroom &cls);
void modifyStudent(Classroom &cls);
int findStudent_BinarySearch(Classroom &cls, int rollNo);

// Academic Operations
void enterMarks(Classroom &cls);
void displayReportCard(Classroom &cls);
void showClassResultReport(Classroom &cls);
char getGrade(float average);

// Attendance Operations
void runBatchRollCall(Classroom &cls);
void showStudentAttendanceStats(Classroom &cls);
void showClassAttendanceReport(Classroom &cls);

// Analytics
void showComprehensiveAnalytics(Classroom &cls);

// ** ADMIN SECTION **
void initializeAdmins();
void addNewAdmin();
void viewAllAdmins();
void deleteAdmin();
void modifyAdmin();
void handleAdminManagement();
// --- MAIN EXECUTION ---
void autoPopulateData()
{
    // Predefined realistic Pakistani names
    string names[] = {
        "Ahmed Ali", "Fatima Khan ", "Hassan Malik", "Ayesha Ahmed", "Usman Tariq",
        "Zainab Hassan", "Bilal Raza", "Mariam Iqbal", "Saad Hussain", "Hira Siddiqui",
        "Hamza Shahid", "Amina Farooq", "Faisal Aziz", "Nadia Rashid", "Imran Saeed",
        "Sana Bibi", "Kamran Javed ", "Rabia Noor", "Arslan Butt", "Javeria Asif",
        "Talha Nasir", "Mehwish Ali", "Adnan Qadir", "Samia Riaz", "Junaid Aslam",
        "Farah Mahmood", "Waseem Akram", "Nimra Shah", "Shoaib Akhtar", "Bushra Yousaf",
        "Rizwan Ahmed", "Laiba Zahid ", "Asif Munir", "Maryam Saleem", "Kashif Mehmood",
        "Aliza Nawaz", "Fahad Umar", "Sadaf Khan", "Waqas Jamil", "Anum Tanveer",
        "Nabeel Haider", "Saima Akram", "Tariq Bashir", "Uzma Pervaiz", "Shahid Afridi",
        "Hina Aslam", "Zohaib Hassan", "Aiman Rauf", "Naveed Iqbal", "Rida Zafar",
        "Muneeb Sultan", "Kiran Ashraf", "Farhan Ghani", "Mahnoor Malik", "Irfan Lodhi",
        "Sidra Batool", "Yasir Anwar", "Arooj Saeed", "Rehan Shafiq", "Tooba Habib"
    };

    int nameCount = 60;

    // Loop through all 5 classes
    for (int c = 0; c < NUM_CLASSES; c++)
    {
        Classroom &cls = classes[c];
        cls.studentCount = 40; // Set 40 students per class

        // Populate students
        for (int i = 0; i < 40; i++)
        {
            Student &s = cls.students[i];
            
            // Roll numbers: Class 1: 1001-1040, Class 2: 2001-2040, etc.
            s.rollNo = (c + 1) * 1000 + (i + 1);
            
            // Assign name (cycle through name array)
            s.name = names[i % nameCount];
            
            // Generate realistic marks (mix of good, average, weak students)
            for (int sub = 0; sub < NUM_SUBJECTS; sub++)
            {
                // Create variety: some excellent, some average, some weak
                if (i < 10) 
                    s.marks[sub] = 80 + (i * 2) % 21; // Top students (80-100)
                else if (i < 25)
                    s.marks[sub] = 60 + (i * 3) % 25; // Average students (60-84)
                else
                    s.marks[sub] = 40 + (i * 2) % 30; // Weaker students (40-69)
            }
            
            // Generate attendance (optional: 70-100% attendance)
            for (int d = 0; d < NUM_DAYS; d++)
            {
                // 80% chance of being present
                if ((i + d) % 5 != 0) 
                    s.attendance[d] = 1; // Present
                else
                    s.attendance[d] = 0; // Absent
            }
            
            s.active = true;
        }
    }

    // cout << "\n[System] Auto-populated 200 students across 5 classes.\n";
}
int main()
{
    // 1. Initialize System
    for (int i = 0; i < NUM_CLASSES; i++)
    {
        classes[i].classID = i + 1;
        classes[i].studentCount = 0;
    }
    initializeAdmins();
    autoPopulateData(); 
    // 2. Perform Login
    if (!performLogin())
    {
        cout << "\nAccess Denied. Exiting...\n";
        return 0;
    }

    // 3. Main Menu Loop
    int choice;
    do
    {
        showDashboard();

        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Student Management\n";
        cout << "2. Academic Records\n";
        cout << "3. Attendance Module\n";
        cout << "4. Analytics & Reports\n";
        cout << "5. Admin Management \n";  
        cout << "6. Exit\n";
        cout << "=====================\n";

        choice = getValidInt("Enter Choice: ", 1, 5);

        switch (choice)
        {
        case 1: handleStudentManagement(); break;
        case 2: handleAcademicRecords(); break;
        case 3: handleAttendance(); break;
        case 4: handleAnalytics(); break;
        case 5: handleAdminManagement(); break; 
        case 6: cout << "\nSaving data... (Simulation) Goodbye!\n"; break;
        }
    } while (choice != 6);

    return 0;
}

// --- INPUT VALIDATION HELPERS ---

int getValidInt(string prompt, int min, int max)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < min || value > max)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between " << min << " and " << max << ".\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string getValidString(string prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// --- AUTHENTICATION ---

bool performLogin()
{
    string username, password;
    cout << "\n==========================================\n";
    cout << "   SYSTEM LOGIN REQUIRED \n";
    cout << "==========================================\n";

    int attempts = 0;
    while (attempts < 5)
    {
        cout << "Username: "; cin >> username;
        cout << "Password: "; cin >> password;

        // ** MODIFIED LOGIN LOGIC - Check against admin array **
        for (int i = 0; i < adminCount; i++)
        {
            if (admins[i].username == username && 
                admins[i].password == password && 
                admins[i].isActive)
            {
                cout << "\nLogin Successful! Welcome, " << admins[i].fullName << "\n";
                cout << "Designation: " << admins[i].designation << "\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return true;
            }
        }
        
        cout << "Invalid Credentials. Try again.\n";
        attempts++;
    }
    
    cout << "Too many failed attempts.\n";
    return false;
}
// --- DASHBOARD ---

void showDashboard()
{
    cout << "\n--------------------------------------------------\n";
    cout << "   DASHBOARD OVERVIEW \n";
    cout << "--------------------------------------------------\n";
    int totalStudents = 0;

    for(int i=0; i<NUM_CLASSES; i++) totalStudents += classes[i].studentCount;

    cout << "Total Students Enrolled: " << totalStudents << "\n\n";

    for(int i=0; i<NUM_CLASSES; i++)
    {
        cout << "[ Class " << classes[i].classID << ": "
             << setw(2) << classes[i].studentCount << " ]  ";
        if(i == 2) cout << "\n";
    }
    cout << "\n--------------------------------------------------\n";
}

// --- UTILITIES ---

int selectClass()
{
    return getValidInt("\nSelect Class (1 - 5): ", 1, 5) - 1;
}

// --- MODULE 1: STUDENT MANAGEMENT ---

void handleStudentManagement()
{
    int idx = selectClass();
    Classroom &cls = classes[idx];
    int choice;
    do {
        cout << "\n--- CLASS " << cls.classID << " MANAGEMENT ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Search Student\n";
        cout << "4. Modify Info\n";
        cout << "5. View Student List\n";
        cout << "6. Back\n";

        choice = getValidInt("Choice: ", 1, 6);

        switch (choice) {
            case 1: addStudent(cls); break;
            case 2: deleteStudent(cls); break;
            case 3: searchStudent(cls); break;
            case 4: modifyStudent(cls); break;
            case 5: displayAllStudents(cls); break;
            case 6: break;
        }
    } while (choice != 6);
}

void addStudent(Classroom &cls)
{
    if (cls.studentCount >= MAX_STUDENTS_PER_CLASS) 
        { cout << "Error: Class Full!\n"; return; }

    Student s;
    s.rollNo = getValidInt("Enter Roll No: ", 1, 99999);

    if (findStudent_BinarySearch(cls, s.rollNo) != -1) 
        { cout << "Error: ID exists!\n"; return; }

    s.name = getValidString("Enter Name: ");

    // Sorted Insert
    int i = 0;
    while (i < cls.studentCount && cls.students[i].rollNo < s.rollNo) i++;
    for (int j = cls.studentCount; j > i; j--) cls.students[j] = cls.students[j - 1];
    cls.students[i] = s;
    cls.studentCount++;
    cout << "Student added.\n";
}

void deleteStudent(Classroom &cls)
{
    int r = getValidInt("Roll No to delete: ", 1, 99999);
    int idx = findStudent_BinarySearch(cls, r);
    if (idx == -1) { cout << "Not found.\n"; return; }

    // Logic: Shift left to overwrite the student
    cout << "Deleting " << cls.students[idx].name << "...\n";
    for (int i = idx; i < cls.studentCount - 1; i++) cls.students[i] = cls.students[i + 1];
    cls.studentCount--;
    cout << "Deleted.\n";
}

int findStudent_BinarySearch(Classroom &cls, int rollNo)
{
    int low = 0, high = cls.studentCount - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (cls.students[mid].rollNo == rollNo) return mid;
        if (cls.students[mid].rollNo < rollNo) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void searchStudent(Classroom &cls)
{
    int r = getValidInt("Enter Roll No: ", 1, 99999);
    int idx = findStudent_BinarySearch(cls, r);
    if (idx != -1) cout << "\nFound: " << cls.students[idx].name << "\n";
    else cout << "Not found.\n";
}

void displayAllStudents(Classroom &cls)
{
    if (cls.studentCount == 0) { cout << "No students.\n"; return; }
    cout << left << setw(10) << "ROLL NO" << setw(25) << "NAME" << "\n";
    cout << "-----------------------------------\n";
    for(int i=0; i<cls.studentCount; i++)
        cout << setw(10) << cls.students[i].rollNo << setw(25) << cls.students[i].name << "\n";
}

void modifyStudent(Classroom &cls)
{
    int r = getValidInt("Roll No: ", 1, 99999);
    int idx = findStudent_BinarySearch(cls, r);
    if (idx == -1) { cout << "Not found.\n"; return; }

    cout << "Old Name: " << cls.students[idx].name << "\n";
    cls.students[idx].name = getValidString("New Name: ");
    cout << "Updated.\n";
}

// --- MODULE 2: ACADEMICS ---

void handleAcademicRecords()
{
    int idx = selectClass();
    Classroom &cls = classes[idx];
    int choice;
    do {
        cout << "\n--- ACADEMICS ---\n";
        cout << "1. Enter Marks\n";
        cout << "2. Single Student Report\n";
        cout << "3. Whole Class Result (Gazette)\n";
        cout << "4. Back\n";

        choice = getValidInt("Choice: ", 1, 4);

        if (choice == 1) enterMarks(cls);
        else if (choice == 2) displayReportCard(cls);
        else if (choice == 3) showClassResultReport(cls);
    } while (choice != 4);
}

void enterMarks(Classroom &cls)
{
    int r = getValidInt("Enter Roll No: ", 1, 99999);
    int idx = findStudent_BinarySearch(cls, r);
    if (idx == -1) { cout << "Not found.\n"; return; }

    cout << "Entering marks for " << cls.students[idx].name << " (0-100):\n";
    for(int i=0; i<NUM_SUBJECTS; i++) {
        string p = "Subject " + to_string(i+1) + ": ";
        cls.students[idx].marks[i] = (float)getValidInt(p, 0, 100);
    }
    cout << "Marks Saved.\n";
}

void displayReportCard(Classroom &cls)
{
    int r = getValidInt("Enter Roll No: ", 1, 99999);
    int idx = findStudent_BinarySearch(cls, r);
    if (idx == -1) { cout << "Not found.\n"; return; }

    Student &s = cls.students[idx];
    float total = 0;
    cout << "\n>>> REPORT CARD: " << s.name << " <<<\n";
    for(int i=0; i<NUM_SUBJECTS; i++) {
        cout << "Subject " << i+1 << ": " << s.marks[i] << "\n";
        total += s.marks[i];
    }
    float avg = total/NUM_SUBJECTS;
    cout << "--------------------------\n";
    cout << "Total: " << total << " | Avg: " << avg << "% | Grade: " << getGrade(avg) << "\n";
}

void showClassResultReport(Classroom &cls)
{
    if (cls.studentCount == 0) { cout << "No students in this class.\n"; return; }

    cout << "\n=================================================================================\n";
    cout << "                      CLASS " << cls.classID << " RESULT GAZETTE                     \n";
    cout << "=================================================================================\n";
    cout << left << setw(8) << "ROLL"
         << setw(18) << "NAME"
         << setw(6) << "S1" << setw(6) << "S2" << setw(6) << "S3" << setw(6) << "S4" << setw(6) << "S5"
         << setw(8) << "TOTAL"
         << setw(8) << "%"
         << setw(4) << "GR" << "\n";
    cout << "---------------------------------------------------------------------------------\n";

    for(int i = 0; i < cls.studentCount; i++)
    {
        float total = 0;
        for(int s=0; s<NUM_SUBJECTS; s++) total += cls.students[i].marks[s];
        float avg = total / NUM_SUBJECTS;

        cout << left << setw(8) << cls.students[i].rollNo
             << setw(18) << cls.students[i].name;

        for(int s=0; s<NUM_SUBJECTS; s++) {
            cout << setw(6) << cls.students[i].marks[s];
        }

        cout << setw(8) << total
             << fixed << setprecision(1) << setw(8) << avg
             << setw(4) << getGrade(avg) << "\n";
    }
    cout << "=================================================================================\n";
}

char getGrade(float avg) {
    if (avg >= 90) return 'A';
    if (avg >= 70) return 'B';
    if (avg >= 50) return 'C';
    return 'F';
}

// --- MODULE 3: ATTENDANCE ---

void handleAttendance()
{
    int idx = selectClass();
    Classroom &cls = classes[idx];
    if (cls.studentCount == 0) { cout << "No students.\n"; return; }

    int choice;
    do {
        cout << "\n--- ATTENDANCE ---\n";
        cout << "1. Daily Roll Call\n";
        cout << "2. Single Student Stats\n";
        cout << "3. Whole Class Report\n";
        cout << "4. Back\n";

        choice = getValidInt("Choice: ", 1, 4);

        if (choice == 1) runBatchRollCall(cls);
        else if (choice == 2) showStudentAttendanceStats(cls);
        else if (choice == 3) showClassAttendanceReport(cls);
    } while (choice != 4);
}

void runBatchRollCall(Classroom &cls)
{
    int day = getValidInt("\nSelect Day (1-30): ", 1, 30);
    cout << "\n>>> BATCH ROLL CALL (Day " << day << ") <<<\n";
    cout << "Type 1 for Present, 0 for Absent.\n";

    for(int i=0; i<cls.studentCount; i++) {
        cout << "[" << cls.students[i].rollNo << "] " << left << setw(20) << cls.students[i].name << ": ";
        int status = getValidInt("", 0, 1);
        cls.students[i].attendance[day-1] = status;
    }
    cout << "Attendance Saved.\n";
}

void showStudentAttendanceStats(Classroom &cls)
{
    int r = getValidInt("Enter Roll No: ", 1, 99999);
    int idx = findStudent_BinarySearch(cls, r);
    if (idx == -1) { cout << "Not found.\n"; return; }

    int present = 0, marked = 0;
    for(int i=0; i<NUM_DAYS; i++) {
        if (cls.students[idx].attendance[i] != -1) {
            marked++;
            if (cls.students[idx].attendance[i] == 1) present++;
        }
    }

    cout << "\n>>> STATS: " << cls.students[idx].name << "\n";
    cout << "Days Marked: " << marked << " | Present: " << present << "\n";
    if (marked > 0) cout << "Percentage: " << fixed << setprecision(1) << ((float)present/marked)*100 << "%\n";
    else cout << "Percentage: N/A\n";
}

void showClassAttendanceReport(Classroom &cls)
{
    if (cls.studentCount == 0) { cout << "No students in this class.\n"; return; }

    cout << "\n==============================================================\n";
    cout << "             CLASS " << cls.classID << " ATTENDANCE REPORT            \n";
    cout << "==============================================================\n";
    cout << left << setw(10) << "ROLL NO"
         << setw(20) << "NAME"
         << setw(10) << "MARKED"
         << setw(10) << "PRESENT"
         << setw(10) << "ABSENT"
         << setw(10) << "%" << "\n";
    cout << "--------------------------------------------------------------\n";

    for(int i = 0; i < cls.studentCount; i++)
    {
        int present = 0, marked = 0, absent = 0;
        for(int d = 0; d < NUM_DAYS; d++) {
            if (cls.students[i].attendance[d] != -1) {
                marked++;
                if (cls.students[i].attendance[d] == 1) present++;
                else absent++;
            }
        }

        cout << left << setw(10) << cls.students[i].rollNo
             << setw(20) << cls.students[i].name
             << setw(10) << marked
             << setw(10) << present
             << setw(10) << absent;

        if (marked > 0)
            cout << fixed << setprecision(1) << ((float)present/marked)*100 << "%";
        else
            cout << "N/A";

        cout << "\n";
    }
    cout << "==============================================================\n";
}

// --- MODULE 4: ANALYTICS ---

void handleAnalytics()
{
    int idx = selectClass();
    Classroom &cls = classes[idx];
    if (cls.studentCount == 0) { cout << "No data in this class.\n"; return; }

    showComprehensiveAnalytics(cls);

    cout << "\nPress Enter to return...";
    cin.ignore(); cin.get();
}

void showComprehensiveAnalytics(Classroom &cls)
{
    float maxMarks = -1.0f;
    int maxIdx = -1;

    float minMarks = 99999.0f;
    int minIdx = -1;

    float grandTotal = 0.0f;

    for(int i = 0; i < cls.studentCount; i++) {
        float sTotal = 0;
        for(int s = 0; s < NUM_SUBJECTS; s++) sTotal += cls.students[i].marks[s];

        grandTotal += sTotal;

        if (sTotal > maxMarks) {
            maxMarks = sTotal;
            maxIdx = i;
        }

        if (sTotal < minMarks) {
            minMarks = sTotal;
            minIdx = i;
        }
    }

    float classAvg = grandTotal / (cls.studentCount * NUM_SUBJECTS);
    float maxAvg = (maxIdx != -1) ? (maxMarks / NUM_SUBJECTS) : 0;
    float minAvg = (minIdx != -1) ? (minMarks / NUM_SUBJECTS) : 0;

    cout << "\n==========================================\n";
    cout << "        CLASS PERFORMANCE METRICS         \n";
    cout << "==========================================\n";
    cout << "Class Average:      " << fixed << setprecision(2) << classAvg << "%\n";
    cout << "------------------------------------------\n";

    if (maxIdx != -1) {
        cout << "TOP PERFORMER (MAX):\n";
        cout << "  Roll No: " << cls.students[maxIdx].rollNo << "\n";
        cout << "  Name:    " << cls.students[maxIdx].name << "\n";
        cout << "  Score:   " << maxMarks << " / " << (NUM_SUBJECTS*100) << " (" << maxAvg << "%)\n";
    }

    cout << "------------------------------------------\n";

    if (minIdx != -1) {
        cout << "LOWEST PERFORMER (MIN):\n";
        cout << "  Roll No: " << cls.students[minIdx].rollNo << "\n";
        cout << "  Name:    " << cls.students[minIdx].name << "\n";
        cout << "  Score:   " << minMarks << " / " << (NUM_SUBJECTS*100) << " (" << minAvg << "%)\n";
    }
    cout << "==========================================\n";
}
// --- ADMIN MANAGEMENT FUNCTIONS ---

void initializeAdmins()
{
    // Default admin account (cannot be deleted)
    admins[0] = Admin("admin", "123", "System Administrator", "Super Admin");
    adminCount = 1;
    
    // Pre-configured additional admins (optional)
    admins[1] = Admin("principal", "pass123", "Dr. Muhammad Asif", "Principal");
    admins[2] = Admin("teacher1", "teach123", "Ms. Fatima Noor", "Head Teacher");
    admins[3] = Admin("clerk", "clerk123", "Ahmed Hassan", "Office Clerk");
    adminCount = 4;
    
    // cout << "[System] Initialized " << adminCount << " admin accounts.\n";
}

void addNewAdmin()
{
    if (adminCount >= MAX_ADMINS)
    {
        cout << "Error: Maximum admin limit reached!\n";
        return;
    }
    
    Admin newAdmin;
    
    cout << "\n=== ADD NEW ADMIN ===\n";
    newAdmin.username = getValidString("Enter Username: ");
    
    // Check for duplicate username
    for (int i = 0; i < adminCount; i++)
    {
        if (admins[i].username == newAdmin.username)
        {
            cout << "Error: Username already exists!\n";
            return;
        }
    }
    
    newAdmin.password = getValidString("Enter Password: ");
    newAdmin.fullName = getValidString("Enter Full Name: ");
    newAdmin.designation = getValidString("Enter Designation: ");
    newAdmin.isActive = true;
    
    admins[adminCount] = newAdmin;
    adminCount++;
    
    cout << "Admin added successfully!\n";
}

void viewAllAdmins()
{
    if (adminCount == 0)
    {
        cout << "No admins in system.\n";
        return;
    }
    
    cout << "\n========================================================================\n";
    cout << "                        ADMIN USER LIST                                \n";
    cout << "========================================================================\n";
    cout << left << setw(15) << "USERNAME" 
         << setw(25) << "FULL NAME" 
         << setw(20) << "DESIGNATION"
         << setw(10) << "STATUS" << "\n";
    cout << "------------------------------------------------------------------------\n";
    
    for (int i = 0; i < adminCount; i++)
    {
        cout << left << setw(15) << admins[i].username
             << setw(25) << admins[i].fullName
             << setw(20) << admins[i].designation
             << setw(10) << (admins[i].isActive ? "Active" : "Inactive") << "\n";
    }
    cout << "========================================================================\n";
    cout << "Total Admins: " << adminCount << "\n";
}

void deleteAdmin()
{
    string uname = getValidString("Enter username to delete: ");
    
    // Protect default admin
    if (uname == "admin")
    {
        cout << "Error: Default admin cannot be deleted!\n";
        return;
    }
    
    int idx = -1;
    for (int i = 0; i < adminCount; i++)
    {
        if (admins[i].username == uname)
        {
            idx = i;
            break;
        }
    }
    
    if (idx == -1)
    {
        cout << "Admin not found.\n";
        return;
    }
    
    cout << "Deleting admin: " << admins[idx].fullName << "...\n";
    
    // Shift left to remove
    for (int i = idx; i < adminCount - 1; i++)
    {
        admins[i] = admins[i + 1];
    }
    adminCount--;
    
    cout << "Admin deleted successfully!\n";
}

void modifyAdmin()
{
    string uname = getValidString("Enter username to modify: ");
    
    int idx = -1;
    for (int i = 0; i < adminCount; i++)
    {
        if (admins[i].username == uname)
        {
            idx = i;
            break;
        }
    }
    
    if (idx == -1)
    {
        cout << "Admin not found.\n";
        return;
    }
    
    cout << "\n--- MODIFYING: " << admins[idx].fullName << " ---\n";
    cout << "1. Change Password\n";
    cout << "2. Change Full Name\n";
    cout << "3. Change Designation\n";
    cout << "4. Toggle Active Status\n";
    
    int choice = getValidInt("Choice: ", 1, 4);
    
    switch (choice)
    {
        case 1:
            admins[idx].password = getValidString("New Password: ");
            cout << "Password updated.\n";
            break;
        case 2:
            admins[idx].fullName = getValidString("New Full Name: ");
            cout << "Name updated.\n";
            break;
        case 3:
            admins[idx].designation = getValidString("New Designation: ");
            cout << "Designation updated.\n";
            break;
        case 4:
            admins[idx].isActive = !admins[idx].isActive;
            cout << "Status toggled to: " << (admins[idx].isActive ? "Active" : "Inactive") << "\n";
            break;
    }
}

void handleAdminManagement()
{
    int choice;
    do {
        cout << "\n========== ADMIN MANAGEMENT ==========\n";
        cout << "1. View All Admins\n";
        cout << "2. Add New Admin\n";
        cout << "3. Modify Admin\n";
        cout << "4. Delete Admin\n";
        cout << "5. Back to Main Menu\n";
        cout << "======================================\n";
        
        choice = getValidInt("Enter Choice: ", 1, 5);
        
        switch (choice)
        {
            case 1: viewAllAdmins(); break;
            case 2: addNewAdmin(); break;
            case 3: modifyAdmin(); break;
            case 4: deleteAdmin(); break;
            case 5: break;
        }
    } while (choice != 5);
}
