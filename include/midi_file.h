#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

#define MIDI_T_NOTE_OFF 8
#define MIDI_T_NOTE_ON  9
#define MIDI_T_NOTE_AFTERTOUCH 10
#define MIDI_T_CONTROLLER 11
#define MIDI_T_PROGRAM_CHANGE 12
#define MIDI_T_CHANNEL_AFTERTOUCH 13
#define MIDI_T_PITCH_BEND 14

#define MIDI_CHANNEL_0 0
#define MIDI_CHANNEL_1 1
#define MIDI_CHANNEL_2 2
#define MIDI_CHANNEL_3 3
#define MIDI_CHANNEL_4 4
#define MIDI_CHANNEL_5 5
#define MIDI_CHANNEL_6 6
#define MIDI_CHANNEL_7 7
#define MIDI_CHANNEL_8 8
#define MIDI_CHANNEL_9 9
#define MIDI_CHANNEL_10 10
#define MIDI_CHANNEL_11 11
#define MIDI_CHANNEL_12 12
#define MIDI_CHANNEL_13 13
#define MIDI_CHANNEL_14 14
#define MIDI_CHANNEL_15 15

// Pianoforte
#define MIDI_I_GRAND_PIANO 0
#define MIDI_I_BRITE_PIANO 1
#define MIDI_I_EL_GRAND_PIANO 2
#define MIDI_I_HONKY_TONK_PIANO 3
#define MIDI_I_EL_PIANO_1 4
#define MIDI_I_EL_PIANO_2 5
#define MIDI_I_HARPICHORD 6
#define MIDI_I_CLAVINET 7

// Chromatic percussion
#define MIDI_I_CELESTA 8
#define MIDI_I_GLOCKEN 9
#define MIDI_I_MUSICBOX 10
#define MIDI_I_VIBES 11
#define MIDI_I_MARIMBA 12
#define MIDI_I_XYLOPHONE 13
#define MIDI_I_TUBULAR_BELLS 14
#define MIDI_I_DULCIMER 15

// Organ
#define MIDI_I_DRAWBAR_ORGAN 16
#define MIDI_I_PERCUSSIVE_ORGAN 17
#define MIDI_I_ROCK_ORGAN 18
#define MIDI_I_CHURCH_ORGAN 19
#define MIDI_I_REED_ORGAN 20
#define MIDI_I_ACCORDION 21
#define MIDI_I_HARMONICA 22
#define MIDI_I_TANGO_ACCORDION 23

// Guitar
#define MIDI_I_NYLON_GUITAR 24
#define MIDI_I_STEEL_GUITAR 25
#define MIDI_I_JAZZ_GUITAR 26
#define MIDI_I_CLEAN_GUITAR 27
#define MIDI_I_MUTE_GUITAR 28
#define MIDI_I_OVERDRIVE_GUITAR 29
#define MIDI_I_DIST_GUITAR 30
#define MIDI_I_GUITAR_HARMONICS 31

// Bass
#define MIDI_I_ACOUSTIC_BASS 32
#define MIDI_I_FINGERED_BASS 31
#define MIDI_I_PICK_BASS 33
#define MIDI_I_FRETLESS_BASS 35
#define MIDI_I_SLAP_BASS_1 36
#define MIDI_I_SLAP_BASS_2 37
#define MIDI_I_SYNTH_BASS_1 38
#define MIDI_I_SYNTH_BASS_2 39

// Strings
#define MIDI_I_VIOLIN 40
#define MIDI_I_VIOLA 41
#define MIDI_I_CELLO 42
#define MIDI_I_CONTRABASS 43
#define MIDI_I_TREMOLO_STRINGS 44
#define MIDI_I_PIZZICATO_STRING 45
#define MIDI_I_HARP 46
#define MIDI_I_TAMPANI 48

// Ensemble
#define MIDI_I_STRINGS_1 48
#define MIDI_I_STRINGS_2 49
#define MIDI_I_SYNTH_STRINGS_1 50
#define MIDI_I_SYNTH_STRINGS_2 51
#define MIDI_I_CHOIR_AAH 52
#define MIDI_I_VOICE_OOH 53
#define MIDI_I_SYNTH_VOICE 54
#define MIDI_I_ORCHASTRAL_HIT 55

