#include <stdio.h>

int totalPaper(int, int, int);
int smallestSide(int, int, int);

int main()
{
    int t = 0; // total paper counter
    int p = 0; // current paper counter
    char* line = NULL;
    FILE* input;
    size_t len = 0;
    ssize_t read;
    int x, y, z; // dimensions

    input = fopen("input.txt", "r");
    if (input == NULL) {
        puts("Error opening file!");
        return 1;
    }

    while ((read = getline(&line, &len, input)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        sscanf(line, "%dx%dx%d", &x, &y, &z);
        printf("x:%d, y:%d, z:%d\n", x, y, z);
        p = totalPaper(x, y, z);
        printf("paper: %d\n", p);
        t = t+p;
    }

    printf("total: %d\n", t);

    fclose(input);

    // 1591801 was too hight...
    return 0;
}

/**
 * Calculate the wrapping paper needed for a box.
 * Done by summing:
 *   - area of the cuboid 2xy + 2yz + 2xz
 *   - some slack (the area of the smallest side)
 */
int totalPaper(int x, int y, int z) {

    int a = x*y;
    int b = x*z;
    int c = z*y;

    // get smallest side
    int s = smallestSide(a, b, c);

    return 2*a + 2*b + 2*c + s;
}

/**
 * Simply returns the smallest of 3 numbers.
 * Would be cool if it could do an array of arbitrary size.
 * Used for finding which side of a cuboid is smallest.
 * Uses <= instead of < because somesides small sides have equal length
 */
int smallestSide(int a, int b, int c) {
    if (a <= b && a <= c) {
        return a;
    } else if (b <= a && b <= c) {
        return b;
    } else {
        return c;
    }
}
