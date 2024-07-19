/*
 * main.c
 * wordlesolvenda
 *
 * Created by Jeremy Rand on 2024-07-17.
 * Copyright (c) 2024 ___ORGANIZATIONNAME___. All rights reserved.
 *
 */


#pragma nda NDAOpen NDAClose NDAAction NDAInit -1 0x03FF "  Wordle Solver\\H**"


#include <orca.h>
#include <GSOS.h>
#include <QuickDraw.h>
#include <Window.h>
#include <Desk.h>
#include <Control.h>
#include <Event.h>
#include <Resources.h>
#include <MiscTool.h>
#include <Memory.h>
#include <Loader.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "solver.h"


// Constants and macros
#define NUM_COLUMNS WORD_LEN
#define NUM_ROWS MAX_GUESSES

#define IS_LETTER_CONTROL(id) (((id) >= WS_RES_BTN_0_0) && ((id) <= WS_RES_BTN_5_4))
#define IS_OK_CONTROL(id) (((id) >= WS_RES_BTN_0_OK) && ((id) <= WS_RES_BTN_5_OK))

#define CONTROL_ROW_COL_TO_ID(row, col) (WS_RES_BTN_0_0 + (col) + ((row) * NUM_COLUMNS))
#define CONTROL_ROW_COL_TO_HANDLE(row, col) GetCtlHandleFromID(winPtr, CONTROL_ROW_COL_TO_ID((row), (col)))
#define CONTROL_ID_TO_ROW(id) (((id) - WS_RES_BTN_0_0) / NUM_COLUMNS)
#define CONTROL_ID_TO_COL(id) (((id) - WS_RES_BTN_0_0) % NUM_COLUMNS)

#define CONTROL_ROW_TO_OK_ID(row) (WS_RES_BTN_0_OK + (row))
#define CONTROL_ROW_TO_OK_HANDLE(row) GetCtlHandleFromID(winPtr, CONTROL_ROW_TO_OK_ID(row))

#define CHAR_TO_BUTTON_STR(ch) ((Pointer)(unsigned long)(((ch) - 'A') + WS_RES_BTN_STR_A))
#define BUTTON_STR_TO_CHAR(buttonStr) ((((long)(buttonStr)) - WS_RES_BTN_STR_A) + 'A')


// Globals

static BOOLEAN ndaActive;
static GrafPortPtr winPtr;
static unsigned int userId;
static unsigned int currentRow;

static char line1[64] = "";
static char line2[64] = "";
static char knownLetters[NUM_COLUMNS];


// Implementation

void NDAClose(void)
{
    if (ndaActive) {
        CloseWindow(winPtr);
        winPtr = NULL;
        ndaActive = FALSE;
    }
    
    ResourceShutDown();
    deinitSolver();
}


void NDAInit(int code)
{
    /* When code is 1, this is tool startup, otherwise tool
     * shutdown.
     */
    
    if (code) {
        ndaActive = FALSE;
        userId = MMStartUp();
    } else {
        if (ndaActive)
            NDAClose();
    }
}


void drawText(void)
{
    Rect frame = {WS_RES_TEXT_1_Y, 0, WS_RES_TEXT_2_Y+WS_RES_TEXT_HEIGHT, WS_RES_WIN_WIDTH};
    EraseRect(&frame);
    PenNormal();
    MoveTo(2*WS_RES_BTN_SPACE_X, WS_RES_TEXT_1_Y + WS_RES_TEXT_HEIGHT);
    DrawCString(line1);
    MoveTo(2*WS_RES_BTN_SPACE_X, WS_RES_TEXT_2_Y + WS_RES_TEXT_HEIGHT);
    DrawCString(line2);
}


#pragma databank 1
void DrawContents(void)
{
    PenNormal();
    DrawControls(GetPort());
    drawText();
}
#pragma databank 0

void setButtonColour(CtlRecHndl ctl, long colour)
{
    HLock((Handle)ctl);
    (*ctl)->ctlColor = (Pointer)colour;
    InvalOneCtlByID(winPtr, (*ctl)->ctlID);
    HUnlock((Handle)ctl);
}

long getButtonColour(CtlRecHndl ctl)
{
    long colour;
    
    HLock((Handle)ctl);
    colour = (long)(*ctl)->ctlColor;
    return colour;
}

