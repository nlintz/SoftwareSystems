/*
  cards.c
  hw01

  Created by Nathan Lintz on 12/28/13.
  Copyright (c) 2013 Nathan Lintz. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>

/* Takes a card name and returns what the cards value 
	is according to blackjack rules
	
	Error handling is done to ensure that the cards 
	value is between 1 and 10 if its not a face or ace

	card_name[]: array holding the name of the card
*/
int cardValue(char card_name[])
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

/* Prompts the user to enter a card name and puts the response 
	in an array

	User input is truncated to two characters

	card_name[]: array holding the name of the card
*/
void cardName(char card_name[3])
{
	puts("Enter the card_name: ");
	scanf("%2s", card_name);
}

/* Computes the change in count based on what the card value is. 
	Returns the updated count of the cards.

	count: integer holding the current count
	card_value: integer holding what the cards numeric value is 
		according to blackjack counting
*/
int cardCount(int count, int card_value)
{
	if ((card_value > 2) && (card_value < 7)) {
		return count+1;
	} else if (card_value == 10) {
		return count-1;
	}
	return count;
}

/* Runs the card counting program. The user enters what card they
	see and the current card count is returned

*/
int main()
{
	char card_name[3];
	int count = 0;
	int card_value;

	while (card_name[0] != 'X') {
		cardName(card_name);

		if (card_name[0] == 'X'){
			break;
		}
		
		card_value = cardValue(card_name);
		count = cardCount(count, card_value);
		printf("Current count: %i\n", count);
	}
	return 0;
}
