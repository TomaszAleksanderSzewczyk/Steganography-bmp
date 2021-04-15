#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funkcje.h"

void kontrola_argumentow(int argc, int** argv)
{
	if (argc != 10)
	{
		printf("--------------------------------------\n| Steganography by LSBs substitution |\n--------------------------------------\nUsage: %s <source file> <secret file> <destination file> -R [] -G [] -B []\n", argv[0]);
		exit(1);
	}

}



int znajdz_d³ugoœæ_nag³owka(FILE** bmp_offset)
{
	fseek(*bmp_offset, 10, 0);
	int offset;
	offset = (int)fgetc(*bmp_offset);
	return offset;
}

int znajdz_glebie_kolorow(FILE** bmp_offset)
{
	fseek(*bmp_offset, 28, 0);
	short offset;
	offset = (short)fgetc(*bmp_offset);
	return offset;
}

int znajdz_dlugosc_pliku(FILE** fp)
{
	fseek(*fp, 0L, SEEK_END);
	int size = ftell(*fp);
	fseek(*fp, 0L, SEEK_SET);
	return(size);
}

int pobierz_bit(char the_byte, int which_bit)
{
	return((the_byte >> (8 - which_bit)) & 1);
}


void zamknij_pliki(FILE** source_file, FILE** secret_file, FILE** output_file)
{
	/*if (*secret_file != NULL)*/fclose(*secret_file);
	/*if (*source_file != NULL)*/fclose(*source_file);
	/*if (*output_file != NULL)*/fclose(*output_file);
}

void za³aduj_rgb(char** argv, int* R, int* G, int* B)
{
	*R = argv[5][0] - '0';
	*G = argv[7][0] - '0';
	*B = argv[9][0] - '0';
}

void b³êdna_g³êbia_kolorów(FILE** source_file, FILE** secret_file, FILE** output_file, int depth)
{
	printf("Incorrect color depth. Program takes only depth of 16 or 24 bits. Depth of current file: %d", depth);
	zamknij_pliki(&*source_file, &*secret_file, &*output_file);
	exit(1);
}
void czytaj_pliki(char** argv, int* secret_file_length, int* offset, short* depth, FILE** source_file, FILE** secret_file, FILE** output_file, int* R, int* G, int* B)
{
	*secret_file_length = znajdz_dlugosc_pliku(&*secret_file);
	int file_length = znajdz_dlugosc_pliku(&*source_file);
	*offset = znajdz_d³ugoœæ_nag³owka(&*source_file);
	rewind(*source_file);
	*depth = znajdz_glebie_kolorow(&*source_file);
	rewind(*source_file);

	/**Check if there is enough memory to save the secret file*/
	if (sprawdzanie_pamieci(*secret_file_length, file_length, *offset, argv, *R, *G, *B, *depth) == 1)
	{
		zamknij_pliki(&*source_file, &*secret_file, &*output_file);
		exit(1);
	}
}

int sprawdzanie_pamieci(int secret_file_length, int file_length, int offset, char** argv, int R, int G, int B, short depth)
{
	if (depth == 24)
	{
		if (secret_file_length > (file_length - offset) / 3 * (R + G + B))
		{
			printf("The size of %s is too big\n", argv[2]);
			return 1;
		}
		else return 0;
	}
	else if (depth == 16)
	{
		if (secret_file_length > (file_length - offset) / 2 * (R + G + B))
		{
			printf("The size of %s is too big\n", argv[2]);
			return 1;
		}
		else return 0;
	}
	else
	{
		printf("The format of BMP is different than 16 or 24 bytes");
		return 1;
	}

}

void wczytaj_pliki(char** argv, FILE** source_file, FILE** secret_file, FILE** output_file, int* R, int* G, int* B)
{
	*source_file = fopen(argv[1], "rb");
	*output_file = fopen(argv[3], "wb");
	*secret_file = fopen(argv[2], "rb");

	if (*source_file == NULL)
	{
		fprintf(stderr, "Can't open source file %s\n", argv[1]);
		zamknij_pliki(&*source_file, &*secret_file, &*output_file);
		exit(1);
	}

	if (*output_file == NULL)
	{
		fprintf(stderr, "Can't create output file %s\n", argv[3]);
		zamknij_pliki(&*source_file, &*secret_file, &*output_file);
		exit(1);
	}

	if (*secret_file == NULL)
	{
		fprintf(stderr, "Can't open secret file %s\n", argv[2]);
		zamknij_pliki(&*source_file, &*secret_file, &*output_file);
		exit(1);
	}
	za³aduj_rgb(argv, R, G, B);
}



void pisz_nag³owek(FILE** source_file, FILE** secret_file, FILE** output_file, int* offset, int secret_file_length, int depth)
{
	char single_byte;
	/** Generate .bmp file with the same header. */
	for (int i = 0; i < *offset; i++)
	{
		single_byte = fgetc(*source_file);
		fputc(single_byte, *output_file);
	}

	/** After file header, the length of the secret file is written as the first {sizeof(int)} bytes. */
	fputc(secret_file_length, *output_file);
	/** After 4 bytes, add another 2 or 1 to keep RGB colores in tact */
	single_byte = 0;
	if (sizeof(int) == 4)
	{
		fputc(single_byte, *output_file);
		if (depth == 24)
			fputc(single_byte, *output_file);
	}
	else if (sizeof(int) == 2)
	{
		if (depth == 24)
			fputc(single_byte, *output_file);
	}
}
void który_kolor(int R, int G, int B, int* actual_color, int position_in_file)
{
	if (position_in_file % 3 == 1)
		*actual_color = R;
	else if (position_in_file % 3 == 2)
		*actual_color = G;
	else
		*actual_color = B;
}

