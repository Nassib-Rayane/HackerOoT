/*
 * File: z_obj_shutter.c
 * Overlay: ovl_Obj_Shutter
 * Description: Unused West Clock Town bank closing shutter
 */

#include "z_obj_shutter.h"
#include "assets/objects/object_f53_obj/object_f53_obj.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

#define THIS ((ObjShutter*)thisx)

void ObjShutter_Init(Actor* thisx, PlayState* play);
void ObjShutter_Destroy(Actor* thisx, PlayState* play);
void ObjShutter_Update(Actor* thisx, PlayState* play2);
void ObjShutter_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Shutter_InitVars = {
    /**/ ACTOR_OBJ_SHUTTER,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_F53_OBJ,
    /**/ sizeof(ObjShutter),
    /**/ ObjShutter_Init,
    /**/ ObjShutter_Destroy,
    /**/ ObjShutter_Update,
    /**/ ObjShutter_Draw,
};

void ObjShutter_InitDynaPoly(ObjShutter* this, PlayState* play) {
    static CollisionHeader* collisionHeaders = &gObjShutterCol;
    s32 pad;
    CollisionHeader* colHeader = NULL;
    s32 pad2[2];


    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(collisionHeaders, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);
}

void ObjShutter_Init(Actor* thisx, PlayState* play) {
    ObjShutter* this = (ObjShutter*)thisx;

    ObjShutter_InitDynaPoly(this, play);
    this->isOpen = (Flags_GetSwitch(play, 0x01)) ? true : false;
    Actor_SetScale(&this->dyna.actor, 0.1f);
    this->dyna.actor.focus.pos = this->dyna.actor.world.pos;
}

void ObjShutter_Destroy(Actor* thisx, PlayState* play) {
    ObjShutter* this = (ObjShutter*)thisx;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void ObjShutter_Open(Actor* thisx, PlayState* play) {
    ObjShutter* this = (ObjShutter*)thisx;

    this->isOpen = true;
    Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_SLIDE_DOOR_OPEN);
}

void ObjShutter_Update(Actor* thisx, PlayState* play) {
    ObjShutter* this = (ObjShutter*)thisx;

    if (Flags_GetSwitch(play, 0x01) && !this->isOpen) {
        ObjShutter_Open(thisx, play);
    }
    if ((this->isOpen) && (this->dyna.actor.world.pos.y < this->dyna.actor.home.pos.y + 55.0f)) {
        Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 55.0f, 2.0f);
    }
}

void ObjShutter_Draw(Actor* thisx, PlayState* play) {
   ObjShutter* this = (ObjShutter*)thisx;


    Gfx_DrawDListOpa(play, gBankShutterDL);
}
