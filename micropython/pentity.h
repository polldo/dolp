#ifndef MICROPYTHON_PENTITY_H
#define MICROPYTHON_PENTITY_H

#include "dolp.h"
extern "C"
{
#include "py/obj.h"
}

typedef struct _dolp_pentity_obj_t
{
	mp_obj_base_t base;
	PEntity pentity;
} dolp_pentity_obj_t;

typedef struct _dolp_animation_obj_t
{
	mp_obj_base_t base;
	Animation animation;
} dolp_animation_obj_t;

#endif