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

    // 동적할당
    Student* arr = (Student*)malloc(sizeof(Student) * N);

    // 파일 열기
    fp = fopen("name_list.txt", "r");
    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return 0;
    }

    char names[100][50]; // 이름 저장
    int name_count = 0;

    // 파일에서 이름 읽기
    while (fgets(names[name_count], sizeof(names[name_count]), fp)) {
        names[name_count][strcspn(names[name_count], "\n")] = 0; // 개행 제거
        name_count++;
    }
    fclose(fp);

    srand(time(NULL));

    // 학생 정보 생성
    for (int i = 0; i < N; i++) {
        strcpy(arr[i].name, names[rand() % name_count]);
        arr[i].id = i + 1;
        arr[i].score = rand() % 100 + 1;
    }

    // 최고 / 최저 / 평균
    int max = 0, min = 0;
    int sum = 0;

    for (int i = 0; i < N; i++) {
        if (arr[i].score > arr[max].score) max = i;
        if (arr[i].score < arr[min].score) min = i;
        sum += arr[i].score;
    }

    printf("\n최고점 학생\n");
    printf("이름: %s 학번: %d 점수: %d\n", arr[max].name, arr[max].id, arr[max].score);

    printf("\n최저점 학생\n");
    printf("이름: %s 학번: %d 점수: %d\n", arr[min].name, arr[min].id, arr[min].score);

    printf("\n평균 점수: %.2f\n", (float)sum / N);

    free(arr);
    return 0;
}
