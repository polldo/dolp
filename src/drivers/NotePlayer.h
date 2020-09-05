#ifndef NOTE_PLAYER_H_
#define NOTE_PLAYER_H_

#include <Common.h>
#include <HwNotePlayer.h>

#define LOOP_DISABLED 0
#define LOOP_ENABLED 1

class NotePlayer {

public:
	NotePlayer();
	~NotePlayer();

	void setup();
	void stop();
	void play(t_song *song, uint8_t loopEn);
	void setVolume(uint8_t volume);

}

#endif /* NOTE_PLAYER_H_ */
