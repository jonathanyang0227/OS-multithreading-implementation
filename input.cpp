#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    char input_file[] = "input.csv";
    int n = atoi(argv[1]), i, size =atoi(argv[2]);
    int num;
    double START, END;
    stringstream ss;
    START = clock();
    FILE *in = fopen(input_file, "w");
    if (in == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    cout << "total number : " << n * size << endl;
    srand(time(NULL));

    int *arr = (int *) malloc((n * size) * sizeof(int));
    for (i = 0; i < n * size; i++) {
        if (i % 2 == 0) {
            arr[i] = rand();
        } else {
            arr[i] = -rand();
        }
    }

    for (i = 0; i < n * size; i++) {
        ss << arr[i];
        if (i % 20 == 19)
            ss << "\n";
        else
            ss << "|";
    }
    fputs(ss.str().c_str(), in);
    ss.str(" ");
    END = clock();
    cout << "time: " << (END - START) / CLOCKS_PER_SEC << endl;

    fclose(in);
    free(arr);
}