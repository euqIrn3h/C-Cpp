#include <iostream>
#include <vector>
#include <memory>


class Person{
public:
    Person(const std::string& name, int id) : Name{name}, Id{id}
    {}

    ~Person(){
        std::cout << Id << " destructed!" << std::endl;
    }

    std::string getName() const {
        return Name;
    }

    virtual void getCredentials() = 0; // Transform the class in abstract

protected:
    std::string Name;
    const int Id;

private:
    std::string Password;
};

class Student : public Person{
public:
    Student(const std::string& name, int id, int year) : Person{name, id} , Year{year}
    {}

    ~Student(){
        std::cout << Id << " destructed!" << std::endl;
    }

    void incrementYear(){
        Year++;
    }

    virtual void getCredentials() override {
        std::cout << "Student:\nName: " << getName() << ",\nId: " << Id << ",\nYear: " << Year << std::endl;
        std::cout << "Situation: " << gradeSituation() << "\n\n";
    }

private:
    int Year;

    std::string gradeSituation() const {
        switch (Year){
        case 1:
            return "Freshman";
        case 2:
        case 3:
            return "Junior";
        default:
            return "Senior";
        }
    }
};

int main(){
    Student sOne{"name0", 0001, 2};
    Student sTwo{"name1", 0002, 6};

    std::vector<Student> students = {sOne, sTwo};

    for(Student& student : students){
        student.getCredentials();   
    }
}