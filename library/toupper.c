/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

int toupper(int c) {
	if (c >= 'a' && c <= 'z') {
		return c - 'a' + 'A';
	}
	return c;
}

