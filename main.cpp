#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
struct Discipline{
    std::string name;
    int mark;
};
struct Student {
    std::string fullName;
    Discipline rez[4];
};
void sort(std::vector<Student> &students) {
    for (int i = 0; i < students.size() - 1; ++i) {
        for (int j = i + 1; j < students.size(); ++j) {
            if (students[i].fullName > students[j].fullName) {
                std::swap(students[i], students[j]);
            }
        }
    }
}
std::ostream& operator<<(std::ostream& out, const std::vector<Student>& students)
{
    for (const auto & student : students)
        out <<student.fullName<< " ";
    return out;
}
std::istream&operator>>(std::istream& in, std::vector<Student>& students) {
    while (!in.eof())
    {
        Student baumanec;
        std::string buffer;
        getline(in, baumanec.fullName, ';');
        if (in.eof()) break;
        for(auto & i : baumanec.rez) {
            getline(in, i.name, ';');
            getline(in, buffer, ';');
            i.mark = stoi(buffer);
            getline(in, buffer, ';');
        }
        students.push_back(baumanec);
    }
    return in;
}
void write_file(const std::vector<Student>&students,const std::string& file){
    std::ofstream write;
    write.open(file,std::ios::app);
    write<<students;
    write.close();
}
void read_file(std::vector<Student>students,const std::string& file){
    std::ifstream read;
    read.open(file,std::ios::app);
    read>>students;
    read.close();
 }
void binary_write(const std::vector<Student> &students, const std::string file) {
    std::ofstream fout(file, std::ios::binary);
    if (!fout.is_open()) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "File is open" << std::endl;
        for (Student s : students) {
            uint8_t z = s.fullName.size();
            fout.write(reinterpret_cast<char *>(&z),sizeof(z));
            fout.write(s.fullName.c_str(),z);
            for(auto & i : s.rez)
            {
                fout.write(reinterpret_cast<char *>(&i.mark), sizeof(&i.mark));
                z = i.name.size();
                fout.write(reinterpret_cast<char *>(&z), sizeof(z));
                fout.write(i.name.c_str(), z);
            }
        }
    }
    fout.close();
}
void binary_read(std::vector<Student> &students, const std::string file) {
    std::ifstream fin(file, std::ios::binary);
    if (!fin.is_open()) {
        std::cout << "Error" << std::endl;
    } else {
        std::cout << "File is open" << std::endl;
        Student s;
        std::string str;
        uint8_t z=s.fullName.size();
        while (fin.read(reinterpret_cast<char *> (&s), sizeof(uint8_t))) {
            for(auto & i : s.rez) {
                fin.read(reinterpret_cast<char *>(&i.mark), sizeof(int));
                fin.read(reinterpret_cast<char *>(&i.name), sizeof(uint8_t));
                str.resize(z);
            }
            fin.read(reinterpret_cast<char *>(&s.fullName), sizeof(uint8_t));
            str.resize(z);
        }
    }
    fin.close();
}
void print(const std::vector <Student>& students)
{
    for (auto & student : students) {
        std::cout <<"Student name: "<< student.fullName << std::endl;
        for (const auto & j : student.rez){
                  std::cout<< " Mark: " << j.mark
                  << " .Name of subject: " << j.name;
        }}
    std::cout << std::endl;
}
int main()
{
    std::vector<Student>students{
            {"Petrov Ilya",   {{"MA", 5}, {"TI", 5}, {"Algos", 5}}},
            {"Ivanov Petr",  {{"MA", 3}, {"TI", 4}, {"Algos", 3}}},
            {"Germanov Roman", {{"MA", 2}, {"TI", 2}, {"Algos", 3}}}
    };
    sort(students);
    std::string st;
    std::cout<<"Enter subjects name"<<std::endl;
    std::cin>>st;
    int a=0;
for( a=0;a<3;++a){
    if (students[0].rez[a].name==st){
        break;
    }
}
    auto b=std::count_if(students.begin(),students.end(),[a](Student&stud){
        bool iz_c=stud.rez[a].mark<3;
        if(iz_c) {
            std::cout<<stud.fullName<<std::endl;
        }
        return iz_c;
    });
std::cout<<b<<std::endl;
    print(students);
    write_file(students,"students.txt");
    read_file(students,  "students.txt");
    binary_write(students,"bstudents1.txt");
    binary_read(students,"bstudents2.txt");
    return 0;
}