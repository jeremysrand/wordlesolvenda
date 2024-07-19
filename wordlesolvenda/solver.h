//
//  solver.h
//  wordlesolvenda
//
//  Created by Jeremy Rand on 2024-07-17.
//

#ifndef solver_h
#define solver_h

#include <TYPES.h>
#include <stdint.h>


// Defines

#define WORD_LEN 5
#define MAX_GUESSES 6


// Types

typedef enum tVariant {
    NYT_VARIANT,
    CQ2_VARIANT,
} tVariant;

typedef enum tLetterState {
    NOT_IN_WORD,
    IN_WORD_AT_POS,
    IN_WORD_OTHER_POS,
    
    MAX_LETTER_STATE
} tLetterState;

typedef struct tValidStates {
    BOOLEAN validStates[WORD_LEN][MAX_LETTER_STATE];
} tValidStates;


// API

extern void initSolver(tVariant variant);
extern void resetSolver(void);
extern void deinitSolver(void);

const char * nextGuess(const tLetterState * states);
uint16_t numRemainingWords(void);
void getValidStates(tValidStates *states);

#endif /* solver_h */
