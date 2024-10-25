#include <iostream>
#include <string>
using namespace std;

class Students{
    public:
        string name;
        int roll_no;
        float sgpa;
};

class operations{
    public:
        void accept(Students* student, int size){
            for (int i = 0; i < size; i++){
                cout << "Enter Information of Students" << i << endl;
                cout << "Name     : ";
                cin >> student[i].name;
                cout << "\n" <<"Roll No. : ";
                cin >> student[i].roll_no;
                cout << "\n" << "SGPA     : ";
                cin >> student[i].sgpa;
            }
        }

        void display(Students* student, int size){
            cout << "Data :- ";
            for (int i = 0; i < size; i++){
                cout << "Name     : " << student[i].name << endl;
                cout << "Roll No. : " << student[i].roll_no << endl;
                cout << "SGPA     : " << student[i].sgpa << endl;
            }
        }

        void bubble_sort(Students* student, int size){
            bool check = true;
            while (check){
                check = false;
                for (int i =0 ; i < size-1; i++){
                    if (student[i].roll_no > student[i+1].roll_no){
                        swap(student[i], student[i+1]);
                        check = true;
                    }
                }
            }

            display(student, size);
        }

        void insert_sort(Students* student, int size){
            for (int i = 0; i < size; i++ ){
                Students key = student[i];
                int j = i-1;
                while(j >= 0 && student[j].name < key.name){
                    student[j+1] = student[j];
                    j -=1;
                }

                student[j+1] = key;
            }
        }

        void quick_sort(Students* student, int first, int last){
            int i = first + 1;
            int j = last;
            float pivot = student[(first + (last - first)/2)].sgpa;

            while(i <= j){
                while(student[first].sgpa < pivot){
                    i++;
                }

                while(student[j].sgpa  > pivot){
                    j--;
                }

                if(i <= j)
                {
                    swap(student[i], student[j]);
                    i++;
                    j--;
                }
            }

            if (j > first){
                quick_sort(student, first, j);
            }
            if (i < last){
                quick_sort(student, i, last);
            }
        }
};

int main(){
    cout << "helloworld" << endl;
}
