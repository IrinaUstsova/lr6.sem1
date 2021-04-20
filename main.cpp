#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <locale>
#include <string>
#include <cmath>

using namespace std;

struct subject
{
    string name_of_subject;
    int grade = 0;
};

struct student
{
    string name;
    vector<subject> sub_vector;
};

ostream& operator <<(ostream& out, const vector<subject>& vec)
{
    for (auto& element : vec)
    {
        out << element.name_of_subject << ";";
        out << element.grade << ";";
    }
        return out;
}

ostream& operator <<(ostream& out, const vector<student>& stud)
{
    for (auto& element : stud)
    {
        out << element.name << ";";
        out << element.sub_vector << endl;
    }
    return out;
}

istream& operator >> (istream& in, vector<student>& stud_1)
{
    string text_str;
    string temp_str;
    while (getline(in,text_str,'\n'))
    {
        int obj = text_str.find(';');
        int obj1 = text_str.find(';',obj+1);
        student stud;
        stud.name = text_str.substr(0, obj);
        size_t pos = 0;
        for (size_t i = obj + 1; text_str[i] != '\0'; i++)
            if (text_str[i] == ';') pos++;
        pos = pos/ 2;
        for (int j = 0; j < pos; j++)
        {
            subject sub1;
            sub1.name_of_subject = text_str.substr(obj + 1, obj1 - obj - 1);
           sub1.grade = stoi(text_str.substr(obj1 + 1, 1));
            obj = obj1+2;
            obj1 = text_str.find(';', obj + 1);
            stud.sub_vector.push_back(sub1);
        }
        stud_1.push_back(stud);
    }

    return in;
}

vector<student>std3;
ofstream file_bin("text.bin", ios::binary);
void write(string& file_bin, vector<student> &std3)
{
    ofstream out(file_bin, ios::binary | ios::trunc);
    if (out.is_open())
    {
        {
            int nstud = std3.size();
            out.write(reinterpret_cast<char*>(&nstud), sizeof(int));

            int nsub = std3[0].sub_vector.size();
            out.write(reinterpret_cast<char*>(&nsub), sizeof(int));

            for (int i = 0; i < nsub; i++) {
                int size = std3[0].sub_vector[i].name_of_subject.length();
                out.write(reinterpret_cast<char*>(&size), sizeof(int));
                out.write(std3[0].sub_vector[i].name_of_subject.c_str(), size);
            }

            for (int i = 0; i < nstud; i++) {
                int name = std3[i].name.length();
                out.write(reinterpret_cast<char*>(&name), sizeof(int));
                out.write(std3[i].name.c_str(), name);
                for (int j = 0; j < nsub; j++)
                    out.write(reinterpret_cast<char*>(&std3[i].sub_vector[j].grade), sizeof(int));
            }

            out.close();
        }
    }
}

void read(fstream& file3, vector<student> &std3)
{
        int nstud = 0;
        file3.read(reinterpret_cast<char*>(&nstud), sizeof(int));
        std3.resize(nstud);

        int nsub = 0;
        file3.read(reinterpret_cast<char*>(&nsub), sizeof(int));

        vector<string> subj (nsub);
        for (int i = 0; i < nsub; i++)
        {
            int size=0;
            file3.read(reinterpret_cast<char*>(&size), sizeof(int));
            char* name = new char [size];
            file3.read(name, size);
            subj[i] = static_cast<string>(name);
        }

        for (int i = 0; i < nstud; i++)
        {
            int name_b = 0;
            file3.read(reinterpret_cast<char*>(&name_b), sizeof(int));
            char* name = new char [name_b];
            file3.read(name, name_b);
            std3[i].name = static_cast<string>(name);
            std3[i].sub_vector.resize(nsub);
            for (int j = 0; j < nsub; j++)
            {
                std3[i].sub_vector[j].name_of_subject = subj[j];
                file3.read(reinterpret_cast<char*>(&std3[i].sub_vector[j].grade), sizeof(int));
            }
        }
}


bool sorting (student stud1, student stud2)
{
    if (stud1.name > stud2.name)
        return false;
    else
        return true;
}

int main()
{
    vector<student>students(3);
    string sub[4]={"maths", "english", "chemistry", "physics"};
    for (int i=0; i<3; i++)
    {
        cout << "enter a name:";
        cin >> students[i].name;
        students[i].sub_vector.resize(4);
        for(int j=0; j<4; j++)
        {
            students[i].sub_vector[j].name_of_subject=sub[j];
            cout << sub[j] << ": ";
            cin >> students[i].sub_vector[j].grade;
        }
    }
    sort(students.begin(), students.end(), sorting);
    for (int i=0; i<3; i++)
    {
        cout << students[i].name << endl;
    }

    ofstream file("text.txt");
    if(file.is_open())
    {
        file << students;
    }
    file.close();

    vector<student>std2;
    ifstream file1("text.txt");
    if(file1.is_open())
    {
        file1 >> std2;
    }
    file1.close();
    cout << std2;

    int badst=0;
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<4; j++)
        {
            if (students[i].sub_vector[j].grade < 3)
            {
                cout << students[i].name << endl;
                badst++;
                break;
            }
        }
    }
    cout<<badst<<endl;

    string file_bin;
    string nfile;
    fstream file3("text_bin.bin", ios::binary);
    //string file3;




    file3.open(nfile, ios::in | ios:: binary);
    if (file3.is_open())
        read(file3, std3);
    else cout << "error";

    write(file_bin, std3);
    return 0;
}