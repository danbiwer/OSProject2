#include <iostream>
#include <deque>
#include <random>
#include <algorithm>
#include <time.h>

static const unsigned int MAXMEMSIZE = 10*1000*1000;//10 MB
struct process{
	unsigned int pid;//process id
	unsigned int numcycles;
	unsigned int origCycles;//original number of cycles
	unsigned int memory;
};

struct results{//holds the elapsed time for each test and the wait time for each process
	results();
	unsigned int elapsedTime;
	int waitTime[50];
};

struct processhandler{
	unsigned int currentPID;
	unsigned int maxCycles;
	unsigned int maxMem;
	unsigned int totalCycles;
	//unsigned int totalMem[1000];g
	int * totalMemory;
	std::deque<process> processes;//waiting queue for processes
	processhandler(unsigned int memSize);
	~processhandler();
	void addProcess(unsigned int n, unsigned int mem);
	void printProcesses();
	void printAverage();
	process *findMin();
};

struct memHandler{
	char *memory;//total memory
	unsigned int totalMemSize;
	unsigned int current;//current position to start search for memory, for next best fit
	std::deque<process> waitList;
	memHandler(unsigned int memSize);
	int get_mem_proc(unsigned int pid);
	bool new_malloc(process p);
	void new_free(unsigned int pid);
	void printMem();
};
struct ps{
	int testcycles1[50];//mean 6000, SD 1000
	int testcycles2[50];//mean 6000, SD 4000
	int testcycles3[50];//mean 3000, SD 6000
	int testcycles4[50];//constant values 3000
	int mempattern[50];//sum is <= 10mb
	int testMemory[50];
	ps();
	results runFIFO(int *tcycles, int *tmem, unsigned int total_mem, int numProcessors);//4 processors
	results runFIFOsystem(int *tcycles, int *mempattern, int numProcessors);//uses system malloc/free
	void testFIFO(int *testcycles);
	void test();
	void printResults(int *testcycles, results R);
};

void genNums(int *arr, int mean, int deviation);//generate array of 50 random numbers using normal distribution
void genMem(int *arr, unsigned int maxSize);
