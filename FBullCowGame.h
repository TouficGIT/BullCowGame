#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//two integers initialised to zero
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Is_NotIsogram,
	Wrong_Lenght,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor
	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetWordLenght() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	FBullCowCount SubmitValidGuess(FString Guess);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
