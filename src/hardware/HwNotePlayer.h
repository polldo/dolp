#ifndef HW_NOTE_PLAYER_H_
#define HW_NOTE_PLAYER_H_

#include "Common.h"

typedef enum noteFrequency {
	DO = 3812,
	RE = 3402,
	MI = 3016,
	FA = 2848,
	SOL = 2536,
	LA = 2273,
	SI = 1987,
	PAUSE = 0
} NoteFrequency;

struct Note
{
	NoteFrequency frequency;
	uint16_t duration;
};

struct Song
{
	Note *notes;
	uint16_t size;
	Song(Note *notes, uint16_t size) :
		notes(notes),
		size(size)
	{
	}
};

void hwNotePlayerSetup();
void hwNotePlayerStart();
void hwNotePlayerStop();
void hwNotePlayerVolume(uint8_t volume);
void hwNotePlayerSong(Note* notes, uint16_t size, uint16_t startIndex, bool loopEn);

#endif /* HW_NOTE_PLAYER_H_ */
