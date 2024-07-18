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

#include "main.h"
#include "solver.h"


// Constants and macros
#define NUM_COLUMNS 5
#define NUM_ROWS 6

#define IS_LETTER_CONTROL(id) (((id) >= WS_RES_BTN_0_0) && ((id) <= WS_RES_BTN_5_4))
#define IS_OK_CONTROL(id) (((id) >= WS_RES_BTN_0_OK) && ((id) <= WS_RES_BTN_5_OK))

#define CONTROL_ROW_COL_TO_ID(row, col) (WS_RES_BTN_0_0 + (col) + ((row) * NUM_COLUMNS))
#define CONTROL_ROW_COL_TO_HANDLE(row, col) GetCtlHandleFromID(winPtr, CONTROL_ROW_COL_TO_ID((row), (col)))
#define CONTROL_ID_TO_ROW(id) (((id) - WS_RES_BTN_0_0) / NUM_COLUMNS)
#define CONTROL_ID_TO_COL(id) (((id) - WS_RES_BTN_0_0) % NUM_COLUMNS)

#define CONTROL_ROW_TO_OK_ID(row) (WS_RES_BTN_0_OK + (row))
#define CONTROL_ROW_TO_OK_HANDLE(row) GetCtlHandleFromID(winPtr, CONTROL_ROW_TO_OK_ID(row))

#define CHAR_TO_BUTTON_STR(ch) ((Pointer)(unsigned long)(((ch) - 'A') + WS_RES_BTN_STR_A))
#define BUTTON_STR_TO_CHAR(buttonStr) (((buttonStr) - WS_RES_BTN_STR_A) + 'A')


// Globals

static BOOLEAN ndaActive;
static GrafPortPtr winPtr;
static unsigned int userId;

static char * guesses[] = {
    "AEROS",
    "UNITY",
    "PHONE",
    "APPLE",
    "RETRO",
    "FAULT"
};


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


#pragma databank 1
void DrawContents(void)
{
    PenNormal();
    DrawControls(GetPort());
}
#pragma databank 0

void setButtonColour(CtlRecHndl ctl, long colour)
{
    HLock((Handle)ctl);
    (*ctl)->ctlColor = (Pointer)colour;
    HUnlock((Handle)ctl);
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

void setupButtons(void)
{
    int row, col;
    CtlRecHndl ctl;
    
    for (row = 0; row < NUM_ROWS; row++) {
        for (col = 0; col < NUM_COLUMNS; col++) {
            ctl = CONTROL_ROW_COL_TO_HANDLE(row, col);
            setButtonColour(ctl, WS_RS_BTN_WHITE);
            setButtonTitle(ctl, guesses[row][col]);
            if (row > 0)
                HideControl(ctl);
            else
                ShowControl(ctl);
        }
        
        ctl = CONTROL_ROW_TO_OK_HANDLE(row);
        if (row > 0)
            HideControl(ctl);
        else
            ShowControl(ctl);
    }
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
    initSolver();
    
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
    
    setupButtons();
    
    SetCurResourceApp(oldResourceApp);
    
    return winPtr;
}


void HandleRun(void)
{
}


void HandleControl(EventRecord *event)
{
    CtlRecHndl ctl;
    
    SetPort(winPtr);
    
    if (IS_LETTER_CONTROL(event->wmTaskData4)) {
        cycleButtonColor(event->wmTaskData4);
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

