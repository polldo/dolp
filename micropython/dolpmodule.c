#include <dolpmodule.h>

STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_pentity_get_id_obj, dolp_pentity_obj_get_id);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(dolp_pentity_set_type_obj, dolp_pentity_obj_set_type);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_pentity_get_type_obj, dolp_pentity_obj_get_type);
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(dolp_pentity_configure_obj, 5, 5, dolp_pentity_obj_configure);
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(dolp_pentity_move_to_obj, 4, 4, dolp_pentity_obj_move_to);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_pentity_is_moving_obj, dolp_pentity_obj_is_moving);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(dolp_pentity_update_obj, dolp_pentity_obj_update);
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(dolp_pentity_collision_obj, 1, 2, dolp_pentity_obj_collision);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(dolp_pentity_collided_obj, dolp_pentity_obj_collided);
STATIC MP_DEFINE_CONST_FUN_OBJ_3(dolp_pentity_set_state_obj, dolp_pentity_obj_set_state);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(dolp_pentity_get_state_obj, dolp_pentity_obj_get_state);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(dolp_pentity_new_timeout_obj, dolp_pentity_obj_new_timeout);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(dolp_pentity_delete_timeout_obj, dolp_pentity_obj_delete_timeout);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(dolp_pentity_get_timeout_obj, dolp_pentity_obj_get_timeout);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_pentity_get_x_obj, dolp_pentity_obj_get_x);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(dolp_pentity_set_x_obj, dolp_pentity_obj_set_x);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_pentity_get_y_obj, dolp_pentity_obj_get_y);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(dolp_pentity_set_y_obj, dolp_pentity_obj_set_y);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_pentity_delete_obj, dolp_pentity_obj_delete);
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(dolp_pentity_set_image_obj, 2, 3, dolp_pentity_obj_set_image);
STATIC MP_DEFINE_CONST_FUN_OBJ_2(dolp_pentity_set_animation_obj, dolp_pentity_obj_set_animation);
STATIC const mp_rom_map_elem_t dolp_pentity_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_get_id), MP_ROM_PTR(&dolp_pentity_get_id_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_type), MP_ROM_PTR(&dolp_pentity_set_type_obj)},
    {MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&dolp_pentity_get_type_obj)},
    {MP_ROM_QSTR(MP_QSTR_configure), MP_ROM_PTR(&dolp_pentity_configure_obj)},
    {MP_ROM_QSTR(MP_QSTR_move_to), MP_ROM_PTR(&dolp_pentity_move_to_obj)},
    {MP_ROM_QSTR(MP_QSTR_is_moving), MP_ROM_PTR(&dolp_pentity_is_moving_obj)},
    {MP_ROM_QSTR(MP_QSTR_update), MP_ROM_PTR(&dolp_pentity_update_obj)},
    {MP_ROM_QSTR(MP_QSTR_collision), MP_ROM_PTR(&dolp_pentity_collision_obj)},
    {MP_ROM_QSTR(MP_QSTR_collided), MP_ROM_PTR(&dolp_pentity_collided_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_state), MP_ROM_PTR(&dolp_pentity_set_state_obj)},
    {MP_ROM_QSTR(MP_QSTR_get_state), MP_ROM_PTR(&dolp_pentity_get_state_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_image), MP_ROM_PTR(&dolp_pentity_set_image_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_animation), MP_ROM_PTR(&dolp_pentity_set_animation_obj)},
    {MP_ROM_QSTR(MP_QSTR_new_timeout), MP_ROM_PTR(&dolp_pentity_new_timeout_obj)},
    {MP_ROM_QSTR(MP_QSTR_delete_timeout), MP_ROM_PTR(&dolp_pentity_delete_timeout_obj)},
    {MP_ROM_QSTR(MP_QSTR_get_timeout), MP_ROM_PTR(&dolp_pentity_get_timeout_obj)},
    {MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&dolp_pentity_get_x_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&dolp_pentity_set_x_obj)},
    {MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&dolp_pentity_get_y_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&dolp_pentity_set_y_obj)},
    {MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&dolp_pentity_delete_obj)},
};

