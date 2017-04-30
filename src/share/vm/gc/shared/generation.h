//
// Created by tzhou on 4/24/17.
//

#ifndef MINISPOT_GENERATION_H
#define MINISPOT_GENERATION_H


// A Generation models a heap area for similarly-aged objects.
// It will contain one ore more spaces holding the actual objects.
//
// The Generation class hierarchy:
//
// Generation                      - abstract base class
// - DefNewGeneration              - allocation area (copy collected)
//   - ParNewGeneration            - a DefNewGeneration that is collected by
//                                   several threads
// - CardGeneration                 - abstract class adding offset array behavior
//   - TenuredGeneration             - tenured (old object) space (markSweepCompact)
//   - ConcurrentMarkSweepGeneration - Mostly Concurrent Mark Sweep Generation
//                                       (Detlefs-Printezis refinement of
//                                       Boehm-Demers-Schenker)
//
// The system configurations currently allowed are:
//
//   DefNewGeneration + TenuredGeneration
//
//   ParNewGeneration + ConcurrentMarkSweepGeneration
//


#include <memory/memRegion.h>

class Generation {
    MemRegion _reserved;
public:
//    // Space enquiries (results in bytes)
//    virtual size_t capacity() const = 0;  // The maximum number of object bytes the
//    // generation can currently hold.                                                                                                                                            virtual size_t used() const = 0;      // The number of used bytes in the gen.
//    virtual size_t free() const = 0;      // The number of free bytes in the gen.

};

#endif //MINISPOT_GENERATION_H
