//this program will generate the steps of a recipe for a dish according to their precedence
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct list
{
  int number;
  
  char str[50];
  
  int inDegree;
  
  bool visited;
  
} node;


typedef struct queue
{
  int data;  
  
  struct queue *next;
    
} queue;


queue *front = NULL;//keeps track of the front end of the queue

queue *rear = NULL;//keeps track of the rear end of the queue


int queueCount ()//functon for counting the number of elements in the queue
{
   queue *p = front;
   
   int count = 0;
  
   if ( front == NULL )
   {
      return count;//if front is NULL, it means that the queue is empty
   }
   
   while ( p != NULL )
   {
      //if front is not NULL, the loop iterates till NULL is encountered
      count = count + 1;//the count is updated
      
      p = p->next;
   } 
  
   return count;//the number of elements in the queue is returned
}


bool isFull ( int n )//to check if the queue is full
{
   //if the number of elements in the queue is equal to the total number of vertices in the graph, then the queue is full
   if ( queueCount() == n ) 
   {
      return true;
   } 
   else
   {
      return false;  
   } 
}


void enqueue ( int data, int n )//function for entering a new element into the queue
{
   if ( !isFull(n) )//to check if the queue is full
   {
      queue *p = NULL;
      
      p = ( queue* )malloc( sizeof( node ) );//allocation of memory
      
      p->data = data;  
      
      //insertion of new element is done at the rear end of the queue 
      if ( front == NULL )
      {
         //if front is NULL, then number of elements in the queue is 0, hence p becomes the first element of the queue
         front = p;
      }
      else
      {
         rear->next = p;//if the queue is not empty, then the new element is inserted at the rear end  
      }
      
      //value of rear is updated and it now points to the newly inserted element(which is now at the end of the queue)
      rear = p;
      
      rear->next = NULL;
   }
}


bool isEmpty ()//function to check if the queue is empty
{
   if ( queueCount() == 0 )//if the number of elements in the queue is 0, then the function returns true 
   {
      return true;
   } 
   else
   {
      return false;  
   } 
}


int dequeue()//function to remove an element from the queue
{
   if ( !isEmpty() )//to check if the queue is empty
   {
      int val = front->data;
    
      queue *temp = front;
      
      if ( front == rear )//if front is equal to rear, then the queue has only one element
      {
         front = rear = NULL;// after removal, the queue will be empty and front and rear will point to NULL
      }
      else
      {  
         /*if the queue has more than 1 element, the value of front is updated and it now stores the value of second 
           element from the front end*/
         front = front->next;
      }
      //while dequeueing, the element is removed from the front end
      
      free ( temp );//to free the memory
    
      return val;//the value of the node is returned
   }
}


void createList ( node p[], int index )//function to create a list of the instructions
{
   p[index].number = index+1;
   
   p[index].visited = false;
   
   scanf(" %[^\n]s",p[index].str);//takes the step or instruction as input
}


//function for sorting the vertices of the graph according to their precedence
void topologicalSort ( node p[], int n, int j, int A[][n] )
{
   static int count = 1;//making the count value available to the recursive call of the function(initialised once) 
   
   p[j].visited = true;//marking the vertice as true if visited
   
   int index = -2, i;
   
   enqueue ( j, n );
   
   for ( i = 0; i < n; i++ )
   {
       //searching for the outgoing edge for the vertex(with in-degree 0) in the adjacency matrix
       if ( A[j][i] == 1 )
       {
          //updating the in-degree of all vertices connected to the vertex having in-degree 0 
          p[i].inDegree = p[i].inDegree - 1;        
       }
       
       //searching for the new unvisited vertex with in-degree 0
       if ( p[i].inDegree == 0 && p[i].visited == false && index == -2 )
       {
          index = i;     
                    
          count++;//incrementing the counter
       }
   }
   
   if ( index != -2 )
   {
      topologicalSort ( p, n, index, A);//recursive call to the topologicalSort
   }
   else
   {
      if ( count != n )
      {
         printf ( "\nThe graph is not a DAG\n" );
         
         exit ( 0 );//exiting the program in case a cycle is found in the graph
      }
   }
}


void delay ( int number_of_seconds )//function for introducing a delay
{
    int milli_seconds = 1000 * number_of_seconds;//total milliseconds by which we want to delay our program
  
    clock_t start_time = clock ();//this has the starting time 
  
    //this loop iterates till the value of clock is equal to the total delay time that we want
    while ( clock() < start_time + milli_seconds )
    {
          ;//blank loop
    }     
}


int main ()
{
    int n, i, j, index, count;
    
    char answer[100], name[20], *token;
    
    bool check_inDegree = false;
    
    
    printf ( "Enter the name of the dish : " ); 
    
    scanf ( " %[^\n]s", name );//taking the name of the dish as input
    
    
    
    printf ( "\nEnter the number of instructions : " );
    
    scanf ( "%d", &n );//to take the number of nodes of the graph as input
    
    
  
    
    int A[n][n];
    
    node p[n];
    
    
    
    
    printf ( "\nEnter the instructions of the recipe of the dish (%s) in random order -\n\n", name );
    
    for ( i = 0; i < n; i++ )
    {
        printf ( "Enter instruction %d : ", i + 1 );
        
        createList ( p, i );//calling the create list function where the instruction is taken as input
    }
  
    printf ( "\n" );
    
    
    
    
    for ( i = 0; i < n; i++ )
    {
        for ( j = 0; j < n; j++ )
        {
             A[i][j] = 0;//the adjacency matrix is populated with zero
        }
    }
    
    
    
    for ( j = 0; j < n; j++ )
    {
        printf ( "Enter the instructions which instruction %d is dependent on / Press 0 if instruction %d is independent : ", j + 1, j + 1 );
               
        scanf ( " %[^\n]s", answer );//takes the steps on which j+1 th step depends
        
        count = 0;
        
        token = strtok( answer, " " );
        
        while ( token )
        {
           if ( *token != '0' )
           {
              index = atoi ( token );
              
              A[index-1][j] = 1;
              
              count++;
           }
           
           token = strtok ( NULL, " " );
        }
        
        p[j].inDegree = count;//setting the in-degree of the vertices 
              
        printf("\n");
    }
    
     
     
    //checking for a vertice with in-degree 0 
    for ( j = 0; j < n; j++ )
    {
        if ( p[j].inDegree == 0 )
        {
           check_inDegree = true;
           
           break;
        }
    }
  
    if ( check_inDegree == false )//to check if the graph formed is a directed acyclic graph(DAG)
    {
       printf ( "\nThe graph is not a DAG\n" );//if the graph is not a DAG, the topological sort cannot be performed
       
       exit ( 0 );
    }
  
  
  
    topologicalSort ( p, n, j, A );//function call for topological sort

    
    //to display the steps after applying topological sort according to their precedence
    printf ( "The sequential steps of the recipe of (%s) are -\n\n", name );
  
    for ( i = 0; i < n; i++ )
    {
        j = dequeue();
        
        delay ( 540 );
        
        printf ( "Step %d (instruction %d)-->  %s\n", i + 1, p[j].number, p[j].str );

    }
     
    printf ( "\n" );
  
    return 0;
}










