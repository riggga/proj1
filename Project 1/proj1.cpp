/**
 * Project 1
 * Yewei Wang
 * 10669043
 * Submission Date: 10/20/2024
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "student.h"
using namespace std;

// A constant that stores the number of courses
const int NUM_COURSES = 3;

// Course Struct
struct Course
{
    string title; // Title of the course
    int number_of_students; // Number of students in the course
    Student* list; // A list of students in the course
    
    
};

/**
 * @brief Reads student data from a file and populates the course structure.
 * @param reader An input file stream used to read the file.
 * @param courseStruct The Course struct to be populated with data from the file.
 */
void read_file(ifstream& reader, Course& courseStruct);

/**
 * @brief Sorts an array of students by their IDs in ascending order.
 * @param list The array of students to be sorted.
 * @param size The number of students in the array.
 */
void sortByID(Student* list, int size);
/**
 * @brief Prints all the information of the students in a course.
 * @param x The course being printed.
 */
void printCourse(Course x);
/**
 * @brief Finds students that take all the courses.
 * @param courses A static array that stores all the courses.
 * @param takeAllList A pointer to a Student array that stores students taking all the classes.
 * @param size Size of the array pointed by takeAllList.
 */
void takeAll(Course courses[], Student*& takeAllList, int& size);
/**
 * @brief Finds students that take two courses.
 * @param courses A static array that stores two courses.
 * @param takeTwoList A pointer to a Student array that stores students taking both of the courses.
 * @param size Size of the takeTwoList.
 * @param IDAvoid An array of student IDs that should be avoided (students who take all courses).
 * @param size_avoid Size of the IDAvoid array.
 * 
 */
void takeTwo(Course courses[], Student*& takeTwoList, int& size, int* IDAvoid, int size_avoid);
/**
 * @brief Initializes an array of Student objects by setting the IDs of each student to 0.
 * @param list A pointer to an array of Student objects.
 * @param size Size of the array pointed by the list.
 */
void make_zero(Student* list, int size);
/**
 * @brief Initializes an integer array by setting all elements to 0.
 * @param list A pointer to an integer array.
 * @param size Size of the array.
 * 
 */
void make_zero(int* list, int size);
/**
 * @brief Checks if a student is in the given course.
 * @param stu The student being checked.
 * @param crs The course being checked.
 * @return Boolean True if the student is in the course, false otherwise.
 */
bool in_this_course(Student stu, Course crs);
/**
 * @brief Finds the score of a specific student in a course.
 * 
 * @param stu The student whose score is being found.
 * @param crs The course in which the student is enrolled.
 * 
 * @return int The student's score in the course, or -1 if not found.
 */
int find_student_score_in_course(Student stu, Course crs);
/**
 * @brief Checks if a given number exists in an array.
 * 
 * @param num The number to check.
 * @param size The size of the array.
 * @param arr The array being checked.
 * 
 * @return bool True if the number is found, false otherwise.
 */
bool alreadyInArray(int num, int size, int* arr);

/**
 * @brief Finds the top three scores in a course and the students who achieved those scores.
 * 
 * @param course The course for which the top scores are being found.
 * @param top_student_list A pointer to a Student array storing students with the top scores.
 * @param top_3_scores A pointer to an integer array storing the top three scores.
 * @param size Size of the top_student_list.
 * 
 */
void top_scores(Course course, Student*& top_student_list, int*& top_3_scores, int& size);
/**
 * @brief Sorts an array of integers in descending order using the selection sort algorithm.
 * 
 * @param arr The array to be sorted.
 * @param size The size of the array.
 * 
 */
void selectionSort(int* arr, int size);


