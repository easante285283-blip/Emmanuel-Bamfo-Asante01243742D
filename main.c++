#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    string name;
    string index;

    void input() {
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter index number: ";
        getline(cin, index);
    }

    void display() {
        cout << index << " - " << name << endl;
    }
};

class Attendance {
public:
    string index;
    string status;   // Present, Absent, Late
};

vector<Student> students;
vector<Attendance> session;

/* ================= STUDENT FILE ================= */
void saveStudents() {
    ofstream file("students.txt");
    for (auto s : students)
        file << s.index << "," << s.name << endl;
    file.close();
}

void loadStudents() {
    ifstream file("students.txt");
    if (!file) return;

    string index, name;
    while (getline(file, index, ',')) {
        getline(file, name);
        students.push_back({name, index});
    }
    file.close();
}

/* ================= STUDENT MENU ================= */
void registerStudent() {
    Student s;
    s.input();
    students.push_back(s);
    saveStudents();
    cout << "Student registered successfully\n";
}

void viewStudents() {
    for (auto s : students) s.display();
}

void searchStudent() {
    string id;
    cout << "Enter index to search: ";
    cin >> id;

    for (auto s : students)
        if (s.index == id) {
            s.display();
            return;
        }
    cout << "Student not found\n";
}

/* ================= SESSION ================= */
void createSession() {
    string course, date;
    cout << "Course code: ";
    cin >> course;
    cout << "Date: ";
    cin >> date;

    session.clear();
    cout << "Session created\n";
}

void markAttendance() {
    for (auto s : students) {
        Attendance a;
        a.index = s.index;

        int choice;
        cout << s.name << " (1=Present 2=Absent 3=Late): ";
        cin >> choice;

        if (choice == 1) a.status = "Present";
        else if (choice == 2) a.status = "Absent";
        else a.status = "Late";

        session.push_back(a);
    }
}

void saveSession() {
    ofstream file("session.txt");
    for (auto a : session)
        file << a.index << "," << a.status << endl;
    file.close();
}

void report() {
    int p=0,a=0,l=0;
    for (auto s : session) {
        cout << s.index << " - " << s.status << endl;
        if (s.status=="Present") p++;
        else if (s.status=="Absent") a++;
        else l++;
    }

    cout << "\nSummary\n";
    cout << "Present: " << p << endl;
    cout << "Absent: " << a << endl;
    cout << "Late: " << l << endl;
}

/* ================= MAIN MENU ================= */
int main() {
    loadStudents();
    int choice;

    do {
        cout << "\n==== DIGITAL ATTENDANCE SYSTEM ====\n";
        cout << "1. Register student\n";
        cout << "2. View students\n";
        cout << "3. Search student\n";
        cout << "4. Create session\n";
        cout << "5. Mark attendance\n";
        cout << "6. Save session\n";
        cout << "7. Report\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: createSession(); break;
            case 5: markAttendance(); break;
            case 6: saveSession(); break;
            case 7: report(); break;
        }

    } while(choice!=0);

    return 0;
}
