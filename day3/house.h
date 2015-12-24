#ifndef _HOUSE_H
#define _HOUSE_H

// typedefs
typedef struct house house;
struct house {
    int x;
    int y;
    house* next;
};

// public functions
void   house_free(house*);
house* house_init(int, int);
void   house_add(house*, int, int);
void   house_uniq(house*);
house* house_join(house**, int);
int    house_count(house*);

#endif /* _HOUSE_H */

#ifndef HOUSE_VERBOSE
#define HOUSE_VERBOSE 1 // verbosity level (lots of output trips at 2)
#endif
