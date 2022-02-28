/* File: netpbm.c */
#include <stdio.h>                                                                                    /* Header file for standard I/O library */
#include <string.h>                                           /* Header file which contains declarations of functions that operate on strings */
#define BnW_ASCII         '1'                                                                               /* Black and white image in ASCII */
#define GRAY_ASCII        '2'                                                                                    /* Gray scale image in ASCII */
#define COLOR_ASCII       '3'                                                                                     /* RGB color image in ASCII */
#define BnW_BINARY        '4'                                                                              /* Black and white image in binary */
#define GRAY_BINARY       '5'                                                                                   /* Gray scale image in binary */
#define COLOR_BINARY      '6'                                                                                    /* RGB color image in binary */
#define OK                 0                                                                                      /* Define a constant for OK */
#define ERROR             -2                                                                    /* Define a constant for returning when ERROR */
#define exit()             do {printf("Input error!\n"); return ERROR;} while(0)                   /* Termination in case of unexpected input */
#define MAX_SIGNED_INT     ( ~ ( 1 << ( 8 * sizeof(int) - 1 ) ) )                 /* This is an integer with msb 0 and the rest of its bits 1 */



int get_integer(int *pch);                                                                              /* Convert number in ASCII to integer */
int white_space_or_comment(int *pch);                                                    /* Check for white space and skip potential comments */
int white_space(int *pch);                                                                                           /* Check for white space */
int single_white_character(int *pch);                                                                   /* Check for a single white character */
int gray2bnw_ascii(int ch);                                                                             /* Convert gray image in ASCII to BnW */
int color2gray_ascii (int ch);                                                                        /* Convert color image in ASCII to gray */
int gray2bnw_binary (int ch);                                                                          /* Convert gray image in binary to BnW */
int color2gray_binary(int ch);                                                                       /* Convert color image in binary to gray */
int bnw_ascii2binary(int ch);                                                                         /* Convert BnW image in ASCII to binary */
int gray_ascii2binary(int ch);                                                                       /* Convert gray image in ASCII to binary */
int color_ascii2binary(int ch);                                                                     /* Convert color image in ASCII to binary */
int bnw_binary2ascii(int ch);                                                                         /* Convert BnW image in binary to ASCII */
int gray_binary2ascii(int ch);                                                                       /* Convert gray image in binary to ASCII */
int color_binary2ascii(int ch);                                                                     /* Convert color image in binary to ASCII */


int main(int argc, char *argv[]) {
  if (argc == 1) {                                 /* Standard case: Convert color image(.ppm) to gray(.pgm) or gray image(.pgm) to BnW(.pbm) */
    int ch;                                                                                 /* Declare ch as int because of getchar() and EOF */
    ch = getchar();                                                                                                      /* Get the next byte */
    if (ch == 'P') {                                                                            /* Every magic number should start with a 'P' */
      putchar(ch);                                                                                        /* 'P' should be included in output */
      ch = getchar();                                                                                                    /* Get the next byte */
      switch (ch) {                                                                            /* Choose the conversion based on magic number */
        case GRAY_ASCII:
          return (gray2bnw_ascii(ch));                                                                                  /* Finish the program */
        case COLOR_ASCII:
          return (color2gray_ascii (ch));                                                                               /* Finish the program */
        case GRAY_BINARY:
          return (gray2bnw_binary (ch));                                                                                /* Finish the program */
        case COLOR_BINARY:
          return (color2gray_binary(ch));                                                                               /* Finish the program */
        default:                                                                                     /* If none of the above cases, then exit */
          exit();
      }
    }
    else exit();
  }
  else if (argc == 2 && !strcmp(argv[1], "bonus")){                     /* Bonus case: Convert ASCII image to binary or binary image to ASCII */
    int ch;                                                                                 /* Declare ch as int because of getchar() and EOF */
    ch = getchar();                                                                                                      /* Get the next byte */
    if (ch == 'P') {                                                                            /* Every magic number should start with a 'P' */
      putchar(ch);                                                                                        /* 'P' should be included in output */
      ch = getchar();                                                                                                    /* Get the next byte */
      switch (ch) {                                                                            /* Choose the conversion based on magic number */
        case BnW_ASCII:
          return (bnw_ascii2binary(ch));                                                                                /* Finish the program */
        case GRAY_ASCII:
          return (gray_ascii2binary(ch));                                                                               /* Finish the program */
        case COLOR_ASCII:
          return (color_ascii2binary(ch));                                                                              /* Finish the program */
        case BnW_BINARY:
          return (bnw_binary2ascii(ch));                                                                                /* Finish the program */
        case GRAY_BINARY:
          return (gray_binary2ascii(ch));                                                                               /* Finish the program */
        case COLOR_BINARY:
          return (color_binary2ascii(ch));                                                                              /* Finish the program */
        default:                                                                                     /* If none of the above cases, then exit */
          exit();
      }
    }
    else exit();
  }
  else {                                                                                                  /* Other case: Not supported option */
    printf("Not supported option, try one of those: \"./netpbm\" or \"./netpbm bonus\".\n");
    return ERROR;                                                                                                       /* Finish the program */
  }
}

