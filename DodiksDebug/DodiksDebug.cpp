/**
 * @file DodiksDebug.cpp
 * @author Мусаев П.П., гр. 515и
 * @date 15 лютого 2021
 * @brief Лабораторная работа №1
 *
 * Розгауження та вибір. Завдання 2
 */

 // Константа ширини вагону та ширини кімнати кондуктора
#define WIDTH 2.f
#define CONDUCTOR 1.5f

// Підключення бібліотек
#include <stdio.h>
#include <clocale>
#include <math.h>

// Функція обробки посадчних місць
void ProcessSeat(int seat);
// Функція визначення верхнього, чи нижнього місця
void TopDownSeat(int seat);

// Функція визначення номеру купе
int GetKupe(int seat);
// Конвертація номеру купе в римський аналог
const char* roman(int number);

// Функція визначення найкоротшого шляху до туалету
float GetDistanceWC(int kupe);

int main()
{
	// смена кодовой таблицы символов - включение русского языка
	setlocale(LC_ALL, "Rus");
	// Друге завдання
	int seat;
	printf("Введите место посадки\n");
	scanf_s("%d", &seat);
	ProcessSeat(seat);

}


/* Релізація методів */

void ProcessSeat(int seat)
{
	// Місця до 37-го відносяться до купе
	if (seat > 0 && seat < 37)
	{
		printf("У вас купе: %s\n", roman(GetKupe(seat))); // Одразу конвертуємо номер купе у строковий параметер 
		TopDownSeat(seat);
		printf("Расстояние до туалета: %0.1f метра", GetDistanceWC(GetKupe(seat)));
	}
	else if (seat > 36 && seat < 55) // Більші та менші за 55 місця - бокові
	{
		printf("У вас боковое место\n");
		TopDownSeat(seat);
		printf("Расстояние до туалета: %0.1f метра", GetDistanceWC(GetKupe(seat)));
	}
	else // Невірний ввод
	{
		printf("Указанного места не существует");
	}
}

float GetDistanceWC(int kupe)
{
	float distance;

	// Для купе, які менші за 5 шлях коротший до лівого туалету
	if (kupe < 5)
	{
		// Беремо половину ширини вагону (середину), потім до купе пассажира додаємо купе пассажира мінус один, множимо його на ширину купе та додаємо ширину кімнаті кондуктора
		distance = WIDTH / 2.f + ((float)kupe - 1.f) * WIDTH + CONDUCTOR;
	}
	// Іншим - коротший до правого туалету
	else
	{
		// Беремо половину ширини вагону (середину), потім до купе пассажира додаємо дев'ять мінус пассажирське купе помножене на ширину купе
		distance = WIDTH / 2.f + ((9.f - float(kupe)) * WIDTH);
	}

	return distance;
}

// Верхнє чи нижнє 
void TopDownSeat(int seat)
{
	seat % 2 == 0 ? printf("Верхнее место\n") : printf("Нижнее место\n");
}

// Парсинг у римські числа
const char* roman(int number)
{
	// Якщо номер купе меньше або дорінює 0 - прирівняти до 1
	number <= 0 ? number = 1 : number = number;
	// Массив рядків
	const char* romans[10] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

	// Повертаємо на 1 меньший номер, бо індексація починається з 0
	return romans[number - 1];
}

// Оскільки в кожному купе по 4 місця - ми ділемо на 4 за модулем, де ціле є купе
int GetKupe(int seat)
{
	// Якщо ділиться без залишку - присвоїти операцію, в іншому випадку додати 1 (через те, що ціле в інших місць на 1 меньше за номер купе)
	if (seat < 37)
		seat % 4 == 0 ? seat /= 4 : seat = seat / 4 + 1;
	// Дызнатися яке купе знаходиться навпроти бокового місця
	else
		seat = (float)seat / 2.f - 28.f;
	// Повертаємо модуль числа
	return fabsf(seat);
}

