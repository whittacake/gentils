/*This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either 
version 2.1 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public 
License along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int 
main(int argc, char *argv[])
{
	char *currentPath;
	char c;

	c = getopt(argc, argv, "L");

	if (c == 'L')
		currentPath = getenv("PWD");
	else	
		currentPath = getcwd(NULL, 0);

	printf("%s\n", currentPath);

	return 0;
}
