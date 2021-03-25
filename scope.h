#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Record {
typedef unsigned long long hrtime;

__inline__ unsigned long long gethrtime(void)
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

public:
    string name;
    hrtime start_timestamp;
    hrtime end_timestamp;
    static int internal_level;
    Record(string _name) {
        name = _name;
        start_timestamp = gethrtime();
        internal_level++;
        for (int i=0; i<internal_level; i++) {
            cout <<"--";
        }
        cout << "Begin scope "<< name << endl;
    }
    ~Record() {
        end_timestamp = gethrtime();
        for (int i=0; i<internal_level; i++) {
          cout <<"--";
        }
        cout << "The time taken in scope " << name << " is " << end_timestamp - start_timestamp << endl;
        internal_level--;
    }
private:
    Record() {}

};

int Record::internal_level = 0;


#define PROF_SCOPE(number, name) Record r##number(name)

