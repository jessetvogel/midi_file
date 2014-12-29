#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "../include/midi_file.h"

#define FORMAT_TYPE 1
#define DELTA_TIME_TICKS_PER_QUARTER_NOTE 600

int main()
{
    MIDI_FILE file(FORMAT_TYPE, DELTA_TIME_TICKS_PER_QUARTER_NOTE);
    
    MIDI_TRACK piano(MIDI_CHANNEL_0, MIDI_I_GRAND_PIANO);

    MIDI_EVENT event;

    event.delta_time = 600;
    event.type = MIDI_T_NOTE_ON;
    event.parameter_1 = 60;
    event.parameter_2 = 127;
    piano.add_event(&event);
    
    event.delta_time = 600;
    event.type = MIDI_T_NOTE_OFF;
    event.parameter_1 = 60;
    event.parameter_2 = 127;
    piano.add_event(&event);

    event.delta_time = 600;
    event.type = MIDI_T_NOTE_ON;
    event.parameter_1 = 64;
    event.parameter_2 = 127;
    piano.add_event(&event);
    
    event.delta_time = 600;
    event.type = MIDI_T_NOTE_OFF;
    event.parameter_1 = 64;
    event.parameter_2 = 127;
    piano.add_event(&event);
    
    file.add_track(&piano);

    file.save("piano.mid");
    
    return 0;
}
