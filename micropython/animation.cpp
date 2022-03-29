#include "pentity.h"
extern "C"
{
#include <dolpmodule.h>
#include "py/obj.h"
#include "py/runtime.h"
}

mp_obj_t animation_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
	mp_arg_check_num(n_args, n_kw, 2, 3, false);
	dolp_animation_obj_t *p = m_new_obj(dolp_animation_obj_t);

	if (!mp_obj_is_type(args[0], &mp_type_list))
	{
		mp_raise_TypeError("first parameter should be a list of bytearray");
	}
	if (!mp_obj_is_type(args[1], &mp_type_list))
	{
		mp_raise_TypeError("second parameter should be a list of int");
	}
	if (n_args > 2 && !mp_obj_is_type(args[2], &mp_type_list))
	{
		mp_raise_TypeError("third parameter should be a list of bytearray");
	}

	mp_obj_list_t *images = (mp_obj_list_t *)MP_OBJ_TO_PTR(args[0]);
	mp_obj_list_t *times = (mp_obj_list_t *)MP_OBJ_TO_PTR(args[1]);
	if (images->len != times->len)
	{
		mp_raise_TypeError("length of bytearray list should equal the length of int list");
	}
	mp_obj_list_t *masks = NULL;
	if (n_args > 2)
	{
		masks = (mp_obj_list_t *)MP_OBJ_TO_PTR(args[2]);
		if (masks->len != images->len)
		{
			mp_raise_TypeError("length of first bytearray list should equal the length of second bytearray list");
		}
	}

	if (images->len < 1)
	{
		mp_raise_TypeError("give me at least a frame!");
	}

	for (size_t i = 0; i < images->len; i++)
	{
		mp_buffer_info_t imgbuf;
		if (!mp_get_buffer(images->items[i], &imgbuf, 1))
		{
			mp_raise_TypeError("first parameter should be a list of bytearray");
		}
	}

	for (size_t i = 0; i < times->len; i++)
	{
		if (!mp_obj_is_int(times->items[i]))
		{
			mp_raise_TypeError("second parameter should be a list of int");
		}
	}

	if (masks)
	{
		for (size_t i = 0; i < masks->len; i++)
		{
			mp_buffer_info_t imgbuf;
			if (!mp_get_buffer(masks->items[i], &imgbuf, 1))
			{
				mp_raise_TypeError("third parameter should be a list of bytearray");
			}
		}
	}

	p->base.type = &dolp_animation_type;
	p->animation = Animation(images, times, masks);
	return MP_OBJ_FROM_PTR(p);
}
