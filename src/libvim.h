#include "vim.h"

/* libvim.c */

/*
 * vimInit
 *
 * This must be called prior to using any other methods.
 *
 * This expects an `argc` and an `argv` parameters,
 * for the command line arguments for this vim instance.
 */
void vimInit(int argc, char **argv);

/***
 * Buffer Methods
 ***/

/*
 * vimBufferOpen
 *
 * Open a buffer and set as current.
 */

buf_T *vimBufferOpen(char_u *ffname_arg, linenr_T lnum, int flags);
buf_T *vimBufferGetById(int id);
buf_T *vimBufferGetCurrent(void);
void vimBufferSetCurrent(buf_T *buf);

char_u *vimBufferGetFilename(buf_T *buf);
char_u *vimBufferGetFiletype(buf_T *buf);
int vimBufferGetId(buf_T *buf);
long vimBufferGetLastChangedTick(buf_T *buf);
char_u *vimBufferGetLine(buf_T *buf, linenr_T lnum);
size_t vimBufferGetLineCount(buf_T *buf);
int vimBufferGetModified(buf_T *buf);

void vimSetBufferUpdateCallback(BufferUpdateCallback bufferUpdate);

/***
 * Autocommands
 ***/

void vimSetAutoCommandCallback(AutoCommandCallback autoCommandDispatch);

/**
 * Commandline
 ***/

char_u vimCommandLineGetType(void);
char_u *vimCommandLineGetText(void);
int vimCommandLineGetPosition(void);
void vimCommandLineGetCompletions(char_u ***completions, int *count);

/***
 * Cursor Methods
 ***/
colnr_T vimCursorGetColumn(void);
linenr_T vimCursorGetLine(void);
pos_T vimCursorGetPosition(void);
void vimCursorSetPosition(pos_T pos);

/***
 * vimCursorGetDesiredColumn
 *
 * Get the column that we'd like to be at - used to stay in the same
 * column for up/down cursor motions.
 */
colnr_T vimCursorGetDesiredColumn(void);

/***
 * User Input
 ***/
void vimInput(char_u *input);

void vimExecute(char_u *cmd);

/***
 * Messages
 ***/

void vimSetMessageCallback(MessageCallback messageCallback);

/**
 * Misc
 **/

void vimSetDirectoryChangedCallback(DirectoryChangedCallback callback);

/*
 * vimSetQuitCallback
 *
 * Called when a `:q`, `:qa`, `:q!` is called
 * 
 * It is up to the libvim consumer how to handle the 'quit' call.
 * There are two arguments passed:
 * - `buffer`: the buffer quit was requested for
 * - `force`: a boolean if the command was forced (ie, if `q!` was used)
 */
void vimSetQuitCallback(QuitCallback callback);

/*
 * vimSetUnhandledEscapeCallback
 *
 * Called when <esc> is pressed in normal mode, but there is no
 * pending operator or action.
 *
 * This is intended for UI's to pick up and handle (for example,
 * to clear messages or alerts).
 */
void vimSetUnhandledEscapeCallback(VoidCallback callback);

/***
 * Options
 **/

void vimOptionSetTabSize(int tabSize);
void vimOptionSetInsertSpaces(int insertSpaces);

int vimOptionGetInsertSpaces(void);
int vimOptionGetTabSize(void);

/***
 * Registers
 ***/

void vimRegisterGet(int reg_name, int *num_lines, char_u ***lines);

/***
 * Visual Mode
 ***/

int vimVisualGetType(void);
int vimVisualIsActive(void);
int vimSelectIsActive(void);

/*
 * vimVisualGetRange
 *
 * If in visual mode or select mode, returns the current range.
 * If not in visual or select mode, returns the last visual range.
 */
void vimVisualGetRange(pos_T *startPos, pos_T *endPos);

/***
 * Search
 ***/

/*
 * vimSearchGetMatchingPair
 *
 * Returns the position of a matching pair,
 * based on the current buffer and cursor position
 *
 * result is NULL if no match found.
 */
pos_T *vimSearchGetMatchingPair(int initc);

/*
 * vimSearchGetHighlights
 *
 * Get highlights for the current search
 */
void vimSearchGetHighlights(linenr_T start_lnum, linenr_T end_lnum,
                            int *num_highlights,
                            searchHighlight_T **highlights);

/*
 * vimSearchGetPattern
 *
 * Get the current search pattern
 */
char_u *vimSearchGetPattern();

void vimSetStopSearchHighlightCallback(VoidCallback callback);

/***
 * Window
 */

int vimWindowGetWidth(void);
int vimWindowGetHeight(void);
int vimWindowGetTopLine(void);
int vimWindowGetLeftColumn(void);

void vimWindowSetWidth(int width);
void vimWindowSetHeight(int height);
void vimWindowSetTopLeft(int top, int left);

void vimSetWindowSplitCallback(WindowSplitCallback callback);
void vimSetWindowMovementCallback(WindowMovementCallback callback);

/***
 * Misc
 ***/

void vimSetClipboardGetCallback(ClipboardGetCallback callback);

int vimGetMode(void);

void vimSetYankCallback(YankCallback callback);

/* Callbacks for when the `:intro` and `:version` commands are used
  
  The Vim license has some specific requirements when implementing these methods:
    
    3) A message must be added, at least in the output of the ":version"
       command and in the intro screen, such that the user of the modified Vim
       is able to see that it was modified.  When distributing as mentioned
       under 2)e) adding the message is only required for as far as this does
       not conflict with the license used for the changes.
*/
void vimSetDisplayIntroCallback(VoidCallback callback);
void vimSetDisplayVersionCallback(VoidCallback callback);

/* vim: set ft=c : */
