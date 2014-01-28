#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

int main(){
	return 0;
}

int cardValue(char *card_name)
{
	int val = 0;
	switch(card_name[0]) {
		case 'K':
		case 'Q':
		case 'J':
			val = 10;
			break;
		case 'A':
			val = 11;
			break;
		case 'X':
			break;
		default:
			val = atoi(card_name);
			if ((val < 1) || (val > 10)) {
				puts ("I don't understand that value!");
				break;
			}
	}
	return val;
}