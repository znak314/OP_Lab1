#pragma warning(disable : 4996
#include"FileLib.h"


// функція для перевірки існування файлу
int is_exist(string Name)
{
	ifstream file(Name);
	if (!file)
		return 0;
	file.close();
	return 1;
}

// Створення файлу
void FileCreate(string Name)
{
	ofstream CreatedFile(Name);
	if (CreatedFile.is_open())
	{
		CreatedFile.close();
		cout << "\t\t\t Файл " << Name << " успішно створено\n";
	}
	else
		cout << "Схоже при створенні файлу сталась помилка\n";
}
void FileCreate(char* Name, char* NewName)
{
	printf("\t\t\t\tУведіть назву файлу (без розширення): ");
	scanf("%s", Name);
	strcpy(NewName, Name);
	strcat(NewName, "_output.txt");
	strcat(Name, ".txt");
	int end = strlen(Name);
	Name[end] = '\0';
	end = strlen(NewName);
	NewName[end] = '\0';

	FILE* file;
	file = fopen(Name, "w");
	if (file)
	{
		printf("\t\t\t\t\t    Файл успішно створено\n");
		fclose(file);
	}
	else {
		printf("Упс! Схоже при створенні файлу сталась помилка!\n");
	}


}

// заповнення файлу
void FileFill(string Name)
{
	ofstream File(Name);

	if (File.is_open())
	{
		srand(time(NULL));
		int NumOfLines = 5 + rand() % (6);

		for (int i = 0; i < NumOfLines; i++)
		{
			int NumOfWords = 5 + rand() % (6);

			for (int k = 0; k < NumOfWords; k++)
			{
				int NumOfLetters = 5 + rand() % (6);

				for (int j = 0; j < NumOfLetters; )
				{
					char symbol = 65 + rand() % (57);
					if (!(symbol > 90 && symbol < 97))
					{
						File << symbol;
						j++;
					}
				}
				File << ". ";
			}
			File << endl;
		}
	}
	else
	{
		cout << "Схоже при відкритті файлу сталась помилка\n";
	}
}
void FileFill(char* Name)
{
	FILE* file;
	file = fopen(Name, "a"); // Відкриття файлу для запису в кінець
	if (file)
	{
		srand(time(NULL));
		int NumOfLines = 5 + rand() % (6);

		for (int i = 0; i < NumOfLines; i++)
		{
			int NumOfWords = 5 + rand() % (6);

			for (int k = 0; k < NumOfWords; k++)
			{
				int NumOfLetters = 5 + rand() % (6);

				for (int j = 0; j < NumOfLetters; )
				{
					char symbol = 65 + rand() % (57);
					if (!(symbol > 90 && symbol < 97))
					{
						fprintf(file, "%c", symbol);
						j++;
					}
				}
				fprintf(file, "%s" ,". ");
			}
			fprintf(file, "%c", '\n');
		}
		printf("\t\t\t\t\tДані успішнно записано у файл\n");
		fclose(file);
	}
	else {
		printf("Упс! Схоже при відкритті файлу сталась помилка\n");
	}
}

//Виведення вмісту файлу
void PrintFile(string Name)
{
	string str;
	ifstream file(Name);

	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, str);
			cout << str << endl;
		}
		file.close();
	}
	else {
		cout << "Схоже при відкритті файлу сталась помилка\n";
	}
}
void PrintFile(char* Name)
{
	char symbol;
	FILE* file;
	file = fopen(Name, "r");
	if (file)
	{
		while ((symbol = fgetc(file)) != EOF)
			printf("%c", symbol);
		fclose(file);
	}
	else {
		printf("Упс! Схоже цей файл не вдалось відкрити\n");
	}
}

// доповнення файлу
void file_append(string Name) {
	char symbol;
	int end = 0;
	ofstream file(Name , ios_base::app);
	while (cin.get() != '\n');		
	while ((symbol = cin.get()) != '0' || !end) {
		if (symbol == '\\') 
			end = 1;
		else if (symbol == -1)
			file << "Я"; //код EOF(-1)
		else 
			file << symbol;
	}
	file << endl;
	file.close();
}
void file_append(char* Name)
{
	char c;
	int signal = 0;
	printf("\t\t\tЩоб закінчити доповнення, введіть символ \\0\n");

	FILE* file = fopen(Name, "a");
	while (fgetc(stdin) != '\n'); 
	while ((c = fgetc(stdin)) != '0' || !signal)
	{
		if (c == '\\')
			signal = 1;
		else if (c == -1)
			fputc('Я', file); // код кінця файлу
		else
			fputc(c, file);
	}
	fputc('\n', file);
	fclose(file);
}

