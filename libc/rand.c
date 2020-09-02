/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

/* Random library */
#include <library/stdlib.h>
#include <library/types.h>

static uint32_t x = 123456789;
static uint32_t y = 362436069;
static uint32_t z = 521288629;
static uint32_t w = 88675123;

uint32_t rand(uint32_t min, uint32_t max)
{
	static uint32_t state = 0xF3DC1A24;
	state = (state * 1299721) + 29443;
	return min + ((state >> 16) % (max - min + 1));
}

void srand(unsigned int seed) {
	w ^= seed;
}