void zakoduj_24(FILE** source_file, FILE** secret_file, FILE** output_file, int R, int G, int B)
{
	int j = 1;
	int i = 1;
	int position_in_file = 0;
	int bits_of_message;
	char file_buffer; 			// Temp variable for one byte from file
	char secret_buffer=0;		// Temp buffer for one byte from secret file;
	int actual_color;
	do {
		if (!feof(*secret_file))
		{
			file_buffer = fgetc(*source_file);
			position_in_file++;
			bits_of_message = 0;

			który_kolor(R, G, B, &actual_color, position_in_file);

			while (!feof(*secret_file) && i <= actual_color) // do until all the bits to cipher are used up
			{
				if (j > 8)
				{
					secret_buffer = fgetc(*secret_file);
					j = 1;
				}
				bits_of_message = bits_of_message << 1;
				bits_of_message = bits_of_message | pobierz_bit(secret_buffer, j);
				j++; i++;

			}
			i = 1;
			file_buffer = file_buffer >> actual_color; // clear the lsbs of byte from source file
			file_buffer = file_buffer << actual_color;
			file_buffer = file_buffer | bits_of_message; // OR the byte from source file with message to encrypt
			fputc(file_buffer, *output_file);           //save it to output file
		}
		else                                            // when the file to encrypt is used up, just copy the rest of source file
		{
			file_buffer = fgetc(*source_file);
			fputc(file_buffer, *output_file);
		}
	} while (!feof(*source_file));
}
void zakoduj_16R(FILE** source_file, FILE** secret_file, FILE** output_file, int R, int* i, int* j, char* file_buffer)
{
	char secret_buffer=0;
	int bits_of_message = 0;
	while (!feof(*secret_file) && *i <= R)
	{
		if (*j > 8)
		{
			secret_buffer = fgetc(*secret_file);
			*j = 1;
		}
		bits_of_message = bits_of_message << 1;
		bits_of_message = bits_of_message | pobierz_bit(secret_buffer, *j);
		(*j)++; (*i)++;

	}
	*i = 1;
	*file_buffer = *file_buffer >> R;
	*file_buffer = *file_buffer << R;
	*file_buffer = *file_buffer | bits_of_message;
	fputc(*file_buffer, *output_file);
}

void zakoduj_16GB(FILE** source_file, FILE** secret_file, FILE** output_file, int G, int B, int* i, int* j, char* file_buffer)
{
	char secret_buffer=0;
	int bits_of_message = 0;
	char tmp;

	/* The G color*/
	while (!feof(*secret_file) && *i <= G)
	{
		if (*j > 8)
		{
			secret_buffer = fgetc(*secret_file);
			*j = 1;
		}
		bits_of_message = bits_of_message << 1;
		bits_of_message = bits_of_message | pobierz_bit(secret_buffer, *j);
		(*j)++; (*i)++;

	}
	*i = 1;
	bits_of_message = bits_of_message << 4;
	tmp = *file_buffer;
	*file_buffer = *file_buffer >> (4 + G);
	*file_buffer = *file_buffer << (4 + G);
	*file_buffer = *file_buffer | bits_of_message;

	/*The B color*/
	tmp = tmp << 4;
	tmp = tmp >> 4;
	*file_buffer = *file_buffer | tmp;
	bits_of_message = 0;
	while (!feof(*secret_file) && *i <= B)
	{
		if (*j > 8)
		{
			secret_buffer = fgetc(*secret_file);
			*j = 1;
		}
		bits_of_message = bits_of_message << 1;
		bits_of_message = bits_of_message | pobierz_bit(secret_buffer, *j);
		(*j)++; (*i)++;
	}
	*i = 1;
	*file_buffer = *file_buffer >> B;
	*file_buffer = *file_buffer << B;
	*file_buffer = *file_buffer | bits_of_message;
	fputc(*file_buffer, *output_file);
}


void zakoduj_16(FILE** source_file, FILE** secret_file, FILE** output_file, int R, int G, int B)
{
	int j = 1;
	int i = 1;
	int position_in_file = 0;
	char file_buffer; 			// Temp variable for one byte from file
	do {
		if (!feof(*secret_file))
		{
			file_buffer = fgetc(*source_file);
			position_in_file++;
			if (position_in_file % 2 == 1)
			{
				zakoduj_16R(source_file, secret_file, output_file, R, &i, &j, &file_buffer);
			}
			else
			{
				zakoduj_16GB(source_file, secret_file, output_file, G, B, &i, &j, &file_buffer);
			}
		}
		else
		{
			file_buffer = fgetc(*source_file);
			fputc(file_buffer, *output_file);
		}
	} while (!feof(*source_file));
}
