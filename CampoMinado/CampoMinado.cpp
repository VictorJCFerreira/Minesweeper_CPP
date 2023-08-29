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

			if(rand() % 5 == 0)
			{
				grid[i][j] = 9;
			}
			else 
			{
				grid[i][j] = 0;
			}

		}
	}

									// Counting the surrounding Mines
	for (int i = 1; i <= 16; i++)
	{
		for (int j = 1; j <= 16; j++)
		{
			int adj = 0;
			if (grid[i][j] == 9) continue;
			if (grid[i + 1][j] == 9) adj++;
			if (grid[i][j + 1] == 9) adj++;
			if (grid[i - 1][j] == 9) adj++;
			if (grid[i][j - 1] == 9) adj++;

			if (grid[i + 1][j + 1] == 9) adj++;
			if (grid[i - 1][j + 1] == 9) adj++;
			if (grid[i + 1][j - 1] == 9) adj++;
			if (grid[i - 1][j - 1] == 9) adj++;

			grid[i][j] = adj;
		}
	
	}



	while (screen.isOpen())
	{

									// Where you are clicking
		Vector2i position = Mouse::getPosition(screen);
		int x = position.x / width;
		int y = position.y / width;

		Event event;
		while (screen.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				screen.close();
			}

									// Clicking event
			if(event.type == Event::MouseButtonPressed)
			{
				if(event.key.code == Mouse::Left) // Left click to reveal the cell
				{
					showGrid[x][y] = grid[x][y];
				} else if (event.key.code == Mouse::Right)	// Right Click for Flag
				{
					showGrid[x][y] = 11;
				}
			}
		}

		screen.clear(Color::White);
		for (int i = 1; i <= 16; i++)
		{
			for (int j = 1; j <= 16; j++)
			{

				if (showGrid[x][y] == 9)
				{
					showGrid[i][j] = grid[i][j];
				}

				sprites.setTextureRect(IntRect(showGrid[i][j] * width, 0, width, width));
				sprites.setPosition(i * width, j * width);
				screen.draw(sprites);
			}
		}

		screen.display();

	}

	return 0;
}