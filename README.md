# Steganography-bmp
## Hiding data in .bmp format file. 
## How to use? 
The program is run from the command line. Should be submitted to the program file names: input, hidden and the file that we will create, i.e. the output file. Then use the -R, -G, -B switches to pass the quantity bits to be used to hide information.
** <source file> <secret file> <destination file> -R [] -G [] -B [] **
Example: marbles.bmp secret.txt marbles1.bmp -R [1] -G [2] -B [3]
Thanks to such an instruction, the program knows how many bits are to be allocated to hiding information from each of the RGB components.
The input file must be in .bmp format.
The file to encrypt may have any format. The output file must be in the input file format.
When entering too many parameters, the console prints a message to us from instruction on how to enter arguments for a program.
