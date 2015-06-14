#ifndef TEXTBOX_H
#define TEXTBOX_H

struct MintTextBox;
struct MintBlinkingCaret;

#include <SDL.h>
#include <mintSDL\display\rend.h>
#include <mintSDL\display\texture.h>

struct MintTextBox {
	BlinkingCaret *caret;
	MintTexture *textImage;
	SDL_Rect bounds;
	char *text;
	int caretPos;
	char focused;
};

struct MintBlinkingCaret {
	SDL_Rect bounds;
	int blinkSpeed;
};

TextBox* mint_CreateTextBox(int x, int y, int width, int height); //Create a textbox
char mint_TextBoxGetFocus(TextBox *tb); //Check if this textbox has focus
void mint_TextBoxBringFocus(TextBox *tb); //Make the textbox focused
void mint_TextBoxEscapeFocus(TextBox *tb); //Make the textbox no longer have focus
void mint_TextBoxAppendText(TextBox *tb, char text, SDL_Color color); //Appends a textbox with a character with the specified color from the current caret position.
float mint_TextBoxGetTextWidth(TextBox *tb); //Gets the pixel width of the text within the textbox
void mint_TextBoxSetCaretPos(TextBox *tb, int pos); //Sets the position of the caret
void mint_TextBoxHighlightText(TextBox *tb, int from, int to); //Highlights text from the given range
void mint_TextBoxFree(TextBox *tb);

#endif
