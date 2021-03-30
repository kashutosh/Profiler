#include "Profilers.h"
using namespace std;

Profilers::Profilers() 
{
}

ObjectStorage *Profilers::getProfiler(string profilername) {
    for (vector<ObjectStorage*>::iterator itprofs = profilers.begin();
         itprofs != profilers.end();
         itprofs++) {
         ObjectStorage *os = *itprofs;
         if (os->getProfilerName() == profilername) {
             return os;
         }
    }
    // No profiler with this name is found
    // Create one and push it to vector
    ObjectStorage *os = new ObjectStorage();
    os->setProfilerName(profilername);
    profilers.push_back(os);
    return os;
}

bool Profilers::deleteProfiler(string profilername) {
    for (vector<ObjectStorage*>::iterator itprofs = profilers.begin();
         itprofs != profilers.end();
         itprofs++) {
         ObjectStorage *os = *itprofs;
         if (os->getProfilerName() == profilername) {
             os->emptyObjectStorage();
             // remove element from vector
             delete os;
             profilers.erase(itprofs, itprofs + 1);
         }
    }
    return true;
}

bool Profilers::doesAProfilerWithThisNameExist(string profilername) {
    for (vector<ObjectStorage*>::iterator itprofs = profilers.begin();
         itprofs != profilers.end();
         itprofs++) {
         ObjectStorage *os = *itprofs;
         if (os->getProfilerName() == profilername) {
             return true;
         }
    }
    return false;
}

bool Profilers::clearAllProfilers() {
    return true;
}

Profilers::~Profilers() {
    cout << "Profilers destructor is called " << endl;
}

