/*
NAME: SWADHA SWAROOP
ROLL: 112201009
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Lab:		Week 13 | 25/Apr/2024
	Tasks:		1 (a,b), 2(a,b,c)
	
	Aim:  To construct hash table for insertion, search, and deletion of a given set of data items.
		Taks 1 (divided into a,b): Construct a hash table with open addressing to perform insertion, search, and deletion.
		Task 2 (divided into a,b,c): Construct a hash table with chaining to perform insertion, search, and deletion, and a hash table that resizes itself (only for insertion)
		
		
	Note: 1) All the tasks are given in Section 2. Section 1 contains some helper/ utility functions which you may require. Section 3 contains functions to run the tests. Do not modify any 		function outside Section 2.
	      2) The tests will show some statistics of the operations performed such as number of clock cycles used per data item, average number of collisions etc.

	
				
	
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


/*****************************************************************Section 1: Helper/ Utility Functions*************************************************************************/

/*Node data structure for nodes used in lists.*/
typedef struct list_node {
	unsigned int data;                             // Data to be stored in the node
	struct list_node* ptr_next;                   // Pointer to its next node in the list
	
} list_node;
/* Create a new linked list node and returns a pointer to it.
Input: Data to be stored in the node.
Output: Pointer to the next node in the list.*/

list_node* create_node (int data){
	list_node* ptr_new_node = (list_node*) malloc (sizeof (list_node));
	if (ptr_new_node != NULL){
		ptr_new_node-> data = data;
		ptr_new_node->ptr_next = NULL;
	}
	return ptr_new_node;
}


/* 
get_random. Returns a random number between lb and ub.
*/




int get_random(int lb, int ub){
	int rand_num;
	srand(time(0));
	rand_num = (rand()%(ub-lb+1)+ lb);
	return rand_num;
}

/*
get_big_random. Returns a random unsigned int.
*/
unsigned int get_big_random(){
	
	unsigned int rand_val;


	
	rand_val  = (unsigned int) rand() & 0xff;
        rand_val |= ((unsigned int)rand() & 0xff) << 8;
        rand_val |= ((unsigned int)rand() & 0xff) << 16;
        rand_val |= ((unsigned int)rand() & 0xff) << 24;
        

        
        return rand_val;
        
}

/*

get_prime. Given an integer it returns a prime greater than the number. 

*/

int next_prime(int m){
	int i, j;
	bool flag;
	int sqval;
	double k;
	
	
	while(1){
		flag = false;
		
		sqval = (int) sqrt(m);
		
		
		for(i =2; i <= sqval; i++){
			if (m % i == 0){
				m++;
				flag = true;
				break;
			}
		}
		
		if(flag == false){
			return m;
		}
	}
}	





/********************************************************************************************Section 2: Tasks*************************************************************************************/


/**************************** Task 1: Hash with Open Addressing*******************************************/


typedef struct {
	int num_data; // Number of elements stored in the table at any given time
	int prime;   // Prime chosen for hash computation
	int num_collisions; // Number of collisions occurred in a certain sequence of insert operations (this is only required for testing and not an essential part of hash table information)
	unsigned int* ptr_table; // Array to store data items in the table. The data items are of unsigned int type.
}OA_Hash_Table;

/********** Task 1(a) *********************/

/*
init_oa_hash_table: Initialize the parameters of the hash table given an estimate of the number of items to be stored.


		   Input: num_data_items - Max number of data items that the table is expected to store.
		   Output : OA_Hash_Table with all its members initialized. num_collisions to be intitialized to 0. All the hash table entries should be initialized to some special value, e.g., 					UINT_MAX.
*/
OA_Hash_Table init_hash_oa_table(int num_data_items){
	OA_Hash_Table ht;
	ht.num_data = num_data_items;
	ht.prime = next_prime(num_data_items); 
	ht.num_collisions = 0;
	ht.ptr_table = (unsigned int*) (malloc(sizeof(unsigned int) * ht.prime));
	for (int i = 0;i< num_data_items; i++){
		ht.ptr_table[i] = UINT_MAX;
	}
	
	return ht;
}

