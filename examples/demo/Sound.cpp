#include "Sound.h"

Note note_array[14] =
{
		{DO, 500}, {PAUSE, 1000}, {RE, 500}, {PAUSE, 1000},
		{MI, 500}, {PAUSE, 200}, {FA, 500}, {PAUSE, 200},
		{SOL, 500}, {PAUSE, 200}, {LA, 500}, {PAUSE, 200}, {SI, 500}, {PAUSE, 2000}
		//{DO, 2000}, {PAUSE, 3000}, {RE, 2000}, {PAUSE, 1000},
		//{DO, 2000}, {PAUSE, 1000}, {RE, 2000}, {PAUSE, 1000},
		//{DO, 2000}, {PAUSE, 1000}, {RE, 2000}, {PAUSE, 1000},
		//{DO, 2000}, {PAUSE, 1000}
};

Note note_2[2] =
{
		{DO, 500}, {PAUSE, 3000}
};

Note note_3[5] =
{
		{PAUSE, 1000}, {DO, 500}, {PAUSE, 1000}, {RE, 500}, {PAUSE, 500}
};

Note note_4[5] =
{
		{PAUSE, 1000}, {DO, 4000}, {PAUSE, 1000}, {RE, 4000}, {PAUSE, 500}
};

//Song song_1 = Song(note_2, 2);
Song song_1 = Song(note_array, 14);
//Song song_1 = Song(note_4, 5);
