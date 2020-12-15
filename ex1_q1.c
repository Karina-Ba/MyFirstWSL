#include "ex1_q1.h"

//-----------------------------------------------//
void main()
{
	runProgram();
}
//-----------------------------------------------//
void runProgram()
{
	struct List* polyList = (struct List*)malloc(sizeof(struct List));
	struct polygon* currPoly = polyList->head = NULL;
	char input[MAX_INPUT];
	enum BOOL* flags;

	while (TRUE)
	{
		scanf("%s", input); //Get command
		flags = getFlags(input); //Turn flags on

		if (flags[N])
		{
			currPoly = getNewPoly(input, flags); //If command has 'N' - create new polygom
			push(polyList, currPoly); //Add the new polygom to the list
		}

		if (flags[C]) //Find out for whom the flags
			doFlagActionsOnCurr(currPoly, flags); //For currentPoly

		else if (flags[A])
			doFlagActionsOnAll(polyList->head, flags); //For All poly

		if (flags[L]) //If flag 'L' is raised stop the loop
			break;

		free(flags); //Free allocated BOOL array
	}

	freeMemory(polyList, flags);
}
//-----------------------------------------------//
enum BOOL * getFlags(char * input)
{
	int stringLen = strlen(input) - 1; //Get the commands length
	enum BOOL * flags = (enum BOOL*)calloc(MAX_FLAGS, sizeof(enum BOOL)); //Allocate memory and set to FALSE

	for (int i = 0; i <= stringLen; ++i) //Ready and raise flags
	{
		switch (input[i])
		{
		case 'a':
			flags[a] = TRUE;
			break;
		case 'd':
			flags[d] = TRUE;
			break;
		case 'p':
			flags[p] = TRUE;
			break;
		case 'C':
			flags[C] = TRUE;
			break;
		case 'A':
			flags[A] = TRUE;
			break;
		case 'L':
			flags[L] = TRUE;
			break;
		case 'N':
			flags[N] = TRUE;
			break;
		case 'Q':
			flags[Q] = TRUE;
			break;
		case 'H':
			flags[H] = TRUE;
			break;
		case 'O':
			flags[O] = TRUE;
			break;
		}
	}

	return flags;
}
//-----------------------------------------------//
struct polygon* getNewPoly(char * input, enum BOOL* flags)
{
	struct polygon* newPoly = (struct polygon*)malloc(sizeof(struct polygon)); //Alocate polygon

	//Get polygon Type
	if (flags[Q])
		newPoly->poly_type = QUADRI;

	else if (flags[H])
		newPoly->poly_type = HEXAGON;

	else if (flags[O])
		newPoly->poly_type = OCTAGON;

	else
		newPoly->poly_type = BAD_POLY;

	getVertices(newPoly); //Get polygon vertices

	return newPoly;
}
//-----------------------------------------------//
void getVertices(struct polygon* currPoly)
{
	lluint vertices[2] = { 0 }; //There will be at least 1 line and at most 2
	
	scanf("%llx", &vertices[0]); //Get first line of vertices

	if (currPoly->poly_type != QUADRI) //If the polygon is not Q then there will be another vertices line input, scan it
		scanf("%llx", &vertices[1]);

	for (int i = 0; i < QUADRI; ++i) //For Any polygon, translate the first line of 4 vertices
	{
		currPoly->vertices[i] = lluintToPoint(&vertices[0]); 
	}

	if (currPoly->poly_type != QUADRI) //For any polygon that isn't Q, translate the rest of the vertices
	{
		for (int i = 0; i < currPoly->poly_type - QUADRI; ++i)
		{
			currPoly->vertices[i + QUADRI] = lluintToPoint(&vertices[1]);
		}
	}
}
//-----------------------------------------------//
struct point lluintToPoint(lluint * vertices)
{
	struct point currPoint;

	currPoint.x = lluintToInt(vertices);
	currPoint.y = lluintToInt(vertices);

	return currPoint;
}
//-----------------------------------------------//
int lluintToInt(lluint * vertices)
{
	//Take the  2 digits on the right
	int temp = *vertices % 256;
	*vertices /= 256;

	//Translate to signed 
	if (temp > 127)
		temp -= 256;
	
	return temp;
}
//-----------------------------------------------//
void doFlagActionsOnCurr(struct polygon* currPoly, enum BOOL* flags)
{
	//Creates a node to use the other function with current polygon and free at the end
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->poly = currPoly;
	node->next = NULL;
	doFlagActionsOnAll(node, flags);
	free(node);
}
//-----------------------------------------------//
void doFlagActionsOnAll(struct Node* currNode, enum BOOL* flags)
{
	while (currNode)
	{
		//For each flag raised do the corresponding action
		if (flags[d])
		{
			printPolygonInformation(currNode);
		}

		if (flags[p])
		{
			printPerimeterOfPolygons(currNode);
		}

		if (flags[a])
		{
			printAreaOfPolygons(currNode);
		}
		currNode = currNode->next;
	}
}
//-----------------------------------------------//
void printAreaOfPolygons(struct Node* currNode)
{
	double area = 0;

	for (int i = 1; i < currNode->poly->poly_type - 1; ++i)
	{
		area += calc_triangle_area(currNode->poly->vertices[0], currNode->poly->vertices[i], currNode->poly->vertices[i + 1]);
	}

	printf("area = %.1f\n", area);
}
//-----------------------------------------------//
void printPerimeterOfPolygons(struct Node* currNode)
{
	double perimeter = 0;

	for (int i = 0; i < currNode->poly->poly_type - 1; ++i)
	{
		perimeter += calc_side(currNode->poly->vertices[i], currNode->poly->vertices[i + 1]);
	}

	perimeter += calc_side(currNode->poly->vertices[currNode->poly->poly_type - 1], currNode->poly->vertices[0]);
		
	printf("perimeter = %.1f\n", perimeter);
}
//-----------------------------------------------//
void printPolygonInformation(struct Node* currNode)
{
	print_polygon_name(currNode->poly->poly_type);

	for (int i = 0; i < currNode->poly->poly_type; ++i)
	{
		print_point(currNode->poly->vertices[i]);
	}

	printf("\n");
}
//-----------------------------------------------//
void freeMemory(struct List* lst, enum BOOL* arr)
{
	struct Node* curr = lst->head;
	struct polygon* poly;

	if (curr) //free Nodes and polygons in nodes
	{
		while (curr->next)
		{
			poly = pop(&curr);
			free(poly);
		}

		free(curr->poly);
		free(curr);
	}

	free(lst);
	
	if (arr) //free the last BOOL array
	{	
		free(arr);
	}
}
//-----------------------------------------------//