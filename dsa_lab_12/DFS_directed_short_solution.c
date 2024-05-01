/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 12 | 04/Apr/2024
	Tasks:		1,2,3
	
	Aim:  To perform the following tasks by running DFS on a directed graph.
		Taks 1: Given the adjacency list and a vertex of a directed graph, list all the vertices reachable from the given vertex.
		Task 2: Given the adjacency list of a directed graph, check whether the graph is strongly connected.
		Task 3: Given the adjacency list of a directed graph, find a topological ordering of it.		
	
*/

#include<stdio.h>
#include<stdlib.h>

/*Node data structure for the DFS tree/ forest.*/
typedef struct list_node {
	int node_index;                             // Index of the node as given by the adjacency matrix
	struct list_node* ptr_sibling;                   // Pointer to its next sibling in the adjacency list
	
} list_node;

/* Create a new adjacency list node and returns a pointer to it.
Input: Index of the node.
Output: Pointer to the newly created adjacency list node or NULL if the node creation fails.*/

list_node* create_node (int node_index){
	list_node* ptr_new_node = (list_node*) malloc (sizeof (list_node));
	if (ptr_new_node != NULL){
		ptr_new_node-> node_index = node_index;
		ptr_new_node->ptr_sibling = NULL;
	}
	return ptr_new_node;
}

/* Print List: Helper function to print the elements of a given list. */
int print_list (list_node* ptr_list_node){
	


	while (ptr_list_node != NULL){
		printf ("%d ", ptr_list_node-> node_index);
		ptr_list_node = ptr_list_node -> ptr_sibling;
	}
	
	return 0;
}

/* create_adjacency_list: Helper function to create adjacency list of a digraph from its adjacency matrix.*/
								

list_node** create_adjacency_list (char* file_name, int * order){


	FILE * graph_data;
	int i, j, temp;
	char* row;

	graph_data = fopen ( file_name,"r"); // Open the file in read-only mode
			
	list_node* ptr_new;
	list_node** adjacency_list;

	if (graph_data != NULL){

		fscanf(graph_data,"%d", &temp);
		(*order) = temp;

		adjacency_list = (list_node**)malloc(temp* sizeof(list_node*));
		row = malloc((temp+2) * sizeof(char));
		fgets(row,(temp+2), graph_data);
		
		for (i = 0; i < temp; i++){
			fgets(row,(temp+2), graph_data);
			adjacency_list[i] = NULL;
			
			for (j=0; j < temp; j++){
				if((row[j] - '0') == 1) {
					ptr_new = create_node(j);
					ptr_new -> ptr_sibling = adjacency_list[i];
					adjacency_list[i] = ptr_new;
				}

				
			} 
		} 

		fclose(graph_data);
	}

	return adjacency_list;
}

int free_list(list_node* list){

		if (list == NULL){
			return 0;
		}

		if(list-> ptr_sibling != NULL){
			free_list(list-> ptr_sibling);
		}
		free(list);
		
		return 0;
}

int free_adjacency_list (list_node** list, int order){
	int i;
	for (i=0; i < order ; i++){

		free_list(list[i]);
	}
	
	free(list);
	
	return 0;
}






/****************************************************************************************************************************/
/*Task 1: Goal of this task is to return a list of vertices reachable from a given vertex (the set includes the vertex itself). 
It is divided into the following two subtasks.
*/

/* Task 1(a): dfs_explore. Run a DFS from a given node and return a list of all the nodes reachable from it. 
				Input: i) order: Order of the graph.
				       ii) adjacency_list: Pointer to the adjacency list of the graph.
				       iii) node_index: Index of the node from which DFS will start.
				       iv) visited: Pointer to an array (indexed by node indices) indicating the list of nodes already visited by the DFS. A node is visited when the DFS reaches the 						   node for the first time.  visited[i] = 1 if the node i has been visited, otherwise visited[i] = 0.
				        
				 Output: i) A list of nodes reachable by the DFS from the starting node. Assume/ note that a node is reachable from itself. 
				 	   visited array should be updated accordingly.
 */
