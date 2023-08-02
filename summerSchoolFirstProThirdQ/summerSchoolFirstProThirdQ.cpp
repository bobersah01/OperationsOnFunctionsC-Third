#include <iostream>
#include <string>
using namespace std;

//PART 1
string normalizeText(string notNormalizedText)
{
	string givenText = notNormalizedText; //which means givenText = notNormalizedText
	string textWithoutSpaces = "";
	const string punctuation = ".,:;’”!?()";
	string textWithoutPunc = "";//updated version 
	//string textWithUpperCase = "";

	//for deleting spaces
	for (int i = 0; i < givenText.length(); i++)
	{
		if (givenText[i] != ' ') //If we use double quotes instead of single quotes,
            //there will be an error because we use char as givenText[i] which means we are controlling
            //each character of givenText(notNormalizedText)
		{
            textWithoutSpaces += givenText[i];
		}
	}

	//for deleting punctuations
	for (int i = 0; i < textWithoutSpaces.length(); i++)
	{
		//int counter = 0;
		bool isPunctuation = false;
		for (int j = 0; j < punctuation.length(); j++)
		{
			if (textWithoutSpaces[i] == punctuation[j])
			{
				//counter += 1;
				isPunctuation = true;
				break;
			}
		}
		if (!isPunctuation) //!ispunctuation
		{
			textWithoutPunc += textWithoutSpaces[i];
		}
	}

	/*I deleted spaces in givenText.Now I want to delete punctuations from updated text(textWithoutSpaces)
	Using arrays is the best solving technique. However, since we do not see the arrays,
	I try to solve other ways. If I use array, I enter the punctuations in an array and 
	try to delete them using for loop (iterate each punc.). If text dos not include punc,
	so we will add text.
	*/

	//for uppercase and lowercase operations 
	for (int i = 0; i < textWithoutPunc.length(); i++)
	{
		if (textWithoutPunc[i] >= 'a' && textWithoutPunc[i] <= 'z')
		{
			textWithoutPunc[i] = textWithoutPunc[i] - ('a' - 'A');
		}
		else
		{
			textWithoutPunc[i] = textWithoutPunc[i];
		}
	}
	return textWithoutPunc;
}

//PART 2
string caesarify(const string& inputText, int shiftKey) {
	/*This function is taking two parameters, first is used to determine the string
	that is given by user or in main function. Second is used to shift the input text.
	*/
	string result = ""; //We are creating empty string for encrypting text. 

	for (int i = 0; i<inputText.length();i++) {
		if (isalpha(inputText[i])) { //We are checking whether c is a character or number.
			//If it is character, this condition will be executed.
			//char base = islower(c) ? 'a' : 'A';
			/*
			In this base part, we dont have to do for lower case letters because
			the question indicates that you may assume that the input text is normalized
			which means we can delete for lowercase letter. 
			We can arrange base to 'A' upper A.
			*/
			char shiftedChar = ((inputText[i] - 'A' + shiftKey) % 26) + 'A';
			result += shiftedChar;
		}
		else {
			//If it is not character, so this is a number, this condition will be executed.
			//Therefore, that number will be same.
			result += inputText[i]; // Non-alphabetic character, keep as is.
		}
	}
	return result;
}

//PART 3
string groupify(const string& inputText, int groupNumber) {

	//I am using two parameters in the function, first is used to determine the text.
	//Second is used to define the group number which means you are determining the group of characters.

	string result = "";
	int remainingLetters = inputText.length();
	int currentIndex = 0; //Indicates the index of given text.

	//We are creating a while loop. This condition will be executed until the number of input text
	//equals 0 or smaller than 0. 
	while (remainingLetters > 0) {
		int groupLength = min(groupNumber, remainingLetters); //this is for forming last group.
		//We are taking minimum of these parameters as do not go behind of whole text.

		//This is for creating a group with starting from first index of the whole text.
		for (int i = 0; i < groupLength; ++i) {
			result += inputText[currentIndex + i];
		}

		//When the group length is smaller than group number we have to append small x to the result
		//or to the group. For example our group number is 2 and group length is 1, 
		//we have to fill the empty blanks with small x as much as needed.
		if (groupLength < groupNumber) {
			//We are adding small x as much as padding number. 
			int padding = groupNumber - groupLength;
			for (int i = 0; i < padding; ++i) {
				result += 'x';
			}
		}

		//At the same time, we are appending spaces to seperate the groups.
		if (remainingLetters > groupLength) {
			result += ' ';
		}

		//To move to next group, we are doing some operations.
		currentIndex += groupLength;
		remainingLetters -= groupLength;
	}

	return result; //Result is composed of group of characters.
}

//PART4
//This is the function that takes all of functions that we created above.
//Additionally, this is used for all of the functions in a function. 
//When we call this function, also we are calling other functions that are created above.

string encryptString(const string& inputText, int shiftKey, int groupSize) {

	//This function is taking three parameters, first is used to take the text from the user.
	//Second is used to determine the shifted characters.
	//Third is used to define the group the characters.

	string normalizedText = normalizeText(inputText);
	string encryptedText = caesarify(normalizedText, shiftKey);
	string cyphertext = groupify(encryptedText, groupSize);

	return cyphertext; //We are returning grouped text at the end of the program.
}

//This is the main function. We can call all functions in the main. Despite of calling all functions,
//we can call only encryptString function that includes all of the functions created above.
//However, we can show all of the functions and their operations.
int main()
{

	cout << "NORMALIZED FUNCTION: " << endl;
	string userText = normalizeText("Keep calm,) (and,! go ahead ");
	cout <<"Normalized text: " << userText << endl;

	cout << "---------------------------------" << endl;

	cout << "CAESARIFY FUNCTION: " << endl;
	int shift = 1; //The second parameter of the encrpting function.
	string originalText = "OMERSAHINEMELNAZCETIN"; //The first parameter of the encrypting function.
	string encryptedText = caesarify(originalText, shift); //Storing encrypted text in a string.
	cout << "Encrypted text: " << encryptedText << endl;

	cout << "---------------------------------" << endl;

	cout << "GROUPIFY FUNCTION: " << endl;
	int groupNumber = 2;
	string inputText = "HELLOGUYS";
	string groupedText = groupify(inputText, groupNumber);
	cout << "Grouped text: " << groupedText << endl;

	cout << "---------------------------------" << endl;

	cout << "ENCRYPT STRING FUNCTION: " << endl;
	string input = "Keep calm,) (and,! go ahead "; //this is same asuser text input.
	int shifted = 3;
	int groupSize = 2;
	string cyphertext = encryptString(input, shifted, groupSize);
	cout << "Cypher text: " << cyphertext << endl;
	cout << "---------------------------------" << endl;
}

