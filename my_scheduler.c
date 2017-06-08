#include "threads.h"
extern int scheduling_type;
extern thread_queue_t *ready_list;

void thread_enqueue(thread_t *t, thread_queue_t *q){
	// Declaring and initializing new thread node
	thread_node_t* newNode = (thread_node_t*)malloc( sizeof( thread_node_t ) ); 
	newNode->thread = t;
	newNode->next = NULL;

	// Checking if queue is empty and adding newNode to queue
	if( q->size == 0 ) {
		// Empty
		q->head = newNode;
		q->tail = newNode;
		q->size++;
	} else if( q->size < 100 ) {
		// Not empty and less than MAX_NO_THREADS
		q->tail->next = newNode;
		q->tail = newNode;
		q->size++;
	}
}

thread_t *thread_dequeue(thread_queue_t *q){
	// Declaring variable to return
	thread_node_t* freeNode; 
	thread_t* retThread; 

	// Checking if queue is empty.  If not dequeue the head node in thread_queue_t q
	if( q->size > 0 ) {
		freeNode = q->head; // pointer to space in memory to free
		retThread = freeNode->thread; // thread to return to be dequeued 
		q->head = q->head->next; // assigning new head in queue
		free( freeNode ); // freeing malloced node
		q->size--;  // updating size
		return retThread;
	} else {
		return NULL;
	}
}

// Function totalTickets calculates the number of tickets or CPU weight in the ready_queue
int totalTickets( void ) {
	// Declearing and initializing variables
	thread_node_t* node = ready_list->head; // pointer to a node in the queue
	int tickets = 0; // used to keep track of the number of tickets

	// walking through every node in the queue
	while( node ) {
		tickets += node->thread->priority;
		node = node->next;
	}

	return tickets;
}

thread_t* scheduler(){
    switch(scheduling_type)
    {
        case 0:   // Round Robin
			return thread_dequeue( ready_list );
        case 1: ; // Lottery
			int counter = 0; // used to keep track if winner found
			int winner = random() % totalTickets(); // selects the winning ticket
			thread_node_t* node = ready_list->head; // walks through the ready_list
			
			// Walking through ready_list until winner found
			while( node ) {
				counter += node->thread->priority;
				if( counter > winner ) {
					return node->thread; // winner found
				} else {
					node = node->next; // winner not found, next node
				}
			}
            return NULL;
        case 2:          //First come first serve
            return ready_list->head->thread;
        default:
            return NULL;
    }
}
