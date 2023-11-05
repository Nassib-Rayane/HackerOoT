#ifndef Z_OBJ_SHUTTER_H
#define Z_OBJ_SHUTTER_H

#include "global.h"

struct ObjShutter;

typedef struct ObjShutter {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x144 */ u8 isOpen;
} ObjShutter; // size = 0x14C

#endif // Z_OBJ_SHUTTER_H
