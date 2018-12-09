#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using Ftext = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
Ftext GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; // instantiate a new game

//the entry point for our application
int main() {

	bool bPlayAgain;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		Ftext Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls : " << BullCowCount.Bulls;
		std::cout << ". Cows : " << BullCowCount.Cows;
		std::cout << std::endl;

		//repeat the guess back to him
		std::cout << "Your guess is : " << Guess;
		std::cout << std::endl;
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

void PrintGameSummary() {

	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE ! YOU WIN \n";
	}
	else {
		std::cout << "BETTER LUCK NEXT TIME";
	}

}


//introduce the game
void PrintIntro() {

	std::cout << "Welcome to Bulls and Cows Game" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetWordLenght();
	std::cout << " letter isogram I'm thinking off ?" << std::endl;
	std::cout << std::endl;

}

//get a guess from the player
Ftext GetValidGuess() {

	EGuessStatus Status = EGuessStatus::Invalid_Status;
	Ftext Guess = "";

	do {
		int32 MyCurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try ";
		std::cout << MyCurrentTry;
		std::cout << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess : ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetWordLenght() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		case EGuessStatus::Is_NotIsogram:
			std::cout << "Please enter a word without repeating letters.\n";
		default:;
			// assume the guess is valid
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{

	std::cout << "\nDo you want to play again ? (y/n)\n" << std::endl;
	Ftext Response = "";
	getline(std::cin, Response); 
	return (Response[0] == 'Y' || Response[0] == 'y');
}
