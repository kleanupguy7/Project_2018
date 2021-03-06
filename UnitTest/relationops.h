#ifndef __RELATIONOPS_H__
#define __RELATIONOPS_H__

#include "parser.h"
#include "relation_loader.h"
#include "results.h"
#include "thread_scheduler.h"

typedef struct tempResultArray{
	std::vector<uint64_t *> rowID;
	std::vector<int> relationID;														// IDs of relations in tempResultArray
	uint64_t size;																		// Number of rowids in each vector element
}tempResultArray;

typedef struct tempResults{
	std::vector<tempResultArray> res;
}tempResults;


tempResults *queryExecute(Query *, relationArray *,threadpool* );

void queryReorder(Query *);																// Reorders predicates in a query

void filtered_relation(predicates* ,relationArray* );
uint64_t *createRowID(uint64_t);
void deleteTR(tempResults** );
void relation_join(predicates *, relationArray *, tempResults *);
uint64_t *tempResultsLookup(tempResults *,int, uint64_t *);
uint64_t getChecksum(tempResultArray* ,relationArray* ,std::vector<checksum_views*> );

int tempResultsFilterUpdate(std::vector<uint64_t> &,int,tempResults *);
int tempResultsAdd(std::vector<uint64_t> &,int,tempResults *);
inline uint64_t **convert_to_arrays(result *,uint64_t &ts);
inline uint64_t* conjure_payload(uint64_t* ,uint64_t* ,uint64_t );
inline uint64_t* createRowID(uint64_t );

void jointest(void);
void fringeCase(relationArray *, tempResults *, int, int, int ,int);
Query *editQuery(Query *);

relationArray *createTempRelArray(relationArray *, Query *);

void tempResultsJoinUpdate2(result *, tempResults *, int relID1, int relID2);



// Debug stuff

void printJoinResults(uint64_t **, relationArray *, int, int, int);
void queryPrint(Query *);
void printTPR(tempResults *, relationArray *);

#endif