list_node* dfs_explore(int order, list_node** adjacency_list, int node_index, int * visited){
	
	int child_index;
	list_node* ptr_list = NULL;
	list_node* ptr_list2 = NULL;
	list_node* ptr_new = NULL;
	list_node* reachable_set = NULL;
	
	
	ptr_list = adjacency_list[node_index];
	visited[node_index] = 1;
	

	
	while (ptr_list != NULL){
		child_index = ptr_list -> node_index;
		if (visited[child_index] == 0){
			ptr_new = dfs_explore (order, adjacency_list, child_index, visited);
			ptr_list2 = ptr_new;
			while (ptr_list2 -> ptr_sibling != NULL){
				ptr_list2 = ptr_list2-> ptr_sibling;
			}
			ptr_list2->ptr_sibling = reachable_set;
			reachable_set = ptr_new;
			
		}
		ptr_list = ptr_list -> ptr_sibling;	
			
			 
	}
	
	ptr_new = create_node(node_index);
	ptr_new -> ptr_sibling = reachable_set;
	reachable_set = ptr_new;
	
	return reachable_set;
}

/* Task 1(b): list_reachable. Return a list of nodes reachable from a given node.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
				iii) node_index: Index of the given node.
			Output:
				A list of nodes reachable from the given node. Assume/note that a node is reachable from itself.
			       	
*/
list_node* list_reachable(int order, list_node** adjacency_list, int node_index ){
	int * visited;
	list_node* reachable_set = NULL;
	visited = (int*) calloc (order, sizeof(int));
	reachable_set = dfs_explore(order, adjacency_list, node_index, visited);
	return reachable_set;
}

/********************************************************************************************************************************


Task 2: Goal of this task is to check whether a given directed graph is strongly connected. It is divided into the following 
two subtasks.*/

/* Task 2(a): get_reverse_adjacency_list. Given the adjacency list of a digraph return the adjacency list of its reverse.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
			Output: Adjacency list of the reverse graph.
*/


list_node** get_reverse_adjacency_list (int order, list_node** adjacency_list){
	int i, child_index;
	list_node** reverse_adjacency_list;
	reverse_adjacency_list = (list_node**) malloc (order * sizeof(list_node*));
	list_node* ptr_list;
	list_node* ptr_new_node;
	
	for (i =0; i< order; i++){
		reverse_adjacency_list[i] = NULL;
	}

	for (i = 0; i < order; i++){
		ptr_list = adjacency_list[i];
		while (ptr_list != NULL){
		

			child_index = ptr_list -> node_index;
			ptr_new_node = create_node(i);
			ptr_new_node -> ptr_sibling = reverse_adjacency_list [child_index];
			reverse_adjacency_list [child_index] = ptr_new_node;
			ptr_list = ptr_list->ptr_sibling;
		}
		
	}
	
	return reverse_adjacency_list;
}
/* Task 2(b): is_strongly_connected. Checks whether the input directed graph (given by the adjacency list) is strongly connected.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
			Output: 1 if the graph is strongly connected; 0 otherwise.
*/
 
int is_strongly_connected(int order, list_node** adjacency_list ){

	list_node* ptr_list;
	list_node** reverse_adjacency_list;
	int count;
	ptr_list = list_reachable(order, adjacency_list, 0);
	
	
	count = 0;
	while (ptr_list != NULL){
		count++;
		ptr_list = ptr_list -> ptr_sibling;
	}
	
	if (count < order){
		return 0;
	}
	
	reverse_adjacency_list = get_reverse_adjacency_list(order, adjacency_list);
	
	ptr_list = list_reachable(order, reverse_adjacency_list, 0);
	
	count = 0;
	while (ptr_list != NULL){
		count++;
		ptr_list = ptr_list -> ptr_sibling;
	}
	
	if (count < order){
		return 0;
	}
	
	return 1;
}


/**********************************************************************************************************************************************************/

/* Task 3: Goal of this task is to generate a topological ordering of a given digraph or indicate that it is not possible (i.e., the digraph is cyclic). The task is
divided into the following two subtasks*/