/*
gives the hash for given x and i
*/
int get_hash(int x,int i,int m){
	if (i == 0 )
		return x % m;
	return (get_hash(x,0,m) + i) % m;
}

/*

hash_oa_insert: Insert a given list of data items into a given hash table with open addressing.
		Input: i) num_data_items - number of data items to be inserted.
		       ii) ptr_data - list of data items to be inserted
		       iii) ptr_oaht - pointer to the OA_Hash_Table hash table data structure.
		       iv) probe_seq - identifier for a particular probe sequence. We will use any one from the list given in the class notes.
		       
		Output: Updata the hash table pointed by ptr_oaht appropriately.       
*/
int hash_oa_insert(int num_data_items, unsigned int* ptr_data, OA_Hash_Table* ptr_oaht, int probe_seq){

	// printf("%d prime\n",ptr_oaht->prime);
	for (int i =0;i< num_data_items; i++){
		unsigned int num = ptr_data[i];
		int y = 0,pos = -1,prime = ptr_oaht->prime;
		int h = num % prime;
		// printf("%u %d,\n",num,h);
		do{
			pos = (h++) % prime;
			y++;
			// printf("%d ,\n",pos);
		}while(ptr_oaht->ptr_table[pos] != UINT_MAX);
		if (ptr_oaht->num_collisions < y)
			ptr_oaht->num_collisions = y;
		// printf("%d , %d\n",pos,num);
		ptr_oaht->ptr_table[pos] = num;
	}
	
	return 0;
}


/*************** Task 1(b) **************************************************************/

/*hash_oa_search: Search the hash table for a given list of data items.
		Input: i) num_data_items - number of data items to be searched.
		       ii) ptr_data - list of data items to be searched.
		       iii) ptr_flag - An array of flags indicating whether a data item has been found in the table. If ptr_data[i] is found in the hash table then ptr_flag[i] should be set to 1.
		       		All the flags are set to 0 in the input.
		       		
		       iv) ptr_oaht - pointer to the OA_Hash_Table hash table data structure.
		       v) probe_seq - identifier for a particular probe sequence. We will use any one from the list given in the class notes.
		Output: Update the ptr_flag array appropriately. */      
		       
int hash_oa_search(int num_data_items, unsigned int* ptr_data, OA_Hash_Table* ptr_oaht, int* ptr_flag, int probe_seq){

	for (int i =0;i< num_data_items; i++){
		unsigned int num = ptr_data[i];
		int y = 0,pos = -1,prime = ptr_oaht->prime;
		int h = num % prime;
		do{
			pos = (h++) % prime;
			y++;
			if (ptr_oaht->ptr_table[pos] == num){
				ptr_flag[i] = 1;
				break;
			}
		}while(y != ptr_oaht->num_collisions);
	}
	
	return 0;
}
/* hash_oa_delete: Delete a given list of data items from the hash table.
		Input: i) num_data_items - number of data items to be deleted.
		       ii) ptr_data - list of data items to be deleted.
		       iii) ptr_flag - An array of flags indicating whether a data item has been found and deleted from the table. If ptr_data[i] is found and deleted from the hash table then 					ptr_flag[i] should be set to 1. All the flags are set to 0 in the input.
		       iv) ptr_oaht - pointer to the OA_Hash_Table hash table data structure.
		       v) probe_seq - identifier for a particular probe sequence. Use any one from the list given in the class notes.
		       
		Output: If a given data item is found in the table then it should be replaced by the default value (e.g., UINT_MAX-1). Update the ptr_flag array appropriately. */  


int hash_oa_delete(int num_data_items, unsigned int* ptr_data, OA_Hash_Table* ptr_oaht, int* ptr_flag, int probe_seq){

	for (int i =0;i< num_data_items; i++){
		unsigned int num = ptr_data[i];
		int y = 0,pos = -1,prime = ptr_oaht->prime;
		int h = num % prime;
		do{
			pos = (h++) % prime;
			y++;
			if (ptr_oaht->ptr_table[pos] == num){
				ptr_oaht->ptr_table[pos] = UINT_MAX;
				ptr_flag[i] = 1;
				break;
			}
		}while(y != ptr_oaht->num_collisions);
	}

	return 0;
}

