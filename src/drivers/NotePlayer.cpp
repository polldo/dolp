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
	hwNotePlayerSetup();
}

void NotePlayer::stop()
{
	hwNotePlayerStop();
}

void NotePlayer::play(Song &song) 
{
	hwNotePlayerStop();
	hwNotePlayerSong(song.notes, song.size, 0, false);
	hwNotePlayerStart();
}

void NotePlayer::play(Song &song, uint16_t startIndex) 
{
	hwNotePlayerStop();
	hwNotePlayerSong(song.notes, song.size, startIndex, false);
	hwNotePlayerStart();
}

void NotePlayer::play(Song &song, bool loopEn) 
{
	hwNotePlayerStop();
	hwNotePlayerSong(song.notes, song.size, 0, loopEn);
	hwNotePlayerStart();
}

void NotePlayer::play(Song &song, uint16_t startIndex, bool loopEn) 
{
	hwNotePlayerStop();
	hwNotePlayerSong(song.notes, song.size, startIndex, loopEn);
	hwNotePlayerStart();
}

void NotePlayer::setVolume(uint8_t volume)
{
	hwNotePlayerVolume(volume);
}