STATIC MP_DEFINE_CONST_DICT(dolp_pentity_locals_dict, dolp_pentity_locals_dict_table);
const mp_obj_type_t dolp_pentity_type = {
    {&mp_type_type},
    .name = MP_QSTR_PEntity,
    .print = pentity_print,
    .make_new = pentity_make_new,
    .locals_dict = (mp_obj_t)&dolp_pentity_locals_dict,
};

STATIC const mp_rom_map_elem_t dolp_animation_locals_dict_table[] = {};

STATIC MP_DEFINE_CONST_DICT(dolp_animation_locals_dict, dolp_animation_locals_dict_table);
const mp_obj_type_t dolp_animation_type = {
    {&mp_type_type},
    .name = MP_QSTR_Animation,
    .make_new = animation_make_new,
    .locals_dict = (mp_obj_t)&dolp_animation_locals_dict,
};

STATIC MP_DEFINE_CONST_FUN_OBJ_0(dolp_begin_obj, dolp_begin);
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(dolp_loop_obj, 0, 1, dolp_loop);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(dolp_loop_begin_obj, dolp_loop_begin);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(dolp_loop_end_obj, dolp_loop_end);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(dolp_new_entity_obj, dolp_new_entity);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_delete_entity_obj, dolp_delete_entity);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(dolp_new_timeout_obj, dolp_new_timeout);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_delete_timeout_obj, dolp_delete_timeout);
STATIC MP_DEFINE_CONST_FUN_OBJ_3(dolp_set_timeout_obj, dolp_set_timeout);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_check_timeout_obj, dolp_check_timeout);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(dolp_width_obj, dolp_width);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(dolp_height_obj, dolp_height);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_pressed_obj, dolp_pressed);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(dolp_held_obj, dolp_held);

STATIC const mp_rom_map_elem_t dolp_module_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_dolp)},
    {MP_ROM_QSTR(MP_QSTR_begin), MP_ROM_PTR(&dolp_begin_obj)},
    {MP_ROM_QSTR(MP_QSTR_loop), MP_ROM_PTR(&dolp_loop_obj)},
    {MP_ROM_QSTR(MP_QSTR_loop_begin), MP_ROM_PTR(&dolp_loop_begin_obj)},
    {MP_ROM_QSTR(MP_QSTR_loop_end), MP_ROM_PTR(&dolp_loop_end_obj)},
    {MP_ROM_QSTR(MP_QSTR_new_entity), MP_ROM_PTR(&dolp_new_entity_obj)},
    {MP_ROM_QSTR(MP_QSTR_delete_entity), MP_ROM_PTR(&dolp_delete_entity_obj)},
    {MP_ROM_QSTR(MP_QSTR_new_timeout), MP_ROM_PTR(&dolp_new_timeout_obj)},
    {MP_ROM_QSTR(MP_QSTR_delete_timeout), MP_ROM_PTR(&dolp_delete_timeout_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_timeout), MP_ROM_PTR(&dolp_set_timeout_obj)},
    {MP_ROM_QSTR(MP_QSTR_check_timeout), MP_ROM_PTR(&dolp_check_timeout_obj)},
    {MP_ROM_QSTR(MP_QSTR_pressed), MP_ROM_PTR(&dolp_pressed_obj)},
    {MP_ROM_QSTR(MP_QSTR_held), MP_ROM_PTR(&dolp_held_obj)},
    {MP_ROM_QSTR(MP_QSTR_width), MP_ROM_PTR(&dolp_width_obj)},
    {MP_ROM_QSTR(MP_QSTR_height), MP_ROM_PTR(&dolp_height_obj)},

    {MP_ROM_QSTR(MP_QSTR_BUTTON_A), MP_ROM_INT(0)},
    {MP_ROM_QSTR(MP_QSTR_BUTTON_B), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_BUTTON_C), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_BUTTON_D), MP_ROM_INT(3)},

    {MP_OBJ_NEW_QSTR(MP_QSTR_Animation), (mp_obj_t)&dolp_animation_type},
};
STATIC MP_DEFINE_CONST_DICT(dolp_module_globals, dolp_module_globals_table);

const mp_obj_module_t dolp_user_cmodule = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&dolp_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_dolp, dolp_user_cmodule, 1);
