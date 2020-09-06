#include "Sound.h"

Note note_array[14] =
{
		{DO, 500}, {PAUSE, 200}, {RE, 500}, {PAUSE, 200},
		{MI, 500}, {PAUSE, 200}, {FA, 500}, {PAUSE, 200},
		{SOL, 500}, {PAUSE, 200}, {LA, 500}, {PAUSE, 200}, {SI, 500}, {PAUSE, 2000}
};

Song song_1 = Song(note_array, 14);
