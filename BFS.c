#include <stdio.h>
#include <stdlib.h>

struct node
{
	int num;
	struct node *next;
};
typedef struct node node;

void enQueue(node *head, int num)
{
	node *tmp, *newNode;
	newNode = (node*)malloc(sizeof(node));
	newNode -> num = num;
	newNode -> next = NULL;
	
	tmp = head;
	while(tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = newNode;
}

int isEmpty(node *head)
{
	if(head -> next == NULL)
		return 1;
	else
		return 0;
}

int deQueue(node *head)
{
	int num = head -> next -> num;
	node *tmp;
	tmp = head -> next;
	head -> next = head -> next -> next;
	free(tmp); 
	return num;	
}

int main()
{
	int n, p, r, i;
	int x, y;
	int *color, *distance, *PI;
	int u, v;
	node *tmp, **array, *queue;
	
	scanf("%d%d%d", &n, &p, &r);
	
	array = (node**)malloc(sizeof(node*)*(n+1));
	queue = (node*)malloc(sizeof(node));
	queue -> num = -1;
	queue -> next = NULL;
	
	for(i=1; i<=n; i++)
	{
		array[i] = (node*)malloc(sizeof(node));
		array[i] -> num = i;
		array[i] -> next = NULL;
	}
	
	for(i=1; i<=p; i++)
	{
		scanf("%d%d", &x, &y);
		tmp = (node*)malloc(sizeof(node));
		tmp -> num = y;
		tmp -> next = array[x] -> next;
		array[x] -> next = tmp;
		
		tmp = (node*)malloc(sizeof(node));
		tmp -> num = x;
		tmp -> next = array[y] -> next;
		array[y] -> next = tmp;
	}
	
	//print the linked list representation of the given graoh
	printf("linked list representation of the graph:\n");
	for(i=1; i<=n; i++)
	{
		printf("%d: ", array[i] -> num);
		tmp = array[i] -> next;
		while(tmp != NULL)
		{
			printf("%d ", tmp -> num);
			tmp = tmp -> next;
		}
		printf("\n");
	}
	
	// begin the process of BFS
	printf("\n%d as source node, the process of the BFS:\n", r);
	color = (int*)malloc(sizeof(int)*(n+1));
	distance = (int*)malloc(sizeof(int)*(n+1));
	PI = (int*)malloc(sizeof(int)*(n+1));
	
	
	for(i=1; i<=n; i++)
	{
		color[i] = -1; //-1 represents WHITE, 0 represents GRAY, 1 represents BLACK
		distance[i] = -1;
		PI[i] = -1;
	}
	color[r] = 0;
	distance[r] = 0;
	enQueue(queue, r);
	
	while(isEmpty(queue) == 0)
	{
		u = deQueue(queue);
		printf("delete vertex: %d\n", u);
		tmp = array[u] -> next;
		while(tmp != NULL)
		{
			v = tmp -> num;
			if(color[v] == -1)
			{
				printf("   add vertex: %d\n", v);
				color[v] = 0;
				PI[v] = u;
				distance[v] = distance[u] + 1;
				enQueue(queue, v);
			}
			tmp = tmp -> next;
			
		}
		color[u] = 1;
	}
	
	printf("\nafter BFS, property of each node:\n");
	printf("color:    ");
	for(i=1; i<=n; i++)
		printf("%d  ", color[i]);
	printf("\n");
	
	printf("distance: ");
	for(i=1; i<=n; i++)
		printf("%d  ", distance[i]);
	printf("\n");
	
	printf("PI:      ");
	for(i=1; i<=n; i++)
		printf("%d  ", PI[i]);
	//printf("\n");
	
	for(i=0; i<=n; i++)
		free(array[i]);
	free(array);
	free(tmp);
	free(queue);
	free(color);
	free(distance);
	free(PI);
	return 0;
}
