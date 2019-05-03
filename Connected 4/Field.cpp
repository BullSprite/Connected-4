#include "Field.h"

Field::Field() {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			field[i][j] = 0;
	result = 0;
}