/************************************************************* Task 2: Hash with Chaining ******************************************/

typedef struct {
	int num_elements; // Number of elements stored in the hash table at any given time.
	int prime; // Prime number chosen for hash computation.
	int num_collisions; // Number of collisions occurred in a certain sequence of insert operations (this is only required for testing and not an essential part of hash table information).
	int ptr_coeffs[4]; // Array of 4 coefficients of the hash function.
	list_node** ptr_table; // Pointer to the array of chains.
} Hash_Table;

/****************************** Task 2(a) **************************************************************/
 /* init_hash_table. Initialize the hash table based on its size.
 
		   Input:   size - Max number of data items that the table is expected to store.
		   Output : Hash_Table with all its members initialized. For generation of prime you can use the the function next_prime() which takes as input a number and generates a prime greater than or equal to the number. num_collisions to be intitialized to 0. All the hash chains should be initialized to NULL. To generate the four coefficients for the hash function you can use the function get_random() which takes as input two values (say, Lower < Upper) and generates a random number between Lower and Upper.
 
 */

Hash_Table init_hash_table(int size){
	Hash_Table ht;

	ht.num_elements = size;
	ht.prime = next_prime(size); 
	ht.num_collisions = 0;
	ht.ptr_table = (list_node**) (malloc(sizeof(list_node*) * ht.prime));
	for (int i = 0;i< size; i++){
		ht.ptr_table[i] = NULL;
	}
	int LOWER = 0;
	int UPPER = ht.prime - 1;
	for (int i=0; i< 4;i++){
		ht.ptr_coeffs[i] = get_random(LOWER,UPPER);
	}
	
	return ht;
}


/*

hash_chain_insert: Insert a given list of data items into a given hash table with chaining.
		Input: i) num_data_items - number of data items to be inserted.
		       ii) ptr_data - list of data items to be inserted
		       iii) ptr_ht - pointer to the OA_Hash_Table hash table data structure.

		       
		Output: Updata the hash table pointed by ptr_ht appropriately.       
*/



int hash_chain_insert(int num_data_items, unsigned int* ptr_data, Hash_Table* ptr_ht){
	
	for (int i = 0;i< num_data_items;i++){
		unsigned int num=ptr_data[i];
		// getting the value of position
		int pos = 0,pow_var = 24;
		for (int j = 0;j<4;j++){
			int val = num / (int)pow(2,pow_var);
			num = num % (int)pow(2,pow_var);
			pow_var -=8;
			pos += val * ptr_ht->ptr_coeffs[j];
		}
		pos %= (int) ptr_ht->prime;
		num=ptr_data[i];
		list_node* head = ptr_ht->ptr_table[pos];
		if(head != NULL){
			ptr_ht->num_collisions ++;
		}
		list_node* newNode = create_node(num);
		newNode->ptr_next = head;
		ptr_ht->ptr_table[pos] = newNode;

	}
		

	return 0;
	
}

/****************************** Task 2(b) **************************************************************/

/*hash_chain_search: Search the hash table (with chaining) for a given list of data items.
		Input: i) data_size - number of data items to be searched.
		       ii) ptr_data - list of data items to be searched.
		       iii) ptr_flag - An array of flags indicating whether a data item has been found in the table. If ptr_data[i] is found in the hash table then ptr_flag[i] should be set to 1.
		       		All the flags are set to 0 in the input.
		       		
		       iv) ptr_ht - pointer to the OA_Hash_Table hash table data structure.

		Output: Update the ptr_flag array appropriately. */     


