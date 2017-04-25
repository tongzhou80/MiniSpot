//
// Created by tzhou on 4/24/17.
//

#include "gcCause.h"


const char* GCCause::to_string(GCCause::Cause cause) {
    switch (cause) {
        case _java_lang_system_gc:
            return "System.gc()";

        case _full_gc_alot:
            return "FullGCAlot";

        case _scavenge_alot:
            return "ScavengeAlot";

        case _allocation_profiler:
            return "Allocation Profiler";

        case _jvmti_force_gc:
            return "JvmtiEnv ForceGarbageCollection";

        case _gc_locker:
            return "GCLocker Initiated GC";

        case _heap_inspection:
            return "Heap Inspection Initiated GC";

        case _heap_dump:
            return "Heap Dump Initiated GC";

        case _wb_young_gc:
            return "WhiteBox Initiated Young GC";

        case _wb_conc_mark:
            return "WhiteBox Initiated Concurrent Mark";

        case _wb_full_gc:
            return "WhiteBox Initiated Full GC";

        case _update_allocation_context_stats_inc:
        case _update_allocation_context_stats_full:
            return "Update Allocation Context Stats";

        case _no_gc:
            return "No GC";

        case _allocation_failure:
            return "Allocation Failure";

        case _tenured_generation_full:
            return "Tenured Generation Full";

        case _metadata_GC_threshold:
            return "Metadata GC Threshold";

        case _metadata_GC_clear_soft_refs:
            return "Metadata GC Clear Soft References";

        case _cms_generation_full:
            return "CMS Generation Full";

        case _cms_initial_mark:
            return "CMS Initial Mark";

        case _cms_final_remark:
            return "CMS Final Remark";

        case _cms_concurrent_mark:
            return "CMS Concurrent Mark";

        case _old_generation_expanded_on_last_scavenge:
            return "Old Generation Expanded On Last Scavenge";

        case _old_generation_too_full_to_scavenge:
            return "Old Generation Too Full To Scavenge";

        case _adaptive_size_policy:
            return "Ergonomics";

        case _g1_inc_collection_pause:
            return "G1 Evacuation Pause";

        case _g1_humongous_allocation:
            return "G1 Humongous Allocation";

        case _dcmd_gc_run:
            return "Diagnostic Command";

        case _last_gc_cause:
            return "ILLEGAL VALUE - last gc cause - ILLEGAL VALUE";
        default:
            return "unknown GCCause";
    }
}