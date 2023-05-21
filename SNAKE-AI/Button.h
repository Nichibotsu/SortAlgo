#ifndef Button_H
#define Button_H
#include "global.h"

using namespace sf;
using namespace std;

class Button{
public:
    Button(int x_posi, int y_posi, int x_size, int y_size, Color inhalt, Color raender, int randdicke, string text, int textsize, Color textfarb);
    void setup();
    void draw(RenderWindow *w) ;
    void klick(RenderWindow *w);
    int start_number,resetnumber,verarbeiter;


private:
    //Erstellung der Variabeln
    RectangleShape box, boxtest;
    Text text;
    Vector2f Posi, box_size;
    Color innenseite, auﬂenseite, textfarbe;
    int randdick, textgroesse;
    string knopftext;
    //RectangleShape hori, verti;   Test Objekte ob der Text mittig ist

};

#endif // !Button_h
