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

    ObjectStorage *getProfiler(const string profilername);

    bool deleteProfiler(const string profilername);

    bool doesAProfilerWithThisNameExist(const string profilername) const;

    bool clearAllProfilers();

    ~Profilers();


};




#endif
