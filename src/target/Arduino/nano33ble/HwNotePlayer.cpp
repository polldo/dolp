#include "hardware/HwConfiguration.h"
#if defined(ARDUINO_ARDUINO_NANO33BLE)

#include "hardware/HwNotePlayer.h"
#include "Arduino.h"

#define NOTE_PIN 3

Note *notesList;
uint16_t notesSize;
uint16_t notesIndex;
uint16_t notesStartIndex;
bool notesLoop;

// mbed::PwmOut* pwm = digitalPinToPwm(NOTE_PIN);

void hwNotePlayerSetup()
{
}

void playNextNote()
{
  // if (notesList != NULL) {

  //// end
  // if (notesIndex > notesSize) {
  // if (notesLoop) {
  // notesIndex = notesStartIndex;
  //} else {
  ////notesList = NULL;
  // hwNotePlayerStop();
  //}
  //}
  ////tone(NOTE_PIN, );
  //}
}

void hwNotePlayerStart()
{
  if (notesList != NULL)
  {

    playNextNote();
  }
}

void hwNotePlayerStop()
{
  // noTone(NOTE_PIN);
}

void hwNotePlayerVolume(uint8_t volume)
{
}

void hwNotePlayerSong(Note *notes, uint16_t size, uint16_t startIndex, bool loopEn)
{
  notesList = notes;
}

#endif
