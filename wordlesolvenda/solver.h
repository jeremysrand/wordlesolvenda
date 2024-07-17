//
//  solver.h
//  wordlesolvenda
//
//  Created by Jeremy Rand on 2024-07-17.
//

#ifndef solver_h
#define solver_h

#undef FIND_BEST_START_WORD

extern void initSolver(void);
extern void deinitSolver(void);

#ifndef FIND_BEST_START_WORD
extern void solvePuzzle(void);
#else
extern void findBestStartWord(void);
#endif

#endif /* solver_h */
