#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include "var.h"
#include<Windows.h>
#include<fstream>
#include <sstream>

using namespace sf;

void ClearNum()
{
	numbers.oneRoundRollTime1 = 0;
	numbers.oneRoundRollTime2 = 0;
	numbers.oneRoundRollTime3 = 0;

	numbers.storage1 = 0;
	numbers.storage2 = 0;
	numbers.storage3 = 0;

	numbers.pic1 = rand() % 5;
	numbers.pic2 = rand() % 5;
	numbers.pic3 = rand() % 5;

	numbers.rollTime1 = float(rand() % 18 + 8.0);
	numbers.rollTime2 = float(rand() % 18 + 8);
	numbers.rollTime3 = float(rand() % 18 + 8);
}

class Picture
{
private: float x, y = 0;
public:
	String file_name;
	Image image;
	Texture texture;
	Sprite sprite;
	Picture(String file_name, int width, int heigth, float width_position, float heigth_position) {
		image.loadFromFile("images/" + file_name);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, width, heigth));
		sprite.setPosition(width_position, heigth_position);
	}
};

void change_combo(int &Score, int &earn, Sound &win, Sound &JackPot, Sound &lose)
{
	if (numbers.pic1 == 0 && numbers.pic2 == 0 && numbers.pic3 == 0) { Score += 50; JackPot.play(); earn = 50; }
	else if ((numbers.pic1 == 0 && numbers.pic2 == 0) || (numbers.pic1 == 0 && numbers.pic3 == 0) || (numbers.pic2 == 0 && numbers.pic3 == 0)) { Score += 15; win.play(); earn = 15; }
		 else if (numbers.pic1 == 1 && numbers.pic2 == 1 && numbers.pic3 == 1) { Score += 50; JackPot.play(); earn = 50; }
			  else if ((numbers.pic1 == 1 && numbers.pic2 == 1) || (numbers.pic1 == 1 && numbers.pic3 == 1) || (numbers.pic2 == 1 && numbers.pic3 == 1)) { Score += 15; win.play(); earn = 15; }
				   else  if (numbers.pic1 == 2 && numbers.pic2 == 2 && numbers.pic3 == 2) { Score += 50;  JackPot.play(); earn = 50; }
						 else if ((numbers.pic1 == 2 && numbers.pic2 == 2) || (numbers.pic1 == 2 && numbers.pic3 == 2) || (numbers.pic2 == 2 && numbers.pic3 == 2)) { Score += 15; win.play(); earn = 15; }
							  else if (numbers.pic1 == 3 && numbers.pic2 == 3 && numbers.pic3 == 3) { Score += 50; JackPot.play(); earn = 50; }
							       else if ((numbers.pic1 == 3 && numbers.pic2 == 3) || (numbers.pic1 == 3 && numbers.pic3 == 3) || (numbers.pic2 == 3 && numbers.pic3 == 3)) { Score += 15; win.play(); earn = 15; }
									    else if (numbers.pic1 == 4 && numbers.pic2 == 4 && numbers.pic3 == 4) { Score += 100; JackPot.play(); earn = 100; }
											 else if ((numbers.pic1 == 4 && numbers.pic2 == 4) || (numbers.pic1 == 4 && numbers.pic3 == 4) || (numbers.pic2 == 4 && numbers.pic3 == 4)) { Score += 15; win.play(); earn = 15; }
												  else { lose.play(); earn = 0; }
}

void output_of_the_game(RenderWindow &window, Picture &drum1, Picture &drum2, Picture &drum3, Picture fon_s, Text text, Picture &hand)
{
	window.clear();

	window.draw(fon_s.sprite);

	std::ostringstream PlayerEarnString;
	PlayerEarnString << earn;
	text.setString(PlayerEarnString.str());
	text.setPosition(480, 335);
	window.draw(text);

	std::ostringstream PlayerBetString;
	PlayerBetString << bet;
	text.setString(PlayerBetString.str());
	text.setPosition(150, 335);
	window.draw(text);

	std::ostringstream PlayerScoreString;
	PlayerScoreString << Score;
	text.setString(PlayerScoreString.str());
	text.setPosition(300, 60);
	window.draw(text);

	window.draw(hand.sprite);
	window.draw(drum3.sprite);
	window.draw(drum2.sprite);
	window.draw(drum1.sprite);
	window.display();
}