// Brass
#define MIDI_I_TRUMPET 56
#define MIDI_I_TROMBONE 57
#define MIDI_I_TUBA 58
#define MIDI_I_MUTE_TRUMPET 59
#define MIDI_I_FRENCH_HORN 60
#define MIDI_I_BRASS_SECTION 61
#define MIDI_I_SYNTH_BRASS_1 62
#define MIDI_I_SYNTH_BRASS_2 63

// Reed
#define MIDI_I_SOPRANO_SAX 64
#define MIDI_I_ALTO_SAX 65
#define MIDI_I_TENOR_SAX 66
#define MIDI_I_BARITON_SAX 67
#define MIDI_I_OBOE 68
#define MIDI_I_ENGLISH_HORN 69
#define MIDI_I_BASSOON 70
#define MIDI_I_CLARINET 71

// Flutes
#define MIDI_I_PICCOLO 72
#define MIDI_I_FLUTE 73
#define MIDI_I_RECORDER 74
#define MIDI_I_PANFLUTE 75
#define MIDI_I_BOTTLE 76
#define MIDI_I_SHAKUHACHI 77
#define MIDI_I_WHISTLE 78
#define MIDI_I_OCARINA 79

// Lead synth
#define MIDI_I_SQUARE_LEAD 80
#define MIDI_I_SAWTOOTH_LEAD 81
#define MIDI_I_CALIOPE_LEAD 82
#define MIDI_I_CHIFF_LEAD 83
#define MIDI_I_CHARANG_LEAD 84
#define MIDI_I_VOICE_LEAD 85
#define MIDI_I_FIFTH_LEAD 86
#define MIDI_I_BASS_LEAD 87

// Synth pads
#define MIDI_I_NEW_AGE_PAD 88
#define MIDI_I_WARM_PAD 89
#define MIDI_I_POLY_SYNTH_PAD 90
#define MIDI_I_CHOIR_PAD 91
#define MIDI_I_BOWED_PAD 92
#define MIDI_I_METAL_PAD 93
#define MIDI_I_HALO_PAD 94
#define MIDI_I_SWEEP_PAD 95

// Effects
#define MIDI_I_RAIN 96
#define MIDI_I_SOUNDTRACK 97
#define MIDI_I_CRYSTAL 98
#define MIDI_I_ATMOSPHERE 99
#define MIDI_I_BRIGHT 100
#define MIDI_I_GOBLINS 101
#define MIDI_I_ECHOES 102
#define MIDI_I_SCI_FI 103

// Ethnic
#define MIDI_I_SITAR 104
#define MIDI_I_BANJO 105
#define MIDI_I_SHAMISEN 106
#define MIDI_I_KOTO 107
#define MIDI_I_KALIMBA 108
#define MIDI_I_BAGPIPE 109
#define MIDI_I_FIDDLE 110
#define MIDI_I_SHANAI 111
#define MIDI_I_TINKLE_BELL 112
#define MIDI_I_AGAGO 113
#define MIDI_I_STEEL_DRUM 114
#define MIDI_I_WOODBLOCK 115
#define MIDI_I_TAIKO_DRUM 116
#define MIDI_I_MELODIC_TOM 117
#define MIDI_I_SYNTH_DRUM 118
#define MIDI_I_REV_CYMBAL 119

// Sound effects
#define MIDI_I_FRET_NOISE 120
#define MIDI_I_BREATH_NOISE 121
#define MIDI_I_SEASHORE 122
#define MIDI_I_TWEET 123
#define MIDI_I_TELEPHONE 124
#define MIDI_I_HELICOPTER 125
#define MIDI_I_APPLAUSE 126
#define MIDI_I_GUNSHOT 127

// Drum kits
#define MIDI_I_DRUM_STANDARD 0
#define MIDI_I_DRUM_ROOM 8
#define MIDI_I_DRUM_ROCK 16
#define MIDI_I_DRUM_ELECTRONIC 24
#define MIDI_I_DRUM_ANALOG 25
#define MIDI_I_DRUM_JAZZ 32
#define MIDI_I_DRUM_BRUSH 40
#define MIDI_I_DRUM_CLASSICAL 48

