//
// Created by tzhou on 4/23/17.
//

#include "init.h"
#include "../memory/universe.h"

void init::vm_init_globals() {

}

jint init::init_globals() {
    Universe::universe_init();
}