/* Task 3(a): dfs_explore_with_time. Run the DFS. Also, maintain (i) an array indicating already visited nodes  (iii) an array of finish times of the already visited nodes (iv) an array where the already visited nodes are arranged in the reverse order of their visit (finish) times (ii) a clock counter.  

				Input 
				       i) order: Order of the graph.
				      ii) adjacency_list: Pointer to the adjacency list of the graph.
				      iii) node_index: Index of the node from which DFS will start.
				       iv) visited: Pointer to an array (indexed by node indices) indicating the list of nodes already visited by the DFS. A node is visited when the DFS reaches the 						   node for the first time.  visited[i] = 1 if the node i has been visited, otherwise visited[i] = 0.
				       v) clk: Pointer to a clock counter. 
				       vi) finished: Pointer to an array (indexed by node indices) indicating whether DFS has finished at/ returned from the corresponding node. finished[i] = 1, if 						    the DFS has returned from node i, otherwise finish[i] = 0. 
				       vii) topo_order: Pointer to an array containing node indices arranged in the reverse DFS finish time order. If the DFS has finished at node i before node j then 						    in the topo_order array node j appears before node i.
				       
				Output  0 if the subgraphs induced by the unvisited nodes of the DFS tree rooted at the input node can be topologically ordered, otherwise -1 (indicating that the 						induced subgraph is cyclic). Also update visited, clk, finish_time, topo_order.
				      */

int dfs_explore_with_time(int order, list_node** adjacency_list, int node_index, int * visited, int* clk,  int* finished,  int * topo_order){
	
	list_node* ptr_list;
	ptr_list = adjacency_list[node_index];
	int child_index;
	
	visited[node_index] = 1;
	
	
	while (ptr_list != NULL){
		child_index = ptr_list -> node_index;
		if (visited[child_index] == 0){
			if (dfs_explore_with_time (order, adjacency_list, child_index, visited,  clk, finished, topo_order) == -1){
				return -1;
			}
		} else if (finished[child_index] == 0){
			return -1;
		}
		ptr_list = ptr_list -> ptr_sibling;	
			
			 
	} 
	topo_order [order-1-*clk] = node_index;
	(*clk)++;
	finished[node_index] = 1;
	return 0;
	
}

/* Task 3(b): topo_order. Given a digraph return a topological ordering of it or indicate that it is not possible.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
			Output: A pointer to a sequence of nodes representing a topological order: If there is an u->v edge
				 then u preceedes v in the order. Return NULL if there is no such order (i.e., the digraph is cyclic).*/
				 
int* topo_order (int order, list_node** adjacency_list){
	int clk = 0;
	int i;
	int * visited;
	int * topo_order;
	int* finished;
	
	
	
	visited = (int*) calloc (order, sizeof(int));
	topo_order = (int*) malloc (order * sizeof(int));
	finished = (int*) calloc (order, sizeof(int));
	
	
	
	for (i =0; i < order; i++){
		if(visited[i] == 0){
			if (dfs_explore_with_time(order, adjacency_list, i, visited, &clk, finished, topo_order) ==-1){
				return NULL;
			}
		}
	}
	
/*	for (i=0; i< order; i++){*/
/*		printf("%d ", ptr_finish[i]);*/
/*	}*/
	
	return topo_order;
		
}
/*******************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
/*int dfs_explore_scc(int order, list_node** adjacency_list, int node_index, int * finish,  list_node** ptr_scc){*/
/*	*/
/*	list_node* ptr_list;*/
/*	list_node* ptr_new;*/
/*	int child_index;*/
/*	ptr_list = adjacency_list[node_index];*/
/*	*/
/*	*/
/*	*/
/*	finish[node_index] = -1;*/
/*	ptr_new = create_node(node_index);*/
/*	ptr_new -> ptr_sibling = (*ptr_scc);*/
/*	(*ptr_scc) = ptr_new;*/

/*	printf("coming to dfs explore node index = %d\n", node_index);*/

