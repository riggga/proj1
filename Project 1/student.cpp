#include "student.h"
using namespace std;
Student::Student() {
    id = 0;
    name = "";
    score = 0;
}
Student::Student(int i, string n, int s) {
    id = i;
    name = n;
    score = s;
}

void Student::setID(int i) {
    id = i;
}
void Student::setName(string n) {
    name = n;
}
void Student::setScore(int s) {
    score = s;
}

int Student::getID() {
    return id;
}
string Student::getName() {
    return name;
}
int Student::getScore() {
    return score;
}