// Перепис у новий файл з заміною букв у парних рядках
void FillNewFile(string OldFile,string NewFile)
{
	ifstream Old(OldFile);
	ofstream New(NewFile);

	string line;
	string word;
	int NumberOfRow = 1;

	// будемо зчитувати строку посимвольно і у випадку зустрічі крапки або пробілу розділяти строку на слова
	if (Old.is_open() && New.is_open())
	{
		while (!Old.eof())
		{
			while (getline(Old, line, '\n'))
			{
				if (NumberOfRow++ % 2 == 0)
				{
					line += ' ';
					char previous; // змінна для збереження останнього символу слова
					int currentIndex = 0; // змінна для збереження поточної позиції символу в строці

					for (char c : line)
					{
						word += c; // додаємо символ до нашого слова
						if (c != ' ' && c != '.')
						{
							previous = c; // зберігаємо записаний символ
							currentIndex++;
						}
						else // якщо зустрінемо крапку або пробіл, то далі йде наступне слово, тобто ми можемо записати поточне сформоване слово у файл
						{
							for (int i = 0; i < currentIndex-1; i++)
							{
								if (word[i] == previous) // заміна букв
									word[i] = '.';
							}
							New << word; // запис слова у файл
							currentIndex = 0; // обнулення індекса
							word.clear(); // очищення слова
							
						}
					}
					New << endl;
				}
			}
		}
		Old.close();
		New.close();
	}
	else
	{
		cout << "\nУпс! Схоже при відкритті файлsd сталась помилка\n";
	}


}
void FillNewFile(char* OldFile, char* NewFile)
{
	FILE* Old, *New;
	Old = fopen(OldFile, "r");
	New = fopen(NewFile, "w");

	char word[15];
	char symbol;
	int index;

	if (Old && New)
	{
		int LineNumber = 1;
		int index = 0;
		
		while ((symbol = fgetc(Old)) != EOF)
		{
			if (LineNumber % 2 == 0)
			{
				if (symbol != ' ' && symbol != '.')
				{
					word[index++] = symbol;
				}
				else {
					for (int i = 0; i < index; i++)
					{
						if (word[i] == word[index-1] && i != index-1) // заміна букв
							word[i] = '.';
						fputc(word[i], New);
					}
					fputc(symbol, New);
					index = 0;
				}
			}
			if (symbol == '\n')
				LineNumber++;
	
		}
		fclose(Old);
		fclose(New);
		
	}
	else {
		printf("Упс! Схоже при виведенні файлу сталась помилка\n");
	}


}

// Видалення слів у непарних рядках файлу
void ReFillFile(string Name)
{
	ifstream file(Name);
	ofstream temp("temporary.txt");

	if (file.is_open())
	{
		string line;
		int NumberOfString = 1;
		while (getline(file, line))
		{
			string word; // строка для збереження слів
			if (NumberOfString++ % 2 == 1)
			{
				int CurrentIndex = 0;
				bool AreWords = 0; // Чи ми записали хоч 1 слово у рядок?
				bool Already = false;
				char LastLetter = 'Я'; // остання літера першого слова

				for (char c : line) // знаходження останньої літери першого слова
				{
					if (c != ' ' && c != '.')
					{
						LastLetter = c;
					}
					else
						break;
				}

				line += ' ';
				for (char c : line)
				{
					if (c != ' ' && c != '.')
					{
						word += c;
						CurrentIndex++;
						Already = false;
					}
					else if (!Already)
					{
						int flag = 1;
						for (int i = 0; i < CurrentIndex; i++)
						{
							if (word[i] == LastLetter)
							{
								flag = 0;
								break;
							}
						}
						if (flag)
						{
							temp << word << ' ';
							AreWords++;
						}
						word.clear();
						CurrentIndex = 0;
						Already = true;
					}

				}
				if (AreWords)
					temp << endl;
			}
			else //Якщо рядок парний, то просто переписуємо його у файл без змін
			{
				temp << line << endl;
			}
		}
		file.close();
		temp.close();

		remove(string(Name).c_str());
		rename("temporary.txt", Name.c_str());
	}
	else {
		cout << "Упс! Схоже при відкритті файлу сталась помилка\n";
	}
}
void ReFillFile(char* Name)
{
	FILE* Old, * New;
	Old = fopen(Name, "r");
	New = fopen("temp.txt", "w");

	char array[20]; // масив останніх символів
	char word[20];
	char c;
	char LastLetter;
	int currentIndex = 0;
	int flag = 0;
	int Line = 1;

	while ((c = fgetc(Old)) != EOF)
	{
		if (!flag && Line % 2)
		{
			if (c != ' ' && c != '.')
			{
				LastLetter = c;
			}
			else
			{
				array[currentIndex++] = LastLetter;
				flag = 1;
			}
		}
		if (c == '\n')
		{
			flag = 0;
			Line++;
		}
	}
	Line = 1;
	currentIndex = 0;
	fclose(Old);
	Old = fopen(Name, "r");
	while ((c = fgetc(Old)) != EOF)
	{
		if (Line % 2)
		{
			if (c != ' ' && c != '.' && c !='\n')
			{
				word[currentIndex++] = c;
			}
			else {
				int point = 1;
				for (int i = 0; i < currentIndex; i++)
				{
					if (word[i] == array[Line - 1 - Line/2])
					{
						point = 0;
						break;
					}
				}
				if (point)
				{
					for (int i = 0; i < currentIndex; i++)
					{
						if (c != '\n')
							fputc(word[i], New);
					}
					if (c != '\n')
						fputc(c, New);
				}
				currentIndex = 0;
			}
		}
		else {
			if (c != '\n')
				fputc(c, New);
		}
		if (c == '\n')
		{
			fputc('\n', New);
			Line++;
		}
	}

	fclose(Old);
	fclose(New);
	remove(Name);
	rename("temp.txt", Name);

}
