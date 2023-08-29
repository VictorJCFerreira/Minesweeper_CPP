#include <SFML/Graphics.hpp>
#include <time.h>
#include <conio.h>


using namespace sf;

int main() {

	srand(time(0));

	RenderWindow screen(VideoMode(600, 600), "Minesweeper");

	int width = 32;
	int grid[20][20];
	int showGrid[20][20];

	Texture tile;
	tile.loadFromFile("Images/tiles.jpg");
	Sprite sprites(tile);

	for (int i = 1; i <= 16; i++)
	{
		for (int j = 1; j <= 16; j++)
		{
			showGrid[i][j] = 10;
		}
	}


	while (screen.isOpen())
	{
		Event event;
		while (screen.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				screen.close();
			}
		}

		screen.clear(Color::White);
		for (int i = 1; i <= 16; i++)
		{
			for (int j = 1; j <= 16; j++)
			{
				sprites.setTextureRect(IntRect(showGrid[i][j] * width, 1, width, width));
				sprites.setPosition(i * width, j * width);
				screen.draw(sprites);
			}
		}

		screen.display();

	}

	return 0;
}