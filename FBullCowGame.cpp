#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetWordLenght() const { return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLenghtMaxTries{ {3,4},{4,7},{5,10},{6,16} };
	return WordLenghtMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	bGameIsWon = false;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if the guess isn't an isogram
	{
		return EGuessStatus::Is_NotIsogram;
	}
	else if (!IsLowerCase(Guess)) //if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetWordLenght()) //if the guess lenght is wrong
	{
		return EGuessStatus::Wrong_Lenght;
	}
	else
	{
		return EGuessStatus::OK;
	}
	return EGuessStatus::OK; // TODO Make actual error
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//increment the turn number
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length();

	//loop through all letters in the hidden word

	for (int32 HWChar = 0; HWChar < WordLenght; HWChar++) {

		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLenght; GChar++) {

			if (Guess[GChar] == MyHiddenWord[HWChar]) {
				if (HWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}

		}

	}

	if (BullCowCount.Bulls == WordLenght) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {

		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false; //we do not have a Isogram
		}
		else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{

	for (auto Letter : Word) {

		if (!islower(Letter)) {
			return false;
		}


	}

	return true;
}
