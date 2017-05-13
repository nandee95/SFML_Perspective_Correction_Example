#include <SFML\Graphics.hpp>

#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#else
#pragma comment(lib,"sfml-graphics-2.lib")
#pragma comment(lib,"sfml-system-2.lib")
#pragma comment(lib,"sfml-window-2.lib")
#endif


void main()
{
	sf::Texture texture;
	texture.loadFromFile("chess.jpg");
	//texture.setSmooth(true);
	texture.generateMipmap();


	sf::RenderWindow window(sf::VideoMode(800,600), "Perspective correction");
	window.setFramerateLimit(60);
	sf::Shader shader;
	shader.loadFromFile("pers.vert", "pers.frag");


	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				return;
			}
			sf::VertexArray va(sf::Quads, 4);
			const float trap_wide = 400;
			const float trap_narrow = 200;
			const float mid = 400;
			const sf::Vector2f shift = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))-sf::Vector2f(mid,470);
			va.append(sf::Vertex(sf::Vector2f(mid - trap_wide / 2, 10), sf::Color(0.0f, 0.0f, 0.0f, trap_wide / 600.f*255.f)));
			va.append(sf::Vertex(sf::Vector2f((mid+shift.x) - trap_narrow / 2, 470+shift.y), sf::Color(trap_narrow / 600.f*255.f, 0.f, 0.0f, trap_narrow / 600.f*255.f)));
			va.append(sf::Vertex(sf::Vector2f((mid+shift.x) + trap_narrow / 2, 470+shift.y), sf::Color(trap_narrow / 600.f*255.f, trap_narrow / 600.f*255.f, 0.0f, trap_narrow / 600.f*255.f)));
			va.append(sf::Vertex(sf::Vector2f(mid + trap_wide / 2, 10), sf::Color(0, trap_wide / 600.f*255.f, 0.0f, trap_wide / 600.f*255.f)));

			window.clear(sf::Color(100,100,100));
			sf::RenderStates states;
			states.texture = &texture;
			states.shader = &shader;
			window.draw(va,states);

			window.display();
		}
	}
}
