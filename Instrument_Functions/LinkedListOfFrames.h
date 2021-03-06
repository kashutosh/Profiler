#include "Trace.h"
#include <string>

namespace FlightRecorder {
void initializeLinkedLists() __attribute__((no_instrument_function));
bool appendNodeToTailOfAList(FrameInformation *node, int index) __attribute__((no_instrument_function));
FrameInformation *getFrame(int index) __attribute__((no_instrument_function));
FrameInformation *getTail(int index) __attribute__((no_instrument_function));
bool printTheListsOutToAFile() __attribute__((no_instrument_function));
void cleanupLinkedLists() __attribute__((no_instrument_function));
bool aggregateStacks() __attribute__((no_instrument_function));

std::string getFunctionName(void *addr) __attribute__((no_instrument_function));
}
