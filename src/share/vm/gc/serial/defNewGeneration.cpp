//
// Created by tzhou on 4/29/17.
//

#include <cstdlib>
#include "defNewGeneration.h"
#include "gc/shared/generation.h"

HeapWord* DefNewGeneration::allocate(int word_size) {
    return eden_space()->allocate(word_size);
}

bool DefNewGeneration::collect() {
    ZPPL("start collecting");

}
