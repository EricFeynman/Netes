#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define GB 1073741824
#define BUFFER_SIZE 8192
#define DOUBLE_SIZE sizeof(double)
#define FILE_NAME "test.txt"
#define PART_FILE_1 "part1.txt"
#define PART_FILE_2 "part2.txt"
#define PART_FILE_3 "part3.txt"
#define N 16

double randfrom(double min, double max) {
    return ((double)rand() * (max - min)) / (double)RAND_MAX + min;
}

void createfile(long long size) {
    FILE* fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    const int buff = BUFFER_SIZE;
    double* arr = malloc(buff * DOUBLE_SIZE);
    if (arr == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    int n = buff / DOUBLE_SIZE;
    long int s = (long int)(size / buff);
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < n; j++) {
            arr[j] = randfrom(1.0, 100.0);
        }
        fwrite(arr, DOUBLE_SIZE, n, fp);
    }
    free(arr);
    fclose(fp);
}

void handleFileError(FILE* file, const char* message) {
    if (file == NULL) {
        perror(message);
        exit(1);
    }
}

int cmpD(const void* p, const void* q) {
    double res = *(double*)p - *(double*)q;
    if (res > 0)
        return 1;
    else if (res < 0)
        return -1;
    else
        return 0;
}

void init(long long size) {
    FILE* fp = fopen(FILE_NAME, "rb+");
    handleFileError(fp, "Error opening file");

    const int buff = BUFFER_SIZE;
    double* arr = malloc(buff * DOUBLE_SIZE);
    if (arr == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    int n = buff / DOUBLE_SIZE;
    long int k = (long int)(size / buff);
    long int d;

    while (d = fread(arr, DOUBLE_SIZE, n, fp)) {
        qsort(arr, n, DOUBLE_SIZE, cmpD);
        fseek(fp, -d * DOUBLE_SIZE, SEEK_CUR);
        fwrite(arr, DOUBLE_SIZE, d, fp);
    }

    free(arr);
    fclose(fp);
}

void mergeFiles(FILE* src1, FILE* src2, FILE* dest, int size) {
    double* arr1 = malloc(size * DOUBLE_SIZE);
    double* arr2 = malloc(size * DOUBLE_SIZE);
    if (arr1 == NULL || arr2 == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    int n = size / DOUBLE_SIZE;
    int a = fread(arr1, DOUBLE_SIZE, n, src1);
    int b = fread(arr2, DOUBLE_SIZE, n, src2);

    while (a > 0 && b > 0) {
        int i = 0, j = 0;
        while (i < a && j < b) {
            if (arr1[i] <= arr2[j]) {
                fwrite(&arr1[i++], DOUBLE_SIZE, 1, dest);
            } else {
                fwrite(&arr2[j++], DOUBLE_SIZE, 1, dest);
            }
        }
        while (i < a) {
            fwrite(&arr1[i++], DOUBLE_SIZE, 1, dest);
        }
        while (j < b) {
            fwrite(&arr2[j++], DOUBLE_SIZE, 1, dest);
        }

        a = fread(arr1, DOUBLE_SIZE, n, src1);
        b = fread(arr2, DOUBLE_SIZE, n, src2);
    }

    free(arr1);
    free(arr2);
}

void MergeSort(long long size) {
    FILE* fp = fopen(FILE_NAME, "rb+");
    handleFileError(fp, "Error opening file");

    FILE* fp1 = fopen(PART_FILE_1, "wb+");
    FILE* fp2 = fopen(PART_FILE_2, "wb+");
    FILE* fp3 = fopen(PART_FILE_3, "wb+");

    handleFileError(fp1, "Error opening file");
    handleFileError(fp2, "Error opening file");
    handleFileError(fp3, "Error opening file");

    const int buff = BUFFER_SIZE;
    double* arr = malloc(buff * DOUBLE_SIZE);
    if (arr == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    int n = buff / DOUBLE_SIZE;
    long int k = (long int)(size / buff);
    long int h = k / 2;

    for (int i = 0; i < h; i++) {
        fread(arr, DOUBLE_SIZE, n, fp);
        fwrite(arr, DOUBLE_SIZE, n, fp1);
        fread(arr, DOUBLE_SIZE, n, fp);
        fwrite(arr, DOUBLE_SIZE, n, fp2);

        fseek(fp1, -buff, SEEK_CUR);
        fseek(fp2, -buff, SEEK_CUR);

        mergeFiles(fp1, fp2, fp3, buff);
    }

    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

int main() {
    srand(time(NULL));

    // Time measurement
    struct timeval start, end;
    gettimeofday(&start, NULL);

    long long mem = (long long) N * GB;
    createfile(mem);
    init(mem);
    MergeSort(mem);

    gettimeofday(&end, NULL);
    // Time calculation
    long long start_usec = start.tv_sec * 1000000 + start.tv_usec;
    long long end_usec = end.tv_sec * 1000000 + end.tv_usec;
    double elapsed = (double)(end_usec - start_usec) / 1000000.0;
    printf("Elapsed time (sec): %.4f\n", elapsed);

    return 0;
}