int gray2bnw_ascii(int ch) {                                                                            /* Convert gray image in ASCII to BnW */
  int width, height, max, h, w, pixel;
  putchar(ch - 1);                                                                /* Magic numbers are consecutive, so go to the previous one */
  ch = getchar();                                                                                                        /* Get the next byte */
  if (white_space_or_comment(&ch) == OK) {                                               /* Check for white space and skip potential comments */
    putchar('\n');                                                                         /* Change line as the white space needed in output */
    width = get_integer(&ch);                                                                       /* The width of the input image in pixels */
    if (width != ERROR) {                                                                                          /* Check if width is valid */
      printf("%d", width);                                                                                 /* Output image has the same width */
      if (white_space(&ch) == OK) {                                                                                  /* Check for white space */
        putchar(' ');                                                                  /* and put a space as the white space needed in output */
        height = get_integer(&ch);                                                                 /* The height of the input image in pixels */
        if (height != ERROR) {                                                                                    /* Check if height is valid */
          printf("%d", height);                                                                           /* Output image has the same height */
          if (white_space(&ch) == OK) {                                                                              /* Check for white space */
            putchar('\n');                                                                 /* Change line as the white space needed in output */
            max = get_integer(&ch);                                          /* The maximum value for gray color in pixels of the input image */
            if (max != ERROR && max <= 255) {                                                                        /* Check if max is valid */
              if (white_space(&ch) == OK) {                                                                          /* Check for white space */
                for (h = 1; h <= height; h++) {                                                       /* h: current height from top to bottom */
                  for (w = 1; w <= width; w++) {                                                       /* w: current width from left to right */
                    pixel = get_integer(&ch);                                                                          /* Current input pixel */
                    if (pixel != ERROR && pixel <= max) {                                            /* Check if current input pixel is valid */
                      pixel = (pixel > (max + 1) / 2) ? '0' : '1';                              /* Find the color of the current output pixel */
                      putchar(pixel);
                    }
                    else exit();
                    if (white_space(&ch) == OK) {                                                            /* Check if there is white space */
                      putchar (' ');                                                   /* and put a space as the white space needed in output */
                    }
                    else if (w != width || h != height) {                                  /* Else check if the current pixel is the last one */
                      exit();                                                                         /* and if not, exit with error notation */
                    }
                  }
                  putchar('\n');                                                           /* Change line as the white space needed in output */
                }
              }
              else exit();
            }
            else exit();
          }
          else exit();
        }
        else exit();
      }
      else exit();
    }
    else exit();
  }
  else exit();
  return OK;
}

