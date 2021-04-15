/** @file */
#pragma once



/** Program sprawdza czy podana iloœæ argumentów jest poprawna. Je¿eli nie to wyswietla polecenie
@param argc liczba argumentów programu
@param argv tablica argumentów programu*/
void kontrola_argumentow(int argc, int** argv);

/** Funkcja oblicza d³ugoœæ nag³ówka pliku .bmp
@param bmp_offset wskaŸnik na plik .bmp
@return d³ugoœæ podanego pliku .bmp
*/
int znajdz_d³ugoœæ_nag³owka(FILE** bmp_offset);

/** Funkcja znajduje g³êbiê kolorów pliku .bmp
@param bmp_offset wskaŸnik na plik .bmp
@return zwraca g³êbiê kolorów pliku .bmp*/
int znajdz_glebie_kolorow(FILE** bmp_offset);

/**Funkcja wypisuje b³¹d je¿eli g³êbia kolorów pliku przekazanego przez u¿ytkownika jest b³êdna
@param source_file plik g³ówny
@param secret_file plik do zaszyfrowania
@param output_file plik wychodz¹cy
@param depth wartoœæ g³ebi*/
void b³êdna_g³êbia_kolorów(FILE** source_file, FILE** secret_file, FILE** output_file, int depth);

/**Funkcja zwraca d³ugoœæ pliku
@param fp wskaŸnik na plik .bmp
@return zwraca d³ugoœæ pliku */
int znajdz_dlugosc_pliku(FILE** fp);

/**Funkcja zwraca podany bit z okreœlonego bajtu
@param the_byte wskazany bajt
@param which_bit który bit w podanym bajcie
@return wartoœæ wskazanego bitu */
int pobierz_bit(char the_byte, int which_bit);

/**Funkcja zamyka pliki
@param source_file plik Ÿród³owy
@param secret_file plik do zaszyfrowania
@param output_file plik wyjœciowy*/
void zamknij_pliki(FILE** source_file, FILE** secret_file, FILE** output_file);

/** Funkcja sprawdza czy plik do zaszyfrowania zmieœci siê w pliku Ÿród³owym
@param secret_file_length d³ugoœæ pliku do zaszyfrowania
@param file_length d³ugoœæ pliku Ÿród³owego
@param offset d³ugoœæ nag³ówka pliku .bmp
@param argv tablica argumentów programu
@param R iloœæ bitów jaka ma byæ przeznaczona dla odcieni czerwieni
@param G iloœæ bitów jaka ma byæ przeznaczona dla odcieni zieleni
@param B iloœæ bitów jaka ma byæ przeznaczona dla odcieni niebieskiego
@param depth wartoœæ g³êbi pliku danego przez u¿ytkownika
*/
int sprawdzanie_pamieci(int secret_file_length, int file_length, int offset, char** argv, int R, int G, int B, short depth);

/** Funkcja otwiera pliki podane przez u¿ytkownika
@param argv tablica argumentów programu
@param source_file plik Ÿród³owy
@param secret_file plik do zaszyfrowania
@param output_file plik wyjœciowy
@param R wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni czerwieni
@param G wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni zieleni
@param B wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni niebieskiego
*/
void wczytaj_pliki(char** argv, FILE** source_file, FILE** secret_file, FILE** output_file, int* R, int* G, int* B);

/** Funkcja odczytuje dane z plików podanych przez u¿ytkownika
@param argv tablica argumentów programu
@param secret_file_length d³ugoœæ pliku do zaszyfrowania
@param offset d³ugoœæ nag³ówka pliku .bmp
@param depth wartoœæ g³êbi pliku danego przez u¿ytkownika
@param source_file plik Ÿród³owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param R wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni czerwieni
@param G wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni zieleni
@param B wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni niebieskiego
*/
void czytaj_pliki(char** argv, int* secret_file_length, int* offset, short* depth, FILE** source_file, FILE** secret_file, FILE** output_file, int* R, int* G, int* B);