int hash_chain_search( Hash_Table* ptr_ht, int data_size, unsigned int* ptr_data, int* ptr_flag){
	// print_hash_table(*ptr_ht);

	for (int i = 0;i< data_size;i++){
		unsigned int num=ptr_data[i];
		// getting the value of position
		int pos = 0,pow_var = 24;
		for (int j = 0;j<4;j++){
			int val = num / (int)pow(2,pow_var);
			num = num % (int)pow(2,pow_var);
			pow_var -=8;
			pos += val * ptr_ht->ptr_coeffs[j];
		}
		pos %= (int) ptr_ht->prime;
		list_node* head = ptr_ht->ptr_table[pos];
		num=ptr_data[i];
		while (head != NULL){
			if(head->data == num){
				ptr_flag[i] = 1;
				break;
			}
			head = head->ptr_next;
		}

	}
	
		
	return 0;
}
/* hash_chain_delete: Delete a given list of data items from the hash table with chaining.
		Input: i) data_size - number of data items to be deleted.
		       ii) ptr_data - list of data items to be deleted.
		       iii) ptr_flag - An array of flags indicating whether a data item has been found and deleted from the table. If ptr_data[i] is found and deleted from the hash table then 					ptr_flag[i] should be set to 1. All the flags are set to 0 in the input.
		       iv) ptr_ht - pointer to the Hash_Table hash table data structure.
		       
		       
		Output: If a given data item is found in the table then it should be deleted. Update the ptr_flag array appropriately. */  
int hash_chain_delete(Hash_Table* ptr_ht, int data_size, unsigned int* ptr_data, int* ptr_flag){
	

	for (int i = 0;i< data_size;i++){
		unsigned int num=ptr_data[i];
		// getting the value of position
		int pos = 0,pow_var = 24;
		for (int j = 0;j<4;j++){
			int val = num / (int)pow(2,pow_var);
			num = num % (int)pow(2,pow_var);
			pow_var -=8;
			pos += val * ptr_ht->ptr_coeffs[j];
		}
		pos %= (int) ptr_ht->prime;
		num=ptr_data[i];
		list_node* head = ptr_ht->ptr_table[pos];
		list_node* prev = NULL;
		while (head != NULL){
			if(head->data == num){
				ptr_flag[i] = 1;
				break;
			}
			head = head->ptr_next;
		}
		// deleting the node
		if (head != NULL){
			if (prev != NULL){
				prev->ptr_next = head->ptr_next;
			}else{
				ptr_ht->ptr_table[pos] = head->ptr_next;
			}
			free(head);
		}
	}
	// print_hash_table(*ptr_ht);

	return 0;
}



/************************** Task 2(c) *****************************************************************/

/*

hash_chain_resize_insert: Insert a given list of data items into a given hash table with chaining. The table should be resized if the number of data items in the table crosses half the size of the 				   table
		Input: i) num_data_items - number of data items to be inserted.
		       ii) ptr_data - list of data items to be inserted
		       iii) ptr_oaht - pointer to the OA_Hash_Table hash table data structure.
		       iv) probe_seq - identifier for a particular probe sequence. We will use any one from the list given in the class notes.
		       
		Output: Final hash table.       
*/

Hash_Table hash_chain_resize_insert(int num_data_items, unsigned int* ptr_data, Hash_Table* ptr_ht){
	
	Hash_Table ht;
	if (ptr_ht->num_elements <= num_data_items){
		ht = init_hash_table(ptr_ht->num_elements * 2);
		ptr_ht = &ht;
		
	}

	for (int i = 0;i< num_data_items;i++){
		unsigned int num=ptr_data[i];
		// getting the value of position
		int pos = 0,pow_var = 24;
		for (int i = 0;i<4;i++){
			int val = num / (int)pow(2,pow_var);
			num = num % (int)pow(2,pow_var);
			pow_var -=8;
			pos += val * ht.ptr_coeffs[i];
		}
		pos %= (int) ht.prime;
		num=ptr_data[i];
		list_node* head = ht.ptr_table[pos];
		list_node* newNode = create_node(num);
		newNode->ptr_next = head;
		ht.ptr_table[pos] = newNode;

	}

	return ht;
	

}




/**************************************************** Section 3: Testing Functions ***********************************************************/

/************ Data structure for test data *************************************************************/
typedef struct{
	int ins_set_size;
	int del_set_size;
	int search_set_size;
	unsigned int* ptr_insert_data;
	unsigned int* ptr_delete_data;
	unsigned int* ptr_search_data;
	
	int* ptr_delete_pattern;
	int* ptr_search_pattern;
} Test_Data;