int main() {
    // declaration of the file names
    string file1, file2, file3;

    // Takes input of the filenames
    cout << "Enter filename #1: ";
    cin >> file1;
    cout << "Enter filename #2: ";
    cin >> file2;
    cout << "Enter filename #3: ";
    cin >> file3;

    
    Course course_list[NUM_COURSES];  // declarate the static array used to store the courses
    ifstream reader1, reader2, reader3; // declaration of the file readers
    int selection;
    bool run = true;

    // Open the files
    reader1.open(file1);
    reader2.open(file2);
    reader3.open(file3);
    
    // Reads the files 
    read_file(reader1, course_list[0]);
    read_file(reader2, course_list[1]);
    read_file(reader3, course_list[2]);
    
    // Closes the readers after reading
    reader1.close();
    reader2.close();
    reader3.close();
    
    do {
        cout << "===================== Menu =====================" << endl;
        cout << "    1. Show All course lists (sorting)\n    2. List Of students who take all courses\n    3. List of students who take two courses\n    4. Print out top three scores for each course\n    5. Exit\n    ------> Select: ";
        cin >> selection;

        switch(selection){

            // Menu 1
            case 1:
                for (int i = 0; i < 3; i++) {
                    sortByID(course_list[i].list, course_list[i].number_of_students);
                    printCourse(course_list[i]);
                }
                break;

            // Menu 2
            case 2:
                {
                    Student* studentsTakingAll;
                    int size = 0;
                    for (int i = 0; i < NUM_COURSES; i++) {
                        sortByID(course_list[i].list, course_list[i].number_of_students);
        
                    }
                    takeAll(course_list, studentsTakingAll, size);

                    cout << "There are " << size << " students who take 3 courses\n--------------------------------------------------------" << endl;
                    for (int i = 0; i < size; i++) {
                    cout << studentsTakingAll[i].getID() << setw(12) << studentsTakingAll[i].getName() << setw(6) << course_list[0].title << "(" << find_student_score_in_course(studentsTakingAll[i], course_list[0]) << ")" << setw(6) << course_list[1].title << "(" << find_student_score_in_course(studentsTakingAll[i], course_list[1]) << ")" << setw(8) << course_list[2].title << "(" << find_student_score_in_course(studentsTakingAll[i], course_list[2]) << ")"<< endl;
            
                    }

                    delete[] studentsTakingAll;
                }
                break;
            
            // Menu 3
            case 3: 
                {
                    Student* students_crs_1_2, *students_crs_1_3, *students_crs_2_3, *studentsTakingAll;
                    int size_1_2, size_1_3, size_2_3, idx_1_2, idx_1_3, idx_2_3, size_all;

                    for (int i = 0; i < 3; i++) {
                        sortByID(course_list[i].list, course_list[i].number_of_students);
                    }

                    takeAll(course_list, studentsTakingAll, size_all);
                    int* idTakeALL = new int[size_all];

                    for (int i = 0; i < size_all; i++) {
                        idTakeALL[i] = studentsTakingAll[i].getID();
                    }


                    Course crs_1_2[2], crs_1_3[2], crs_2_3[2];
                    
                    idx_1_2 = 0;
                    idx_1_3 = 0;
                    idx_2_3 = 0;
                    
                    crs_1_2[0] = course_list[0];
                    crs_1_2[1] = course_list[1];

                    crs_1_3[0] = course_list[0];
                    crs_1_3[1] = course_list[2];

                    crs_2_3[0] = course_list[1];
                    crs_2_3[1] = course_list[2];
                    
                    takeTwo(crs_1_2, students_crs_1_2, size_1_2, idTakeALL, size_all);
                    takeTwo(crs_1_3, students_crs_1_3, size_1_3, idTakeALL, size_all);
                    takeTwo(crs_2_3, students_crs_2_3, size_2_3, idTakeALL, size_all);
                    
                    cout << "There are " << size_1_2 << " who take " << course_list[0].title << " and " << course_list[1].title << "\n--------------------------------------------------------" << endl;
                    for (int i = 0; i < size_1_2; i++) {
                        cout << students_crs_1_2[i].getID() << setw(12) << students_crs_1_2[i].getName() << setw(6) << course_list[0].title << "(" << find_student_score_in_course(students_crs_1_2[i], course_list[0]) << ")" << setw(6) << course_list[1].title << "(" << find_student_score_in_course(students_crs_1_2[i], course_list[1]) << ")"<< endl;
                    }
                    cout << "There are " << size_1_3 << " who take " << course_list[0].title << " and " << course_list[2].title << "\n--------------------------------------------------------" << endl;
                    for (int i = 0; i < size_1_3; i++) {
                        cout << students_crs_1_3[i].getID() << setw(12) << students_crs_1_3[i].getName() << setw(6) << course_list[0].title << "(" << find_student_score_in_course(students_crs_1_3[i], course_list[0]) << ")" << setw(6) << course_list[2].title << "(" << find_student_score_in_course(students_crs_1_3[i], course_list[2]) << ")"<< endl;
            
                    }
                    cout << "There are " << size_2_3 << " who take " << course_list[1].title << " and " << course_list[2].title << "\n--------------------------------------------------------" << endl;
                    for (int i = 0; i < size_2_3; i++) {
                        cout << students_crs_2_3[i].getID() << setw(12) << students_crs_2_3[i].getName() << setw(6) << course_list[1].title << "(" << find_student_score_in_course(students_crs_2_3[i], course_list[1]) << ")" << setw(6) << course_list[2].title << "(" << find_student_score_in_course(students_crs_2_3[i], course_list[2]) << ")"<< endl;
            
                    }

                    delete[] students_crs_1_2;
                    delete[] students_crs_1_3;
                    delete[] students_crs_2_3;
                    delete[] studentsTakingAll;
                    delete[] idTakeALL;

                }

                
                break;
            
            // Menu 4
            case 4:
                Student* crs_1_highest_score, *crs_2_highest_score, *crs_3_highest_score;
                int* top_scores_crs_1, *top_scores_crs_2, *top_scores_crs_3, size_crs_1, size_crs_2, size_crs_3;
                for (int i = 0; i < 3; i++) {
                    sortByID(course_list[i].list, course_list[i].number_of_students);
                }
                
                top_scores(course_list[0], crs_1_highest_score, top_scores_crs_1, size_crs_1);
                top_scores(course_list[1], crs_2_highest_score, top_scores_crs_2, size_crs_2);
                top_scores(course_list[2], crs_3_highest_score, top_scores_crs_3, size_crs_3);
                
            
                
                // Course 1
                cout << "[ " << course_list[0].title << " Top Three Scores ]" << endl;
                for (int i = 0; i < 3; i++) {
                    
                    int current_score = top_scores_crs_1[i];
                    
                    cout << i + 1 << "." << setw(4) << current_score << endl;
                    
                    for( int j = 0; j < size_crs_1; j++) {
                        Student current_top_score_student = crs_1_highest_score[j];
                        if(current_top_score_student.getScore() == current_score) {
                            cout << current_top_score_student.getID() << setw(7) << current_top_score_student.getName() << endl;
                        }
                        
                    }
                }

                // Course 2
                cout << "[ " << course_list[1].title << " Top Three Scores ]" << endl;
                for (int i = 0; i < 3; i++) {
                    
                    int current_score = top_scores_crs_2[i];
                    cout << i + 1 << "." << setw(4) << current_score << endl;
                    for( int j = 0; j < size_crs_2; j++) {
                        Student current_top_score_student = crs_2_highest_score[j];
                        if(current_top_score_student.getScore() == current_score) {
                            cout << current_top_score_student.getID() << setw(14) << current_top_score_student.getName() << endl;
                        }
                    }
                }

                // Course 3
                cout << "[ " << course_list[2].title << " Top Three Scores ]" << endl;
                for (int i = 0; i < 3; i++) {

                    int current_score = top_scores_crs_3[i];
                    cout << i + 1 << "." << setw(4) << current_score << endl;
                    for( int j = 0; j < size_crs_3; j++) {
                        Student current_top_score_student = crs_3_highest_score[j];
                        if(current_top_score_student.getScore() == current_score) {
                            cout << current_top_score_student.getID() << setw(7) << current_top_score_student.getName() << endl;
                        }
                    }
                }

                delete[] crs_1_highest_score;
                delete[] crs_2_highest_score;
                delete[] crs_3_highest_score;
                delete[] top_scores_crs_1;
                delete[] top_scores_crs_2;
                delete[] top_scores_crs_3;


                break;
            
            //  Menu 5
            case 5:
                cout << "\nExiting...";
                for(int i = 0; i < NUM_COURSES; i++) {
                    delete[] course_list[i].list;
                }
                run = false;
                break;

        }
    } while(run);

    return 0;
}


