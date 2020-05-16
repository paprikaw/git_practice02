// Assignment 2 20T1 COMP1511: CS bEats
// test_beats.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0: Assignment released.
#include <stdio.h>
#include <stdlib.h>

#include "test_beats.h"
#include "beats.h"


// Test function for `add_note_to_beat`
int test_add_note_to_beat(void) {
    // Test 1: Rejecting negative inputs.
    Beat test_beat = create_beat();
    if (add_note_to_beat(test_beat, -1, -1) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, -1, 0) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, -1) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Rejecting overrange inputs

    if (add_note_to_beat(test_beat, 15, 1) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 15, 15) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, 15) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 3: Adding the valid notes in the beats

    add_note_to_beat(test_beat, 3, 3);
    if (add_note_to_beat(test_beat, 4, 3) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 4, 4) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 5, 5) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 4: Rejecting the notes which is not highest

    if (add_note_to_beat(test_beat, 4, 5) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 5, 5) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    } 
    if (add_note_to_beat(test_beat, 5, 4) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    return MEETS_SPEC;
}

// Test function for `count_notes_in_octave`
int test_count_notes_in_octave(void){
    // Test 1: Counting invalid octaves.
    Beat test_beat = create_beat();
    add_note_to_beat(test_beat, 1, 1);
    if (count_notes_in_octave(test_beat, -1) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 11) != 0) {
        return DOES_NOT_MEET_SPEC;
    }


    // Test 2: No similar octave in beat
    if (count_notes_in_octave(test_beat, 3) != 0) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Counting valid octave in beat
    if (count_notes_in_octave(test_beat, 1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    return MEETS_SPEC;
}

// Test function for `add_beat_to_track`
int test_add_beat_to_track(void){
    
    Track testTrack = create_track();
    Beat testBeat = create_beat();
    add_note_to_beat(testBeat, 3, 4);
    add_beat_to_track(testTrack, testBeat);
    // One beat remained
    
    // Test 1: Function doesn't add any beat 
    // into the track

    if (count_beats_left_in_track(testTrack) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: If function change the current beat
    Beat testBeatA = create_beat();
    add_note_to_beat(testBeatA, 1, 1);
    add_beat_to_track(testTrack, testBeatA);
    if (count_beats_left_in_track(testTrack) != 2) {
        return DOES_NOT_MEET_SPEC;
    } // Two beats remained.


    // Test 3: Remove the First beat
    remove_selected_beat(testTrack);
    Beat testBeatB = create_beat();
    add_note_to_beat(testBeatB, 2, 1);
    add_beat_to_track(testTrack, testBeatB); 
    if (count_beats_left_in_track(testTrack) !=3) {
        return DOES_NOT_MEET_SPEC;
    } // Three beats remained

    // Test 4: Remove the last beat
    remove_selected_beat(testTrack);
    remove_selected_beat(testTrack);
    Beat testBeatC = create_beat();
    add_note_to_beat(testBeatC, 2, 1);
    add_beat_to_track(testTrack, testBeatC);  
    if (count_beats_left_in_track(testTrack) != 4) {
        return DOES_NOT_MEET_SPEC;
    } // Four beats remained


    return MEETS_SPEC;
}

// Test function for `remove_selected_beat`
int test_remove_selected_beat(void){
    
    // Create a track with two beats
    Track testTrack = create_track();
    Beat testBeat = create_beat();
    Beat testBeatA = create_beat();
    add_note_to_beat(testBeat, 3, 4);
    add_note_to_beat(testBeatA, 3, 3);
    add_beat_to_track(testTrack, testBeat);
    add_beat_to_track(testTrack, testBeatA);
    // Two beats remained
    
    // Test 1: Function doesn't remove the beat
    select_next_beat(testTrack);
    remove_selected_beat(testTrack);
    if (count_beats_left_in_track(testTrack) != 0) {
        return DOES_NOT_MEET_SPEC;
    } //one beat remain


    // Test 2: Remove the first beat
    Beat testBeatB = create_beat();
    add_note_to_beat(testBeatB, 5, 6);
    add_beat_to_track(testTrack, testBeatB);
    remove_selected_beat(testTrack);
    if (count_beats_left_in_track(testTrack) != 0) {
        return DOES_NOT_MEET_SPEC;
    } // one beat remain
    

    // Test 3: Remove the last beat.
    Beat testBeatC = create_beat();
    add_note_to_beat(testBeatC, 6, 6);
    add_beat_to_track(testTrack,testBeatC);
    select_next_beat(testTrack);
    remove_selected_beat(testTrack); 
    if (count_beats_left_in_track(testTrack) != 1) {
        return DOES_NOT_MEET_SPEC;
    } // One beat remain


    // Test 4: Remove the only one beat in
    // the track
    select_next_beat(testTrack);
    remove_selected_beat(testTrack);
    if (count_beats_left_in_track(testTrack) != 0) {
        return DOES_NOT_MEET_SPEC;
    } // No beat in the track

    // There is no need to test if the function
    // would delete multiple beat in the track
    // since above tests has covered that. 

    return MEETS_SPEC;
}

// Test function for `add_musical_note_to_beat`
int test_add_musical_note_to_beat(void){
    // Test 1: invalid input
    Beat beat = create_beat();
    if (add_musical_note_to_beat(beat, "3G?") != INVALID_MUSICAL_NOTE ||
    add_musical_note_to_beat(beat, "3G#?") != INVALID_MUSICAL_NOTE ||
    add_musical_note_to_beat(beat, "aG") != INVALID_MUSICAL_NOTE ||
    add_musical_note_to_beat(beat, "9G########") != INVALID_MUSICAL_NOTE ||
    add_musical_note_to_beat(beat, "3a") != INVALID_MUSICAL_NOTE ||
    add_musical_note_to_beat(beat, "3G##?") != INVALID_MUSICAL_NOTE ||
    add_musical_note_to_beat(beat, "11G") != INVALID_MUSICAL_NOTE ||
    add_musical_note_to_beat(beat, "3H") != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Valid input
    
    // One note in the beat and add a note before it;
    if (add_musical_note_to_beat(beat, "3G") != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    if (add_musical_note_to_beat(beat, "1G") != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    // One note in the beat and add a note after it;
    Beat beatA = create_beat();
    if (add_musical_note_to_beat(beatA, "3G#") != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    if (add_musical_note_to_beat(beat, "7G") != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    if (add_musical_note_to_beat(beat, "4A") != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    


    // Test 3: Add the musical note correctly
    if (count_notes_in_octave(beatA, 4) != 2) {
        return DOES_NOT_MEET_SPEC;
    }

    if (count_notes_in_octave(beat, 1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }


    return MEETS_SPEC;
}
