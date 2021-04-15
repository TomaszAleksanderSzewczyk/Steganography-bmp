/** @file */
#pragma once



/** Program sprawdza czy podana ilo�� argument�w jest poprawna. Je�eli nie to wyswietla polecenie
@param argc liczba argument�w programu
@param argv tablica argument�w programu*/
void kontrola_argumentow(int argc, int** argv);

/** Funkcja oblicza d�ugo�� nag��wka pliku .bmp
@param bmp_offset wska�nik na plik .bmp
@return d�ugo�� podanego pliku .bmp
*/
int znajdz_d�ugo��_nag�owka(FILE** bmp_offset);

/** Funkcja znajduje g��bi� kolor�w pliku .bmp
@param bmp_offset wska�nik na plik .bmp
@return zwraca g��bi� kolor�w pliku .bmp*/
int znajdz_glebie_kolorow(FILE** bmp_offset);

/**Funkcja wypisuje b��d je�eli g��bia kolor�w pliku przekazanego przez u�ytkownika jest b��dna
@param source_file plik g��wny
@param secret_file plik do zaszyfrowania
@param output_file plik wychodz�cy
@param depth warto�� g�ebi*/
void b��dna_g��bia_kolor�w(FILE** source_file, FILE** secret_file, FILE** output_file, int depth);

/**Funkcja zwraca d�ugo�� pliku
@param fp wska�nik na plik .bmp
@return zwraca d�ugo�� pliku */
int znajdz_dlugosc_pliku(FILE** fp);

/**Funkcja zwraca podany bit z okre�lonego bajtu
@param the_byte wskazany bajt
@param which_bit kt�ry bit w podanym bajcie
@return warto�� wskazanego bitu */
int pobierz_bit(char the_byte, int which_bit);

/**Funkcja zamyka pliki
@param source_file plik �r�d�owy
@param secret_file plik do zaszyfrowania
@param output_file plik wyj�ciowy*/
void zamknij_pliki(FILE** source_file, FILE** secret_file, FILE** output_file);

/** Funkcja sprawdza czy plik do zaszyfrowania zmie�ci si� w pliku �r�d�owym
@param secret_file_length d�ugo�� pliku do zaszyfrowania
@param file_length d�ugo�� pliku �r�d�owego
@param offset d�ugo�� nag��wka pliku .bmp
@param argv tablica argument�w programu
@param R ilo�� bit�w jaka ma by� przeznaczona dla odcieni czerwieni
@param G ilo�� bit�w jaka ma by� przeznaczona dla odcieni zieleni
@param B ilo�� bit�w jaka ma by� przeznaczona dla odcieni niebieskiego
@param depth warto�� g��bi pliku danego przez u�ytkownika
*/
int sprawdzanie_pamieci(int secret_file_length, int file_length, int offset, char** argv, int R, int G, int B, short depth);

/** Funkcja otwiera pliki podane przez u�ytkownika
@param argv tablica argument�w programu
@param source_file plik �r�d�owy
@param secret_file plik do zaszyfrowania
@param output_file plik wyj�ciowy
@param R wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni czerwieni
@param G wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni zieleni
@param B wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni niebieskiego
*/
void wczytaj_pliki(char** argv, FILE** source_file, FILE** secret_file, FILE** output_file, int* R, int* G, int* B);

/** Funkcja odczytuje dane z plik�w podanych przez u�ytkownika
@param argv tablica argument�w programu
@param secret_file_length d�ugo�� pliku do zaszyfrowania
@param offset d�ugo�� nag��wka pliku .bmp
@param depth warto�� g��bi pliku danego przez u�ytkownika
@param source_file plik �r�d�owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param R wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni czerwieni
@param G wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni zieleni
@param B wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni niebieskiego
*/
void czytaj_pliki(char** argv, int* secret_file_length, int* offset, short* depth, FILE** source_file, FILE** secret_file, FILE** output_file, int* R, int* G, int* B);


