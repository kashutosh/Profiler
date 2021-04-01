#include <stdio.h>
#include <dlfcn.h>
#include <iostream>

#ifdef __cplusplus
using namespace std;
extern "C"
{
    void __cyg_profile_func_enter(void *this_fn, void *call_site)
        __attribute__((no_instrument_function));
    void __cyg_profile_func_exit(void *this_fn, void *call_site)
        __attribute__((no_instrument_function));
}
#endif

class Dummy {
    public:
        int data;
        int array[10];
        int counter;
        Dummy(int data) __attribute__((no_instrument_function)) { this->data = data; this->counter=0;}
        // One can call only such code that does not perform any 
        //    function calls or standard library calls from over here
        // One should be able to maintain a linked list or something like. No issues.
        void print () __attribute__((no_instrument_function)) { 
            counter++;
            if (counter>=9) counter=0;
            printf("Dummy data is %d\n", data); 
            array[counter]= data; 
        }
};

// When we enter the function, this block of code executes
void __cyg_profile_func_enter(void* this_fn, void* call_site)
{
    Dl_info info;
    printf("entering %p @@", (void*)(int*)this_fn);
    if (dladdr(this_fn, &info)) {
        printf("[%s] ",info.dli_sname ? info.dli_sname : "?");
        printf("[%s]\n",info.dli_fname ? info.dli_fname : "?");
        Dummy d (10);
        d.print();
    }
}

void __cyg_profile_func_exit(void* this_fn, void* call_site)
{
    Dl_info info;
    printf("exiting %p @@", (void *)(int*)this_fn);
    if (dladdr(this_fn, &info)) {
        printf("[%s] ",info.dli_sname ? info.dli_sname : "?");
        printf("[%s]\n",info.dli_fname ? info.dli_fname : "?");
    }

}

/*
void foo() {
    cout << "foo " << endl;
}

class C {
public:
    C() {
    }
    ~C() {

    }
    void printC() {
        cout << "Printing C " << endl;
    }
};


int main() {
    foo();
    C * c = new C();
    c->printC();
    delete c;
    return 0;
}

*/
