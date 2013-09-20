#include <stdio.h>
#include <math.h>

void print_n_times(char *x, int n) {
    // Print a string n times
    int i;
    for (i = 0; i < n; i++) {
        printf("%s", x);
    }
}


double powerOf(double x, int n) {
    double pow;
    int i;
    pow = 1;
    // code that computes pow = x to the nth power here
    for (i = 0; i < n; i++) {
        pow = x * pow;
    }
    return pow;
}

void make_row(double point) {
    // Given a point to be graphed for some row
    // scale that point and put the correct number
    // of spaces around it.
    int image;
    image = (int)round(20 * point);

    if (image < 0) {
        print_n_times(" ", 20 + image);
        printf("*");
        print_n_times(" ", 0 - image - 1);
        printf("|");
        print_n_times(" ", 20);
        printf("\n");
    }
    else if (image > 0) {
        print_n_times(" ", 20);
        printf("|");
        print_n_times(" ", image - 1);
        printf("*");
        print_n_times(" ", 20 - image);
        printf("\n");
    }
    else {
        print_n_times(" ", 20);
        printf("*");
        print_n_times(" ", 20);
        printf("\n");
    }
}

void make_graph(int n) {
    // Make a graph of sin(x)^n between -pi and pi
    // range_band is the x distance between points we calculate
    // the intended graph is 41 chars wide and 21 chars long.
    double point;
    double neg_pi;
    double range_band;
    int i;
    neg_pi = -3.14159265359;
    range_band = 3.14159265359/10.5;

    printf("Here's the graph of sin(x)^%d between -pi and pi:\n", n);
    for (i = 1; i <= 21; i++) {
        point = powerOf(sin(neg_pi + (range_band * i)), n);
        make_row(point);
    }
}

int main() {
    int power;
    printf("Enter the power of sine which you wish to graph: ");
    scanf("%d", &power);
    make_graph(power);
}
