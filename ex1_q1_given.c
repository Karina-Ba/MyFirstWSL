#include "ex1_q1.h"

// ----------------------------------------------- //
void my_exception(int line, const char* function, char* msg)
{
	fprintf(stderr, "ERROR (line %d function: %s) !!!%s\n", line, function, msg);
    exit(1);
}
// ----------------------------------------------- //
double calc_side(struct point pt1, struct point pt2)
{
	double x = pt1.x - pt2.x;
	double y = pt1.y - pt2.y;
	return sqrt(x*x + y*y);	
}
// ----------------------------------------------- //
double calc_triangle_area(struct point p1, struct point p2, struct point p3)
{
	double area, 
	      x1 = p1.x, 
	      x2 = p2.x, 
	      x3 = p3.x, 
	      y1 = p1.y, 
	      y2 = p2.y, 
	      y3 = p3.y;		  
	area = 0.5*(x1*y2 + x2*y3 + x3*y1 - x2*y1 - x3*y2 -x1*y3);
	area = (area > 0) ? area : -area;
	return area;
}
// ----------------------------------------------- //
void print_point(struct point pt)
{
	printf("{%d, %d} ", pt.x, pt.y);
}
// ----------------------------------------------- //
void print_polygon_name(enum POLY_TYPE poly)
{
  switch (poly)
  {
    case QUADRI:  printf("quadrilateral "); break;
    case HEXAGON: printf("hexagon "); break;
    case OCTAGON: printf("octagon "); break;

    default: my_exception(__LINE__, __func__, "bad-polygon_type ");
  }
}
// ----------------------------------------------- //
void push(struct List * lst, struct polygon * poly)
{
	if (lst->head == NULL)
	{
		lst->head = (struct Node *)malloc(sizeof(struct Node));
		lst->head->poly = poly;
		lst->head->next = NULL;
	}

	else
	{
		struct Node * current = lst->head;

		while (current->next != NULL)
			current = current->next;
		
		current->next = (struct Node *)malloc(sizeof(struct Node));
		current->next->poly = poly;
		current->next->next = NULL;
	}
}
// ----------------------------------------------- //
struct polygon* pop(struct Node ** head)
{
	struct polygon* retval = NULL;
	struct Node * next_node = NULL;

	next_node = (*head)->next;
	retval = (*head)->poly;
	free(*head);
	*head = next_node;

	return retval;
}
// ----------------------------------------------- //