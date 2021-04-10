#ifndef FUNCTIONTRACER_H
#define FUNCTIONTRACER_H

class FunctionTracer {
private:
    FunctionTracer();
    FunctionTracer(FunctionTracer &);
    FunctionTracer &operator = (FunctionTracer &);
public:
    static FILE *fp;
    static bool initializeTracer(float clock_speed_=2.0);
    static bool stopTracer();
    static int id;
    static float clock_speed;
};

#endif