/** Funkcja przepisuje nag��wek pliku .bmp oraz zapisuje d�ugo�� szyfrowanego pliku
@param source_file plik �r�d�owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param offset d�ugo�� nag��wka pliku .bmp
@param secret_file_length d�ugo�� pliku do zaszyfrowania
@param depth warto�� g��bi pliku danego przez u�ytkownika
*/
void pisz_nag�owek(FILE** source_file, FILE** secret_file, FILE** output_file, int* offset, int secret_file_length, int depth);

/** Funkcja zapisuje ilo�� bit�w przeznaczonych do zaszyfrowania dla ka�dego z kolor�w
@param argv tablica argument�w programu
@param R wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni czerwieni
@param G wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni zieleni
@param B wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni niebieskiego
*/
void za�aduj_rgb(char** argv, int* R, int* G, int* B);

/** Funkcja ustawia ile bit�w obecnego bajtu ma zosta� przeznaczonych do szyfrowania
@param R wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni czerwieni
@param G wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni zieleni
@param B wska�nik na ilo�� bit�w jaka ma by� przeznaczona dla odcieni niebieskiego
@param actual_color ilo�� bit�w obecnego bajtu ma zosta� u�ytych do szyfrowania
@param position_in_file pozycja w pliku
*/
void kt�ry_kolor(int R, int G, int B, int* actual_color, int position_in_file);

/** Funkcja zakodowuje warto�ci sk�adowych G i B pixela w pliku o g��bi 16 bit�w
@param source_file plik �r�d�owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param G ilo�� bit�w jaka ma by� przeznaczona dla odcieni zieleni
@param B ilo�� bit�w jaka ma by� przeznaczona dla odcieni niebieskiego
@param i iterator s�u��cy do sprawdzenia czy zosta�a ju� wykorzystana ilo�� bit�w przeznaczonych do szyfrowania
@param j wska�nik ile bajt�w do zaszyfrowania zosta�o wykorzystanych
@param file_buffer bajt pobrany z pliku �r�d�owego
*/
void zakoduj_16GB(FILE** source_file, FILE** secret_file, FILE** output_file, int G, int B, int* i, int* j, char* file_buffer);

/** Funkcja zakodowuje warto�ci sk�adowej R pixela w pliku o g��bi 16 bit�w
@param source_file plik �r�d�owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param R ilo�� bit�w jaka ma by� przeznaczona dla odcieni czerwieni
@param i iterator s�u��cy do sprawdzenia czy zosta�a ju� wykorzystana ilo�� bit�w przeznaczonych do szyfrowania
@param j wska�nik ile bajt�w do zaszyfrowania zosta�o wykorzystanych
@param file_buffer bajt pobrany z pliku �r�d�owego
*/
void zakoduj_16R(FILE** source_file, FILE** secret_file, FILE** output_file, int R, int* i, int* j, char* file_buffer);

/** Funkcja szyfruje plik w pliku o g��bi 16 bit�w
@param source_file plik �r�d�owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param R ilo�� bit�w jaka ma by� przeznaczona dla odcieni czerwieni
@param G ilo�� bit�w jaka ma by� przeznaczona dla odcieni zieleni
@param B ilo�� bit�w jaka ma by� przeznaczona dla odcieni niebieskiego
*/
void zakoduj_16(FILE** source_file, FILE** secret_file, FILE** output_file, int R, int G, int B);

/** Funkcja szyfruje plik w pliku o g��bi 24 bity
@param source_file plik �r�d�owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param R ilo�� bit�w jaka ma by� przeznaczona dla odcieni czerwieni
@param G ilo�� bit�w jaka ma by� przeznaczona dla odcieni zieleni
@param B ilo�� bit�w jaka ma by� przeznaczona dla odcieni niebieskiego
*/
void zakoduj_24(FILE** source_file, FILE** secret_file, FILE** output_file, int R, int G, int B);