Test_Data generate_data(int ins_set_size, int block_size, int test_block_num)
{
	Test_Data td;
	int i,j, p, t;
	
	td.ins_set_size = ins_set_size;

	
	td.ptr_insert_data = (unsigned int*) malloc (ins_set_size* sizeof(unsigned int));
	td.ptr_delete_data = (unsigned int*) malloc (((block_size+2)*test_block_num)* sizeof(unsigned int));
	td.ptr_search_data = (unsigned int*) malloc (((block_size+2)*test_block_num)* sizeof(unsigned int));
	td.ptr_delete_pattern = (int*) malloc (((block_size+2)*test_block_num)* sizeof(int));
	td.ptr_search_pattern = (int*) malloc (((block_size+2)*test_block_num)* sizeof(int));
	
	srand(time(NULL));
	
	for (i = 0; i < ins_set_size; i++){
		td.ptr_insert_data[i] = get_big_random();
	}
	
	for (i =0; i< test_block_num; i++){
		for(j=0; j < block_size-2; j++){ 
			td.ptr_delete_data[i*block_size+j] = td.ptr_insert_data[i*block_size+j];
			td.ptr_delete_pattern[i*block_size+j] = 1;			
		}
		
		td.ptr_delete_data[i*block_size+j] = td.ptr_delete_data[i*block_size+j - 3];
		td.ptr_delete_pattern[i*block_size+j]=0;
		
		td.ptr_delete_data[i*block_size+j+1] = td.ptr_delete_data[i*block_size+j-2];
		td.ptr_delete_pattern[i*block_size+j+1]=0;	
	}
	td.del_set_size = test_block_num* block_size;
	
	
	
	
	for (i =0; i< test_block_num; i++){
		for(j=0; j < block_size-2; j++){ 
			td.ptr_search_data[i*block_size+j] = td.ptr_insert_data[td.del_set_size+i*block_size+j];
			td.ptr_search_pattern[i*block_size+j] = 1;
			
		}
		td.ptr_search_data[i*block_size+j] = td.ptr_search_data[i*block_size+j-4]+1;
		
		td.ptr_search_pattern[i*block_size+j]=0;
	
		td.ptr_search_data[i*block_size+j+1] = td.ptr_search_data[i*block_size+j-2]+1;
		td.ptr_search_pattern[i*block_size+j+1]=0;	
	}
	
	td.search_set_size = test_block_num* block_size;
	
	return td;
	
}


/**************************** Tests for Task 1 ****************************************************/




int test_hash_oa_insert (OA_Hash_Table* ptr_oaht, int data_size, unsigned int* ptr_data, int probe_seq){

	clock_t start, end;

	start = clock();
        hash_oa_insert(data_size, ptr_data, ptr_oaht, probe_seq);
        end = clock();

        printf ("Total cpu cycles used %f\n",(double)(end - start));
        printf("Average cpu cycles per data item = %f\n",((double)(end - start)/ data_size));
        printf ("No. of collisions = %d\n", ptr_oaht-> num_collisions);
        printf("Average no. of collisions = %f\n",((double)ptr_oaht-> num_collisions/ data_size));
      
	return 0;
	
}


int test_hash_oa_search(OA_Hash_Table* ptr_oaht, int data_size, unsigned int* ptr_data, int * ptr_input_flag, int probe_seq){
	
	int i;
	bool bflag = false;
	clock_t start, end;
	int * ptr_flag = (int *) calloc (data_size, sizeof(int));
	
	start = clock();
	hash_oa_search(data_size, ptr_data, ptr_oaht, ptr_flag, probe_seq);
	end = clock();
	for (i = 0; i< data_size; i++){
		if (ptr_flag[i] != ptr_input_flag[i]){
			bflag = true;
			break;
		}
	}
	
	if (bflag == true){
		printf("Search failed for index %d,data : %u, %d : %d\n", i,ptr_data[i],ptr_input_flag[i],ptr_flag[i]);
		for(int j =0;j< ptr_oaht->num_data;j++){
			printf("%d:%d, ",j,ptr_oaht->ptr_table[j]);
		}
		printf("\n");
	} else {
		 printf ("Total cpu cycles used %f\n",(double)(end - start));
        	  printf("Average cpu cycles per data item = %f\n",((double)(end - start)/ data_size));
		
	}
	
	return 0;
	
}


