#ifndef NOTE_PLAYER_H_
#define NOTE_PLAYER_H_

#include <Common.h>
#include "hardware/HwNotePlayer.h"

class NotePlayer
{
public:
	NotePlayer();
	virtual ~NotePlayer();

	void setup();
	void stop();

	void play(Song &song);
	void play(Song &song, uint16_t startIndex);
	void play(Song &song, bool loopEn);
	void play(Song &song, uint16_t startIndex, bool loopEn);

	void setVolume(uint8_t volume);
};

#endif /* NOTE_PLAYER_H_ */
