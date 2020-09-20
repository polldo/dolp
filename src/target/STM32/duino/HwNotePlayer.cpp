#include "hardware/HwConfiguration.h"
#if defined (_STM32_DUINO_)

#include "Arduino.h"
#include <hardware/HwNotePlayer.h>
#include <HardwareTimer.h>

Note* _notes;
uint16_t _size;
volatile uint16_t _index;
uint16_t _startIndex;
bool _loopEn;
uint8_t _volume;
volatile uint32_t _duration;

#define NOTE_PIN (11) 
// Timer 3, channel 2 are suitable to drive this pin 
#define NOTE_TIMER (TIM3)
#define NOTE_CHANNEL (2)
//#define PAUSE_TIMER (TIM4)
#define DURATION_TIMER (TIM4)
// Functions to retrieve the correct timer and channel for driving the given pin
//TIM_TypeDef *p_timer = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(NOTE_PIN), PinMap_PWM);
//uint32_t _timerChannel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(NOTE_PIN), PinMap_PWM));
//HardwareTimer _noteTimer(p_timer);
HardwareTimer _noteTimer (NOTE_TIMER);
//HardwareTimer _pauseTimer (PAUSE_TIMER);
HardwareTimer _durationTimer (DURATION_TIMER);

void timerNoteCallback(void);
static void hwNotePlayerNextNote();

#define DURATION_OVERFLOW(duration) (duration * 10)
void hwNotePlayerSetup()
{
    // clk@80MHz -> 100 us per tick  -> overflow = duration*10 ms
    _noteTimer.setPreloadEnable(true);
    _durationTimer.setPreloadEnable(true);
    _durationTimer.setMode(1, TIMER_OUTPUT_COMPARE);  
    _durationTimer.setPrescaleFactor(8000);
    _durationTimer.attachInterrupt(timerNoteCallback);
}

static void hwNotePlayerNextNote()
{
    auto nextFrequency = _notes[_index].frequency;_notes[_index].frequency;
    auto nextDuration = _notes[_index].duration;
    _index++;
    if (nextFrequency != PAUSE) {
        _noteTimer.setPWM(NOTE_CHANNEL, NOTE_PIN, nextFrequency, _volume);
        //_noteTimer.refresh();
    } 
    //DURATION_TIMER->ARR = nextDuration * 10; /* period = duration ms */
    _durationTimer.setOverflow(nextDuration * 10, TICK_FORMAT); 
    _durationTimer.refresh();
    _durationTimer.resume();
}

void timerNoteCallback(void)
{
    hwNotePlayerStop();
    if (_index >= _size) {
        _index = _startIndex;
        if (_loopEn) {
            hwNotePlayerNextNote();
        }
    } else {
        hwNotePlayerNextNote();
    }
}

void hwNotePlayerStart()
{
    timerNoteCallback();
}

void hwNotePlayerStop()
{
    _durationTimer.pause();
    _durationTimer.setCount(0);
    _noteTimer.pause();
    _noteTimer.setCount(0);
}

void hwNotePlayerVolume(uint8_t volume)
{
    _volume = volume;
}

void hwNotePlayerSong(Note* notes, uint16_t size, uint16_t startIndex, bool loopEn)
{
    _notes = notes;
    _size = size;
    _startIndex = startIndex;
    _index = startIndex;
    _loopEn = loopEn;
}

#endif
