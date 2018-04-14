#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 22

char field[FIELD_HEIGHT][FIELD_WIDTH];
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH];

enum
{
	MINO_TYPE_I,
	MINO_TYPE_O,
	MINO_TYPE_S,
	MINO_TYPE_Z,
	MINO_TYPE_J,
	MINO_TYPE_L,
	MINO_TYPE_T,
	MINO_TYPE_MAX
};

enum
{
	MINO_ANGLE_0,
	MINO_ANGLE_90,
	MINO_ANGLE_180,
	MINO_ANGLE_270,
	MINO_ANGLE_MAX
};

#define MINO_WIDTH 4
#define MINO_HEIGHT 4

char minoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_HEIGHT][MINO_WIDTH] =
{
	//MINO_TYPE_I,
	{
		//MINO_ANGLE_0
		{
			0,1,0,0,
			0,1,0,0,
			0,1,0,0,
			0,1,0,0
		},
	//MINO_ANGLE_90
		{
			0,0,0,0,
			0,0,0,0,
			1,1,1,1,
			0,0,0,0
		},
	//MINO_ANGLE_180
		{
			0,0,1,0,
			0,0,1,0,
			0,0,1,0,
			0,0,1,0
		},
	//MINO_ANGLE_270
		{
			0,0,0,0,
			1,1,1,1,
			0,0,0,0,
			0,0,0,0 
		}
	//MINO_ANGLE_MAX
	}
	//MINO_TYPE_O,
	//MINO_TYPE_S,
	//MINO_TYPE_Z,
	//MINO_TYPE_J,
	//MINO_TYPE_L,
	//MINO_TYPE_T,

};

int minoType = 0, minoAngle = 0;
int minoX = 5, minoY = 0;

void display()
{
	memcpy(displayBuffer, field, sizeof(field));

	for (int iy = 0; iy < MINO_HEIGHT; iy++)
	{
		for (int ix = 0; ix < MINO_WIDTH; ix++)
		{
			displayBuffer[minoY + iy][minoX + ix] |= minoShapes[minoType][minoAngle][iy][ix];
		}
	}

	system("cls");
	for (int iy = 0; iy < FIELD_HEIGHT; iy++)
	{
		for (int ix = 0; ix < FIELD_WIDTH; ix++)
		{
			printf(displayBuffer[iy][ix] ? "¡" : "@");
		}
		printf("\n");
	}
}

bool isHit(int _minoX, int _minoY, int _minoType, int _minoAngle)
{
	for (int i = 0; i < MINO_HEIGHT; i++)
	{
		for (int j = 0; j < MINO_WIDTH; j++)
		{
			if (minoShapes[_minoType][_minoAngle][i][j]
				&& field[_minoY + i][_minoX + j])
			{
				return true;
			}
		}
	}
	return false;
}

int main()
{
	memset(field, 0, sizeof(field));

	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		field[i][0] = field[i][FIELD_WIDTH - 1] = 1;
	}

	for (int i = 0; i < FIELD_WIDTH; i++)
	{
		field[FIELD_HEIGHT - 1][i] = 1;
	}

	time_t t = time(NULL);
	while (1)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			//case 'w':
			case 's': 
				if (!isHit(minoX, minoY + 1, minoType, minoAngle)) minoY++;
				break;
			case 'a': 
				if (!isHit(minoX - 1, minoY, minoType, minoAngle)) minoX--;
				break;
			case 'd':
				if (!isHit(minoX + 1, minoY, minoType, minoAngle)) minoX++;
				break;
			case 0x20:
				if (!isHit(minoX, minoY, minoType, (minoAngle + 1) % MINO_ANGLE_MAX))
				minoAngle = (minoAngle + 1) % MINO_ANGLE_MAX;

			default:
				break;
			}
			display();
		}

		if (t != time(NULL))
		{
			t = time(NULL);

			if (isHit(minoX, minoY + 1, minoType, minoAngle))
			{
				for (int i = 0; i < MINO_HEIGHT; i++)
				{
					for (int j = 0; j < MINO_WIDTH; j++)
					{
						field[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
					}
				}

				minoX = 5;
				minoY = 0;
				minoType = 0;//rand() % MINO_TYPE_MAX;
				minoAngle = 0;//rand() % MINO_ANGLE_MAX;

			}
			else
			{
				minoY++;
			}

			display();
		}
	}


	_getch();
}
