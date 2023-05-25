#include "global.h"


//global
sf::Mouse maus;
std::random_device rd;
std::uniform_int_distribution<int> dist(0, 475);
vector<RectangleShape>rect;//array mit Rechtecken
Event ev;//Zuständig für Aktionen
sf::Font font;
sf::Text text;
Button start(850, 25, 100, 50, Color::White, Color::Black, 2, "Start", 15, Color::Black);
Button random(975, 25, 100, 50, Color::White, Color::Black, 2, "Random", 15, Color::Black);
std::vector<Button>Knopf_collection = { start,random};
std::vector<string> Sortalgo = {"Bubblesort","Quicksort","Mergesort","Insertion Sort","c"};
bool finish=true;
bool start_timer = true;
int startzeit;

//Verlinkungen
void BLOCKS();
void ui(sf::RenderWindow* w);
void finish_();
void drawer(sf::RenderWindow* w);
// Algoverlinkung
void bubblesort(sf::RenderWindow* w);
void quicksort(sf::RenderWindow* w);
void mergesort(sf::RenderWindow* w);
void insertion_Sort(sf::RenderWindow* w);


Fenster::Fenster():
window(VideoMode(1250, 480), "Sorting-Algo", Style::Titlebar | Style::Close)
{


}

void Fenster :: begin() {
	//Setup
	font.loadFromFile("font.TTF");
	text.setFillColor(Color::Black);
	text.setPosition(820,300);
	text.setFont(font);
	text.setCharacterSize(20);
	text.setString("Sortierungsalgorithmus:"+Sortalgo[0]);
	this->window.setFramerateLimit(30);
	
	BLOCKS();
	for (int i = 0; i < Knopf_collection.size(); i++)
	{
		Knopf_collection[i].setup();
	}
	int sortierungswechsel = 0;
	sf::Clock clock;
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
				if (ev.key.code == Keyboard::Left) {
					if (sortierungswechsel!=0) {
						text.setString("Sortierungsalgorithmus:"+Sortalgo[sortierungswechsel-1]);
						sortierungswechsel--;
					}
					else if (sortierungswechsel == 0) {
						text.setString("Sortierungsalgorithmus:"+Sortalgo[Sortalgo.size() - 1]);
						sortierungswechsel = Sortalgo.size() - 1;
						
					}
					
				}
				if (ev.key.code == Keyboard::Right) {

					if (sortierungswechsel != Sortalgo.size() - 1) {
						text.setString("Sortierungsalgorithmus:"+Sortalgo[sortierungswechsel + 1]);
						sortierungswechsel++;
					}
					else if (sortierungswechsel == Sortalgo.size() - 1) {
						text.setString("Sortierungsalgorithmus:"+Sortalgo[0]);
						sortierungswechsel = 0;

					}
				}
				break;


			}

		}
		
		this->window.clear();//Clear old frame
		
		for (int i = 0; i < rect.size(); i++) {
			this->window.draw(rect[i]);//Rechtecke zeichnen
		}
		
		finish = true;
		if (Knopf_collection[0].start_number!=0&&finish) {//Auswahl
			
			
			switch (sortierungswechsel)
			{
			case 0:
				clock.restart();
				bubblesort(&this->window);
				break;
			
			case 1:
				clock.restart();
				quicksort(&this->window);
				break;
			case 2:
				clock.restart();
				mergesort(&this->window);
				break;
			case 3:
				clock.restart();
				insertion_Sort(&this->window);
			default:
				break;
			}
			Knopf_collection[0].start_number = 0;
			
			sf::Time elapsed = clock.getElapsedTime();
			std::cout << elapsed.asSeconds() << std::endl;
		}
		if (Knopf_collection[1].start_number != 0) {//Random
			BLOCKS();
			Knopf_collection[1].start_number = 0;
		}

		
		ui(&this->window);
		this->window.draw(text);
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

//
//finish
//
void finish_() {

	int n = 0;
	for (int i = 0; i < rect.size()-1; i++)
	{
		if (abs(rect[i].getSize().y) >= abs(rect[i + 1].getSize().y)) {

			n++;
		}
	}
	if (n == rect.size() - 1) {
		finish = false;
	}
}
void drawer(sf::RenderWindow *w) {

	for (int i = 0; i < rect.size(); i++) {
		w->draw(rect[i]);//Rechtecke zeichnen
	}
	ui(w);

}

//
//Algo
//

void bubblesort(sf::RenderWindow* w) {

	while (finish)
	{
		w->clear();
		
		drawer(w);

		float connector = 0;//Dient als Zwischenspeicher
		for (int lauf = 0; lauf < rect.size() - 1; lauf++)
		{
			if (abs(rect[lauf].getSize().y) < abs(rect[lauf + 1].getSize().y)) {

				connector = rect[lauf].getPosition().x;
				rect[lauf].setPosition(rect[lauf + 1].getPosition().x, 480);
				rect[lauf + 1].setPosition(connector, 480);
				swap(rect[lauf], rect[lauf + 1]);//Vertausche die Positionen der beiden Elementen im vector
			}
		}
		finish_();
		w->display();
	}

}

void quicksort(sf::RenderWindow* w) {

	while (finish)
	{
		w->clear();
		
		drawer(w);

		//logic





		//Timer finish
		finish_();
		w->display();

	}


}

void mergesort(sf::RenderWindow* w) {

	while (finish)
	{
		w->clear();
		drawer(w);

		//logic
		




		//Timer finish
		finish_();
		w->display();

	}


}
void insertion_Sort(sf::RenderWindow* w) {

	while (finish)
	{
		w->clear();
		drawer(w);


		//Array speichern
		//logic
		float connector = 0;//Dient als Zwischenspeicher
		for (int lauf = 0; lauf < rect.size() - 1; lauf++)
		{
			if (abs(rect[lauf].getSize().y) < abs(rect[lauf + 1].getSize().y)) {

				connector = rect[lauf].getPosition().x;
				rect[lauf].setPosition(rect[lauf + 1].getPosition().x, 480);
				rect[lauf + 1].setPosition(connector, 480);
				swap(rect[lauf], rect[lauf + 1]);//Vertausche die Positionen der beiden Elementen im vector
			}
		}

		//Timer finish
		finish_();
		w->display();

	}


}