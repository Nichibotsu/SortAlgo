#include "global.h"


//global
sf::Mouse maus;
std::random_device rd;
std::uniform_int_distribution<int> dist(0, 450);
vector<RectangleShape>rect;//array mit Rechtecken
Event ev;//Zuständig für Aktionen
sf::Font font;
Button start(850, 25, 100, 50, Color::White, Color::Black, 2, "Start", 15, Color::Black);
Button random(975, 25, 100, 50, Color::White, Color::Black, 2, "Random", 15, Color::Black);
void BLOCKS();
void ui(sf::RenderWindow* w);
std::vector<Button>Knopf_collection = { start,random};


//TEST
Fenster::Fenster():
window(VideoMode(1250, 480), "Sorting-Algo", Style::Titlebar | Style::Close)
{


}

void Fenster :: begin() {
	//Setup
	font.loadFromFile("font.TTF");
	this->window.setFramerateLimit(30);
	BLOCKS();
	for (int i = 0; i < Knopf_collection.size(); i++)
	{
		Knopf_collection[i].setup();
	}





	while (this->window.isOpen()) {

		//Event polling
		while (this->window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed://Schließt das Fenster
				this->window.close();
				break;

			case Event::KeyPressed://Schließt das Fenster mit ESC
				if (ev.key.code == Keyboard::Escape) {
					this->window.close();

				}
				break;

			}

		}
		this->window.clear();//Clear old frame
		
		for (int i = 0; i < rect.size(); i++) {
			this->window.draw(rect[i]);//Rechtecke zeichnen
		}

		if (Knopf_collection[0].start_number!=0) {
			float connector = 0;//Dient als Zwischenspeicher
			for (int lauf = 0; lauf < rect.size() - 1; lauf++)
			{
				if (rect[lauf].getSize().y < rect[lauf + 1].getSize().y) {

					connector = rect[lauf].getPosition().x;
					rect[lauf].setPosition(rect[lauf + 1].getPosition().x, 480);
					rect[lauf + 1].setPosition(connector, 480);
					swap(rect[lauf], rect[lauf + 1]);//Vertausche die Positionen der beiden Elementen im vector
				}
			}
			
		}
		if (Knopf_collection[1].start_number != 0) {
			BLOCKS();
			Knopf_collection[1].start_number = 0;
		}
		ui(&this->window);
		this->window.display();
	}



}


void ui(sf::RenderWindow *w) {
	sf::RectangleShape recttest;
	Vector2f position(801, 0);
	recttest.setPosition(position);
	recttest.setFillColor(Color(127, 255, 212));
	recttest.setSize(Vector2f(w->getSize().x - 800, w->getSize().y));

	w->draw(recttest);
	
	for (int i = 0; i < Knopf_collection.size(); i++)
	{
		Knopf_collection[i].draw(w);
	}
	
	
	
}

void BLOCKS() {
	//Befüllen des Arrays
	rect.clear();
	sf::RectangleShape recttest;

	for (int i = 0; i < 800; i = 3 + i)
	{
		Vector2f position(i, 480);
		recttest.setPosition(position);
		recttest.setSize(Vector2f(3, -dist(rd)));
		rect.push_back(recttest);


	}
}