void read_file(ifstream& reader, Course& courseStruct){
    int num_of_stu, id, score, idx;
    string course_title, size, name;
    
    idx = 0;

    if (!reader.is_open()) {
        cerr << "File could not be opened." << endl;
        return;
    }

    reader >> course_title >> num_of_stu;

    courseStruct.title = course_title;
    courseStruct.number_of_students = num_of_stu;
    courseStruct.list = new Student[num_of_stu];

    while(idx < num_of_stu && reader >> id >> name >> score) {
        
        courseStruct.list[idx].setID(id);
        courseStruct.list[idx].setName(name);
        courseStruct.list[idx].setScore(score);
        idx++;

    }


}


void sortByID(Student* list, int size) {
    int i, j, min_idx;
    
    for (i = 0; i < size - 1; i++){
        min_idx = i;
        for (j = i + 1; j < size; j++){
            if (list[j].getID() < list[min_idx].getID())
            min_idx = j;
        }
           

        if (min_idx != i)
            swap(list[min_idx], list[i]);

    }  
}


void printCourse(Course x){
    cout << "======================== " << x.title << " ========================\n";

    for (int i = 0; i < x.number_of_students; i++) {
        cout << setw(4) << x.list[i].getID() << setw(10) << x.list[i].getName() << setw(10) << x.list[i].getScore() << endl;
    }

}


