#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Point {
    float x, y;
};

float dist(struct Point p1, struct Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

int cmpX(const void *a, const void *b) {
    return (((struct Point*)a)->x > ((struct Point*)b)->x);
}

int cmpY(const void *a, const void *b) {
    return (((struct Point*)a)->y > ((struct Point*)b)->y);
}

float brute(struct Point P[], int n) {
    float min = 1e9;
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

float stripClosest(struct Point strip[], int size, float d) {
    float min = d;
    qsort(strip, size, sizeof(struct Point), cmpY);

    for(int i = 0; i < size; i++)
        for(int j = i+1; j < size && (strip[j].y - strip[i].y) < min; j++)
            if (dist(strip[i], strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}

float closestUtil(struct Point P[], int n) {
    if (n <= 3)
        return brute(P, n);

    int mid = n / 2;
    struct Point midP = P[mid];

    float dl = closestUtil(P, mid);
    float dr = closestUtil(P + mid, n - mid);

    float d = (dl < dr) ? dl : dr;

    struct Point strip[n];
    int j = 0;
    for(int i = 0; i < n; i++)
        if (fabs(P[i].x - midP.x) < d)
            strip[j++] = P[i];

    return stripClosest(strip, j, d);
}

float closest(struct Point P[], int n) {
    qsort(P, n, sizeof(struct Point), cmpX);
    return closestUtil(P, n);
}

int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    struct Point P[n];
    printf("Enter x y for each point: \n");
    for(int i = 0; i < n; i++)
        scanf("%f %f", &P[i].x, &P[i].y);

    float ans = closest(P, n);
    printf("Minimum Distance = %f\n", ans);

    return 0;
}