int color2gray_ascii (int ch) {
  int width, height, max, h, w, pixel, red, green, blue;
  putchar(ch - 1);                                                                /* Magic numbers are consecutive, so go to the previous one */
  ch = getchar();                                                                                                        /* Get the next byte */
  if (white_space_or_comment(&ch) == OK) {                                               /* Check for white space and skip potential comments */
    putchar('\n');                                                                         /* Change line as the white space needed in output */
    width = get_integer(&ch);                                                                       /* The width of the input image in pixels */
    if (width != ERROR) {                                                                                          /* Check if width is valid */
      printf("%d", width);                                                                                 /* Output image has the same width */
      if (white_space(&ch) == OK) {                                                                                  /* Check for white space */
        putchar(' ');                                                                  /* and put a space as the white space needed in output */
        height = get_integer(&ch);                                                                 /* The height of the input image in pixels */
        if (height != ERROR) {                                                                                    /* Check if height is valid */
          printf("%d", height);                                                                           /* Output image has the same height */
          if (white_space(&ch) == OK) {                                                                              /* Check for white space */
            putchar('\n');                                                                 /* Change line as the white space needed in output */
            max = get_integer(&ch);                                          /* The maximum value for each color in pixels of the input image */
            if (max != ERROR && max <= 255) {                                                                        /* Check if max is valid */
              printf("%d", max);                                                                             /* Output image has the same max */
              if (white_space(&ch) == OK) {                                                                          /* Check for white space */
                putchar('\n');                                                             /* Change line as the white space needed in output */
                for (h = 1; h <= height; h++) {                                                       /* h: current height from top to bottom */
                  for (w = 1; w <= width; w++) {                                                       /* w: current width from left to right */
                    red = get_integer(&ch);                                         /* The value of color red in current pixel of input image */
                    if (red != ERROR && red <= max) {                                                       /* Check if value of red is valid */
                      if (white_space(&ch) == OK) {                                                                  /* Check for white space */
                        green = get_integer(&ch);                                 /* The value of color green in current pixel of input image */
                        if (green != ERROR && green <= max) {                                             /* Check if value of green is valid */
                          if (white_space(&ch) == OK) {                                                              /* Check for white space */
                            blue = get_integer(&ch);                               /* The value of color blue in current pixel of input image */
                            if (blue != ERROR && blue <= max) {                                            /* Check if value of blue is valid */
                              pixel = (299 * red + 587 * green + 114 * blue) / 1000;            /* Find the color of the current output pixel
                                                                                                                   based on luminosity method */
                              printf("%d", pixel);                                                   /* Print the decimal equivalent of pixel */
                              if (white_space(&ch) == OK) {                                                  /* Check if there is white space */
                                putchar (' ');                                         /* and put a space as the white space needed in output */
                              }
                              else if (w != width || h != height) {                        /* Else check if the current pixel is the last one */
                                exit();                                                               /* and if not, exit with error notation */
                              }
                            }
                            else exit();
                          }
                          else exit();
                        }
                        else exit();
                      }
                      else exit();
                    }
                    else exit();
                  }
                  putchar('\n');                                                           /* Change line as the white space needed in output */
                }
              }
              else exit();
            }
            else exit();
          }
          else exit();
        }
        else exit();
      }
      else exit();
    }
    else exit();
  }
  else exit();
  return OK;
}

int gray2bnw_binary (int ch) {
  int width, height, max, h, w, pixels;
  putchar(ch - 1);                                                                /* Magic numbers are consecutive, so go to the previous one */
  ch = getchar();                                                                                                        /* Get the next byte */
  if (white_space_or_comment(&ch) == OK) {                                               /* Check for white space and skip potential comments */
    putchar('\n');                                                                         /* Change line as the white space needed in output */
    width = get_integer(&ch);                                                                       /* The width of the input image in pixels */
    if (width != ERROR) {                                                                                          /* Check if width is valid */
      printf("%d", width);                                                                                 /* Output image has the same width */
      if (white_space(&ch) == OK) {                                                                                  /* Check for white space */
        putchar(' ');                                                                  /* and put a space as the white space needed in output */
        height = get_integer(&ch);                                                                 /* The height of the input image in pixels */
        if (height != ERROR) {                                                                                    /* Check if height is valid */
          printf("%d", height);                                                                           /* Output image has the same height */
          if (white_space(&ch) == OK) {                                                                              /* Check for white space */
            putchar('\n');                                                                 /* Change line as the white space needed in output */
            max = get_integer(&ch);                                          /* The maximum value for gray color in pixels of the input image */
            if (max != ERROR && max <= 255) {                                                                        /* Check if max is valid */
              if (single_white_character(&ch) == OK) {                                                  /* Check for a single white character */
                for (h = 1; h <= height; h++) {                                                       /* h: current height from top to bottom */
                  for (w = 1; w <= width; w++) {                                                       /* w: current width from left to right */
                    if (w%8 == 1) {                                                   /* Check if current output pixel is the first of a byte */
                      pixels = 0xFF;                    /* If yes, then reset pixels to 11111111 (due to ace padding at the end of each line) */
                    }
                    if (ch > (max + 1) / 2 ) {                          /* Check if the color of the current output pixel should be white (0) */
                      pixels &= ~(0x80 >> (w-1)%8);                                           /* If yes, then "clean" it by using an AND-mask */
/* Note: By default when shifting force 0-fill, so by using (~) after (>>) the AND-mask is full of 1 except the bit that should get "cleaned" */
                    }
                    if (w%8 == 0 || w == width) {            /* Check if the current output pixel is the last of a byte or the last of a line */
                      putchar(pixels);                                                                       /* If yes, then put current byte */
                    }
                    ch = getchar();                                                                                      /* Get the next byte */
                    if (ch == EOF  && (w != width || h != height)) exit();           /* If EOF sooner than expected, exit with error notation */
                  }
                }
              }
              else exit();
            }
            else exit();
          }
          else exit();
        }
        else exit();
      }
      else exit();
    }
    else exit();
  }
  else exit();
  return OK;
}

