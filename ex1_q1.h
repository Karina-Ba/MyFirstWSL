#include <stdio.h>
//#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

// ------------------------------------------------------------------------------ //
// *****   declarations of types and constants   *****

#define lluint long long unsigned int

#define MAX_VERT    8 // maximum number of vertices (6 is for hexagon)
#define MAX_INPUT   20 // Maximum input
#define MAX_FLAGS   10

// ------------------------------------------------------------------------------ //
enum POLY_TYPE {QUADRI = 4, PENTAGON, HEXAGON = 6, OCTAGON = 8, BAD_POLY};
enum FLAG {a = 0, d, p, C, A, L, N, Q, H, O };
enum BOOL {FALSE = 0, TRUE = 1};

// ------------------------------------------------------------------------------ //
struct point {
   int x, y;
};

struct polygon {
     enum POLY_TYPE poly_type;
     struct point vertices[MAX_VERT];
}; 

struct Node {
    struct polygon* poly;
    struct Node* next;
};

struct List {
	struct Node * head;
};

// ------------------------------------------------------------------------------ //
// *****   declarations of function prototypes   *****
void my_exception(int line, const char* function, char* msg);
double calc_side(struct point pt1, struct point pt2);
double calc_triangle_area(struct point p1, struct point p2, struct point p3);
void print_point(struct point pt);
void print_polygon_name(enum POLY_TYPE poly);

// --------------------- My Functions ---------------------- //
void runProgram();
struct polygon* getNewPoly(char * input, enum BOOL * flags);
void getVertices(currPoly);
struct point lluintToPoint(lluint * vertices);
int lluintToInt(lluint * vertices);
enum BOOL* getFlags(char * input);
void doFlagActionsOnCurr(struct polygon* currPoly, enum BOOL* flags);
void doFlagActionsOnAll(struct Node* currPoly, enum BOOL* flags);
void printAreaOfPolygons(struct Node* currNode);
void printPerimeterOfPolygons(struct Node* currNode);
void printPolygonInformation(struct Node* currNode);
void freeMemory(struct List* lst, enum BOOL* arr);

// ------------------- List Functions --------------------- //
void push(struct List * lst, struct polygon * poly);
struct polygon* pop(struct Node ** head);