void takeAll(Course courses[], Student*& takeAllList, int& size) {
    int numOfAllStudent;
    
    for (int i = 0; i < 3; i++) {
        numOfAllStudent += courses[i].number_of_students;
    }
    int* IDchecked = new int[numOfAllStudent];
    Student* tempStudentTakeAll = new Student[numOfAllStudent];

    make_zero(IDchecked, numOfAllStudent);
    make_zero(tempStudentTakeAll, numOfAllStudent);

    int idx = 0;
    
    for (int i = 0; i < 3; i++) {
        Course current_course = courses[i];
        for (int j = 0; j < current_course.number_of_students; j++) {
            Student current_student = current_course.list[j];
            int current_studentID = current_student.getID();

            if (!alreadyInArray(current_studentID, numOfAllStudent, IDchecked)) {
                IDchecked[idx] = current_studentID;
                int num_coursesIn = 0;

                for (int k = 0; k < 3; k++) {
                    if (in_this_course(current_student, courses[k])) {
                        num_coursesIn++;
                    }
                }

                if (num_coursesIn == 3) {
                    tempStudentTakeAll[idx] = current_student;
                    idx++;
                }
            }
        }
    }

    size = 0;
    for (int i = 0; i < numOfAllStudent; i++) {
        if (tempStudentTakeAll[i].getID() != 0) {
            size++;
        }
    }

    takeAllList = new Student[size];

    for (int i = 0; i < size; i++) {
        takeAllList[i] = tempStudentTakeAll[i];
    }

    delete[] IDchecked;
    delete[] tempStudentTakeAll;

}

void takeTwo(Course courses[], Student*& takeTwoList, int& size, int* IDAvoid, int size_avoid) {
    int numOfAllStudent = 0;
    for (int i = 0; i < 2; i++) {
        numOfAllStudent += courses[i].number_of_students;
    }
    
    int* IDchecked =  new int[numOfAllStudent];
    Student* tempStudentTakeTwo = new Student[numOfAllStudent];
    
    make_zero(IDchecked, numOfAllStudent);
    make_zero(tempStudentTakeTwo, numOfAllStudent);
    
    int idx = 0;
    
    for (int i = 0; i < 2; i++) {
        Course current_course = courses[i];
        for (int j = 0; j < current_course.number_of_students; j++) {
            Student current_student = current_course.list[j];
            int current_studentID = current_student.getID();
    
            if (!alreadyInArray(current_studentID, numOfAllStudent, IDchecked)) {
                IDchecked[idx] = current_studentID;
                int num_coursesIn = 0;

                for (int k = 0; k < 2; k++) {
                    if (in_this_course(current_student, courses[k])) {
                        num_coursesIn++;
                    }
                }

                if (num_coursesIn == 2 && !alreadyInArray(current_studentID, size_avoid, IDAvoid)) {
                    tempStudentTakeTwo[idx] = current_student;
            
                    idx++;
                }
            }
        }
    }
    

    size = 0;
    for (int i = 0; i < numOfAllStudent; i++) {
        if (tempStudentTakeTwo[i].getID() != 0) {
            size++;
        }
    }

    takeTwoList = new Student[size];

    for (int i = 0; i < size; i++) {
        takeTwoList[i] = tempStudentTakeTwo[i];
    }

    

    delete[] IDchecked;
    delete[] tempStudentTakeTwo;



}

