#pragma once

#include<stdlib.h>

#define cellSize 4
#define width OLED_DISPLAY_WIDTH/cellSize
#define height OLED_DISPLAY_HEIGHT/cellSize
#define MUTATION_THRESHOLD  (int) (.07 * (float) RAND_MAX)
#define UPDATE_INTERVAL 250
#define FAST_UPDATE_INTERVAL 50
#define STOP_UPDATING_TIMEOUT 30000

static int queuedUpdates = 0;
static uint16_t lastUpdate = 0;
static uint16_t lastKeyPress = 0;
static bool runUpdates = true;

bool stateA[width][height];
bool stateB[width][height];

bool currentIsA = true;

bool getState(int x, int y) {
	if (x < 0 || x >= width) {
		return false;
	}
	if (y < 0 || y >= height) {
		return false;
	}

	if (currentIsA) {
		return stateA[x][y];
	} else {
		return stateB[x][y];
	}
}

void setNextState(int x, int y, bool alive) {
	if (currentIsA) {
		stateB[x][y] = alive;
	} else {
		stateA[x][y] = alive;
	}
}

void draw(int x, int y, bool alive) {
	int startX = x * cellSize;
	int startY = y * cellSize;
	for (int i = startX; i < startX + cellSize; i++) {
		for (int j = startY; j < startY + cellSize; j++) {
			oled_write_pixel(i, j, alive);
		}
	}
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	srand(timer_read());
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			stateA[i][j] = rand() % 2 == 0;
		}
	}

	return OLED_ROTATION_0;
}

void update(bool shouldMutate, bool shouldDrawChanges) {
	int totalAlive = 0;
	for (int x=0; x<width; x++) {
		for (int y=0; y<height; y++) {
			int neighbors = 0;
			for (int xOffset=-1; xOffset<=1; xOffset++) {
				for (int yOffset=-1; yOffset<=1; yOffset++) {
					if ((xOffset != 0 || yOffset != 0) && getState(x + xOffset, y + yOffset)) {
						neighbors++;
					}
				}
			}

			bool curr = getState(x, y);

			bool next;
			if (curr) {
				if (neighbors == 2 || neighbors == 3) {
					next = true;
				} else {
					next = false;
				}
			} else {
				if (neighbors == 3) {
					next = true;
				} else if (neighbors < 3) {
					next = shouldMutate && rand() < MUTATION_THRESHOLD;
				} else {
					next = false;
				}
			}
			setNextState(x, y, next);

			if (next) {
				totalAlive++;
			}
			// Try not to render mutation updates
			if (next != curr && (!next || neighbors == 3)) {
				draw(x, y, next);
			}
		}
	}

	currentIsA = !currentIsA;
}

bool oled_task_user(void) {
	uint32_t timeSinceKeypress = timer_elapsed(lastKeyPress);
	uint32_t timeSinceUpdate = timer_elapsed(lastUpdate);
	if (queuedUpdates == 0 && (!runUpdates || timeSinceKeypress > STOP_UPDATING_TIMEOUT)) {
		runUpdates = false;
		return false;
	}

	if ((timeSinceKeypress < UPDATE_INTERVAL && timeSinceUpdate > FAST_UPDATE_INTERVAL) || timeSinceUpdate > UPDATE_INTERVAL) {
		uprintf("Last key press was %d ms ago\n", timeSinceKeypress);
		bool shouldMutate = queuedUpdates > 0;
		update(shouldMutate, true);
		if (queuedUpdates > 0) {
			queuedUpdates--;
		}

		lastUpdate = timer_read();
	}
	runUpdates = true;

	return false;
}
