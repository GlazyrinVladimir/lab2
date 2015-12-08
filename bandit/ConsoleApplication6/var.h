#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


int coordinate[5] = { 0, 184, 368, 552, 730 };

int Score = 100;
int bet = 10;
int earn = 0;

struct init_numbers 
{
	double oneRoundRollTime1 = 0, oneRoundRollTime2 = 0, oneRoundRollTime3 = 0;
	double storage1 = 0, storage2 = 0, storage3 = 0;
	float rollTime1 = float(rand() % 18 + 8.0), rollTime2 = float(rand() % 18 + 8.0), rollTime3 = float(rand() % 18 + 8.0);
	int pic1 = rand() % 5, pic2 = rand() % 5, pic3 = rand() % 5;
};

init_numbers numbers;

