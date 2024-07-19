//
//  words.h
//  wordlesolve
//
//  Created by Jeremy Rand on 2022-07-21.
//

#ifndef words_h
#define words_h

#include <stdint.h>


// Types

typedef struct tWordData {
    uint16_t numWords;
    char words[1];
} tWordData;

typedef struct tCountData {
    uint16_t rank[1];
} tCountData;


// Declarations

extern tWordData nytWordData;
extern tCountData nytCountData;

extern tWordData cq2WordData;
extern tCountData cq2CountData;


#endif /* words_h */