/** Funkcja przepisuje nag³ówek pliku .bmp oraz zapisuje d³ugoœæ szyfrowanego pliku
@param source_file plik Ÿród³owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param offset d³ugoœæ nag³ówka pliku .bmp
@param secret_file_length d³ugoœæ pliku do zaszyfrowania
@param depth wartoœæ g³êbi pliku danego przez u¿ytkownika
*/
void pisz_nag³owek(FILE** source_file, FILE** secret_file, FILE** output_file, int* offset, int secret_file_length, int depth);

/** Funkcja zapisuje iloœæ bitów przeznaczonych do zaszyfrowania dla ka¿dego z kolorów
@param argv tablica argumentów programu
@param R wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni czerwieni
@param G wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni zieleni
@param B wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni niebieskiego
*/
void za³aduj_rgb(char** argv, int* R, int* G, int* B);

/** Funkcja ustawia ile bitów obecnego bajtu ma zostaæ przeznaczonych do szyfrowania
@param R wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni czerwieni
@param G wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni zieleni
@param B wskaŸnik na iloœæ bitów jaka ma byæ przeznaczona dla odcieni niebieskiego
@param actual_color iloœæ bitów obecnego bajtu ma zostaæ u¿ytych do szyfrowania
@param position_in_file pozycja w pliku
*/
void który_kolor(int R, int G, int B, int* actual_color, int position_in_file);

/** Funkcja zakodowuje wartoœci sk³adowych G i B pixela w pliku o g³êbi 16 bitów
@param source_file plik Ÿród³owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param G iloœæ bitów jaka ma byæ przeznaczona dla odcieni zieleni
@param B iloœæ bitów jaka ma byæ przeznaczona dla odcieni niebieskiego
@param i iterator s³u¿¹cy do sprawdzenia czy zosta³a ju¿ wykorzystana iloœæ bitów przeznaczonych do szyfrowania
@param j wskaŸnik ile bajtów do zaszyfrowania zosta³o wykorzystanych
@param file_buffer bajt pobrany z pliku Ÿród³owego
*/
void zakoduj_16GB(FILE** source_file, FILE** secret_file, FILE** output_file, int G, int B, int* i, int* j, char* file_buffer);

/** Funkcja zakodowuje wartoœci sk³adowej R pixela w pliku o g³êbi 16 bitów
@param source_file plik Ÿród³owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param R iloœæ bitów jaka ma byæ przeznaczona dla odcieni czerwieni
@param i iterator s³u¿¹cy do sprawdzenia czy zosta³a ju¿ wykorzystana iloœæ bitów przeznaczonych do szyfrowania
@param j wskaŸnik ile bajtów do zaszyfrowania zosta³o wykorzystanych
@param file_buffer bajt pobrany z pliku Ÿród³owego
*/
void zakoduj_16R(FILE** source_file, FILE** secret_file, FILE** output_file, int R, int* i, int* j, char* file_buffer);

/** Funkcja szyfruje plik w pliku o g³êbi 16 bitów
@param source_file plik Ÿród³owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param R iloœæ bitów jaka ma byæ przeznaczona dla odcieni czerwieni
@param G iloœæ bitów jaka ma byæ przeznaczona dla odcieni zieleni
@param B iloœæ bitów jaka ma byæ przeznaczona dla odcieni niebieskiego
*/
void zakoduj_16(FILE** source_file, FILE** secret_file, FILE** output_file, int R, int G, int B);

/** Funkcja szyfruje plik w pliku o g³êbi 24 bity
@param source_file plik Ÿród³owy
@param secret_file plik do zaszyfrowania
@param output_file plik wynikowy
@param R iloœæ bitów jaka ma byæ przeznaczona dla odcieni czerwieni
@param G iloœæ bitów jaka ma byæ przeznaczona dla odcieni zieleni
@param B iloœæ bitów jaka ma byæ przeznaczona dla odcieni niebieskiego
*/
void zakoduj_24(FILE** source_file, FILE** secret_file, FILE** output_file, int R, int G, int B);