void Rolling_drums(Picture &drum1, Picture &drum2, Picture &drum3, Picture fon_s, RenderWindow &window, float time, Text text, Picture &hand)
{
	while ((numbers.storage1 < numbers.rollTime1) | (numbers.storage2 < numbers.rollTime2) | (numbers.storage3 < numbers.rollTime3))
	{
		if (numbers.storage1 < numbers.rollTime1)
		{
			numbers.storage1 += time * 0.001;
			if (numbers.oneRoundRollTime1 < 4.0) { numbers.oneRoundRollTime1 += time * 0.007; }
			else { numbers.oneRoundRollTime1 = 0.0; }
			drum3.sprite.setTextureRect(IntRect(0, 181 * numbers.oneRoundRollTime1, 132, 181));
		}

		if (numbers.storage2 < numbers.rollTime2)
		{
			numbers.storage2 += time * 0.001;
			if (numbers.oneRoundRollTime2 < 4) { numbers.oneRoundRollTime2 += time * 0.007; }
			else { numbers.oneRoundRollTime2 = 0; }
			drum2.sprite.setTextureRect(IntRect(0, 181 * numbers.oneRoundRollTime2, 132, 181));
		}

		if (numbers.storage3 < numbers.rollTime3)
		{
			numbers.storage3 += time * 0.001;
			if (numbers.oneRoundRollTime3 < 4) { numbers.oneRoundRollTime3 += time * 0.007; }
			else { numbers.oneRoundRollTime3 = 0; }
			drum1.sprite.setTextureRect(IntRect(0, 181 * numbers.oneRoundRollTime3, 132, 181));
		}

		if (numbers.storage1 > numbers.rollTime1) { drum3.sprite.setTextureRect(IntRect(0, coordinate[numbers.pic1], 132, 181)); }
		if (numbers.storage2 > numbers.rollTime2) { drum2.sprite.setTextureRect(IntRect(0, coordinate[numbers.pic2], 132, 181)); }
		if (numbers.storage3 > numbers.rollTime3) { drum1.sprite.setTextureRect(IntRect(0, coordinate[numbers.pic3], 132, 181)); }

		output_of_the_game(window, drum1, drum2, drum3, fon_s, text, hand);
	}
	hand.sprite.rotate(-10);
	hand.sprite.setPosition(570, 212);
}

void start_game(RenderWindow &window, Picture fon_s, Picture drum1, Picture drum2, Picture drum3, Font font, Text text, Sound win, Sound JackPot, Sound lose, Sound music, Clock clock, Picture &hand)
{
	while (window.isOpen())
	{
		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time = time / 800;
		Event event;

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			ClearNum();
			hand.sprite.rotate(10);
			hand.sprite.setPosition(605,216);
			lose.stop();
			win.stop();
			music.play();

			Score = Score - bet;

			Rolling_drums(drum1, drum2, drum3, fon_s, window, time, text, hand);

			music.stop();

			change_combo(Score, earn, win, JackPot, lose);
			
			
		}
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) || (Score <= 0)) { window.close(); }
		}
		output_of_the_game(window, drum1, drum2, drum3, fon_s, text, hand);
	}
}

int main()
{
	RenderWindow window(sf::VideoMode(655, 491), "Slots");

	SoundBuffer musicBuffer;
	musicBuffer.loadFromFile("bandit.ogg");
	Sound music(musicBuffer);

	SoundBuffer winBuffer;
	winBuffer.loadFromFile("sound.ogg");
	Sound win(winBuffer);

	SoundBuffer JackPotBuffer;
	JackPotBuffer.loadFromFile("jackpot2.ogg");
	Sound JackPot(JackPotBuffer);

	SoundBuffer loseBuffer;
	loseBuffer.loadFromFile("lose.ogg");
	Sound lose(loseBuffer);

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setColor(Color::White);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	Picture fon_s("bandit.png", 655, 491, 0, 0);
	Picture drum1("slots2.png", 132, 181, 248, 152);
	Picture drum2("slots2.png", 132, 181, 100, 152);
	Picture drum3("slots2.png", 132, 181, 398, 152);
	Picture hand("hand.png", 69, 183, 570, 212);

	Clock clock;

	srand(time(NULL));
	
	start_game(window, fon_s, drum1, drum2, drum3, font, text, win, JackPot, lose, music, clock, hand);
}