#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Structure to hold student information
struct Student {
    string name;
    int rollNumber;
    string address;
    string phoneNumber;
};

// Function to display menu options
void displayMenu() {
    cout << "========= Student Record Management System =========" << endl;
    cout << "1. Add New Student" << endl;
    cout << "2. Display All Students" << endl;
    cout << "3. Search Student" << endl;
    cout << "4. Update Student Details" << endl;
    cout << "5. Delete Student" << endl;
    cout << "6. Exit" << endl;
    cout << "===================================================" << endl;
    cout << "Enter your choice (1-6): ";
}

// Function to add a new student to the records
void addStudent() {
    Student student;
    cout << "Enter Student Name: ";
    getline(cin.ignore(), student.name);
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore();
    cout << "Enter Address: ";
    getline(cin, student.address);
    cout << "Enter Phone Number: ";
    getline(cin, student.phoneNumber);

    ofstream file("students.txt", ios::app);
    if (file.is_open()) {
        file << student.name << "," << student.rollNumber << "," << student.address << "," << student.phoneNumber << endl;
        file.close();
        cout << "Student record added successfully!" << endl;
    } else {
        cout << "Unable to open file!" << endl;
    }
}

// Function to display all students from the records
void displayAllStudents() {
    ifstream file("students.txt");
    if (file.is_open()) {
        string line;
        cout << "========= All Students =========" << endl;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, address, phoneNumber;
            int rollNumber;
            getline(ss, name, ',');
            ss >> rollNumber;
            ss.ignore();
            getline(ss, address, ',');
            getline(ss, phoneNumber);
            cout << "Name: " << name << endl;
            cout << "Roll Number: " << rollNumber << endl;
            cout << "Address: " << address << endl;
            cout << "Phone Number: " << phoneNumber << endl;
            cout << "-------------------------------" << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}

// Function to search for a student by roll number
void searchStudent() {
    int rollNumber;
    cout << "Enter Roll Number to search: ";
    cin >> rollNumber;
    cin.ignore();

    ifstream file("students.txt");
    if (file.is_open()) {
        string line;
        bool found = false;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, address, phoneNumber;
            int fileRollNumber;
            getline(ss, name, ',');
            ss >> fileRollNumber;
            ss.ignore();
            getline(ss, address, ',');
            getline(ss, phoneNumber);
            if (fileRollNumber == rollNumber) {
                cout << "========= Student Details =========" << endl;
                cout << "Name: " << name << endl;
                cout << "Roll Number: " << rollNumber << endl;
                cout << "Address: " << address << endl;
                cout << "Phone Number: " << phoneNumber << endl;
                cout << "-------------------------------" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student not found!" << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}

// Function to update student details
void updateStudent() {
    int rollNumber;
    cout << "Enter Roll Number to update: ";
    cin >> rollNumber;
    cin.ignore();

    fstream file("students.txt", ios::in | ios::out);
    if (file.is_open()) {
        string line;
        bool found = false;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, address, phoneNumber;
            int fileRollNumber;
            getline(ss, name, ',');
            ss >> fileRollNumber;
            ss.ignore();
            getline(ss, address, ',');
            getline(ss, phoneNumber);
            if (fileRollNumber == rollNumber) {
                cout << "========= Student Details =========" << endl;
                cout << "Name: " << name << endl;
                cout << "Roll Number: " << rollNumber << endl;
                cout << "Address: " << address << endl;
                cout << "Phone Number: " << phoneNumber << endl;
                cout << "-------------------------------" << endl;

                // Update student details
                Student updatedStudent;
                cout << "Enter Updated Student Name: ";
                getline(cin.ignore(), updatedStudent.name);
                cout << "Enter Updated Address: ";
                getline(cin, updatedStudent.address);
                cout << "Enter Updated Phone Number: ";
                getline(cin, updatedStudent.phoneNumber);

                // Write updated details to the file
                file.seekp(file.tellg() - line.length() - 1);
                file << updatedStudent.name << "," << rollNumber << "," << updatedStudent.address << "," << updatedStudent.phoneNumber << endl;

                cout << "Student record updated successfully!" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student not found!" << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}

// Function to delete a student from the records
void deleteStudent() {
    int rollNumber;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNumber;
    cin.ignore();

    ifstream inputFile("students.txt");
    if (inputFile.is_open()) {
        ofstream outputFile("temp.txt");
        if (outputFile.is_open()) {
            string line;
            bool found = false;
            while (getline(inputFile, line)) {
                stringstream ss(line);
                string name, address, phoneNumber;
                int fileRollNumber;
                getline(ss, name, ',');
                ss >> fileRollNumber;
                ss.ignore();
                getline(ss, address, ',');
                getline(ss, phoneNumber);
                if (fileRollNumber == rollNumber) {
                    cout << "========= Student Details =========" << endl;
                    cout << "Name: " << name << endl;
                    cout << "Roll Number: " << rollNumber << endl;
                    cout << "Address: " << address << endl;
                    cout << "Phone Number: " << phoneNumber << endl;
                    cout << "-------------------------------" << endl;

                    cout << "Student record deleted successfully!" << endl;
                    found = true;
                } else {
                    outputFile << line << endl;
                }
            }
            if (!found) {
                cout << "Student not found!" << endl;
            }
            outputFile.close();
            inputFile.close();

            remove("students.txt");
            rename("temp.txt", "students.txt");
        } else {
            cout << "Unable to create temporary file!" << endl;
        }
    } else {
        cout << "Unable to open file!" << endl;
    }
}

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                cout << "Thank you for using the Student Record Management System!" << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 6." << endl;
                break;
        }

        cout << endl;
    } while (choice != 6);

    return 0;
}
