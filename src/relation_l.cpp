#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../header/relation_loader.h"


using namespace std;


relationArray* init_relations()
{
	string line;
	relationArray *R = new relationArray;
	   		cout << "Enter file path" << endl;
   	while (getline(cin, line)) {
      if (line == "Done" || line == "DONE" || line == "done") break;
      R->relations.push_back(load_relations(line.c_str()));
   	}

   	return R;
}

Relations* load_relations(const char* fileName)
{	

	Relations *R = new Relations;

	int fd = open(fileName, O_RDONLY);
	if (fd==-1) {
	cerr << "cannot open " << fileName << endl;
	throw;
	}

	// Obtain file size
	struct stat sb;
	if (fstat(fd,&sb)==-1)
	cerr << "fstat\n";

	auto length=sb.st_size;
	char* tempadr;
	char* addr=static_cast<char*>(mmap(nullptr,length,PROT_READ,MAP_PRIVATE,fd,0u));
	tempadr = addr;
	if (addr==MAP_FAILED) {
	cerr << "cannot mmap " << fileName << " of length " << length << endl;
	throw;
	}

	if (length<16) {
	cerr << "relation file " << fileName << " does not contain a valid header" << endl;
	throw;
	}

	R->size=*reinterpret_cast<uint64_t*>(addr);
	addr+=sizeof(R->size);
	R->numColumns=*reinterpret_cast<int*>(addr);
	addr+=sizeof(size_t);

	R->relation = new uint64_t*[R->numColumns];

	for(int i = 0 ; i < R->numColumns ; i ++){
		R->relation[i] = new uint64_t[R->size];
	}

	for (unsigned i=0;i<R->numColumns;++i) {
		for(unsigned j = 0 ; j < R->size ; j++){
			R->relation[i][j] = *((uint64_t*)addr);
			addr+=sizeof(uint64_t);
		}
	}


	munmap(tempadr,length);

	return R;
}