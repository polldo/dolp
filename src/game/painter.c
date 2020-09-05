#include "painter.h"

void painter_change_dir(t_painter *paint)
{
	paint->dir += 1;
	if (paint->dir == 4)
		paint->dir = 0;
}

void painter_move(t_painter *paint)
{
	switch(paint->dir) {
	case 0 :
		paint->x += 1;
		break;
	case 1 :
		paint->y += 1;
		break;
	case 2 :
		paint->x -= 1;
		break;
	case 3 :
		paint->y -= 1;
		break;
	};
	if (paint->x == 128)
		paint->x = 1;
	else if (paint->x == 0)
		paint->x = 127;
	if (paint->y == 64)
		paint->y = 1;
	else if (paint->y == 1)
		paint->y = 63;
}

void painter_draw(t_painter *paint)
{
	display_draw(paint->x, paint->y, 2);
}
