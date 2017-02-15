#include "sort.h"
#include <algorithm>
#include <map>
#include <sys/time.h>
#include <stdio.h>

//helper function to test sort algorithm.. 
void run(vector <int> input, vector <int> &sorted, string name, void (*func_ptr)(vector <int> &));

int main(int argc, char **argv)
{
    vector <int> input, sorted;
    int num;

    //map or "dictionary" of function pointers keyed on algorithm name
    map <string, void (*)(vector <int> &)> algos;
    map <string, void (*)(vector <int> &)>::iterator it;

    //create a "dictionary" of algorithm names and function pointers
    algos["insertion"] = insertionSort;
    algos["quick"] = quickSort;
    algos["radix"] = radixSort;

    //get input from stdin
    while(cin >> num){
        input.push_back(num);
    }

    //make copy of input and sort using built-in function
    sorted = input;
    sort(sorted.begin(), sorted.end());

    //print out the table header
    printf("%12s %12s %12s %12s\n", "algorithm", "N", "runtime", "test");
    cout << "=====================================================" << endl;

    //go through the "dictionary" of algorithms and test
    for(it = algos.begin(); it != algos.end(); it++){
        run(input, sorted, it->first, it->second);
    }
}

void run(vector <int> v, vector <int> &sorted, string name, void (*func_ptr)(vector <int> &))
{
    double elapsed;
    timeval start, end;

    //time the algorithm with microsecond precision
    gettimeofday(&start, NULL);
    (*func_ptr)(v); //make use of function pointer
    gettimeofday(&end, NULL);
    elapsed = end.tv_sec*1e6 + end.tv_usec - (start.tv_sec*1e6 + start.tv_usec);
    
    //output 
    printf("%12s %12lu %12.2f %14s\n", name.c_str(), (unsigned long) sorted.size(), elapsed, (v == sorted) ? "SORTED" : "NOT SORTED");
}