int color2gray_binary(int ch) {
  int width, height, max, h, w, pixel, red, green, blue;
  putchar(ch - 1);                                                                /* Magic numbers are consecutive, so go to the previous one */
  ch = getchar();                                                                                                        /* Get the next byte */
  if (white_space_or_comment(&ch) == OK) {                                               /* Check for white space and skip potential comments */
    putchar('\n');                                                                         /* Change line as the white space needed in output */
    width = get_integer(&ch);                                                                       /* The width of the input image in pixels */
    if (width != ERROR) {                                                                                          /* Check if width is valid */
      printf("%d", width);                                                                                 /* Output image has the same width */
      if (white_space(&ch) == OK) {                                                                                  /* Check for white space */
        putchar(' ');                                                                  /* and put a space as the white space needed in output */
        height = get_integer(&ch);                                                                 /* The height of the input image in pixels */
        if (height != ERROR) {                                                                                    /* Check if height is valid */
          printf("%d", height);                                                                           /* Output image has the same height */
          if (white_space(&ch) == OK) {                                                                              /* Check for white space */
            putchar('\n');                                                                 /* Change line as the white space needed in output */
            max = get_integer(&ch);                                          /* The maximum value for each color in pixels of the input image */
            if (max != ERROR && max <= 255) {                                                                        /* Check if max is valid */
              printf("%d", max);                                                                             /* Output image has the same max */
              if (single_white_character(&ch) == OK) {                                                  /* Check for a single white character */
                putchar('\n');                                                             /* Change line as the white space needed in output */
                for (h = 1; h <= height; h++) {                                                       /* h: current height from top to bottom */
                  for (w = 1; w <= width; w++) {                                                       /* w: current width from left to right */
                    if (ch <= max) {                                                 /* Check if the value for the first color (red) is valid */
                      red = ch;
                      ch = getchar();                                                                                    /* Get the next byte */
                      if (ch == EOF) exit();                                         /* If EOF sooner than expected, exit with error notation */
                      if (ch <= max) {                                              /* Check if the value for the next color (green) is valid */
                        green = ch;
                        ch = getchar();                                                                                  /* Get the next byte */
                        if (ch == EOF) exit();                                       /* If EOF sooner than expected, exit with error notation */
                        if (ch <= max) {                                             /* Check if the value for the last color (blue) is valid */
                          blue = ch;
                          ch = getchar();                                                                                /* Get the next byte */
                          if (ch == EOF && (w != width || h != height)) exit();      /* If EOF sooner than expected, exit with error notation */
                          pixel = (299 * red + 587 * green + 114 * blue) / 1000;                /* Find the color of the current output pixel
                                                                                                                   based on luminosity method */
                          putchar(pixel);
                        }
                        else exit();
                      }
                      else exit();
                    }
                    else exit();
                  }
                }
              }
              else exit();
            }
            else exit();
          }
          else exit();
        }
        else exit();
      }
      else exit();
    }
    else exit();
  }
  else exit();
  return OK;
}