/*	while (ptr_list != NULL){*/
/*		child_index = ptr_list -> node_index;*/
/*		if (finish[child_index] != -1){*/
/*			dfs_explore_scc (order, reverse_adjacency_list, child_index, finish, ptr_scc);*/
/*		} */
/*		ptr_list = ptr_list -> ptr_sibling;*/
/*	}*/
/*	*/
/*	return 0;*/
/*}*/

int dfs_explore_with_finish_time(int order, list_node** adjacency_list, int node_index, int * visited, int* clk,  int * finish_order){
	
	list_node* ptr_list;
	ptr_list = adjacency_list[node_index];
	int child_index;
	
	visited[node_index] = 1;
	
	
	while (ptr_list != NULL){
		child_index = ptr_list -> node_index;
		if (visited[child_index] == 0){
			dfs_explore_with_finish_time (order, adjacency_list, child_index, visited,  clk, finish_order);
				
		}
		
		ptr_list = ptr_list -> ptr_sibling;	
	}
	 
	finish_order [order-*clk] = node_index;
	(*clk)++;
	return 0;
	
}

/* Task 3(b): topo_order. Given a digraph return a topological ordering of it or indicate that it is not possible.
			Input:
				i) order: Order of the graph.
				ii) adjacency_list: Pointer to the adjacency list of the graph.
			Output: A pointer to a sequence of nodes representing a topological order: If there is an u->v edge
				 then u preceedes v in the order. Return NULL if there is no such order (i.e., the digraph is cyclic).*/
				 
int* finish_time_order (int order, list_node** adjacency_list){
	int clk = 1;
	int i;
	int * visited;
	int * finished_order;
	int* finished;
	
	
	
	visited = (int*) calloc (order, sizeof(int));
	finished_order = (int*) malloc (order * sizeof(int));
	
	
	for (i =0; i < order; i++){
		if(visited[i] == 0){
			dfs_explore_with_finish_time(order, adjacency_list, i, visited, &clk, finished_order);
		}
	}
	
	return finished_order;
		
}

list_node** strong_components(int order, list_node** adjacency_list){
	
	int i, j=0;
	int * ptr_finish;
	int * ptr_visited;
	int node_index;

	list_node** reverse_adjacency_list;
	list_node** ptr_scc;
	
	
	
	ptr_finish = (int*) calloc (order, sizeof(int));

	
	ptr_scc = (list_node**) malloc (order * sizeof (list_node*));
	
	for (i = 0 ; i < order; i++){
		ptr_scc[i] = NULL;
	}

	
	

	
	reverse_adjacency_list = (list_node**) malloc (order * sizeof (list_node*));
	
	reverse_adjacency_list = get_reverse_adjacency_list (order, adjacency_list);
	ptr_finish = finish_time_order(order, reverse_adjacency_list);
	
	ptr_visited = (int*) calloc(order, sizeof(int));

	
	for (i = 0 ; i < order; i++){
		node_index = ptr_finish[i];
		if (ptr_visited[node_index] == 0){

			ptr_scc[j] = dfs_explore(order, reverse_adjacency_list, node_index, ptr_visited);
			
		
		}
		j++;
		
	}
	
	return ptr_scc;
	
}


