//
// Created by GentlyGuitar on 4/21/2017.
//

#ifndef MINISPOT_DEBUG_H
#define MINISPOT_DEBUG_H

#define ASSERT

// assertions
#include <cstddef>


/* @comment
 * Macro trick: use do {} while (false) to turn a block into a single statement to avoid the ending semicolon issue.
 */
#ifdef ASSERT
#define assert(condition, args...) \
    do { \
        if (! (condition)) { \
            fprintf(stderr, "Assertion `" #condition "` failed in %s line %d: ", __FILE__, __LINE__); \
            fprintf(stderr, ##args); \
            fprintf(stderr, "\n"); \
            std::terminate(); \
        } \
    } while (false)
#else
#define assert(condition, message) do { } while (false)
#endif
//#ifdef ASSERT
//    #define assert(condition, message) \
//    do { \
//        if (! (condition)) { \
//            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
//                      << " line " << __LINE__ << ": " << message << std::endl; \
//            std::terminate(); \
//        } \
//    } while (false)
//#else
//    #define assert(condition, message) do { } while (false)
//#endif


#define guarantee(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Guarantee `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)




#define ZPP(fmt, args...) \
  std::printf(fmt, ##args);

#define ZPPL(fmt, args...) \
  std::printf(fmt, ##args); \
  std::printf("\n");





#endif //MINISPOT_DEBUG_H
