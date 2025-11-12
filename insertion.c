#include <stdio.h>

struct Student {
    int roll;
    int age;
    float marks;
};

void insertionSort(struct Student s[], int n) {
    for (int i = 1; i < n; i++) {
        struct Student key = s[i];
        int j = i - 1;

        // Move elements that are greater than key.marks to one position ahead
        while (j >= 0 && s[j].marks > key.marks) {
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = key;
    }
}

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    struct Student s[n];

    // Input student details
    for (int i = 0; i < n; i++) {
        printf("\nEnter details of student %d:\n", i + 1);
        printf("Roll number: ");
        scanf("%d", &s[i].roll);
        printf("Age: ");
        scanf("%d", &s[i].age);
        printf("Marks: ");
        scanf("%f", &s[i].marks);
    }

    // Sort by marks using insertion sort
    insertionSort(s, n);

    // Display sorted list
    printf("\nStudents sorted in ascending order of marks:\n");
    printf("Roll\tAge\tMarks\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%.2f\n", s[i].roll, s[i].age, s[i].marks);
    }

    return 0;
}
