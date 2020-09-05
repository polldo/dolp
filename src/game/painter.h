#ifndef PAINTER_H_
#define PAINTER_H_

#include <hw_common.h>
#include "display.h"

typedef struct painter
{
	uint8_t x;
	uint8_t y;
	uint8_t dir;
} t_painter;


void painter_change_dir(t_painter *paint);
void painter_move(t_painter *paint);
void painter_draw(t_painter *paint);

#endif /* PAINTER_H_ */
