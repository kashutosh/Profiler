#ifndef PROFILERS_H
#define PROFILERS_H

#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include "ObjectStorage.h"

using namespace std;

class Profilers{
private:
    vector<ObjectStorage *> profilers;

public:
    Profilers();

    ObjectStorage *getProfiler(string profilername);

    bool deleteProfiler(string profilername);

    bool doesAProfilerWithThisNameExist(string profilername);

    bool clearAllProfilers();

    ~Profilers();


};




#endif
