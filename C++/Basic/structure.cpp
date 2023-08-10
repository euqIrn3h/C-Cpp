#include <iostream>
 
using namespace std;

struct database {
    int id_number;
    int age;
    float salary;
};

struct xampl {
    int x;
};
 
int main()
{
    database employee;  //There is now an employee variable that has modifiable 
                        // variables inside it.
    employee.age = 22;
    employee.id_number = 1;
    employee.salary = 12000.21;

    cout<< employee.age <<"\n"<< employee.salary <<"\n";

    xampl structure;
    xampl *ptr = new xampl;

    ptr->x = 12;
    cout<< ptr->x <<"\n";

    ptr = &structure;

    structure.x = 25;
    cout<< ptr->x <<"\n";

    ptr->x = 10;
    cout<< structure.x <<"\n";
    cout<< ptr->x <<"\n";
}