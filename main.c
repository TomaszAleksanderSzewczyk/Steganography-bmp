#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funkcje.h"

int main(int argc, char** argv)
{
    kontrola_argumentow(argc, argv);
    int R, G, B;

    FILE* source_file; FILE* secret_file; FILE* output_file;
    wczytaj_pliki(argv, &source_file, &secret_file, &output_file, &R, &G, &B);
    int offset;
    int secret_file_length;
    short depth;
    czytaj_pliki(argv, &secret_file_length, &offset, &depth, &source_file, &secret_file, &output_file, &R, &G, &B);



    pisz_nag³owek(&source_file, &secret_file, &output_file, &offset, secret_file_length, depth);


    
    if (depth == 24)
        zakoduj_24(&source_file, &secret_file, &output_file, R, G, B);
    else if (depth == 16)
        zakoduj_16(&source_file, &secret_file, &output_file, R, G, B);
    else
        b³êdna_g³êbia_kolorów(&source_file, &secret_file, &output_file, depth);

   
    zamknij_pliki(&source_file, &secret_file, &output_file);

    return 0;
}