int bnw_ascii2binary(int ch) {
  int width, height, h, w, pixels;
  putchar(ch + 3);                                  /* To convert the magic number of an image in ASCII to binarry, add 3 to the numeric part */
  ch = getchar();                                                                                                        /* Get the next byte */
  if (white_space_or_comment(&ch) == OK) {                                               /* Check for white space and skip potential comments */
    putchar('\n');                                                                         /* Change line as the white space needed in output */
    width = get_integer(&ch);                                                                       /* The width of the input image in pixels */
    if (width != ERROR) {                                                                                          /* Check if width is valid */
      printf("%d", width);                                                                                 /* Output image has the same width */
      if (white_space(&ch) == OK) {                                                                                  /* Check for white space */
        putchar(' ');                                                                  /* and put a space as the white space needed in output */
        height = get_integer(&ch);                                                                 /* The height of the input image in pixels */
        if (height != ERROR) {                                                                                    /* Check if height is valid */
          printf("%d", height);                                                                           /* Output image has the same height */
          if (white_space(&ch) == OK) {                                                                              /* Check for white space */
            putchar('\n');                                                                 /* Change line as the white space needed in output */
            for (h = 1; h <= height; h++) {                                                           /* h: current height from top to bottom */
              for (w = 1; w <= width; w++) {                                                           /* w: current width from left to right */
                if (w%8 == 1) {                                                       /* Check if current output pixel is the first of a byte */
                  pixels = 0xFF;                        /* If yes, then reset pixels to 11111111 (due to ace padding at the end of each line) */
                }
                while (ch == '0') {                                                                   /* Skip the leading zeros of the number */
                  ch = getchar();                                                                                        /* Get the next byte */
                }
                if (white_space(&ch) == OK) {   /* Check the first non-zero byte; if white space then the numeric value of current pixel is 0 */
                  pixels &= ~(0x80 >> (w-1)%8);                                                       /* Then "clean" it by using an AND-mask */
/* Note: By default when shifting force 0-fill, so by using (~) after (>>) the AND-mask is full of 1 except the bit that should get "cleaned" */
                }
                else if (ch == '1') {                       /* If the first non-zero byte is '1' then the numeric value of current pixel is 1 */
                  ch = getchar();                                                                                        /* Get the next byte */
                  if (white_space(&ch) != OK) {                                             /* Check if there is no white space after an '1', */
                    if (ch != EOF || w != width || h != height) {                         /* but exclude the case of EOF after the last pixel */
                      putchar(pixels);         /* In any other case of no white space, put the current byte (the unchecked bits will be aces) */
                      exit();                                                                            /* and then exit with error notation */
                    }
                  }
                }
                else exit();                                    /* If after zeros there is no white space or an '1', exit with error notation */
                if (w%8 == 0 || w == width) {                /* Check if the current output pixel is the last of a byte or the last of a line */
                  putchar(pixels);                                                                          /* If yes, then put current pixel */
                }
              }
            }
          }
          else exit();
        }
        else exit();
      }
      else exit();
    }
    else exit();
  }
  else exit();
  return OK;
}

int gray_ascii2binary(int ch) {
  int width, height, max, h, w, pixel;
  putchar(ch + 3);                                  /* To convert the magic number of an image in ASCII to binarry, add 3 to the numeric part */
  ch = getchar();                                                                                                        /* Get the next byte */
  if (white_space_or_comment(&ch) == OK) {                                               /* Check for white space and skip potential comments */
    putchar('\n');                                                                         /* Change line as the white space needed in output */
    width = get_integer(&ch);                                                                       /* The width of the input image in pixels */
    if (width != ERROR) {                                                                                          /* Check if width is valid */
      printf("%d", width);                                                                                 /* Output image has the same width */
      if (white_space(&ch) == OK) {                                                                                  /* Check for white space */
        putchar(' ');                                                                  /* and put a space as the white space needed in output */
        height = get_integer(&ch);                                                                 /* The height of the input image in pixels */
        if (height != ERROR) {                                                                                    /* Check if height is valid */
          printf("%d", height);                                                                           /* Output image has the same height */
          if (white_space(&ch) == OK) {                                                                              /* Check for white space */
            putchar('\n');                                                                 /* Change line as the white space needed in output */
            max = get_integer(&ch);                                          /* The maximum value for gray color in pixels of the input image */
            if (max != ERROR && max <= 255) {                                                                        /* Check if max is valid */
              printf("%d", max);                                                                             /* Output image has the same max */
              if (white_space(&ch) == OK) {                                                                          /* Check for white space */
                putchar('\n');                                                             /* Change line as the white space needed in output */
                for (h = 1; h <= height; h++) {                                                       /* h: current height from top to bottom */
                  for (w = 1; w <= width; w ++) {                                                      /* w: current width from left to right */
                    pixel = get_integer(&ch);                                                                          /* Current input pixel */
                    if (pixel != ERROR && pixel <= max) {                                            /* Check if current input pixel is valid */
                      putchar(pixel);
                      if (white_space(&ch) != OK) {                                                       /* Check if there is no white space */
                        if (ch != EOF || w != width || h != height) {                     /* but exclude the case of EOF after the last pixel */
                          exit();                                                                             /* and exit with error notation */
                        }
                      }
                    }
                    else exit();
                  }
                }
              }
              else exit();
            }
            else exit();
          }
          else exit();
        }
        else exit();
      }
      else exit();
    }
    else exit();
  }
  else exit();
  return OK;
}

