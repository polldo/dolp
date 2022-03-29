#include "py/runtime.h"

extern mp_obj_t dolp_begin();
extern mp_obj_t dolp_loop(size_t n_args, const mp_obj_t *args);
extern mp_obj_t dolp_loop_begin();
extern mp_obj_t dolp_loop_end();
extern mp_obj_t dolp_new_entity();
extern mp_obj_t dolp_delete_entity(mp_obj_t entity);
extern mp_obj_t dolp_new_timeout();
extern mp_obj_t dolp_delete_timeout(mp_obj_t index);
extern mp_obj_t dolp_set_timeout(mp_obj_t index, mp_obj_t millis, mp_obj_t repeat);
extern mp_obj_t dolp_check_timeout(mp_obj_t index);
extern mp_obj_t dolp_pressed(mp_obj_t button);
extern mp_obj_t dolp_held(mp_obj_t button);
extern mp_obj_t dolp_width();
extern mp_obj_t dolp_height();

extern const mp_obj_type_t dolp_pentity_type;
extern mp_obj_t dolp_pentity_obj_get_id(mp_obj_t self_in);
extern mp_obj_t dolp_pentity_obj_set_type(mp_obj_t self_in, mp_obj_t typ);
extern mp_obj_t dolp_pentity_obj_get_type(mp_obj_t self_in);
extern mp_obj_t dolp_pentity_obj_configure(size_t n_args, const mp_obj_t *args);
extern mp_obj_t dolp_pentity_obj_move_to(size_t n_args, const mp_obj_t *args);
extern mp_obj_t dolp_pentity_obj_is_moving(mp_obj_t self_in);
extern mp_obj_t dolp_pentity_obj_update(mp_obj_t self_in, mp_obj_t cback);
extern mp_obj_t dolp_pentity_obj_collision(size_t n_args, const mp_obj_t *args);
extern mp_obj_t dolp_pentity_obj_collided(mp_obj_t self_in, mp_obj_t other_in);
extern mp_obj_t dolp_pentity_obj_set_state(mp_obj_t self_in, mp_obj_t index, mp_obj_t value);
extern mp_obj_t dolp_pentity_obj_get_state(mp_obj_t self_in, mp_obj_t index);
extern mp_obj_t dolp_pentity_obj_set_image(size_t n_args, const mp_obj_t *args);
extern mp_obj_t dolp_pentity_obj_set_animation(mp_obj_t self_in, mp_obj_t animation_in);
extern mp_obj_t dolp_pentity_obj_new_timeout(mp_obj_t self_in, mp_obj_t index);
extern mp_obj_t dolp_pentity_obj_delete_timeout(mp_obj_t self_in, mp_obj_t index);
extern mp_obj_t dolp_pentity_obj_get_timeout(mp_obj_t self_in, mp_obj_t index);
extern mp_obj_t dolp_pentity_obj_get_x(mp_obj_t self_in);
extern mp_obj_t dolp_pentity_obj_get_y(mp_obj_t self_in);
extern mp_obj_t dolp_pentity_obj_delete(mp_obj_t self_in);
extern mp_obj_t pentity_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args);
extern void pentity_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind);

extern const mp_obj_type_t dolp_animation_type;
extern mp_obj_t animation_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args);
