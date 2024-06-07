#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
	sf::RenderWindow win(sf::VideoMode(900, 900), "SFML Window");
	sf::CircleShape circle;
	circle.setRadius(100);
	circle.setFillColor(sf::Color(123, 13, 144));
	circle.setPosition(400, 400);
	
	sf::Font font;
	if (!font.loadFromFile("src/arial.ttf"))
		std::cout << "not find styl of text" << std::endl;

	sf::Text text;
	text.setFont(font);
	text.setPosition(350, 150);
	text.setString("Kiss your mom, baby");
	text.setCharacterSize(30);
	text.setColor(sf::Color(76, 234, 51));
	text.setStyle(sf::Text::Bold);
	
	sf::Music music;
	music.openFromFile("src/SmashMouth-AllStar.ogg");
	music.play();

	while (win.isOpen())
	{
		sf::Event ev;
		while (win.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				win.close();
		}
		
		win.clear(sf::Color(132, 14, 55));
		win.draw(circle);
		win.draw(text);
		win.display();
	}


	return 0;
}