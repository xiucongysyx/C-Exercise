#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

void Person_create(struct Person *struct_name, char *name, int age, int height, int weight)
{

    struct_name->name = strdup(name);
    struct_name->age = age;
    struct_name->height = height;
    struct_name->weight = weight;
}

void Person_print(struct Person struct_name)
{
    printf("Name: %s\n", struct_name.name);
    printf("\tAge: %d\n",struct_name.age);
    printf("\tHeight: %d\n", struct_name.height);
    printf("\tweight: %d\n", struct_name.weight);
}

int main(int argc, char *argv[])
{
    struct Person joe;
    struct Person frank;

    Person_create(&joe, "Joe Alex", 32, 64, 140);

    Person_create(&frank, "Frank Blank", 20, 72, 180);

    printf("Joe is at memory location %p:\n", &joe);
    Person_print(joe);

    printf("Frank is at memory location %p\n", &frank);
    Person_print(frank);

    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);

    free(joe.name);
    free(frank.name);
    return 0;
}
