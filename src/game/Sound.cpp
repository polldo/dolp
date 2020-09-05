#include <sound.h>

#define DO 3812
#define RE 3402
#define MI 3016
#define FA 2848
#define SOL 2536
#define LA 2273
#define SI 1987
#define PAUSE 0

t_note note_array[14] =
{
		{DO, 500}, {PAUSE, 200}, {RE, 500}, {PAUSE, 200},
		{MI, 500}, {PAUSE, 200}, {FA, 500}, {PAUSE, 200},
		{SOL, 500}, {PAUSE, 200}, {LA, 500}, {PAUSE, 200}, {SI, 500}, {PAUSE, 2000}
};

t_song song_1 = { note_array, 14 };