int main(){

	list_node** adjacency_list;
	list_node* list;
	list_node** scc;
	int order, i, j;
	int * ptr_topo_order;

	char graph1[] = "dfs_dir_1";
	char graph2[] = "dfs_dir_2";
	char graph3[] = "dfs_dir_3";
	

	



/* Task 1*/
	printf("********************** Task 1 ********************\n");
	
	adjacency_list = create_adjacency_list(graph1,&order);
	list = list_reachable(order, adjacency_list, 4);
	print_list(list);

	free_adjacency_list (adjacency_list,order);


	
	
	adjacency_list = create_adjacency_list(graph2,&order);
	list = list_reachable(order, adjacency_list, 0);
	print_list(list);
	free_adjacency_list (adjacency_list,order);

	adjacency_list = create_adjacency_list(graph3,&order);
	list = list_reachable(order, adjacency_list, 0);
	print_list(list);
	free_adjacency_list (adjacency_list,order);

/*  Task 2*/
	printf("********************** Task 2 ********************\n");
	
	adjacency_list = create_adjacency_list(graph1,&order);
	if (is_strongly_connected(order, adjacency_list) == 1){
		printf ("Strongly connected \n");
	} else {
		printf ("Not strongly connected\n");
	}
	
	free_adjacency_list (adjacency_list,order);
	
	adjacency_list = create_adjacency_list(graph2,&order);
	
	if (is_strongly_connected(order, adjacency_list) == 1){
		printf ("Strongly connected \n");
	} else {
		printf ("Not strongly connected\n");
	}
	
	free_adjacency_list (adjacency_list,order);
	adjacency_list = create_adjacency_list(graph3,&order);
	if (is_strongly_connected(order, adjacency_list) == 1){
		printf ("Strongly connected \n");
	} else {
		printf ("Not strongly connected\n");
	}

	free_adjacency_list (adjacency_list,order);


/* Task 3*/

	printf("********************** Task 3 ********************\n");
	adjacency_list = create_adjacency_list(graph1,&order);
	
	ptr_topo_order = topo_order(order, adjacency_list);
	if (ptr_topo_order != NULL){
		printf("Topological order \n");
		for (i =0; i < order; i++){
			printf("%d ", ptr_topo_order[i]);
		}
	}else{
		printf("Digraph is cyclic\n");
	}
	
	free_adjacency_list (adjacency_list,order);
	
	adjacency_list = create_adjacency_list(graph2,&order);
	
	ptr_topo_order = topo_order(order, adjacency_list);
	if (ptr_topo_order != NULL){
		printf("Topological order \n");
		for (i =0; i < order; i++){
			printf("%d ", ptr_topo_order[i]);
		}
	}else{
		printf("Digraph is cyclic\n");
	}
	free_adjacency_list (adjacency_list,order);
	
	
	adjacency_list = create_adjacency_list(graph3,&order);
	
	ptr_topo_order = topo_order(order, adjacency_list);
	if (ptr_topo_order != NULL){
		printf("Topological order \n");
		for (i =0; i < order; i++){
			printf("%d ", ptr_topo_order[i]);
		}
	}else{
		printf("Digraph is cyclic\n");
	}
	
	free_adjacency_list (adjacency_list,order);
	
/* Task 4*/	
	
	printf("********************** Task 4 ********************\n");
	
	adjacency_list = create_adjacency_list(graph1,&order);
	
	scc = strong_components(order, adjacency_list);
	printf("Strong components \n");
	
	for(i=0; i< order; i++){
		if (scc[i] != NULL){
			printf("\n");
			print_list(scc[i]);
		}
	}
	
	free_adjacency_list(adjacency_list, order);
	free_adjacency_list(scc, order);
	
	
	
	

/*	adjacency_list = create_adjacency_list(graph2,&order);*/
/*	*/
/*	scc = strong_components(order, adjacency_list);*/
/*	printf("\n Strong components \n");*/
/*	*/
/*	for(i=0; i< order; i++){*/
/*		if (scc[i] != NULL){*/
/*			printf("\n");*/
/*			print_list(scc[i]);*/
/*		}*/
/*	}*/
/*	*/
/*	free_adjacency_list(adjacency_list, order);*/
/*	free_adjacency_list(scc, order);*/
/*	*/

/*	adjacency_list = create_adjacency_list(graph3,&order);*/
/*	*/
/*	scc = strong_components(order, adjacency_list);*/
/*	*/
/*	printf("Strong components \n");*/
/*	*/
/*	for(i=0; i< order; i++){*/
/*		if (scc[i] != NULL){*/
/*			printf("\n");*/
/*			print_list(scc[i]);*/
/*		}*/
/*	}*/
/*	*/
/*	free_adjacency_list(adjacency_list, order);*/
/*	free_adjacency_list(scc, order);*/
/*	*/

	return 0;
}
	
	
	