int color_ascii2binary(int ch) {
  int width, height, max, h, w, subpixel, color; //red, green, blue;
  putchar(ch + 3);                                  /* To convert the magic number of an image in ASCII to binarry, add 3 to the numeric part */
  ch = getchar();                                                                                                        /* Get the next byte */
  if (white_space_or_comment(&ch) == OK) {                                               /* Check for white space and skip potential comments */
    putchar('\n');                                                                         /* Change line as the white space needed in output */
    width = get_integer(&ch);                                                                       /* The width of the input image in pixels */
    if (width != ERROR) {                                                                                          /* Check if width is valid */
      printf("%d", width);                                                                                 /* Output image has the same width */
      if (white_space(&ch) == OK) {                                                                                  /* Check for white space */
        putchar(' ');                                                                  /* and put a space as the white space needed in output */
        height = get_integer(&ch);                                                                 /* The height of the input image in pixels */
        if (height != ERROR) {                                                                                    /* Check if height is valid */
          printf("%d", height);                                                                           /* Output image has the same height */
          if (white_space(&ch) == OK) {                                                                              /* Check for white space */
            putchar('\n');                                                                 /* Change line as the white space needed in output */
            max = get_integer(&ch);                                          /* The maximum value for each color in pixels of the input image */
            if (max != ERROR && max <= 255) {                                                                        /* Check if max is valid */
              printf("%d", max);                                                                             /* Output image has the same max */
              if (white_space(&ch) == OK) {                                                                          /* Check for white space */
                putchar('\n');                                                             /* Change line as the white space needed in output */
                for (h = 1; h <= height; h++) {                                                       /* h: current height from top to bottom */
                  for (w = 1; w <= width; w++) {                                                       /* w: current width from left to right */
                    for (color = 1; color <= 3; color ++) {                                          /* Each pixel consists of 3 colors (RGB) */
                      subpixel = get_integer(&ch);                                                            /* Current subpixel value (RGB) */
                      if (subpixel != ERROR && subpixel <= max) {                                         /* Check if subpixel value is valid */
                        putchar(subpixel);
                        if (white_space(&ch) != OK) {                                                     /* Check if there is no white space */
                          if (ch != EOF || w != width || h != height) {                   /* but exclude the case of EOF after the last pixel */
                            exit();                                                                           /* and exit with error notation */
                          }
                        }
                      }
                      else exit();
                    }
                  }
                }
              }
              else exit();
            }
            else exit();
          }
          else exit();
        }
        else exit();
      }
      else exit();
    }
    else exit();
  }
  else exit();
  return OK;
}

