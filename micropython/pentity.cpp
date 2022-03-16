#include "pentity.h"
extern "C"
{
#include <dolpmodule.h>
#include "py/obj.h"
#include "py/runtime.h"
}

mp_obj_t dolp_pentity_obj_get_id(mp_obj_t self_in)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	return mp_obj_new_int(self->pentity.getId());
}

mp_obj_t dolp_pentity_obj_set_type(mp_obj_t self_in, mp_obj_t typ)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	int t = mp_obj_get_int(typ);
	self->pentity.setType(t);
	return mp_const_none;
}

mp_obj_t dolp_pentity_obj_get_type(mp_obj_t self_in)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	return mp_obj_new_int(self->pentity.getType());
}

mp_obj_t dolp_pentity_obj_configure(size_t n_args, const mp_obj_t *args)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(args[0]);
	int x = mp_obj_get_int(args[1]);
	int y = mp_obj_get_int(args[2]);
	int w = mp_obj_get_int(args[3]);
	int h = mp_obj_get_int(args[4]);
	self->pentity.configure(x, y, w, h);
	return mp_const_none;
}

mp_obj_t dolp_pentity_obj_move_to(size_t n_args, const mp_obj_t *args)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(args[0]);
	int x = mp_obj_get_int(args[1]);
	int y = mp_obj_get_int(args[2]);
	int v = mp_obj_get_int(args[3]);
	self->pentity.moveTo(x, y, v);
	return mp_const_none;
}

mp_obj_t dolp_pentity_obj_is_moving(mp_obj_t self_in)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	return mp_obj_new_bool(self->pentity.isMoving());
}

mp_obj_t dolp_pentity_obj_update(mp_obj_t self_in, mp_obj_t cback)
{
	// TODO: check if the function params are correct
	if (!mp_obj_is_fun(cback))
	{
		mp_raise_TypeError("passed parameter is not a function");
	}
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	self->pentity.update(cback);
	return mp_const_none;
}

mp_obj_t dolp_pentity_obj_collision(size_t n_args, const mp_obj_t *args)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(args[0]);
	if (n_args < 2)
	{
		self->pentity.collision();
		return mp_const_none;
	}
	auto cback = args[1];
	if (!mp_obj_is_fun(cback))
	{
		mp_raise_TypeError("passed parameter is not a function");
	}
	self->pentity.collision(cback);
	return mp_const_none;
}

mp_obj_t dolp_pentity_obj_collided(mp_obj_t self_in, mp_obj_t other_in)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	dolp_pentity_obj_t *other = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(other_in);
	return mp_obj_new_bool(self->pentity.collided(other->pentity));
}

mp_obj_t dolp_pentity_obj_set_state(mp_obj_t self_in, mp_obj_t index, mp_obj_t value)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	int idx = mp_obj_get_int(index);
	int val = mp_obj_get_int(value);
	self->pentity.setState(idx, val);
	return mp_const_none;
}

mp_obj_t dolp_pentity_obj_get_state(mp_obj_t self_in, mp_obj_t index)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	int idx = mp_obj_get_int(index);
	return mp_obj_new_int(self->pentity.getState(idx));
}

mp_obj_t dolp_pentity_obj_set_image(size_t n_args, const mp_obj_t *args)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(args[0]);
	mp_buffer_info_t imgbuf;
	mp_get_buffer_raise(args[1], &imgbuf, 1);
	const uint8_t *b = (const uint8_t *)imgbuf.buf;
	self->pentity.setImage(b);
	if (n_args > 2)
	{
		mp_buffer_info_t mskbuf;
		mp_get_buffer_raise(args[2], &mskbuf, 1);
		const uint8_t *m = (const uint8_t *)mskbuf.buf;
		self->pentity.setImage(b, m);
	}
	return mp_const_none;
}

mp_obj_t dolp_pentity_obj_new_timeout(mp_obj_t self_in, mp_obj_t index)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	int idx = mp_obj_get_int(index);
	return mp_obj_new_int(self->pentity.newTimeout(idx));
}

mp_obj_t dolp_pentity_obj_delete_timeout(mp_obj_t self_in, mp_obj_t index)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	int idx = mp_obj_get_int(index);
	self->pentity.deleteTimeout(idx);
	return mp_const_none;
}

mp_obj_t dolp_pentity_obj_get_timeout(mp_obj_t self_in, mp_obj_t index)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	int idx = mp_obj_get_int(index);
	return mp_obj_new_int(self->pentity.getTimeout(idx));
}

mp_obj_t dolp_pentity_obj_get_x(mp_obj_t self_in)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	return mp_obj_new_int(self->pentity.getX());
}

mp_obj_t dolp_pentity_obj_get_y(mp_obj_t self_in)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	return mp_obj_new_int(self->pentity.getY());
}

mp_obj_t dolp_pentity_obj_delete(mp_obj_t self_in)
{
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	dolp.deleteEntity(self->pentity);
	return mp_const_none;
}

mp_obj_t pentity_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
	mp_arg_check_num(n_args, n_kw, 0, 0, true);
	dolp_pentity_obj_t *p = m_new_obj(dolp_pentity_obj_t);

	auto ent = dolp.newEntity();
	p->base.type = &dolp_pentity_type;
	p->pentity = ent;
	return MP_OBJ_FROM_PTR(p);
}

void pentity_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
	(void)kind;
	dolp_pentity_obj_t *self = (dolp_pentity_obj_t *)MP_OBJ_TO_PTR(self_in);
	mp_print_str(print, "entity(");
	mp_print_str(print, "id: ");
	mp_obj_print_helper(print, mp_obj_new_int(self->pentity.getId()), PRINT_REPR);
	mp_print_str(print, ", type: ");
	mp_obj_print_helper(print, mp_obj_new_int(self->pentity.getType()), PRINT_REPR);
	mp_print_str(print, ", x: ");
	mp_obj_print_helper(print, mp_obj_new_int(self->pentity.getX()), PRINT_REPR);
	mp_print_str(print, ", y: ");
	mp_obj_print_helper(print, mp_obj_new_int(self->pentity.getY()), PRINT_REPR);
	mp_print_str(print, ")");
}
