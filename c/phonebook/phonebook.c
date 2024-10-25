#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main (void)
{
    person people[3];

    people[0].name = "Carter";
    people[0].number = "901-160-4105";

    people[1].name = "David";
    people[1].number = "738-576-0936";

    people[2].name = "Sid";
    people[2].number = "901-160-4105";


    for(int i = 0; i <= 2; i++)
    {
        if(strcmp(people[i].name, "David") == 0)
        {
            printf("Found\n%s :- %s\n", people[i].name , people[i].number);
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;


}