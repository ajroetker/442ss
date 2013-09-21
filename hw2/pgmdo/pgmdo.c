#include <stdio.h>
#include <stdlib.h>

//
// MATH 442: pgmdo
//
// Simple portable grey map (PGM) image processor.
//

// outPGM
//
// Output a character to the given file, one that
// corresponds in brightness to the value (from 0.0
// to 1.0) given.
//
void outPGM(FILE *f, float* img, int width, int height) {
  int r, c;
  // for each image row
  fprintf(f, "P2\n# CREATOR: Reed College... Hell Yeah!\n60\n68\n255");
  for (r=0; r<height; r++) {
    // for each image column
    for (c=0; c<width; c++) {
      fprintf(f, "%d", (int)img[r*width+c]*255);
      fprintf(f,"\n");
    }
  }
}

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

void invertImage(float *img, int width, int height){
  int r, c, i;
  // for each image row
  for (r=0; r<height; r++) {
    // for each image column
    for (c=0; c<width; c++) {
      i = r * width + c;
      img[i] = (1-img[i]);
    }
  }
}

void blurImage(float *img, float *omg, int width, int height){
  int r, c, i;
  // for each image row
  for (r=0; r<height; r++) {
    // for each image column
    for (c=0; c<width; c++) {
      i = r * width + c;
      if ((i % width) == 0) {
        if (i < width){
          omg[i] = (4*img[i] + 2*img[i+1]  + 2*img[i+r])/8;
        }
        else if (i >= (width * (height - 1))){
          omg[i] = (4*img[i] + 2*img[i+1]  + 2*img[i-r])/8;
        } else {
          omg[i] = (5*img[i] + img[i+1] + img[i-r] + img[i+r])/8;
        }
      }
      else if ((i % (width - 1)) == 0){
        if (i < width){
          omg[i] = (4*img[i] + 2*img[i-1]  + 2*img[i+r])/8;
        }
        else if (i >= (width * (height - 1))){
          omg[i] = (4*img[i] + 2*img[i-1]  + 2*img[i-r])/8;
        } else {
          omg[i] = (5*img[i] + img[i-1] + img[i-r] + img[i+r])/8;
        }
      }
      else if (i < width){
        omg[i] = (5*img[i] + img[i+1] + img[i-1] + img[i+r])/8;
      }
      else if (i >= (width * (height - 1))){
        omg[i] = (5*img[i] + img[i+1] + img[i-1] + img[i-r])/8;
      }
      else{
        omg[i] = (4*img[i] + img[i+1] + img[i-1] + img[i-r] + img[i+r])/8;
      }
    }
  }
}

// echoASCII
//
// Read the a PGM file opened as "inf" and write a text file
// of characters to "outf", ones whose brightness suggest the
// levels of grey specified by the original image.
//
void echoASCII(float *img, FILE *outf, int width, int height) {
  int r, c;
  // for each image row
  for (r=0; r<height; r++) {
    // for each image column
    for (c=0; c<width; c++) {
      // output a pixel character to make ASCII art
      outASCII(outf,img[r*width+c]);
    }
    // end the ASCII text line
    fprintf(outf,"\n");
  }
}

float *readImage(FILE *inf,  int *width, int *height) {

  int max;
  int pixel;
  int r,c;
  float *img=(float *)malloc(sizeof(float));

  // Read the PGM file's header info,
                             // for example:

  eatLine(inf);                // P5 (or P2)
  eatLine(inf);                // # this was produced by some software
  fscanf(inf, "%d", width);   // 9 5
  fscanf(inf, "%d", height);
  fscanf(inf, "%d", &max);     // 255
  img=(float *)malloc(sizeof(float));
  // for each image row
  for (r=0; r<(*height); r++) {
    // for each image column
    for (c=0; c<(*width); c++) {
      // read a PGM pixel grey value (from 0 to max)
      fscanf(inf,"%d", &pixel);
      img[(r*(*width)) + c] = (float)pixel/(float)max;
    }
  }
  return img;
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
  float *img, *omg;
  int width, height;

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
    img = readImage(inf,&width,&height);
    omg = img;
    if (strcmp(argv[1],"--blur") == 0) {
      blurImage(img, omg, width, height);
      outPGM(outf, img, width, height);
    } else if (strcmp(argv[1],"--invert") == 0) {
      printf("Here!");
      invertImage(img, width, height);
      outPGM(outf, img, width, height);
    } else if (strcmp(argv[1],"--ascii") == 0) {
      echoASCII(img,outf, width, height);
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
