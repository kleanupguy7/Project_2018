//#include "unity.h"
//#include "../header/randarr.h"
#include <stdlib.h>
#include <stdio.h>
#include "../header/relation_loader.h"


// void test_empty(void)
// {
// 	int32_t *arr = malloc(sizeof(int32_t)*0);
// 	TEST_ASSERT_EQUAL_INT32_ARRAY(arr, create_column(0,0), 0); 
// }

// void test_one(void)
// {
// 	int32_t arr[1];
// 	arr[0] = 1;
// 	TEST_ASSERT_EQUAL_INT32_ARRAY(arr, create_column(1,1), 1); 
// }

// void test_doc_paths(void)
// {
// 	int totaldocs = 14;
// }

int main(void)
{
	init_relations("filepaths.txt");
}