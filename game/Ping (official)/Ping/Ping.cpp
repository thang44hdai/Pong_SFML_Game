#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#define PI 3.1416
#define scrWidth 1000
#define scrHeight 700
#define barSize leftBar.getSize()

using namespace sf;


int main()
{
	//Create window
	RenderWindow window(VideoMode(scrWidth, scrHeight), "Pong");
	window.setFramerateLimit(60);

	//Create Ball
	CircleShape ball(10);
	ball.setFillColor(Color::Yellow);
	ball.setOutlineThickness(2);
	ball.setOutlineColor(Color::White);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(scrWidth / 2, scrHeight / 2);

	//Create LeftBar
	RectangleShape leftBar(Vector2f(50, 150));
	leftBar.setFillColor(Color::Blue);
	leftBar.setOutlineThickness(2);
	leftBar.setOutlineColor(Color::White);
	leftBar.setOrigin(barSize.x / 2, barSize.y / 2);
	leftBar.setPosition(0, scrHeight / 2);

	//Create RightBar
	RectangleShape rightBar(Vector2f(50, 150));
	rightBar.setFillColor(Color::Red);
	rightBar.setOutlineThickness(2);
	rightBar.setOutlineColor(Color::White);
	rightBar.setOrigin(barSize.x / 2, barSize.y / 2);
	rightBar.setPosition(scrWidth, scrHeight / 2);

	//Ball properties
	const float ballSpeed = 300;
	float angleBall = -90; // bien de doi huong qua bong

	//Bar properties
	const float barSpeed = 250;

	//Bot properties
	float botTarget = scrHeight / 2;
	float botPeriod = 0.01;
	float botTimer = 0;

	//Timer
	Clock clock;
	float deltaTime = 0;

	bool isPlaying = false;
	bool isModeOn = false;

	//Gameloop
	while (window.isOpen())
	{
		//Time
		deltaTime = clock.restart().asSeconds();

		//Close
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		if (!isPlaying && Keyboard::isKeyPressed(Keyboard::Space))
		{
			isPlaying = true;
			ball.setPosition(scrWidth / 2, scrHeight / 2);
			leftBar.setPosition(0, scrHeight / 2);
			rightBar.setPosition(scrWidth, scrHeight / 2);
			do
			{
				angleBall = rand() % 360;
			} while (angleBall < 45 || (angleBall > 135 && angleBall < 225) || angleBall > 315);
		}
		if (isPlaying)
		{
			//Ball moving
			float factor = ballSpeed * deltaTime;
			ball.move(cos(angleBall * PI / 180) * factor, sin(angleBall * PI / 180) * factor);

			//Touch Top or bot (Dap vao 2 canh tren duoi)
			if (ball.getPosition().x - ball.getRadius() <= 0 || ball.getPosition().x + ball.getRadius() >= scrWidth)
			{
				angleBall = - angleBall;
			}
			else if (ball.getPosition().y - ball.getRadius() <= 0 || ball.getPosition().y + ball.getRadius() >= scrHeight)
			{
				angleBall = 180 - angleBall;
			}

			//Touch Bar (Dap vao thanh do)
			//LeftBar
			if (ball.getPosition().y - ball.getRadius() - barSize.y / 2 <= 0
				&& ball.getPosition().x >= leftBar.getPosition().y - barSize.y / 2
				&& ball.getPosition().y <= leftBar.getPosition().y + barSize.y / 2
				&& ball.getPosition().x > leftBar.getPosition().x)
			{
				angleBall = 360 - angleBall + rand() % 10;
			}

			//RightBar
			if (ball.getPosition().x + ball.getRadius() + barSize.x >= scrWidth
				&& ball.getPosition().y >= rightBar.getPosition().y - barSize.y 
				&& ball.getPosition().y <= rightBar.getPosition().y + barSize.y 
				&& ball.getPosition().x < rightBar.getPosition().x)
			{
				angleBall = 360 - angleBall - rand() % 10;
			}

			//LeftBar moving
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (leftBar.getPosition().y - barSize.y / 2 - barSpeed * deltaTime <= 0)
				{
					leftBar.setPosition(0, barSize.y / 2);
				}
				else leftBar.move(0, -barSpeed * deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (leftBar.getPosition().y + barSize.y / 2 + barSpeed * deltaTime >= scrHeight)
				{
					leftBar.setPosition(0, scrHeight - barSize.y / 2);
				}
				else leftBar.move(0, barSpeed * deltaTime);
			}

			
			//Oneplayer
			//Update Target Bot
			botTimer += deltaTime;
			if (botTimer >= botPeriod)
			{
				botTarget = ball.getPosition().y;
				botTimer = 0;
			}

			//Bot moving (RightBar)
			if (rightBar.getPosition().y - barSize.y / 5 > botTarget)
			{
				if (rightBar.getPosition().y - barSize.y / 2 - barSpeed * deltaTime <= 0)
				{
					rightBar.setPosition(scrWidth, barSize.y / 2);
				}
				else rightBar.move(0, -barSpeed * deltaTime);
			}
			if (rightBar.getPosition().y + barSize.y / 5 < botTarget)
			{
				if (rightBar.getPosition().y + barSize.y / 2 + barSpeed * deltaTime >= scrHeight)
				{
					rightBar.setPosition(scrWidth, scrHeight - barSize.y / 2);
				}
				else rightBar.move(0, barSpeed * deltaTime);
			}
			

			if (ball.getPosition().x <= 0)
			{
				isPlaying = false;
			}
			else if (ball.getPosition().x >= scrWidth)
			{
				isPlaying = false;
			}
		}

		//Display Screen
		window.clear(Color::Black);
		if (isPlaying)
		{
			window.draw(ball);
			window.draw(leftBar);
			window.draw(rightBar);
		}
		window.display();
	}
	return 0;
}