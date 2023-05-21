#pragma once
#ifndef Fentser_H
#define Fenster_H

#include "global.h"
class Fenster {
public:
	Fenster();
	void begin();

private:
	sf::RenderWindow window;
};



#endif