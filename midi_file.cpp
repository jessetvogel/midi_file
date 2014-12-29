#include "midi_file.h"

MIDI_FILE::MIDI_FILE(unsigned char format, int ticks_per_quarter_note)
{
    // Values about the file format
    this->format = format;
    this->ticks_per_quarter_note = ticks_per_quarter_note;
}

void MIDI_FILE::add_track(MIDI_TRACK *track)
{
    // Create a new tracklist element
    MIDI_TRACKLIST *element = (MIDI_TRACKLIST*) malloc(sizeof(MIDI_TRACKLIST));
    
    // Give it the right values
    element->track = track;
    element->previous = last_track;
    element->next = NULL;
    
    // If there was a last track (list was non-empty), then set the previous' next to the new element
    if(last_track != NULL) last_track->next = element;
    
    // If the track was empty, then this is the first event
    if(first_track == NULL) first_track = element;
    
    // Set the last track to this element
    last_track = element;
    
    // Increment the number of tracks by one
    number_of_tracks ++;
}

void MIDI_FILE::save(char* path)
{
    // Open filestream
    std::ofstream midi(path);
    
    // First write header
    write_header(&midi, format, number_of_tracks, ticks_per_quarter_note);
    
    // Write all the tracks
    MIDI_TRACKLIST *track_ptr = first_track;
    
    while(track_ptr != NULL)
    {
        // Write track
        write_track(&midi, track_ptr->track);
        
        // Go to next track in the list
        track_ptr = track_ptr->next;
    }
    
    // Close file
    midi.close();
}

void MIDI_FILE::write_header(std::ofstream *midi, unsigned char format, int number_of_tracks, int ticks_per_quarter_note)
{
    // Header chunk
    *midi << "MThd";
    *midi << '\0' << '\0' << '\0' << '\6';
    *midi << '\0' << format;
    *midi << (unsigned char) (number_of_tracks >> 8) << (unsigned char) (number_of_tracks % 256);
//    *midi << (char) ((tempo >> 8) | TIME_DIVISION) << (char) (tempo % 256);
    *midi << (unsigned char) (ticks_per_quarter_note >> 8) << (unsigned char) (ticks_per_quarter_note % 256);
}

void MIDI_FILE::write_track(std::ofstream *midi, MIDI_TRACK *track)
{
    // size = each event (length of time + 3 bytes)
    long chunk_size = 0;
    
    // Go through all the events
    MIDI_TRACK_EVENT *event_ptr = track->first_event;
    
    while(event_ptr != NULL)
    {
        // Calculate how many bytes are needed to write delta_time
        if(event_ptr->delta_time == 0)
        {
            // In case delta_time is 0, then it costs 4 bytes
            chunk_size += 4;
        }
        else
        {
            // Otherwise, this strange calculation, which just works
            int bits_needed = log2(event_ptr->delta_time) + 1;
            // {DELTA TIME} (var) + {TYPE & CHANNEL} (1 byte) + {PARAMETERS} (2 bytes)
            chunk_size += bits_needed / 7 + ((bits_needed % 7) > 0 || bits_needed == 0) + 3;
        }
        
        // If parameter 2 is empty, size is one less
        if(event_ptr->parameter_2 == 0) chunk_size --;
        
        // Next event
        event_ptr = event_ptr->next;
    }
    
    chunk_size += 4; // End of track bit.
    chunk_size += 3; // Instrument part.
    
    // Beginning of track
    *midi << "MTrk";
    
    // Write length of chunk
    *midi << (char) ((chunk_size >> 24) % 256);
    *midi << (char) ((chunk_size >> 16) % 256);
    *midi << (char) ((chunk_size >> 8) % 256);
    *midi << (char) (chunk_size % 256);
    
    // Write instrument
    *midi << (unsigned char) 0;
    *midi << (unsigned char) (192 | track->channel); // TODO: implement better
    *midi << (unsigned char) (track->instrument % 128);
    
    // Write all events
    event_ptr = track->first_event;
    
    while(event_ptr != NULL)
    {
        write_event(midi, event_ptr);
        event_ptr = event_ptr->next;
    }
    
    // End of track
    *midi << (char) 1 << (char) 255 << (char) 47 << (char) 0;
}

void MIDI_FILE::write_event(std::ofstream *midi, MIDI_TRACK_EVENT *event)
{
    if(event->type < MIDI_T_NOTE_OFF || event->type > MIDI_T_PITCH_BEND) return; // TODO implement better
    
    // Delta time (variable-length)
    if(event->delta_time == 0)
    {
        *midi << (char) 0;
    }
    else
    {
        int bits_needed = log2(event->delta_time) + 1;
        int length = bits_needed / 7 + ((bits_needed % 7) > 0 || bits_needed == 0);
        unsigned char delta[length];
        memset(delta, (unsigned char) 0, length);
        
        for(int i = 0;i < length;i ++)
        {
            if(i != length - 1) delta[i] |= 128;
            delta[i] |= (event->delta_time >> (7 * (length - 1 - i))) % 128;
            
            *midi << delta[i];
        }
    }
    
    // Type (4 bits) & MIDI Channel (4 bits)
    *midi << (char) (((event->type % 16) << 4) | (event->channel % 16));
    
    // Parameters (2 bytes)
    *midi << event->parameter_1;
    if(event->parameter_2 != '\0') * midi << event->parameter_2;
}

MIDI_FILE::~MIDI_FILE()
{
    // Free tracklist memory
    MIDI_TRACKLIST *track_ptr = first_track;
    
    while(track_ptr != NULL)
    {
        // Free the memory!
        free(track_ptr);
        
        // Go to the next tracklist element
        track_ptr = track_ptr->next;
    }
}


MIDI_TRACK::MIDI_TRACK(int channel, unsigned char instrument)
{
    // Set values for channel and instrument
    this->channel = channel;
    this->instrument = instrument;
    
    // Set the pointers to the first and last event to NULL
    first_event = NULL;
    last_event = NULL;
}

void MIDI_TRACK::add_event(MIDI_EVENT *event)
{
    // Create a new midi_track_event element
    MIDI_TRACK_EVENT *element = (MIDI_TRACK_EVENT*) malloc(sizeof(MIDI_TRACK_EVENT));
    
    // Give it the right values
    element->delta_time =   event->delta_time;
    element->type =         event->type;
    element->channel =      channel; // event->channel; // TODO: look carefully at this
    element->parameter_1 =  event->parameter_1;
    element->parameter_2 =  event->parameter_2;
    
    element->next = NULL;
    element->previous = last_event;
    
    // If there was a last element (track was non-empty), then set the previous' next to the new element
    if(last_event != NULL) last_event->next = element;
    
    // If the track was empty, then this is the first event
    if(first_event == NULL) first_event = element;
    
    // Set the last event to this element
    last_event = element;
}

MIDI_TRACK::~MIDI_TRACK()
{
    // Free eventlist memory
    MIDI_TRACK_EVENT *event_ptr = first_event;
    
    while(event_ptr != NULL)
    {
        // Free the memory!
        free(event_ptr);
        
        // Go to the next tracklist element
        event_ptr = event_ptr->next;
    }
}