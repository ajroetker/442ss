#include <stdio.h>
#include <stdlib.h>

//
// MATH 442: pgmdo
//
// Simple portable grey map (PGM) image processor.
//


// outASCII
//
// Output a character to the given file, one that
// corresponds in brightness to the value (from 0.0
// to 1.0) given.
//
void outASCII(FILE *f, float value) {
  if (value > 0.8) {
    fprintf(f,"#");
  } else if (value > 0.5) {
    fprintf(f,"x");
  } else if (value > 0.25) {
    fprintf(f,";");
  } else if (value > 0.15) {
    fprintf(f,",");
  } else {
    fprintf(f," ");
  }
}

// eatLine
//
// Reads a line of characters.
//
void eatLine(FILE *f) {
  while (fgetc(f) != '\n');
}

// echoASCII
//
// Read the a PGM file opened as "inf" and write a text file
// of characters to "outf", ones whose brightness suggest the
// levels of grey specified by the original image.
//
void echoASCII(FILE *inf, FILE *outf) {

  int width, height;
  int max;
  int pixel;
  int r,c;

  // Read the PGM file's header info,
                             // for example:

  eatLine(inf);                // P5 (or P2)
  eatLine(inf);                // # this was produced by some software
  fscanf(inf, "%d", &width);   // 9 5
  fscanf(inf, "%d", &height);
  fscanf(inf, "%d", &max);     // 255

  // for each image row
  for (r=0; r<height; r++) {
    // for each image column
    for (c=0; c<width; c++) {

      // read a PGM pixel grey value (from 0 to max)
      fscanf(inf,"%d", &pixel);
                             // 0 10 30 80 120 135 225 245 255 
                             // (4 more rows)

      // output a pixel character to make ASCII art
      outASCII(outf,(float)pixel/(float)max);
    }

    // end the ASCII text line 
    fprintf(outf,"\n");
  }
}

// usage
//
// Outputs a message that gives the command-line description.
//
void usage(char *cmd) {
  fprintf(stderr,"usage: %s <option> <infile> <outfile>\n", cmd);
  fprintf(stderr,"\twhere <infile> is a PGM and <option> is one of\n");
  fprintf(stderr,"\t\t--blur    :outputs a blurred PGM image\n");
  fprintf(stderr,"\t\t--invert  :outputs PGM negative image\n");
  fprintf(stderr,"\t\t--ascii   :converts to ASCII art\n");
}

// main
// 
// This program accepts three arguments: a processing option
// ("blur", "invert", or "ascii"), a PGM file name for input,
// and a text file name for output.  It reads the PGM file and
// creates an output file with either an appropriate PGM (if 
// one of the first two options are given) or a text file (if
// the last option is given).
//
// Right now, only the "ascii" option works.
//
int main(int argc, char **argv) {

  // input and output file "handles"
  FILE *inf, *outf;

  if (argc < 4) {
    
    // whoops! not enough arguments
    fprintf(stderr,"Error: not enough arguments!\n");
    usage(argv[0]);
    return -1;

  } else {

    // open the input (PGM) file
    inf = fopen(argv[2],"r");
    if (inf == NULL) {
      fprintf(stderr,"Error: can't open file '%s' for reading.\n",argv[2]);
      return -1;
    }

    // open the output file
    outf = fopen(argv[3],"w");
    if (outf == NULL) {
      fprintf(stderr,"Error: can't open file '%s' for writing.\n",argv[3]);
      return -1;
    }

    if (strcmp(argv[1],"--blur") == 0) {

      fprintf(stderr, "***BLUR NOT SUPPORTED YET!!!***\n");
      //
      // write the code that performs a blur of the image
      //  

    } else if (strcmp(argv[1],"--invert") == 0) {

      fprintf(stderr, "***INVERT NOT SUPPORTED YET!!!***\n");
      //
      // write the code that inverts the image
      //  

    } else if (strcmp(argv[1],"--ascii") == 0) {

      echoASCII(inf,outf);
      //
      // change this so that it is given an image array and
      // the outf
      //

    } else {

      fprintf(stderr,"Error: unrecognized option '%s.'\n",argv[1]);
      usage(argv[0]);
      
      // return FAIL
      return -1;
    }

    // close the files
    fclose(inf);
    fclose(outf);

    // return OK
    return 0;
  }
}
  
