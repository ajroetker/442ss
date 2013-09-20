#include <stdio.h>

void print_n_times(char *x, int n) {
    // Print a string n times
    int i;
    for (i = 0; i < n; i++) {
        printf("%s", x);
    }
}

void make_graph(int rows) {
    int spaces;
    for (spaces = rows; spaces >= 0; spaces--) {
        print_n_times(" ", spaces + 1);
        print_n_times("* ", rows-spaces);
        printf("\n");
    }
}

int main(){
    int rows;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    make_graph(rows);
    printf("\n");
}
