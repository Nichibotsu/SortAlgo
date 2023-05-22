
#include "Button.h"
#include <iostream>
#include "global.h"

using namespace sf;
using namespace std;


extern Font font;
extern Mouse maus;
extern vector<Button>Knopf_collection;
int delay = 0;
int delay2 = 0;


Button::Button(int x_posi, int y_posi, int x_size, int y_size, Color inhalt, Color raender, int randdicke, string text, int textsize, Color textfarb) {

        //Übergrabe der Werte an private Variabeln;
    this->Posi.x= x_posi;
    this->Posi.y = y_posi;
    this->box_size.x = x_size;
    this->box_size.y = y_size;
    this->innenseite = inhalt;
    this->außenseite = raender;
    this->randdick = randdicke;
    this->knopftext = text;
    this->textgroesse = textsize;
    this->textfarbe = textfarb;
   
    
}

    void Button::setup() {

        //
        //Eigenschaften des Rechteckes
        this->box.setPosition(this->Posi);
        this->box.setSize(this->box_size);
        this->box.setFillColor(this->innenseite);
        this->box.setOutlineColor(this->außenseite);
        this->box.setOutlineThickness(this->randdick);

        //
        //Text Eigenschaften
       

        this->text.setString(this->knopftext);
        this->text.setFont(font);
        this->text.setCharacterSize(this->textgroesse);
        this->text.setPosition(this->Posi.x + ((this->box_size.x - this->textgroesse) / 2) - this->text.getCharacterSize(), this->Posi.y + ((this->box_size.y - this->textgroesse) / 2) * 0.92);//Zentieren
        this->text.setFillColor(this->textfarbe);

       

    }
    void Button::draw(RenderWindow* w) {
        
        //Flyover
        delay = 0;
        //delay2 = 0;
        if (((maus.getPosition().x - w->getPosition().x) >= this->box.getPosition().x && (this->box_size.x + this->box.getPosition().x) >= (maus.getPosition().x - w->getPosition().x)) && ((this->box_size.y + this->box.getPosition().y) >= (maus.getPosition().y - w->getPosition().y - 30) && (maus.getPosition().y - w->getPosition().y - 30) >= this->box.getPosition().y))
        {
            this->box.setFillColor(Color(136, 136, 136));
            if (maus.isButtonPressed(maus.Left)) {
                delay = 1;   
            }
            if (delay == 0) {
                delay2 = 0;
            }
        }
        else
        {
            this->box.setFillColor(this->innenseite);
        }

        if (delay==1&&delay2==0) {
            klick(w);
        }

        
        w->draw(this->box);
        w->draw(this->boxtest);
        w->draw(this->text);
        
       
    }

    void Button::klick(RenderWindow *w) {
        delay2 = 1;

        //Herrausfinden wechler Button gemeint ist
        int j=0;
        for (int n = 0; n < Knopf_collection.size(); n++) {
            if (this->Posi == Knopf_collection[n].Posi) {

                j = n;
            }
            
        }
        switch (j)
        {
        case 0:
            if (this->start_number == 1) {
                this->start_number = 0;
                this->innenseite = Color::White;
            }
            else {
                this->start_number = 1;
                this->innenseite = Color::Green;
            }
            break;
        case 1:
            if (this->start_number == 1)
                this->start_number = 0;
            else
                this->start_number = 1;
            break;
        default:
            break;
        }

        //Buttonaktion

   
        
    }