int bnw_binary2ascii(int ch) {
  int width, height, h, w, pixel;
  putchar(ch - 3);                             /* To convert the magic number of an image in binarry to ASCII, subtract 3 by the numeric part */
  ch = getchar();                                                                                                        /* Get the next byte */
  if (white_space_or_comment(&ch) == OK) {                                               /* Check for white space and skip potential comments */
    putchar('\n');                                                                         /* Change line as the white space needed in output */
    width = get_integer(&ch);                                                                       /* The width of the input image in pixels */
    if (width != ERROR) {                                                                                          /* Check if width is valid */
      printf("%d", width);                                                                                 /* Output image has the same width */
      if (white_space(&ch) == OK) {                                                                                  /* Check for white space */
        putchar(' ');                                                                  /* and put a space as the white space needed in output */
        height = get_integer(&ch);                                                                 /* The height of the input image in pixels */
        if (height != ERROR) {                                                                                    /* Check if height is valid */
          printf("%d", height);                                                                           /* Output image has the same height */
          if (single_white_character(&ch) == OK) {                                                      /* Check for a single white character */
            putchar('\n');                                                                 /* Change line as the white space needed in output */
            for (h = 1; h <= height; h++) {                                                           /* h: current height from top to bottom */
              for (w = 1; w <= width; w++) {                                                           /* w: current width from left to right */
                pixel = ch;                                                                                               /* Save ch as pixel */
                pixel &= 0x80;                                          /* Use AND-mask in orded to isolate the first bit and fill with zeros */
                pixel = (pixel == 0x00) ? '0' : '1';                           /* If the first bit is 0 then current pixel is 0, else it is 1 */
                putchar(pixel);
                putchar(' ');                                                              /* Put a space as the white space needed in output */
                ch <<= 1;                                                              /* Left shift ch by 1, so the next bit becomes the msb */
                if (w % 8 == 0 || w == width) {              /* Check if the current output pixel is the last of a byte or the last of a line */
                  ch = getchar();                                                                                        /* Get the next byte */
                  if (ch == EOF && (w != width || h != height)) exit();              /* If EOF sooner than expected, exit with error notation */
                }
              }
              putchar('\n');                                                               /* Change line as the white space needed in output */
            }
          }
          else exit();
        }
        else exit();
      }
      else exit();
    }
    else exit();
  }
  else exit();
  return OK;
}

int gray_binary2ascii(int ch) {
  int width, height, max, h, w;
  putchar(ch - 3);                             /* To convert the magic number of an image in binarry to ASCII, subtract 3 by the numeric part */
  ch = getchar();                                                                                                        /* Get the next byte */
  if (white_space_or_comment(&ch) == OK) {                                               /* Check for white space and skip potential comments */
    putchar('\n');                                                                         /* Change line as the white space needed in output */
    width = get_integer(&ch);                                                                       /* The width of the input image in pixels */
    if (width != ERROR) {                                                                                          /* Check if width is valid */
      printf("%d", width);                                                                                 /* Output image has the same width */
      if (white_space(&ch) == OK) {                                                                                  /* Check for white space */
        putchar(' ');                                                                  /* and put a space as the white space needed in output */
        height = get_integer(&ch);                                                                 /* The height of the input image in pixels */
        if (height != ERROR) {                                                                                    /* Check if height is valid */
          printf("%d", height);                                                                           /* Output image has the same height */
          if (white_space(&ch) == OK) {                                                                              /* Check for white space */
            putchar('\n');                                                                 /* Change line as the white space needed in output */
            max = get_integer(&ch);                                          /* The maximum value for gray color in pixels of the input image */
            if (max != ERROR && max <= 255) {                                                                        /* Check if max is valid */
              printf("%d", max);                                                                             /* Output image has the same max */
              if (single_white_character(&ch) == OK) {                                                  /* Check for a single white character */
                putchar('\n');                                                             /* Change line as the white space needed in output */
                for (h = 1; h <= height; h++) {                                                       /* h: current height from top to bottom */
                  for (w = 1; w <= width; w++) {                                                       /* w: current width from left to right */
                    if (ch <= max) {                                                                       /* Check if current pixel is valid */
                      printf("%d ", ch);                                                                /* Print the decimal equivalent of ch */
                      ch = getchar();                                                                                    /* Get the next byte */
                      if (ch == EOF && (w != width || h != height)) exit();          /* If EOF sooner than expected, exit with error notation */
                    }
                    else exit();
                  }
                  putchar('\n');                                                           /* Change line as the white space needed in output */
                }
              }
              else exit();
            }
            else exit();
          }
          else exit();
        }
        else exit();
      }
      else exit();
    }
    else exit();
  }
  else exit();
  return OK;
}