int test_hash_oa_delete(OA_Hash_Table* ptr_oaht, int data_size, unsigned int* ptr_data, int * ptr_input_flag, int probe_seq){
	int i;
	bool bflag = false;
	clock_t start, end;
	int * ptr_flag = (int *) calloc (data_size, sizeof(int));
	
	start = clock();
	hash_oa_delete(data_size, ptr_data, ptr_oaht, ptr_flag, probe_seq);
	end = clock();
	for (i = 0; i< data_size; i++){
		if (ptr_flag[i] != ptr_input_flag[i]){
			bflag = true;
			break;
		}
	}
	
	if (bflag == true){
		printf("Deletion failed for index %d\n", i);
	} else {
		 printf ("Total cpu cycles used %f\n",(double)(end - start));
        	  printf("Average cpu cycles per data item = %f\n",((double)(end - start)/ data_size));
		
	}
	
	return 0;
	
}

int hash_oa_search2(int num_data_items, unsigned int* ptr_data, OA_Hash_Table* ptr_oaht, int* ptr_flag, int probe_seq){

	int i, j, hash, init_hash;
	
	for (i =0; i< num_data_items; i++){
	
		init_hash = ptr_data[i] % ptr_oaht->prime;
	
		for (j = 0; j < ptr_oaht->prime; j++){
			hash = (init_hash+j) % ptr_oaht->prime;
			if (ptr_oaht->ptr_table[hash] == ptr_data[i]){
			
				ptr_flag[i] = 1;
			
			} 
		}

	}
	return 0;
}





int test_hash_oa_search2(OA_Hash_Table* ptr_oaht, int data_size, unsigned int* ptr_data, int * ptr_input_flag, int probe_seq){
	
	int i;
	bool bflag = false;
	clock_t start, end;
	int * ptr_flag = (int *) calloc (data_size, sizeof(int));
	
	start = clock();
	hash_oa_search2(data_size, ptr_data, ptr_oaht, ptr_flag, probe_seq);
	end = clock();
	for (i = 0; i< data_size; i++){
		if (ptr_flag[i] != ptr_input_flag[i]){
			bflag = true;
			break;
		}
	}
	
	if (bflag == true){
		printf("Search test failed for insert\n");
	} else {
		 
		printf("Search test passed for insert\n");
		
	}
	
	return 0;
	
}


/**************************** Tests for Task 2 ***************************************************/

int test_hash_chain_insert (Hash_Table* ptr_ht, int data_size, unsigned int* ptr_data){

	clock_t start, end;

	start = clock();
        hash_chain_insert(data_size, ptr_data, ptr_ht);
        end = clock();

        printf ("Total cpu cycles used %f\n",(double)(end - start));
        printf("Average cpu cycles per data item = %f\n",((double)(end - start)/ data_size));
        printf ("No. of collisions = %d\n", ptr_ht-> num_collisions);
        printf("Average no. of collisions = %f\n",((double)ptr_ht-> num_collisions/ data_size));
      
	return 0;
	
}

int test_hash_chain_search(Hash_Table* ptr_ht, int data_size, unsigned int* ptr_data, int * ptr_input_flag){
	
	int i;
	bool bflag = false;
	clock_t start, end;
	int * ptr_flag = (int *) calloc (data_size, sizeof(int));
	
	start = clock();
	hash_chain_search(ptr_ht, data_size, ptr_data, ptr_flag);
	end = clock();
	for (i = 0; i< data_size; i++){
		if (ptr_flag[i] != ptr_input_flag[i]){
			bflag = true;
			break;
		}
	}
	
	if (bflag == true){
		printf("Search failed for index %d\n", i);
	} else {
		 printf ("Total cpu cycles used %f\n",(double)(end - start));
        	  printf("Average cpu cycles per data item = %f\n",((double)(end - start)/ data_size));
		
	}
	
	return 0;
	
}

