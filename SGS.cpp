#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Assignment {
public:
    string name;
    double score;
    double maxScore;
    double weight; // percentage weight for this assignment type

    Assignment(string n, double s, double m, double w) : name(n), score(s), maxScore(m), weight(w) {}

    double getWeightedScore() const {
        return (score / maxScore) * weight;
    }
};

class Subject {
private:
    string subjectName;
    vector<Assignment> assignments;

public:
    Subject(string name) : subjectName(name) {}

    void addAssignment(const string& name, double score, double maxScore, double weight) {
        assignments.push_back(Assignment(name, score, maxScore, weight));
    }

    double calculateTotalGrade() const {
        double total = 0;
        for (const auto& assignment : assignments) {
            total += assignment.getWeightedScore();
        }
        return total;
    }

    void displayAssignments() const {
        for (const auto& assignment : assignments) {
            cout << "Assignment: " << assignment.name 
                 << " | Score: " << assignment.score 
                 << "/" << assignment.maxScore 
                 << " | Weighted: " << assignment.getWeightedScore() << endl;
        }
    }

    string getSubjectName() const { return subjectName; }
};

class Student {
private:
    string name;
    int studentID;
    map<string, Subject> subjects;

public:
    Student(string n, int id) : name(n), studentID(id) {}

    void addSubject(const string& subjectName) {
        subjects[subjectName] = Subject(subjectName);
    }

    void addAssignmentToSubject(const string& subjectName, const string& assignmentName, double score, double maxScore, double weight) {
        subjects[subjectName].addAssignment(assignmentName, score, maxScore, weight);
    }

    double calculateOverallGrade() const {
        double totalGrade = 0;
        int subjectCount = subjects.size();
        for (const auto& subject : subjects) {
            totalGrade += subject.second.calculateTotalGrade();
        }
        return totalGrade / subjectCount;
    }

    void displayGrades() const {
        cout << "Grades for " << name << " (ID: " << studentID << ")\n";
        for (const auto& subject : subjects) {
            cout << "Subject: " << subject.first << "\n";
            subject.second.displayAssignments();
        }
        cout << "Overall Grade: " << calculateOverallGrade() << endl;
    }
};

class GradeSystem {
private:
    vector<Student> students;

public:
    void addStudent(const string& name, int id) {
        students.emplace_back(name, id);
    }

    void addSubjectForStudent(int id, const string& subjectName) {
        for (auto& student : students) {
            if (student.getID() == id) {
                student.addSubject(subjectName);
            }
        }
    }

    void addAssignmentForStudent(int id, const string& subjectName, const string& assignmentName, double score, double maxScore, double weight) {
        for (auto& student : students) {
            if (student.getID() == id) {
                student.addAssignmentToSubject(subjectName, assignmentName, score, maxScore, weight);
            }
        }
    }

    void displayStudentGrades(int id) const {
        for (const auto& student : students) {
            if (student.getID() == id) {
                student.displayGrades();
                return;
            }
        }
        cout << "Student with ID " << id << " not found.\n";
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file!\n";
            return;
        }

        for (const auto& student : students) {
            // Code to write student data to file
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file!\n";
            return;
        }

        // Code to read and restore student data from file
        file.close();
    }
};
