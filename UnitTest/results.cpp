#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "results.h"
#include <gtest/gtest.h>

using namespace std;




/*
*	Iterates through column of non Indexed Array nonIndexed for matches on
*	Indexed Array T.
*	Results are stored in a tuple with tuple.key being the nonIndexed columns Id
*	and tuple.payload being the Indexed columns Id
*/

result** getResults(Table_Info *T,Table_Info* nonIndexed,daIndex **Index,threadpool* tp,int flag){

	int jobs = 1<<N;

	result *r = new result;

	if(r == NULL){
		fprintf(stderr,"Error allocating space for result struct \n");
		exit(0);
	}


	uint64_t counter = 0;

	uint64_t mask = (1 << N) - 1;

	rlist** partials = new rlist*[jobs];
	for(int i = 0 ; i < jobs ; i++)
	{
		partials[i] = new rlist;
	}

	joinArg** args = new joinArg*[jobs];


	for(int i = 0 ; i < jobs ; i++){
		args[i] = new joinArg;

		args[i]->indexed = T;
		args[i]->nonIndexed= nonIndexed;
		args[i]->Index = Index;
		args[i]->partials=partials[i];
		args[i]->bucket = i;
		args[i]->flag = flag;
		add_work(tp->Q,&joinJob,args[i]);
	}


	thread_wait();

	for(int i = 0 ; i < jobs ; i++){
		delete args[i];
	}

	delete[] args;

	rlist* temp;
	for(int i = 0 ; i < jobs ; i++){
		while(partials[i] != NULL){
			for(int j = 0 ; j < partials[i]->size ;j++){
				toumble* temp = new toumble;
				temp->key = partials[i]->ts[j].key;
				temp->payload = partials[i]->ts[j].payload;
				temp->rids = partials[i]->ts[j].rids;
				r->results_array.push_back(temp);
			}
			temp = partials[i];
			partials[i] = partials[i]->next;
			delete[] temp->ts;
			delete temp;
		}
	}

	delete[] partials;



	result** rets = new result*[1];
	rets[0] = r;

	return rets;
}

/*
*	Prints the results kinda prettily
*
*/

void print_results(result* r){


	printf("\n");
	printf("|	Table A Row Id  	|	Table B Row Id 		|\n");

	for(int i = 0 ; i < r->results_array.size() ; i++ ){

			std::cout << "|	 	"<< r->results_array.at(i)->key <<"		|	 	"<< r->results_array.at(i)->payload << "		|\n";

	}
	printf("\n");
}



void destroy_results(result** r)
{

	for(std::vector<toumble*>::iterator it = (*r)->results_array.begin(); it != (*r)->results_array.end(); it++)
	{
		if((*it) != NULL)
		{
			if((*it)->rids != NULL)
			{
				delete[] (*it)->rids;
			}
			delete (*it);
		}
	}


	vector<toumble*>().swap((*r)->results_array);
	delete (*r);

}