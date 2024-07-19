//
//  solver.h
//  wordlesolvenda
//
//  Created by Jeremy Rand on 2024-07-17.
//

#ifndef solver_h
#define solver_h

#undef FIND_BEST_START_WORD

#define WORD_LEN 5
#define MAX_GUESSES 6

typedef enum tLetterState {
    NOT_IN_WORD,
    IN_WORD_AT_POS,
    IN_WORD_OTHER_POS,
} tLetterState;

extern void initSolver(void);
extern void resetSolver(void);
extern void deinitSolver(void);

const char * nextGuess(const tLetterState * states);
int numRemainingWords(void);

#endif /* solver_h */
