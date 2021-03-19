#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <locale>
#include <string>

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

    return 0;
}