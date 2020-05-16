// Assignment 2 20T1 COMP1511: CS bEats
// beats.c
//
// This program was written by Bai Xu (z5292197)
// on 20/4/2020
//
// Version 1.0.0: Assignment released.
// Implemented the stage 1.


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
// Add any extra #includes your code needs here.

#include "beats.h"

// Add your own #defines here.

////////////////////////////////////////////////////////////////////////

// You don't have to use the provided struct track, you are free to
// make your own struct instead.
// If you use the provided struct track, you will have to add fields
// to store other information.

struct track {
    struct beat *curr;
    struct beat *beats;
};

// You don't have to use the provided struct beat, you are free to
// make your own struct instead.
// If you use the provided struct beat, you may add fields
// to it to store other information.

struct beat {
    // You may choose to add or change fields in this struct.
    struct note *notes;
    struct beat *next;
};

// You don't have to use the provided struct note, you are free to
// make your own struct instead.
// If you use the provided struct note, you add fields
// to it to store other information.

struct note {
    // You may choose to add or change fields in this struct.
    int octave;
    int key;
    struct note *next;
};

// Add any other structs you define here.





// Return a malloced Beat with fields initialized.
Beat create_beat(void) {
    Beat new_beat = malloc(sizeof (struct beat));
    assert(new_beat != NULL);

    new_beat->next = NULL;
    new_beat->notes = NULL;

    // You do not need to change this function, unless you change
    // the implementation of struct beat.

    return new_beat;
}

////////////////////////////////////////////////////////////////////////
//                    functions created by me                         //
////////////////////////////////////////////////////////////////////////

// Create a note
struct note *create_note(int octave, int key) {
    struct note *newNote = malloc(sizeof(struct note));
    newNote->key = key;
    newNote->octave = octave;
    newNote->next = NULL;
    return newNote; 
}

// Compare two notes
int compare_Notes (struct note *a, int octave, int key) {
    if(a->octave == octave) {
        if(a->key > key) {
            return -1;
        } else if (a->key < key) {
            return 1;
        } else {
            return 0;
        }
    } else if (a->octave < octave) {
        return 1;
    } else {
        return -1;
    }
}

// Print a note
void print_note(struct note *inputNote) {
    if(inputNote->key < 10) {
        printf("%d 0%d", inputNote->octave, inputNote->key);
    } else {
        printf("%d %d", inputNote->octave, inputNote->key);
    }
}



// Transfer musical letter to key
int transferLetter(char trans) {
    if (trans == 'A') {
        return 0;
    }  else if (trans == 'B') {
        return 2;
    } else if (trans == 'C') {
        return 3;
    } else if (trans == 'D') {
        return 5;
    } else if (trans == 'E') {
        return 7;
    } else if (trans == 'F') {
        return 8;
    } else if (trans == 'G') {
        return 10;
    } else {// Invalid input
        return -1;
    }

}


////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a note to the end of a beat.
int add_note_to_beat(Beat beat, int octave, int key) {

    // Eastimate if the octave and key are valid
    if (octave < 0 || octave > 9 ) {
        return INVALID_OCTAVE;
    } else if ((octave >= 0 && octave <= 9) &&
    (key < 0 || key > 11)) {
        return INVALID_KEY;
    }

    // When the beat is empty.
    if (beat->notes == NULL) {
        beat->notes = create_note(octave, key);
    } else {// When the beat is not empty.

        struct note *curr = beat->notes;
        while(curr->next != NULL) {
            curr = curr->next;
        }
        // eastimate whether the note is the highest one.
        if (compare_Notes(curr, octave, key) == 1) {
            curr->next = create_note(octave, key);
        } else {
            return NOT_HIGHEST_NOTE;
        }
    }
    return VALID_NOTE;
}

// Print the contents of a beat.
void print_beat(Beat beat) {

    
    // When beat is empty
    if (beat->notes == NULL) {
        printf("\n");
    } else {// When beat is not empty
        struct note *curr = beat->notes;
        while(curr != NULL) {
            //formatting the note printing
            if(curr->next != NULL) {
                print_note(curr);
                printf(" | ");
            } else {
                print_note(curr);
                printf("\n");
            }
            curr = curr->next;
        }
    }
    
}