// Drum notes
#define MIDI_D_ACOUSTIC_BASS_DRUM 35
#define MIDI_D_BASS_DRUM 36
#define MIDI_D_SIDE_STICK 37
#define MIDI_D_ACOUSTIC_SNARE 38
#define MIDI_D_HAND_CLAP 39
#define MIDI_D_ELECTRIC_SNARE 40
#define MIDI_D_LOW_FLOOR_TOM 41
#define MIDI_D_CLOSED_HI_HAT 42
#define MIDI_D_HIGH_FLOOR_TOM 43
#define MIDI_D_PEDAL_HI_HAT 44
#define MIDI_D_LOW_TOM 45
#define MIDI_D_OPEN_HI_HAT 46
#define MIDI_D_LOW_MID_TOM 47
#define MIDI_D_HI_MID_TOM 48
#define MIDI_D_CRASH_CYMBAL_1 49
#define MIDI_D_HIGH_TOM 50
#define MIDI_D_RIDE_CYMBAL_1 51
#define MIDI_D_CHINESE_CYMBAL 52
#define MIDI_D_RIDE_BELL 53
#define MIDI_D_TAMBOURINE 54
#define MIDI_D_SPLASH_CYMBAL 55
#define MIDI_D_COWBELL 56
#define MIDI_D_CRASH_CYMBAL_2 57
#define MIDI_D_VIBRASLAP 58
#define MIDI_D_RIDE_CYMBAL_2 59
#define MIDI_D_HI_BONGO 60
#define MIDI_D_LOW_BONGO 61
#define MIDI_D_MUTE_HI_CONGA 62
#define MIDI_D_OPEN_HI_CONGA 63
#define MIDI_D_LOW_CONGA 64
#define MIDI_D_HIGH_TIMBALE 65
#define MIDI_D_LOW_TIMBALE 66
#define MIDI_D_HIGH_AGOGO 67
#define MIDI_D_LOW_AGOGO 68
#define MIDI_D_CABASA 69
#define MIDI_D_MARACAS 70
#define MIDI_D_SHORT_WHISTLE 71
#define MIDI_D_LONG_WHISTLE 72
#define MIDI_D_SHORT_GUIRO 73
#define MIDI_D_LONG_GUIRO 74
#define MIDI_D_CLAVES 75
#define MIDI_D_HI_WOOD_BLOCK 76
#define MIDI_D_LOW_WOOD_BLOCK 77
#define MIDI_D_MUTE_CUICA 78
#define MIDI_D_OPEN_CUICA 79
#define MIDI_D_MUTE_TRIANGLE 80
#define MIDI_D_OPEN_TRIANGLE 81

struct MIDI_EVENT
{
    int delta_time;
    int type;
    int channel;
    unsigned char parameter_1;
    unsigned char parameter_2;
};

struct MIDI_TRACK_EVENT
{
    int delta_time;
    int type;
    int channel;
    unsigned char parameter_1;
    unsigned char parameter_2;
    
    MIDI_TRACK_EVENT *next;
    MIDI_TRACK_EVENT *previous;
};

class MIDI_TRACK
{
    public:

    MIDI_TRACK(int, unsigned char);
    ~MIDI_TRACK();
    
    MIDI_TRACK_EVENT *first_event;
    MIDI_TRACK_EVENT *last_event;

    unsigned char instrument;
    int channel;

    void add_event(MIDI_EVENT*);
};

struct MIDI_TRACKLIST
{
    MIDI_TRACK *track;
    
    MIDI_TRACKLIST *next;
    MIDI_TRACKLIST *previous;
};

class MIDI_FILE
{
    public:
    
    MIDI_FILE(unsigned char, int);
    ~MIDI_FILE();
    
    unsigned char format;
    int ticks_per_quarter_note;
    
    void add_track(MIDI_TRACK*);
    void save(char*);
    
    private:
    
    int number_of_tracks;
    
    MIDI_TRACKLIST *first_track;
    MIDI_TRACKLIST *last_track;
    
    static void write_header(std::ofstream*, unsigned char, int, int);
    static void write_event(std::ofstream*, MIDI_TRACK_EVENT*);
    static void write_track(std::ofstream*, MIDI_TRACK*);
};