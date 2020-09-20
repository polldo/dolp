#ifndef HW_NOTE_PLAYER_H_
#define HW_NOTE_PLAYER_H_

#include "Common.h"

typedef enum noteFrequency {
	DO = 0,
	RE = 1,
	MI = 2,
	FA = 3,
	SOL = 4,
	LA = 5,
	SI = 6,
	C = DO,
	D = RE,  
	E = MI,
	F = FA,
	G = SOL,
	A = LA,
	B = SI,
	PAUSE = 7
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
