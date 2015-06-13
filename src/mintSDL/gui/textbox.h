#ifndef TEXTBOX_H
#define TEXTBOX_H

struct TextBox;
struct BlinkingCaret;

#include <SDL.h>
#include <mintSDL\display\rend.h>
#include <mintSDL\display\texture.h>

struct TextBox {
	BlinkingCaret *caret;
	MintTexture *textImage;
	SDL_Rect bounds;
	char text;
	int caretPos;
	char focused;
};

struct BlinkingCaret {
	SDL_Rect bounds;
	int blinkSpeed;
};

TextBox textbox_Create(int x, int y, int width, int height); //Create a textbox
char textbox_GetFocus(TextBox *tb); //Check if this textbox has focus
void textbox_BringFocus(TextBox *tb); //Make the textbox focused
void textbox_EscapeFocus(TextBox *tb); //Make the textbox no longer have focus
void textbox_AppendText(TextBox *tb, char text, SDL_Color color); //Appends a textbox with a character with the specified color from the current caret position.
float textbox_GetTextWidth(TextBox *tb); //Gets the pixel width of the text within the textbox
void textbox_SetCaretPos(TextBox *tb, int pos); //Sets the position of the caret
void textbox_HighlightText(TextBox *tb, int from, int to); //Highlights text from the given range
void textbox_Free(TextBox *tb);

#endif