void cycleButtonColor(Long id)
{
    CtlRecHndl ctl = GetCtlHandleFromID(winPtr, id);
    HLock((Handle)ctl);
    switch ((int)(unsigned long)((*ctl)->ctlColor)) {
        case WS_RS_BTN_WHITE:
            (*ctl)->ctlColor = (Pointer)WS_RS_BTN_YELLOW;
            break;
            
        case WS_RS_BTN_YELLOW:
            (*ctl)->ctlColor = (Pointer)WS_RS_BTN_GREEN;
            break;
            
        case WS_RS_BTN_GREEN:
            (*ctl)->ctlColor = (Pointer)WS_RS_BTN_WHITE;
            break;
    }
    InvalOneCtlByID(winPtr, id);
    HUnlock((Handle)ctl);
}

void setButtonTitle(CtlRecHndl ctl, char ch)
{
    SetCtlTitle(CHAR_TO_BUTTON_STR(ch), (Handle)ctl);
}

char getButtonTitle(CtlRecHndl ctl)
{
    return BUTTON_STR_TO_CHAR(GetCtlTitle(ctl));
}

void setupButtons(void)
{
    int row, col;
    CtlRecHndl ctl;
    const char * guess;
    
    currentRow = 0;
    memset(knownLetters, 0, sizeof(knownLetters));
    
    *line1 = '\0';
    strcpy(line2, "  Thinking...");
    drawText();
    
    resetSolver();
    guess = nextGuess(NULL);
    
    sprintf(line1, "Words remaining: %d", numRemainingWords());
    strcpy(line2, "Mark letters in solution");
    drawText();
    
    for (row = 0; row < NUM_ROWS; row++) {
        for (col = 0; col < NUM_COLUMNS; col++) {
            ctl = CONTROL_ROW_COL_TO_HANDLE(row, col);
            setButtonColour(ctl, WS_RS_BTN_WHITE);
            if (row > 0)
                HideControl(ctl);
            else {
                setButtonTitle(ctl, guess[col]);
                ShowControl(ctl);
            }
            
            HiliteControl(row == 0 ? noHilite : inactiveHilite, ctl);
        }
        
        ctl = CONTROL_ROW_TO_OK_HANDLE(row);
        if (row != 0)
            HideControl(ctl);
        else
            ShowControl(ctl);
    }
}


void initSolverWithVariant(void) {
    CtlRecHndl ctl = GetCtlHandleFromID(winPtr, WS_RES_POPUP);
    tVariant variant = NYT_VARIANT;
    
    
    HLock((Handle)ctl);
    if ((*ctl)->ctlValue == WS_RES_MENU_ITEM_CQ2)
        variant = CQ2_VARIANT;
    HUnlock((Handle)ctl);
    
    initSolver(variant);
    setupButtons();
}


GrafPortPtr NDAOpen(void)
{
    unsigned int oldResourceApp;
    LevelRecGS levelDCB;
    unsigned int oldLevel;
    SysPrefsRecGS prefsDCB;
    unsigned int oldPrefs;
    
    if (ndaActive)
        return NULL;
    
    levelDCB.pCount = 2;
    GetLevelGS(&levelDCB);
    oldLevel = levelDCB.level;
    levelDCB.level = 0;
    SetLevelGS(&levelDCB);
    
    prefsDCB.pCount = 1;
    GetSysPrefsGS(&prefsDCB);
    oldPrefs = prefsDCB.preferences;
    prefsDCB.preferences = (prefsDCB.preferences & 0x1fff) | 0x8000;
    SetSysPrefsGS(&prefsDCB);
    
    oldResourceApp = OpenResourceFileByID(readEnable, userId);
    
    winPtr = NewWindow2((Pointer)"\p Wordle Solver ", 0, DrawContents, NULL, refIsResource, WS_RES_WINDOW, rWindParam1);
    
    SetSysWindow(winPtr);
    ShowWindow(winPtr);
    SelectWindow(winPtr);
    SetPort(winPtr);
    
    ndaActive = TRUE;
    
    prefsDCB.preferences = oldPrefs;
    SetSysPrefsGS(&prefsDCB);
    
    levelDCB.level = oldLevel;
    SetLevelGS(&levelDCB);
    
    initSolverWithVariant();
    
    SetCurResourceApp(oldResourceApp);
    
    return winPtr;
}


