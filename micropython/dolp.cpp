#include "dolp.h"
#include "pentity.h"
extern "C"
{
#include <dolpmodule.h>
#include <py/obj.h>
#include <py/mphal.h>
}

mp_obj_t dolp_begin()
{
    dolp.begin();
    return mp_const_none;
}

mp_obj_t dolp_loop(size_t n_args, const mp_obj_t *args)
{
    auto n = 1;
    if (n_args > 0)
    {
        n = mp_obj_get_int(args[0]);
    }
    for (int i = 0; i < n; i++)
    {
        dolp.loopBegin();
        dolp.loopEnd();
    }
    return mp_const_none;
}

mp_obj_t dolp_loop_begin()
{
    dolp.loopBegin();
    return mp_const_none;
}

mp_obj_t dolp_loop_end()
{
    dolp.loopEnd();
    return mp_const_none;
}

mp_obj_t dolp_new_entity()
{
    dolp_pentity_obj_t *p = m_new_obj(dolp_pentity_obj_t);
    auto ent = dolp.newEntity();
    p->base.type = &dolp_pentity_type;
    p->pentity = ent;
    return MP_OBJ_FROM_PTR(p);
}

mp_obj_t dolp_delete_entity(mp_obj_t entity)
{
    dolp_pentity_obj_t *ent = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(entity);
    dolp.deleteEntity(ent->pentity);
    return mp_const_none;
}

mp_obj_t dolp_new_timeout()
{
    return mp_obj_new_int(dolp.newTimeout());
}

mp_obj_t dolp_delete_timeout(mp_obj_t index)
{
    int idx = mp_obj_get_int(index);
    dolp.deleteTimeout(idx);
    return mp_const_none;
}

mp_obj_t dolp_set_timeout(mp_obj_t index, mp_obj_t millis, mp_obj_t repeat)
{
    int idx = mp_obj_get_int(index);
    int ms = mp_obj_get_int(millis);
    bool rp = mp_obj_is_true(repeat);
    dolp.setTimeout(idx, ms, rp);
    return mp_const_none;
}

mp_obj_t dolp_check_timeout(mp_obj_t index)
{
    int idx = mp_obj_get_int(index);
    return mp_obj_new_bool(dolp.checkTimeout(idx));
}

mp_obj_t dolp_pressed(mp_obj_t button)
{
    int btn = mp_obj_get_int(button);
    return mp_obj_new_bool(dolp.pressed((JoystickButton)btn));
}

mp_obj_t dolp_held(mp_obj_t button)
{
    int btn = mp_obj_get_int(button);
    return mp_obj_new_bool(dolp.held((JoystickButton)btn));
}

mp_obj_t dolp_width()
{
    return mp_obj_new_int(dolp.width());
}

mp_obj_t dolp_height()
{
    return mp_obj_new_int(dolp.height());
}
