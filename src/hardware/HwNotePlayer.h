#ifndef HW_NOTE_PLAYER_H_
#define HW_NOTE_PLAYER_H_

#include "Common.h"

#define LOOP_DISABLED 0
#define LOOP_ENABLED 1

enum NoteFrequency {
	DO_NOTE = 0,
	RE_NOTE = 1,
	MI_NOTE = 2,
	FA_NOTE = 3,
	SOL_NOTE = 4,
	LA_NOTE = 5,
	SI_NOTE = 6,
	C_NOTE = DO_NOTE,
	D_NOTE = RE_NOTE,  
	E_NOTE = MI_NOTE,
	F_NOTE = FA_NOTE,
	G_NOTE = SOL_NOTE,
	A_NOTE = LA_NOTE,
	B_NOTE = SI_NOTE,
	PAUSE_NOTE = 7
};

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