int color_binary2ascii(int ch) {
  int width, height, max, h, w, color;
  putchar(ch - 3);                             /* To convert the magic number of an image in binarry to ASCII, subtract 3 by the numeric part */
  ch = getchar();                                                                                                        /* Get the next byte */
  if (white_space_or_comment(&ch) == OK) {                                               /* Check for white space and skip potential comments */
    putchar('\n');                                                                         /* Change line as the white space needed in output */
    width = get_integer(&ch);                                                                       /* The width of the input image in pixels */
    if (width != ERROR) {                                                                                          /* Check if width is valid */
      printf("%d", width);                                                                                 /* Output image has the same width */
      if (white_space(&ch) == OK) {                                                                                  /* Check for white space */
        putchar(' ');                                                                  /* and put a space as the white space needed in output */
        height = get_integer(&ch);                                                                 /* The height of the input image in pixels */
        if (height != ERROR) {                                                                                    /* Check if height is valid */
          printf("%d", height);                                                                           /* Output image has the same height */
          if (white_space(&ch) == OK) {                                                                              /* Check for white space */
            putchar('\n');                                                                 /* Change line as the white space needed in output */
            max = get_integer(&ch);                                          /* The maximum value for each color in pixels of the input image */
            if (max != ERROR && max <= 255) {                                                                        /* Check if max is valid */
              printf("%d", max);                                                                             /* Output image has the same max */
              if (single_white_character(&ch) == OK) {                                                  /* Check for a single white character */
                putchar('\n');                                                             /* Change line as the white space needed in output */
                for (h = 1; h <= height; h++) {                                                       /* h: current height from top to bottom */
                  for (w = 1; w <= width; w++) {                                                       /* w: current width from left to right */
                    for (color = 1; color <= 3; color ++) {                                          /* Each pixel consists of 3 colors (RGB) */
                      if (ch <= max) {                                                    /* Check if the value of the current color is valid */
                        printf("%d ", ch);                                                           /* Print the decimal equivalent of pixel */
                        ch = getchar();                                                                                  /* Get the next byte */
                        if (ch == EOF && (w != width || h != height)) exit();        /* If EOF sooner than expected, exit with error notation */
                      }
                      else exit();
                    }
                  }
                  putchar('\n');                                                           /* Change line as the white space needed in output */
                }
              }
              else exit();
            }
            else exit();
          }
          else exit();
        }
        else exit();
      }
      else exit();
    }
    else exit();
  }
  else exit();
  return OK;
}

int get_integer(int *pch) {
  int value;
  if (*pch >= '0' && *pch <= '9') {
    value = *pch - '0';                                                    /* Initialize the value as the numeric part of the ASCII character */
    *pch = getchar();                                                                                                    /* Get the next byte */
    while (*pch >= '0' && *pch <= '9') {                                           /* Repeat as long as the content of the pointer is numeric */
      if (value > MAX_SIGNED_INT / 10) return ERROR;                              /* Check that "value" will not overflow if multiplied by 10 */
      value = 10 * value + (*pch - '0');                                                                         /* Build one digit at a time */
      *pch = getchar();                                                                                                  /* Get the next byte */
    }
  return value;                                                                                                          /* Successful finish */
 }
 else return ERROR;                                                                                                    /* Unsuccessful finish */
}

int white_space_or_comment(int *pch) {
  if (*pch == ' ' || *pch == '\t' || *pch == '\n') {                                            /* Check if there is a single white character */
    *pch = getchar();                                                                                                    /* Get the next byte */
    while (*pch == ' ' || *pch == '\t' || *pch == '\n' || *pch == '#') {    /* Skip every following white character or the potential comments */
      if (*pch == '#') {                                                                                         /* Check if a comment begins */
        while (*pch != '\n') {                                                           /* Skip every character as long as the comment lasts */
          *pch = getchar();                                                                                              /* Get the next byte */
        }
      }
      *pch = getchar();                                                                                                  /* Get the next byte */
    }
    return OK;                                                                                                           /* Successful finish */
  }
  else return ERROR;                                                                                                   /* Unsuccessful finish */
}

int white_space(int *pch) {
  if (*pch == ' ' || *pch == '\t' || *pch == '\n') {                                            /* Check if there is a single white character */
    *pch = getchar();                                                                                                    /* Get the next byte */
    while (*pch == ' ' || *pch == '\t' || *pch == '\n') {                                             /* Skip every following white character */
      *pch = getchar();                                                                                                  /* Get the next byte */
    }
    return OK;                                                                                                           /* Successful finish */
  }
  else return ERROR;                                                                                                   /* Unsuccessful finish */
}

int single_white_character(int *pch) {
  if (*pch == ' ' || *pch == '\t' || *pch == '\n') {                                            /* Check if there is a single white character */
    *pch = getchar();                                                                                                    /* Get the next byte */
    return OK;                                                                                                           /* Successful finish */
  }
  else return ERROR;                                                                                                   /* Unsuccessful finish */
}
