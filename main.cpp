#include"FileLib.h"


int main(int argc, char* argv[])
{
	// налаштування мови
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// виведення поточного режиму роботи
	cout << "\t\t\t\t\tПоточний режим роботи - [" << argv[1] << ' ' << argv[2] << "]\n";
	char exit;

	do // для зациклення програми
	{
		if (string(argv[2]) == "FilePointer")
		{
			// робота з файлами 
			char* file, // ім'я файлу 
				* NewFile, // ім'я нового файлу
				* buff, // буфер
				opt;  //змінна для збереження вибору опцій 

			// Виділяємо пам'ять 
			file = (char*)malloc(50); // Для назв файлів виділяємо максимум 50 байт
			NewFile = (char*)malloc(50); 
			buff = (char*)malloc(350);

			FileCreate(file, NewFile);
			printf( "Для ручного заповнення файлу натисність esc\n Для автоматичного заповнення натисніть будь-яку іншу клавішу\n\n");
			opt = _getch();
			if (opt != 27)
			{
				FileFill(file);
				printf("Бажаєте доповнити файл?\n esc - так\n Інша клавіша - ні\n");
				if (_getch() == 27)
				{
					file_append(file);
				}
			}
			else
			{
				file_append(file);
			}
			printf("\t\t\t\t      Вміст вхідного файлу:\n\n");
			PrintFile(file);

			//Перепис у новий файл з заміною букв у парних рядках
			FillNewFile(file, NewFile);
			printf("\n\t\t\t\t      Вміст нового файлу:\n\n");
			PrintFile(NewFile);

			ReFillFile(file);
			printf("\n\t\t\t\t      Вміст зміненого файлу:\n\n");
			PrintFile(file);

			free(file);
			free(NewFile);
			free(buff);
		}
		else if (string(argv[2]) == "FileStream")
		{
			string FileName, // назва вхідного файлу
				NewFileName; //назва нового файлу
			char opt; // змінна для збереження вибору опцій

			cout << "Уведіть назву файлу (без розширення): ";
			cin >> FileName;
			FileName += ".txt";
			NewFileName = "New_" + FileName;

			if (is_exist(FileName))
			{
				cout << "\t\t\t\t\t\t     Вміст файлу:\n";
				PrintFile(FileName);
				// Користувач обирає, чи хоче доповнити файл
				cout << "\t\t\t\t\t\tБажаєте доповнити файл?\n";
				cout << "\t\t(Натисніть esc, щоб доповнити або будь-яку іншу клавішу, щоб продовжити роботу з файлом)\n"; 
				opt = _getch();
				if (opt == 27)
				{
					cout << "\t\t\t\tЩоб закінчити доповнення, введіть символ \\0\n";
					file_append(FileName);
					cout << "\t\t\t\t\t\tВміст оновленого файлу:\n";
					PrintFile(FileName);
				}
			}
			else {
				// Якщо файлу з таким ім'ям ще не існує, то створюємо його
				FileCreate(FileName);
				cout << "Для ручного заповнення файлу натисність esc" << endl
					<< "Для автоматичного заповнення натисніть будь-яку іншу клавішу\n" << endl;
				if (_getch() != 27)
				{
					FileFill(FileName);
					cout << "\t\t\t\t\t\t     Вміст файлу:\n";
					PrintFile(FileName);
				}
				else
				{
					cout << "\t\t\t\tЩоб закінчити запис, введіть символ \\0\n";
					file_append(FileName);
					cout << "\t\t\t\t\t\t     Вміст файлу:\n";
					PrintFile(FileName);
				}

			}

			// Перепис у новий файл з заміною букв у парних рядках
			FillNewFile(FileName, NewFileName);
			cout << "\n\t\t\t\t\t\tВміст нового файлу:\n";
			PrintFile(NewFileName);

			// Видалення слів у непарних рядках файлу
			ReFillFile(FileName);
			cout << "\n\t\t\t\t\t\tВміст зміненого файлу:\n";
			PrintFile(FileName);
		
		}
		else
		{
			cout << "Упс! Схоже, програма не підтримує цей режим роботи\n";
		}



		cout << "\n\tНатисніть esc для завершення роботи з програмою або будь-яку іншу клавішу, щоб продовжити\n";
		exit = _getch();
	} while (exit != 27);


	return 0;
}