void make_zero(Student* list, int size) {
    for (int i = 0; i < size; i++) {
        list[i].setID(0);
    }
}


void make_zero(int* list, int size) {
    for (int i = 0; i < size; i++) {
        list[i] = 0;
    }
}


bool in_this_course(Student stu, Course crs) {
    for (int i = 0; i < crs.number_of_students; i++){
        if (stu.getID() == crs.list[i].getID()){
            return true;
        }
    }

    return false;
}

int find_student_score_in_course(Student stu, Course crs) {
    int studentID = stu.getID();

    for (int i = 0; i < crs.number_of_students; i++) {
        Student current_course_student = crs.list[i];
        if (studentID == current_course_student.getID()) {
            return current_course_student.getScore();
        }
    }

    return -1;
}

bool alreadyInArray(int num, int size, int* arr) {

    for (int i = 0; i < size; i++) {
        if (num == arr[i]) {
            return true;
        }
    }

    return false;
}


void top_scores(Course course, Student*& top_student_list, int*& top_3_scores, int& size) {

    int num_scores = course.number_of_students;
    int* all_scores = new int[num_scores];
    Student* temp_top_student_list = new Student[num_scores];
    int idx, count, *score_checked, *IDChecked;
    
    score_checked = new int[num_scores];
    IDChecked = new int[num_scores];
    make_zero(score_checked, num_scores);
    make_zero(IDChecked, num_scores);
    make_zero(temp_top_student_list, num_scores);

    for ( int i = 0; i < course.number_of_students; i++) {
        Student current_student = course.list[i];
        all_scores[i] = current_student.getScore();
       
    }
    
    selectionSort(all_scores, num_scores);
    

    top_3_scores = new int[3];

    make_zero(top_3_scores, 3);

    for(int i = 0; i < 3; i++) {
        for( int j = 0; j < num_scores; j++) {
            if (!alreadyInArray(all_scores[j], num_scores, top_3_scores)){
                top_3_scores[i] = all_scores[j];
                break;
            }

        }
        
       
    }

    idx = 0;
    for (int i = 0; i < course.number_of_students; i++) {
        Student current_student = course.list[i];

        for(int j = 0; j < 3; j++) {
            if(current_student.getScore() == top_3_scores[j] && !alreadyInArray(current_student.getID(), num_scores, IDChecked)){
                temp_top_student_list[idx] = current_student;
                idx++;
            }
        }
    }

    count = 0;

    for(int i = 0; i < num_scores; i++) {
        if(temp_top_student_list[i].getID() != 0) {
            count++;
        }
    }

    size = count;

    top_student_list = new Student[size];
    for(int i = 0; i < size; i++) {
        top_student_list[i] = temp_top_student_list[i];
    }

   
    delete[] all_scores;
    delete[] score_checked;
    delete[]  IDChecked;
    delete[] temp_top_student_list;
}

void selectionSort(int* arr, int size) {
    int i, j, min_idx;
    
    for (i = 0; i < size; i++){
        min_idx = i;
        for (j = i + 1; j < size; j++){
            if (arr[j] > arr[min_idx])
            min_idx = j;
        }
           

        if (min_idx != i)
            swap(arr[min_idx], arr[i]);

    }  
}