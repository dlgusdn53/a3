#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[50];
    int id;
    int score;
} Student;

int main() {
    FILE* fp;
    int N;

    printf("학생 수 입력: ");
    scanf("%d", &N);

    Student* arr = (Student*)malloc(sizeof(Student) * N);

    fp = fopen("name_list.txt", "r");
    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return 0;
    }

    char names[100][50];
    int name_count = 0;

    while (fgets(names[name_count], sizeof(names[name_count]), fp)) {
        names[name_count][strcspn(names[name_count], "\n")] = 0;
        name_count++;
    }
    fclose(fp);

    srand(time(NULL));

    // 학생 생성 (포인터 방식)
    for (int i = 0; i < N; i++) {
        strcpy((*(arr + i)).name, names[rand() % name_count]);
        (*(arr + i)).id = i + 1;
        (*(arr + i)).score = rand() % 100 + 1;
    }

    int max = 0, min = 0;
int sum = 0;

for (int i = 0; i < N; i++) {
    if ((*(arr + i)).score > (*(arr + max)).score) max = i;
    if ((*(arr + i)).score < (*(arr + min)).score) min = i;
    sum += (*(arr + i)).score;
}

// 출력
printf("\n[최고점 학생]\n");
printf("이름: %s\n", (*(arr + max)).name);
printf("학번: %d\n", (*(arr + max)).id);
printf("점수: %d\n", (*(arr + max)).score);

printf("\n[최저점 학생]\n");
printf("이름: %s\n", (*(arr + min)).name);
printf("학번: %d\n", (*(arr + min)).id);
printf("점수: %d\n", (*(arr + min)).score);

printf("\n[평균 점수]\n");
printf("%.2f\n", (float)sum / N);

    free(arr);
    return 0;
}
