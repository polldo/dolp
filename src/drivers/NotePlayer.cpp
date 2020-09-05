#if 0

#include <drivers/NotePlayer.h>
#include <hardware/HwNotePlayer.h>

NotePlayer::NotePlayer() 
{
}

NotePlayer::~NotePlayer() 
{
}

void NotePlayer::setup()
{
	hw_note_player_setup();
}

void NotePlayer::stop()
{
	hw_note_player_stop();
}

void NotePlayer::play(t_song *song, uint8_t loopEn)
{
	hw_note_player_stop();
	hw_note_player_song(song, loopEn);
	hw_note_player_start();
}

void NotePlayer::setVolume(uint8_t volume)
{
	hw_note_player_volume(volume);
}

#endif