// Count the number of notes in a beat that are in a given octave.
int count_notes_in_octave(Beat beat, int octave) {
    int count = 0;
    // Beat is empty
    if (beat->notes == NULL) {
        return 0;
    } else{// Beat is not empty
        struct note *curr = beat->notes;
        while(curr != NULL) {
            if(curr->octave == octave) {
                count++;
            }
            curr = curr->next;
        }
    }
    return count;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Return a malloced track with fields initialized.
Track create_track(void) {
    struct track *newTrack = malloc(sizeof(struct track));
    newTrack->curr = NULL;
    newTrack->beats = NULL;
    return newTrack;
}

// Add a beat after the current beat in a track.
void add_beat_to_track(Track track, Beat beat) {
    
    // Track has no current selected beat.
    // No need to eastimate if situation when
    // the track is empty since the operation is
    // the same.
    if (track->curr == NULL) {
        beat->next = track->beats;
        track->beats = beat;
        
    } else { // Track has current selected beat
        Beat temporary = track->curr->next;
        track->curr->next = beat;
        beat->next = temporary;
    }
    return;
}

// Set a track's current beat to the next beat.
int select_next_beat(Track track) {

    // Track don't have any beat
    if (track->beats == NULL) {
        return TRACK_STOPPED;
    }

    // Track is stopped
    if (track->curr == NULL) {
        track->curr = track->beats;
        return TRACK_PLAYING;
    }

    // selected beat is the last one
    if (track->curr->next == NULL) {
        track->curr = NULL;
        return TRACK_STOPPED;
    }

    // select next beat
    track->curr = track->curr->next;
    return TRACK_PLAYING;
}

// Print the contents of a track.
void print_track(Track track) {
    
    // No beats in track
    if (track->beats == NULL) {
        return;
    }

    // Print track
    Beat current = track->beats;
    int count = 1;
    while(current != NULL) {
        // In the position where the beat is selected.
        if (current == track->curr) {
            printf(">[%d] ", count);
            print_beat(current);
           /*  // Beat is not empty
            if (current->notes != NULL) {
                // Lopp through the notes
                struct note *innerCurr = current->notes;
                while(innerCurr != NULL) {
                    // In the last note
                    if (innerCurr->next == NULL) {
                        printf(" ")
                    }
                }
            }
 */
        } else {// The beat is not being selected
            printf(" [%d] ", count);
            print_beat(current);
        }
        current = current->next;
        count ++;
    }
    return;
}

// Count beats after the current beat in a track.
int count_beats_left_in_track(Track track) {
    // count the number of beats
    int count = 0;
    // Point to the first valid beat
    Beat current;
    
    // There are no selected beat
    if (track->curr == NULL) {
        current = track->beats;
        while(current != NULL) {
            count++;
            current = current->next;
        }
        return count;
    } else { //Count all element in the track
        current = track->curr->next;
        while (current != NULL) {
            count++;
            current = current->next;
        } // There is no need for the situation when the track 
        // is empty since if the track is empty, the loop will not happen.
        return count;
    }


    return 0;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Free the memory of a beat, and any memory it points to.
void free_beat(Beat beat) {
    struct note *curr = beat->notes;
    struct note *before = NULL;
    free(beat);
    while(curr != NULL) {
        before = curr;
        curr = curr->next;
        free(before);
    }
    return;
}

// Free the memory of a track, and any memory it points to.
void free_track(Track track) {
    Beat curr = track->beats;
    Beat before = NULL;
    free(track);
    while(curr != NULL) {
        before = curr;
        curr = curr->next;
        free_beat(before);
    }
    return;
}

// Remove the currently selected beat from a track.
int remove_selected_beat(Track track) {
    // Track is stopped
    if (track->curr == NULL) {
        return TRACK_STOPPED;
    }

    // Track is playing;
    
    // If Track is empty
    if (track->beats == NULL) {
        return TRACK_STOPPED;
    }

    // If the current beat is the first 
    // beat in the track, This situation also
    // include there are only one element in 
    // the track.
    if (track->curr == track->beats) {
        track->beats = track->beats->next;
        free_beat(track->curr);
        track->curr = track->beats;
        // eastimate if the track is empty
        if (track->curr == NULL) {
            return TRACK_STOPPED;
        }
        return TRACK_PLAYING;
    }
    


    // Otherwise
    Beat before = track->beats;
    
    while (before->next != track->curr) {
        before = before->next;
    }

    before->next = track->curr->next;
    free_beat(track->curr);
    track->curr = before->next;
    
    // eastimate if track is playing
    if (track->curr == NULL) {
        return TRACK_STOPPED;
    } else {
        return TRACK_PLAYING;
    }
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add note to beat, given its 'musical notation'.
int add_musical_note_to_beat(Beat beat, char *musical_notation) {
    // If music notation don't have any character
    if (musical_notation[0] == '\0') {
        return INVALID_MUSICAL_NOTE;
    }

    int octave = musical_notation[0] - '0';
    int key = transferLetter(musical_notation[1]);

    // If input letter is not valid
    if (key == -1) {
        return INVALID_MUSICAL_NOTE;
    }

    // If the input music notation is invalid
    if (octave < 0 || octave > 9 ) {
        return INVALID_MUSICAL_NOTE;
    } else if ((octave >= 0 && octave <= 9) &&
    (key < 0 || key > 11)) {
        return INVALID_MUSICAL_NOTE;
    }

    // There are '#' in the input character
    if (musical_notation[2] == '#') {
        int i = 2;
        int count = 0;
        while(musical_notation[i] != '\0') {
            // Invalid input after '#'
            if (musical_notation[i] != '#') {
                return INVALID_MUSICAL_NOTE;
            }
            count++;
            i++;
        } // Have got the number of "#"

        // Adding the number of "#" into the
        // ocatave and key
        while (count>0) {
            if (key<11) {
                key++;
            } else {
                octave++;
                key = 0;
            }
            // Invalid input
            if (octave > 9) {
                return INVALID_MUSICAL_NOTE;
            }
            count--;
        }
    } else if (musical_notation[2] == '\0') {
        //Do nothing.
    } else {
        return INVALID_MUSICAL_NOTE;
    }


    // If beat has no note in it
    if (beat->notes == NULL) {
        add_note_to_beat(beat, octave, key);
        return VALID_NOTE;
    }

    // If the new note is smaller than the first
    // note in beat
    if (compare_Notes(beat->notes, octave, key) == -1) {
        struct note *newNote = create_note(octave, key);
        newNote->next = beat->notes;
        beat->notes = newNote;
        return VALID_NOTE;
    } else if (compare_Notes(beat->notes, octave, key) == 1 &&
    beat->notes->next == NULL) { // only one note in the beat
        add_note_to_beat(beat, octave, key);
        return VALID_NOTE;
    } else if (compare_Notes(beat->notes, octave, key) == 0) { // Notes are the same
        return INVALID_MUSICAL_NOTE;
    }

    
    

    struct note *curr = beat->notes->next;
    struct note *before = beat->notes;
    // Multiple notes in the beat
    while (curr != NULL) {
        // same note in the beat
        if (compare_Notes(curr, octave, key) == 0 ||
        compare_Notes(before, octave, key) == 0) {
            return INVALID_MUSICAL_NOTE;
        } else if (compare_Notes(before, octave, key) == 1 &&
        compare_Notes(curr, octave, key) == -1) {
            struct note *newNote = create_note(octave, key);
            newNote->next = curr;
            before->next = newNote;
            return VALID_NOTE;
        }
        before = before->next;
        curr = curr->next;
        
    }

    // New note is the highest note
    if (curr == NULL) {
        add_note_to_beat(beat, octave, key);
    }

    return VALID_NOTE;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Cut a range of beats to the end of a track.
void cut_range_to_end(Track track, int range_length) {
    // Invalid input of range length
    if (range_length < 1) {
        return;
    }

    // Only one beat in the track
    if (track->beats->next == NULL) {
        return;
    }

    // Track is stop
    if (track->curr == NULL) {
        return;
    }
    // In this stage, track is certainly 
    // playing and have more than one beats
    // in it

    Beat current = track->curr;
    Beat endofTrack = track->beats;
    // First beat has been selected
    if (track->curr == track->beats) {
        // Go head for i beats to the end 
        // of the range
        int i = range_length;
        while(i > 1) {
            
            // If there are fewer than "range_length"
            // Beats in the range
            if(current->next == NULL) {
                return;
            } // Exit the function

            current = current->next;
            i --;
        }
        
        // Range covered the beats to the end.
        if (current->next == NULL) {
            return;
        }

        // Loop through the track to the end
        while (endofTrack->next != NULL) {
            endofTrack = endofTrack->next;
        }

        // Cut the range to the end
        track->beats = current->next;
        current->next = NULL;
        endofTrack->next = track->curr;
        return;
    }

    // Multiple beats in the track and 
    // and selected beat is not in the 
    // first place

    Beat before = track->beats;
    while (before->next != track->curr) {
        before = before->next;
    }

    int i = range_length;
    while (i > 1) {
        
        // If there are fewer than "range_length"
        // Beats in the range
        if(current->next == NULL) {
            return;
        } // Exit the function

        current = current->next;
        i --;
    }

    if (current->next == NULL) {
        return;
    } //Exit the function
    
    while (endofTrack->next != NULL) {
    
    endofTrack = endofTrack->next;
    
    }    
    before->next = current->next;
    current->next = NULL;
    endofTrack->next = track->curr;

    return;
}

// Reverse a list of beats within a range of a track.
int reverse_range(Track track, int range_length) {
    // When track is empty
    if (track->beats == NULL) {
        return 0;
    }

    // When track only have one beat
    if (track->beats->next == NULL) {
        return 0;
    }

    // Invalid input of range length
    if (range_length <= 1) {
        return 0;
    }

    
    // The first beats has been selected.
    if (track->beats == track->curr) {
        Beat tail = track->beats;
        int i = range_length;
        int count = 0;
        // Moving tail to the end of the track
        while (i > 1 && tail->next != NULL) {
            tail = tail->next;
            i --;
            count ++ ;
        }

        

        Track newTrack = create_track();
        Beat currentA = track->beats;
        int j = 0;
        while(j <= count) {
            int k = 0;
            while(k < count - j) {
                currentA = currentA->next;
                k++;
            }
            add_beat_to_track(newTrack, currentA);
            currentA = track->beats;
            j++;
        } 

        int x = 0;
        while(x <= count) {
            remove_selected_beat(track);
            x++;
        }
        
        // When track is empty
        if (track->beats == NULL) {
            track->beats = newTrack->beats;
            select_next_beat(track);

        } else { //When track is not empty
            Beat tailA = newTrack->beats;
            while (tailA->next != NULL) {
                tailA = tailA->next;
            }
            tailA->next = track->curr;
            track->beats = newTrack->beats;
        }

        

        return count;
    }

    return 0;
}
