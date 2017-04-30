//
// Created by tzhou on 4/23/17.
//

#ifndef MINISPOT_COLLECTEDHEAP_H
#define MINISPOT_COLLECTEDHEAP_H


// A "CollectedHeap" is an implementation of a java heap for HotSpot.  This
// is an abstract class: there may be many different kinds of heaps.  This
// class defines the functions that a heap must implement, and contains
// infrastructure common to all heaps.

#include "../../memory/memRegion.h"
#include "../../runtime/handles.h"
#include "../../prims/jni.h"
#include "../../oops/oop.h"
#include "../gcCause.h"


//
// CollectedHeap
//   GenCollectedHeap
//   G1CollectedHeap
//   ParallelScavengeHeap
//
class CollectedHeap {
protected:
    MemRegion _reserved;
    int _alignment;
    int _size; /* size usually means size in words in the VM */

    //BarrierSet* _barrier_set;
    bool _is_gc_active;

    // Reason for current garbage collection.  Should be set to
    // a value reflecting no collection between collections.
    GCCause::Cause _gc_cause;
    GCCause::Cause _gc_lastcause;

    unsigned int _total_collections;          // ... started
    unsigned int _total_full_collections;     // ... started

public:
    CollectedHeap();

    int size()  { return _size; }
    int size_in_words()  { return size(); }
    int size_in_bytes() { return WtoB(size()); }

    /**
    * Returns JNI error code JNI_ENOMEM if memory could not be allocated,
    * and JNI_OK on success.
    */
    virtual jint initialize() = 0;

//    // In many heaps, there will be a need to perform some initialization activities
//    // after the Universe is fully formed, but before general heap allocation is allowed.
//    // This is the correct place to place such initialization methods.
//    virtual void post_initialize();
//
//    // Stop any onging concurrent work and prepare for exit.
//    virtual void stop() {}
//
//
    void initialize_reserved_region(HeapWord *start, HeapWord *end);
    MemRegion reserved_region() const { return _reserved; }
    HeapWord* base() const { return reserved_region().start(); }
//
//    virtual size_t capacity() const = 0;
//
//
//    // Returns "TRUE" if "p" points into the reserved area of the heap.
//    bool is_in_reserved(const void* p) const {
//        return _reserved.contains(p);
//    }
//
//    // Returns "TRUE" iff "p" points into the committed areas of the heap.
//    // This method can be expensive so avoid using it in performance critical
//    // code.
//    virtual bool is_in(const void* p) const = 0;
//
//
//
//    // Do common initializations that must follow instance construction,
//    // for example, those needing virtual calls.
//    // This code could perhaps be moved into initialize() but would
//    // be slightly more awkward because we want the latter to be a
//    // pure virtual.
//    void pre_initialize();
//
//    // Create a new tlab. All TLAB allocations must go through this.
//    virtual HeapWord* allocate_new_tlab(size_t size);
//
//    // Accumulate statistics on all tlabs.
//    virtual void accumulate_statistics_all_tlabs();
//
//    // Reinitialize tlabs before resuming mutators.
//    virtual void resize_all_tlabs();

    // Allocate from the current thread's TLAB, with broken-out slow path.
    static HeapWord* allocate_from_tlab(KlassHandle klass, Thread* thread, size_t size);
    static HeapWord* allocate_from_tlab_slow(KlassHandle klass, Thread* thread, size_t size);

    // Allocate an uninitialized block of the given size, or returns NULL if
    // this is impossible.
    static HeapWord* common_mem_allocate_noinit(KlassHandle klass, size_t size, TRAPS);

    // Like allocate_init, but the block returned by a successful allocation
    // is guaranteed initialized to zeros.
    static HeapWord* common_mem_allocate_init(KlassHandle klass, size_t size, TRAPS);

    // Helper functions for (VM) allocation.
    static void post_allocation_setup_common(KlassHandle klass, HeapWord* obj);
    static void post_allocation_setup_no_klass_install(KlassHandle klass,
                                                              HeapWord* objPtr);

    static void post_allocation_setup_obj(KlassHandle klass, HeapWord* obj, int size);

    static void post_allocation_setup_array(KlassHandle klass,
                                                   HeapWord* obj, int length);

    static void post_allocation_setup_class(KlassHandle klass, HeapWord* obj, int size);

    // Clears an allocated object.
    static void init_obj(HeapWord* obj, size_t size);

    // Filler object utilities.
    static size_t filler_array_hdr_size();
    static size_t filler_array_min_size();


    // Fill with a single array; caller must ensure filler_array_min_size() <=
    // words <= filler_array_max_size().
    static void fill_with_array(HeapWord* start, size_t words, bool zap = true);

    // Fill with a single object (either an int array or a java.lang.Object).
    static void fill_with_object_impl(HeapWord* start, size_t words, bool zap = true);




    // Let's define some terms: a "closed" subset of a heap is one that
    //
    // 1) contains all currently-allocated objects, and
    //
    // 2) is closed under reference: no object in the closed subset
    //    references one outside the closed subset.
    //
    // Membership in a heap's closed subset is useful for assertions.
    // Clearly, the entire heap is a closed subset, so the default
    // implementation is to use "is_in_reserved".  But this may not be too
    // liberal to perform useful checking.  Also, the "is_in" predicate
    // defines a closed subset, but may be too expensive, since "is_in"
    // verifies that its argument points to an object head.  The
    // "closed_subset" method allows a heap to define an intermediate
    // predicate, allowing more precise checking than "is_in_reserved" at
    // lower cost than "is_in."

    // One important case is a heap composed of disjoint contiguous spaces,
    // such as the Garbage-First collector.  Such heaps have a convenient
    // closed subset consisting of the allocated portions of those
    // contiguous spaces.

