#include <iostream>
#include "Trace.h"
#include <vector>
#include "FunctionTracer.h"
#include <unistd.h>
#include <pthread.h>

using namespace std;
extern int global;
void callout();

void BAZ() {
    cout << "BAZ " << endl;
}

void bar() {
    cout << "bar " << endl;
    BAZ();
    BAZ();
    BAZ();
}

void foo() {
    cout << "foo " << endl;
    bar();
    bar();
    BAZ();
}

class C {
public:
    C() {
    }
    ~C() {

    }
    void internal() { cout << "This is an internal function " << endl; }
    void printC() {

        internal();
        cout << "Printing C " << endl;
        vector<int> v;
        v.push_back(10); 
    }
};


int function91(int arg)
{
    if (arg <0) arg = 0;
    if (arg >100) arg = 100;

    for (int i=0;i<arg; i++) cout << "=";
    cout << ">" << endl;
    return arg;
}

int callbacker(int (*fptr) (int))
{
    return (*fptr) (71);
}

void *Downloader(void *arg)
{
    int counter = 0;
    //int argToThread = *((int *)arg);
    int (*fptr) (int) = arg;
   // cout << "The thread received argument " <<argToThread << endl;
    while (counter!=10)
    {
        counter++;
        // Callback to main thread
        fptr(counter);
        //I do not know which function to call. The caller should have told me about it
        cout << "Counter is " << counter << endl;
        //sleep (0.1);
    }
    pthread_exit(0);
}



int main() {
    // How would somebody detect that initialization happened here?
    FunctionTracer::initializeTracer(2.4, (void*)&main);
    // There is practically no difference in calling 
    // callout (from external file) and foo (from same file)
    // here
    callout();
    foo();
    C * c = new C();
    c->printC();



    pthread_t downloader;
    int argToThread = 83;
    int (*fptr) (int) = function91;

    if (pthread_create(&downloader, NULL, Downloader, (void *)fptr)!=0) {
        cout << "Failed to create Downloader pthread \n";
        return -1;
    }
     
    if (pthread_join(downloader, NULL)!=0) {
        cout << "Failed to join the forked thread Downloader \n";
        return -1;
    }

    delete c;
    FunctionTracer::stopTracer((void*)&main);
    return 0;
}