int test_hash_chain_delete(Hash_Table* ptr_ht, int data_size, unsigned int* ptr_data, int * ptr_input_flag){
	int i;
	bool bflag = false;
	clock_t start, end;
	int * ptr_flag = (int *) calloc (data_size, sizeof(int));
	
	start = clock();
	hash_chain_delete(ptr_ht, data_size, ptr_data, ptr_flag);
	end = clock();
	for (i = 0; i< data_size; i++){
		if (ptr_flag[i] != ptr_input_flag[i]){
			bflag = true;
			break;
		}
	}
	
	if (bflag == true){
		printf("Deletion failed for index %d, %u %d\n", i,ptr_data[i],ptr_flag[i]);
	} else {
		 printf ("Total cpu cycles used %f\n",(double)(end - start));
        	  printf("Average cpu cycles per data item = %f\n",((double)(end - start)/ data_size));
		
	}
	
	return 0;
	
}


Hash_Table test_hash_chain_resize_insert (Hash_Table* ptr_ht, int data_size, unsigned int* ptr_data){

	clock_t start, end;
	Hash_Table ht;

	start = clock();
        ht  = hash_chain_resize_insert(data_size, ptr_data, ptr_ht);
        end = clock();

        printf ("Total cpu cycles used %f\n",(double)(end - start));
        printf("Average cpu cycles per data item = %f\n",((double)(end - start)/ data_size));
        printf ("No. of collisions = %d\n", ptr_ht-> num_collisions);
        printf("Average no. of collisions = %f\n",((double) ht.num_collisions/ data_size));
        
        printf("\n\n");
      
	return ht;
	
}


int hash_chain_search2( Hash_Table* ptr_ht, int data_size, unsigned int* ptr_data, int* ptr_flag){


	int i, j, hash;
	list_node* ptr_temp;
	for (i =0; i< data_size; i++){
		hash = 0;
		

		for (j = 0; j < 4; j++){
			hash += ((ptr_data[i]>> (8*j)) & 0xff)*ptr_ht->ptr_coeffs[j];
		}
		
		hash = hash % ptr_ht->prime;

		ptr_temp = ptr_ht->ptr_table[hash];
		while(ptr_temp!= NULL){
			if (ptr_temp->data == ptr_data[i]){
				ptr_flag[i] = 1;
				break;
			}
			ptr_temp = ptr_temp->ptr_next;
		}
			
	}
		
	return 0;
}

int test_hash_chain_search2(Hash_Table* ptr_ht, int data_size, unsigned int* ptr_data, int * ptr_input_flag){
	
	int i;
	bool bflag = false;
	clock_t start, end;
	Hash_Table ht;
	int * ptr_flag = (int *) calloc (data_size, sizeof(int));
	
	start = clock();
	hash_chain_search(ptr_ht, data_size, ptr_data, ptr_flag);
	end = clock();
	for (i = 0; i< data_size; i++){
		if (ptr_flag[i] != ptr_input_flag[i]){
			bflag = true;
			break;
		}
	}
	
	if (bflag == true){
		printf("Search test failed for insert index %d, %u :%p\n", i,ptr_data[i],ptr_ht->ptr_table[i]);
	} else {
		 
		printf("Search test passed for insert\n");
	}
	
	return 0;
	
}

int print_hash_table(Hash_Table ht){
	int i;
	list_node* ptr_temp;
	printf ("Printing the hash table \n\n");
	for (i = 0; i< ht.prime; i++){
		printf("Row %d =", i);
		if (ht.ptr_table[i] != NULL){
			ptr_temp = ht.ptr_table[i];
			while (ptr_temp != NULL){
				printf ("%u,", ptr_temp->data);
				ptr_temp = ptr_temp->ptr_next;
				
			}
			
		}
		printf ("\n");
	}
}


