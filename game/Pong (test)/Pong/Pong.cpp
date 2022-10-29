#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
using namespace sf;
#define PI 3.1416
#define scrWidth 1000
#define scrHeight 700
#define barSize left.getSize()

int main()
{
    // Tao cua so
    RenderWindow a(VideoMode(1000, 700), "test");
    // Tao qua bong
    CircleShape ball(10.f);
    ball.setFillColor(Color(224, 245, 66));
	ball.setOutlineThickness(3);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setPosition(scrWidth / 2, scrHeight / 2);
    // Tao thanh trai
    RectangleShape left(Vector2f(30.f, 200.f));
    left.setFillColor(Color(144, 3, 252)); 
    left.setPosition(Vector2f(0.f, 400.f-100.f));
	left.setOutlineThickness(3);
    left.setOrigin(barSize.x / 2, barSize.y / 2);
    left.setPosition(0, scrHeight / 2);
	// Tao thanh phai
	RectangleShape right(Vector2f(30.f, 200.f));
	right.setFillColor(Color(144, 3, 252));
	right.setOutlineThickness(3);
	right.setOrigin(barSize.x / 2, barSize.y / 2);
	right.setPosition(scrWidth, scrHeight / 2);
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
    //
    bool isPlaying = false;
    bool isModeOn = false;
    while (a.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event thao_tac;
     
        while (a.pollEvent(thao_tac))
        {
            if (thao_tac.type == sf::Event::Closed)
                a.close();
        }
        if (!isPlaying && Keyboard::isKeyPressed(Keyboard::Enter))
        {
            isPlaying = true;
            ball.setPosition(scrWidth / 2, scrHeight / 2);
            left.setPosition(0, scrHeight / 2);
            do
            {
                angleBall = rand() % 360;
            } while (angleBall < 45 || (angleBall > 135 && angleBall < 225) || angleBall > 315);
        }
		if (isPlaying)
		{
			//Ball moving
			float factor = ballSpeed * deltaTime;
			ball.move(sin(angleBall * PI / 180) * factor, -cos(angleBall * PI / 180) * factor);

			//Touch Top or bot (Dap vao 2 canh tren duoi)
			if (ball.getPosition().y - ball.getRadius() <= 0 || ball.getPosition().y + ball.getRadius() >= scrHeight)
			{
				angleBall = 180 - angleBall;
			}

			//Touch Bar (Dap vao thanh do)
			//LeftBar
			if (ball.getPosition().x - ball.getRadius() - barSize.x / 2 <= 0
				&& ball.getPosition().y >= left.getPosition().y - barSize.y / 2
				&& ball.getPosition().y <= left.getPosition().y + barSize.y / 2
				&& ball.getPosition().x > left.getPosition().x)
			{
				angleBall = 360 - angleBall + rand() % 10;
			}
			//LeftBar moving
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (left.getPosition().y - barSize.y / 2 - barSpeed * deltaTime <= 0)
				{
					left.setPosition(0, barSize.y / 2);
				}
				else left.move(0, -barSpeed * deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (left.getPosition().y + barSize.y / 2 + barSpeed * deltaTime >= scrHeight)
				{
					left.setPosition(0, scrHeight - barSize.y / 2);
				}
				else left.move(0, barSpeed * deltaTime);
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
			if (right.getPosition().y - barSize.y / 5 > botTarget)
			{
				if (right.getPosition().y - barSize.y / 2 - barSpeed * deltaTime <= 0)
				{
					right.setPosition(scrWidth, barSize.y / 2);
				}
				else right.move(0, -barSpeed * deltaTime);
			}
			if (right.getPosition().y + barSize.y / 5 < botTarget)
			{
				if (right.getPosition().y + barSize.y / 2 + barSpeed * deltaTime >= scrHeight)
				{
					right.setPosition(scrWidth, scrHeight - barSize.y / 2);
				}
				else right.move(0, barSpeed * deltaTime);
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
			a.clear(Color::Black);
			if (isPlaying)
			{
				a.draw(ball);
				a.draw(left);
				a.draw(right);
			}
			a.display();
    }
    return 0;
}