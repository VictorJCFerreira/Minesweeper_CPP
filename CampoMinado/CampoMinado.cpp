#include <SFML/Graphics.hpp>
#include <time.h>
#include <conio.h>


using namespace sf;


int width = 32;
int rows = 16;
int cols = 16;
int grid[18][18];
int showGrid[18][18];
int bombCount = 0;
const int totalBomb = 50;


// function that shows the Open spaces
void revealAdjacentCells(int x, int y) {
	if (x < 1 || x > rows || y < 1 || y > cols || showGrid[x][y] != 10) {
		return;
	}

	showGrid[x][y] = grid[x][y];
	if (grid[x][y] == 0) {
		revealAdjacentCells(x + 1, y);
		revealAdjacentCells(x - 1, y);
		revealAdjacentCells(x, y + 1);
		revealAdjacentCells(x, y - 1);
		revealAdjacentCells(x + 1, y + 1);
		revealAdjacentCells(x - 1, y + 1);
		revealAdjacentCells(x + 1, y - 1);
		revealAdjacentCells(x -1 , y - 1);

	}
}



int main() {


	srand(time(0));

	RenderWindow screen(VideoMode(580, 580), "Minesweeper");

	Texture tile;
	tile.loadFromFile("Images/tiles.jpg");
	Sprite sprites(tile);


	// Placing Bombs and Covered Cells
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= cols; j++)
		{
			showGrid[i][j] = 10;

			if(bombCount < totalBomb && rand() % 5 == 0)
			{
				grid[i][j] = 9;
				bombCount++;
			}
			else 
			{
				grid[i][j] = 0;
			}

		}
	}


	// Counting the surrounding Mines
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= cols; j++)
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
				// Left click to reveal the cells 
				if(event.key.code == Mouse::Left) 
				{
					showGrid[x][y] = grid[x][y];
					//for empty cells
					if (grid[x][y] == 0) 
					{
						revealAdjacentCells(x + 1, y);
						revealAdjacentCells(x - 1, y);
						revealAdjacentCells(x, y + 1);
						revealAdjacentCells(x, y - 1);
					}
				} 
				// Right Click for Flag
				else if (event.key.code == Mouse::Right)	
				{
					showGrid[x][y] = 11;
				}
			}
		}


		screen.clear(Color::White);
		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= cols; j++)
			{
				//ending when clicking a bomb
				if (showGrid[x][y] == 9)
				{
					showGrid[i][j] = grid[i][j];
				}

				//render cells in the screen
				sprites.setTextureRect(IntRect(showGrid[i][j] * width, 0, width, width));
				sprites.setPosition(i * width, j * width);
				screen.draw(sprites);
			}
		}

		screen.display();

	}

	return 0;
}