#ifndef FUNCTIONTRACER_H
#define FUNCTIONTRACER_H

class FunctionTracer {
private:
    // Hide constructors
    FunctionTracer();
    FunctionTracer(FunctionTracer &);
    FunctionTracer &operator = (FunctionTracer &);
public:
    static FILE *fp;

    // Only two functions should be visible from outside
    static bool initializeTracer(float clock_speed_=2.0, void *caller_ptr=0);
    static bool stopTracer(void *caller_ptr);


    static int id;
    static float clock_speed;
};

#endif
