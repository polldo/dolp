#ifndef HW_NOTE_PLAYER_H_
#define HW_NOTE_PLAYER_H_

typedef struct note
{
	uint16_t frequency;
	uint16_t duration;
} t_note;

typedef struct song
{
	t_note *notes;
	uint16_t size;
} t_song;

void hw_note_player_setup();
void hw_note_player_start();
void hw_note_player_stop();
void hw_note_player_volume(uint8_t volume);
void hw_note_player_song(t_song *song, uint8_t loopEn);

#endif /* HW_NOTE_PLAYER_H_ */
