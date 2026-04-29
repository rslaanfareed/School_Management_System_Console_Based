# School Management System — Console Based
> A fully functional C++ console application for managing students, academics, attendance, and admin accounts across multiple classrooms.

---

## What is this?

This is a DSA project built in C++ that simulates a real school management system - no GUI, just a clean terminal interface. It covers everything from student enrollment and grading to attendance tracking and admin control, all backed by arrays and binary search.

---

## Features

### Student Management
- Add, delete, search, and modify student records
- Binary search on sorted roll numbers for fast lookups
- Handles up to 60 students per class across 5 classes

### Academic Records
- Enter subject-wise marks for any student
- Generate individual report cards with grades
- Print full class result gazette with totals and percentages

### Attendance Module
- Daily roll call for any class and day
- Per-student attendance stats with percentage
- Full class attendance report

### Analytics & Reports
- Class average score
- Top and lowest performing students
- Summary performance metrics per class

### Admin Management
- Multi-admin support (up to 10 accounts)
- Add, modify, delete admin users
- Toggle active/inactive status
- Default `admin` account is protected from deletion
- Login system with 5-attempt lockout

---

## Getting Started

### Requirements
- Any C++ compiler (g++, MSVC, Clang)
- C++11 or later

### Compile & Run

```bash
g++ schoolMS.cpp -o schoolMS
./schoolMS
```

On Windows:
```bash
g++ schoolMS.cpp -o schoolMS.exe
schoolMS.exe
```

### Default Login

| Username  | Password   | Role           |
|-----------|------------|----------------|
| admin     | 123        | Super Admin    |
| principal | pass123    | Principal      |
| teacher1  | teach123   | Head Teacher   |
| clerk     | clerk123   | Office Clerk   |

---

## Project Structure

```
School_Management_System_Console_Based/
├── schoolMS.cpp        # Full source code (single file)
├── ROJECT REPORT.pdf   # Project documentation / report
└── .gitattributes
```

---

## Data Structures Used

| Structure | Purpose |
|-----------|---------|
| `struct Student` | Stores roll number, name, marks array, attendance array |
| `struct Classroom` | Holds an array of students + count |
| `struct Admin` | Manages login credentials and designation |
| Binary Search | Fast student lookup by roll number |
| Sorted Insert | Maintains roll number order on each add |
| Shift Delete | Clean removal without gaps in the array |

---

## How the Data Flows

```
main()
├── initializeAdmins()       → loads 4 default admin accounts
├── autoPopulateData()       → fills 5 classes with 40 students each (200 total)
├── performLogin()           → credential check with lockout
└── Main Menu Loop
    ├── Student Management   → CRUD + binary search
    ├── Academic Records     → marks entry + report generation
    ├── Attendance Module    → roll call + stats
    ├── Analytics            → class metrics
    └── Admin Management     → multi-admin control
```

---

## Sample Output

```
--------------------------------------------------
   DASHBOARD OVERVIEW
--------------------------------------------------
Total Students Enrolled: 200

[ Class 1: 40 ]  [ Class 2: 40 ]  [ Class 3: 40 ]
[ Class 4: 40 ]  [ Class 5: 40 ]
--------------------------------------------------
```

---

## Grade Scale

| Average | Grade |
|---------|-------|
| 90%+    | A     |
| 70-89%  | B     |
| 50-69%  | C     |
| Below 50| F     |

---

## Limitations

- Data is not persisted - everything resets on exit (in-memory only)
- No file I/O or database integration
- Single-file architecture (intentional for academic submission)
- No GUI; purely console-based

---

## Author

**Arslan Fareed**  
Software Engineering, Batch 2024-2028  
University of Engineering and Technology (UET) Taxila  

GitHub: [@rslaanfareed](https://github.com/rslaanfareed)

---