    // Return "TRUE" iff the given pointer points into the heap's defined
    // closed subset (which defaults to the entire heap).
//    virtual bool is_in_closed_subset(const void* p) const {
//        return is_in_reserved(p);
//    }
//
//    // An object is scavengable if its location may move during a scavenge.
//    // (A scavenge is a GC which is not a full GC.)
//    virtual bool is_scavengable(const void *p) = 0;

    void set_gc_cause(GCCause::Cause v) {
        _gc_cause = v;
    }
    GCCause::Cause gc_cause() { return _gc_cause; }


    // General obj/array allocation facilities.
    static oop obj_allocate(KlassHandle klass, int size, TRAPS);
    static oop array_allocate(KlassHandle klass, int size, int length, TRAPS);
    static oop array_allocate_nozero(KlassHandle klass, int size, int length, TRAPS);
    static oop class_allocate(KlassHandle klass, int size, TRAPS);

    // Raw memory allocation facilities
    // The obj and array allocate methods are covers for these methods.
    // mem_allocate() should never be
    // called to allocate TLABs, only individual objects.
    virtual HeapWord* mem_allocate(size_t size,
                                   bool* gc_overhead_limit_was_exceeded) = 0;

    // Utilities for turning raw memory into filler objects.
    //
    // min_fill_size() is the smallest region that can be filled.
    // fill_with_objects() can fill arbitrary-sized regions of the heap using
    // multiple objects.  fill_with_object() is for regions known to be smaller
    // than the largest array of integers; it uses a single object to fill the
    // region and has slightly less overhead.
//    static size_t min_fill_size() {
//        return size_t(align_object_size(oopDesc::header_size()));
//    }

    static void fill_with_objects(HeapWord* start, size_t words, bool zap = true);

    static void fill_with_object(HeapWord* start, size_t words, bool zap = true);
    static void fill_with_object(MemRegion region, bool zap = true) {
        fill_with_object(region.start(), region.word_size(), zap);
    }
    static void fill_with_object(HeapWord* start, HeapWord* end, bool zap = true) {
        fill_with_object(start, pointer_delta(end, start), zap);
    }


    // These functions return the addresses of the fields that define the
    // boundaries of the contiguous allocation area.  (These fields should be
    // physically near to one another.)
    virtual HeapWord* volatile* top_addr() const {
        guarantee(false, "contiguous allocation not supported");
        return NULL;
    }
    virtual HeapWord** end_addr() const {
        guarantee(false, "contiguous allocation not supported");
        return NULL;
    }
//
//    // Some heaps may be in an unparseable state at certain times between
//    // collections. This may be necessary for efficient implementation of
//    // certain allocation-related activities. Calling this function before
//    // attempting to parse a heap ensures that the heap is in a parsable
//    // state (provided other concurrent activity does not introduce
//    // unparsability). It is normally expected, therefore, that this
//    // method is invoked with the world stopped.
//    // NOTE: if you override this method, make sure you call
//    // super::ensure_parsability so that the non-generational
//    // part of the work gets done. See implementation of
//    // CollectedHeap::ensure_parsability and, for instance,
//    // that of GenCollectedHeap::ensure_parsability().
//    // The argument "retire_tlabs" controls whether existing TLABs
//    // are merely filled or also retired, thus preventing further
//    // allocation from them and necessitating allocation of new TLABs.
//    virtual void ensure_parsability(bool retire_tlabs);
//
//    // Section on thread-local allocation buffers (TLABs)
//    // If the heap supports thread-local allocation buffers, it should override
//    // the following methods:
//    // Returns "true" iff the heap supports thread-local allocation buffers.
//    // The default is "no".
//    virtual bool supports_tlab_allocation() const = 0;
//
//
//    // The amount of space available for thread-local allocation buffers.
//    virtual size_t tlab_capacity(Thread *thr) const = 0;
//
//    // The amount of used space for thread-local allocation buffers for the given thread.
//    virtual size_t tlab_used(Thread *thr) const = 0;

    // virtual size_t max_tlab_size() const;

    // An estimate of the maximum allocation that could be performed
    // for thread-local allocation buffers without triggering any
    // collection or expansion activity.
    virtual size_t unsafe_max_tlab_alloc(Thread *thr) const {
        guarantee(false, "thread-local allocation buffers not supported");
        return 0;
    }


//    // Perform a collection of the heap; intended for use in implementing
//    // "System.gc".  This probably implies as full a collection as the
//    // "CollectedHeap" supports.
//    virtual void collect(GCCause::Cause cause) = 0;
//
//    // Perform a full collection
//    virtual void do_full_collection(bool clear_all_soft_refs) = 0;

    // This interface assumes that it's being called by the
    // vm thread. It collects the heap assuming that the
    // heap lock is already held and that we are executing in
    // the context of the vm thread.
    // virtual void collect_as_vm_thread(GCCause::Cause cause);
//
//    // Returns the barrier set for this heap
//    BarrierSet* barrier_set() { return _barrier_set; }
//    void set_barrier_set(BarrierSet* barrier_set);

    // Returns "true" iff there is a stop-world GC in progress.  (I assume
    // that it should answer "false" for the concurrent part of a concurrent
    // collector -- dld).
    bool is_gc_active() const { return _is_gc_active; }

    // Total number of GC collections (started)
    unsigned int total_collections() const { return _total_collections; }
    unsigned int total_full_collections() const { return _total_full_collections;}

    // Increment total number of GC collections (started)
    // Should be protected but used by PSMarkSweep - cleanup for 1.4.2
    void increment_total_collections(bool full = false) {
        _total_collections++;
        if (full) {
            increment_total_full_collections();
        }
    }

    void increment_total_full_collections() { _total_full_collections++; }



};




#endif //MINISPOT_COLLECTEDHEAP_H
