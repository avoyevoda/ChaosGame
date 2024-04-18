// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;



int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Timber Game!!", Style::Default);

	//resize window for different resolutions
	View view;
	view.setSize(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	view.setCenter(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);
	window.setView(view);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;
	srand((int)time(0));

	Text messageText;
	Text scoreText;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	scoreText.setFont(font);
	scoreText.setString("Score = 0");
	messageText.setFont(font);
	messageText.setString("Click 3 points to make a triangle");
	scoreText.setCharacterSize(30);
	messageText.setCharacterSize(30);
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 20);


	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 3.0f, 1080 / 3.0f);
	



	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{


		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 3)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
				points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
			
			int rv = rand() % 3;
		    ///calculate midpoint between random vertex and the last point in the vector
			Vector2f temp = (vertices[rv] + points.back());
			temp.x = temp.x / 2;
			temp.y = temp.y / 2;

			points.push_back(temp);
			//points.push_back(temp);
		    ///push back the newly generated coord.
			// Update the score text
			std::stringstream ss;
			ss << "Score = " << points.size();
			scoreText.setString(ss.str());
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}

		for(int i = 0; i < points.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(points[i].x, points[i].y));
		    rect.setFillColor(Color::Green);
			if(i == 0)
			{
				rect.setFillColor(Color::Yellow);
			}
		    window.draw(rect);
		}

		if(vertices.size() == 0)
		{
			window.draw(messageText);
		}
		if(points.size() == 0 && vertices.size() == 3)
		{
			messageText.setString("4th click will draw");
			messageText.setFillColor(Color::Yellow);
			window.draw(messageText);
		}
		window.draw(scoreText);
		window.display();
	}
}
