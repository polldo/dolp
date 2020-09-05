#include "main.h"

void hw_setup();
void wait_end_frame();

void hw_setup()
{
	HAL_Init();
	sysclk_setup();
	refresh_setup();
	display_setup();
	joystick_setup();
	note_player_setup();
	debug_pin_init();
}

void wait_end_frame()
{
	while ( !refresh_get() );
	refresh_reset();
}

int main(void)
{
	/* Setup phase */
	hw_setup();
	/* Init display objects */
	uint64_t frame_counter = 0;
	t_painter paint_1 = {0, 10, 0};
	t_painter paint_2 = {20, 30, 0};
	/* Loop phase */
	while (1)
	{
		/* Check whether a button has been pressed just now */
		joystick_update();
		/* Frame logic */
		/* Demo song logic */
		if (! (frame_counter % 1000) )
			note_player_play(&song_1, LOOP_ENABLED);

		/* Demo game logic */
		if (joystick_pressed(BUTTON_A)) //&& !(frame_counter % 2))
			painter_change_dir(&paint_1);
		if (joystick_pressed(BUTTON_B))// && !(frame_counter % 2))
			painter_change_dir(&paint_2);
		painter_move(&paint_1);
		painter_move(&paint_2);
		painter_draw(&paint_1);
		painter_draw(&paint_2);
		
		/* End of Frame */
		frame_counter++;
		if (frame_counter == 60)
		{
			frame_counter = 0;
		}
		wait_end_frame();
		display_send();
	}
}