/***************************************************************************************Main Function**********************************************************************************/
int main(){


	int i, j;
	Test_Data td1;
	Hash_Table ht1, ht2;
	OA_Hash_Table oaht1;
	int num_data = 60;
	int del_set_block_size = 7;
	int del_set_num_blocks = 4 ;


/**************** Test Task 1*****************************************************************************/

// ********** Task 1(a) ***************

	printf("Testing Task 1(a)...\n");
	for (i = 1; i<=6; i++){
	
		printf ("*******************************************\n");
		printf ("Inserting %d data items \n", i*num_data);

		td1 = generate_data(i*num_data, del_set_block_size, del_set_num_blocks);
		oaht1 = init_hash_oa_table(i*num_data);
		test_hash_oa_insert(&oaht1, td1.ins_set_size, td1.ptr_insert_data,0);
		printf("\n\n");
		printf ("Testing insert through search\n");
		test_hash_oa_search2(&oaht1, td1.search_set_size, td1.ptr_search_data,td1.ptr_search_pattern,0);
		printf ("\n\n\n");
	}

// /************** Task 1(b) ***************/

	printf ("Testing Task 1(b)...\n");
	
	for (i = 1; i<=6; i++){
	
		printf ("*******************************************\n");
		printf ("Inserting %d data items \n", i*num_data);

		td1 = generate_data(i*num_data, del_set_block_size, del_set_num_blocks);
		oaht1 = init_hash_oa_table(i*num_data);
              hash_oa_insert(td1.ins_set_size, td1.ptr_insert_data, &oaht1, 0);
		printf("\n\n");
		printf ("Testing search...\n");
		test_hash_oa_search(&oaht1, td1.search_set_size, td1.ptr_search_data,td1.ptr_search_pattern,0);
		
		printf("\n\n");
		
		printf("Testing delete ....\n");
		test_hash_oa_delete(&oaht1, td1.del_set_size, td1.ptr_delete_data, td1.ptr_delete_pattern,0);
		printf ("\n\n");
	}
	
// **************** Test Task ********************************************************************************/	

/**************** Task 2(a) *********************/
	
	printf ("Testing Task 2(a)...\n");		
	
	for (i = 1; i<=5; i++){
		
		printf ("*******************************************\n");
		printf ("Testing for data size = %d\n", i*num_data);
	
		td1 = generate_data(i*num_data, del_set_block_size, del_set_num_blocks);
		ht1 = init_hash_table(i*num_data);
		test_hash_chain_insert(&ht1, td1.ins_set_size, td1.ptr_insert_data);
		printf ("\n\n");
		printf ("Testing insert by searching ...\n");
		test_hash_chain_search2(&ht1, td1.search_set_size, td1.ptr_search_data, td1.ptr_search_pattern);
		printf ("\n\n");
	}
/*	*/

/**************** Task 2(b) *********************/

	printf ("Testing Task 2(b)...\n");
			
	for (i = 1; i<=6; i++){
		
		printf ("*******************************************\n");
		printf ("Testing for data size = %d\n", i*num_data);
	
		td1 = generate_data(i*num_data, del_set_block_size, del_set_num_blocks);
		ht1 = init_hash_table(i*num_data);
		hash_chain_insert(td1.ins_set_size, td1.ptr_insert_data, &ht1);
		printf("\n\n\n");
		printf("Testing search ....\n");
		test_hash_chain_search(&ht1, td1.search_set_size, td1.ptr_search_data, td1.ptr_search_pattern);
		
		printf("\n\n\n");
		printf("Testing delete ....\n");
		test_hash_chain_delete(&ht1, td1.del_set_size, td1.ptr_delete_data, td1.ptr_delete_pattern);
		
		printf ("\n\n\n");
	}


/**************** Task 2(c) ************************/
	printf ("Testing Task 2(c)...\n");
	for (i = 1; i<=6; i++){
		
		printf ("*******************************************\n");
		printf ("Testing for data size = %d\n", i*num_data);
	
		td1 = generate_data(i*num_data, del_set_block_size, del_set_num_blocks);
		ht1 = init_hash_table(20);
		ht2=test_hash_chain_resize_insert(&ht1, td1.ins_set_size, td1.ptr_insert_data);
		printf ("\n\n");
		printf ("Printing the hash table...\n");
		print_hash_table(ht2);
		
		printf ("Testing insert by searching ...\n");
		test_hash_chain_search2(&ht2, td1.search_set_size, td1.ptr_search_data, td1.ptr_search_pattern);
		printf("\n\n\n");
		

	}
	
	return 0;
	
}
	

	
	
