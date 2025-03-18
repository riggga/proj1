#include <string>
using namespace std;

class Student
{
private:
    int id;
    string name;
    int score;

public:
    Student();
    Student(int, string, int);

    void setID(int);
    void setName(string);
    void setScore(int);

    int getID();
    string getName();
    int getScore();



};