void HandleRun(void)
{
}


void incrementRow(void)
{
    static tLetterState state[WORD_LEN];
    int col;
    CtlRecHndl ctl;
    const char * guess;
    int numSolved = 0;
    
    for (col = 0; col < NUM_COLUMNS; col++) {
        ctl = CONTROL_ROW_COL_TO_HANDLE(currentRow, col);
        HiliteControl(inactiveHilite, ctl);
        switch (getButtonColour(ctl)) {
            case WS_RS_BTN_GREEN:
                state[col] = IN_WORD_AT_POS;
                numSolved++;
                knownLetters[col] = getButtonTitle(ctl);
                break;
            case WS_RS_BTN_YELLOW:
                state[col] = IN_WORD_OTHER_POS;
                break;
            default:
                state[col] = NOT_IN_WORD;
                break;
        }
    }
    HideControl(CONTROL_ROW_TO_OK_HANDLE(currentRow));
    
    if (numSolved == NUM_COLUMNS) {
        strcpy(line1, "Solved the Wordle!");
        strcpy(line2, " Click Restart to try again.");
        drawText();
        return;
    }
    
    currentRow++;
    if (currentRow < NUM_ROWS) {
        strcpy(line2, "  Thinking...");
        drawText();
        guess = nextGuess(state);
        if (guess == NULL) {
            strcpy(line1, "Failed to solve the Wordle!");
            strcpy(line2, " Click Restart to try again.");
            drawText();
            return;
        }
        
        sprintf(line1, "Words remaining: %d", numRemainingWords());
        strcpy(line2, "Mark letters in solution");
        drawText();
        
        for (col = 0; col < NUM_COLUMNS; col++) {
            ctl = CONTROL_ROW_COL_TO_HANDLE(currentRow, col);
            ShowControl(ctl);
            setButtonTitle(ctl, guess[col]);
            if (knownLetters[col] == guess[col]) {
                HiliteControl(inactiveHilite, ctl);
                setButtonColour(ctl, WS_RS_BTN_GREEN);
            } else {
                HiliteControl(noHilite, ctl);
            }
        }
        ShowControl(CONTROL_ROW_TO_OK_HANDLE(currentRow));
    }
}

void HandleControl(EventRecord *event)
{
    CtlRecHndl ctl;
    
    SetPort(winPtr);
    
    if (IS_LETTER_CONTROL(event->wmTaskData4)) {
        cycleButtonColor(event->wmTaskData4);
    } else if (IS_OK_CONTROL(event->wmTaskData4)) {
        incrementRow();
    } else if (event->wmTaskData4 == WS_RES_BTN_RESTART) {
        setupButtons();
    } else if (event->wmTaskData4 == WS_RES_POPUP) {
        initSolverWithVariant();
    }
}


void HandleKey(EventRecord *event)
{
}


void HandleCursor(void)
{
}


void HandleMenu(int menuItem)
{
}


BOOLEAN NDAAction(EventRecord *sysEvent, int code)
{
    static EventRecord localEvent;
    unsigned int eventCode;
    BOOLEAN result = FALSE;
    
    switch (code) {
        case runAction:
            HandleRun();
            break;
            
        case eventAction:
            BlockMove((Pointer)sysEvent, (Pointer)&localEvent, 16);
            localEvent.wmTaskMask = 0x001FFFFF;
            eventCode = TaskMasterDA(0, &localEvent);
            switch(eventCode) {
                case updateEvt:
                    BeginUpdate(winPtr);
                    DrawContents();
                    EndUpdate(winPtr);
                    break;
                    
                case wInControl:
                    HandleControl(&localEvent);
                    break;
                    
                case keyDownEvt:
                case autoKeyEvt:
                    HandleKey(&localEvent);
                    break;
            }
            break;
            
        case cursorAction:
            HandleCursor();
            break;
            
        case cutAction:
        case copyAction:
        case pasteAction:
        case clearAction:
            result = TRUE;
            HandleMenu(code);
            break;
    }
    
    return result;
}

