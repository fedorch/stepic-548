/* getopt_demo - demonstrate getopt() usage
 *
 * This application shows you one way of using getopt() to
 * process your command-line options and store them in a
 * global structure for easy access.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* doc2html supports the following command-line arguments:
 *
 * -I - don't produce a keyword index
 * -l lang - produce output in the specified language, lang
 * -o outfile - write output to outfile instead of stdout
 * -v - be verbose; more -v means more diagnostics
 * additional file names are used as input files
 *
 * The optString global tells getopt() which options we
 * support, and which options have arguments.
 */
struct globalArgs_t {
    int noIndex;                /* -I option */
    char *langCode;             /* -l option */
    const char *outFileName;    /* -o option */
    FILE *outFile;
    int verbosity;              /* -v option */
    char **inputFiles;          /* input files */
    int numInputFiles;          /* # of input files */
} globalArgs;

static const char *optString = "Il:o:vh?";

/* Display program usage, and exit.
 */
void display_usage( void )
{
    puts( "doc2html - convert documents to HTML" );
    /* ... */
    exit( EXIT_FAILURE );
}

/* Convert the input files to HTML, governed by globalArgs.
 */
void convert_document( void )
{
    /* ... */
}

int main( int argc, char *argv[] )
{
    int opt = 0;

    /* Initialize globalArgs before we get to work. */
    globalArgs.noIndex = 0;        /* false */
    globalArgs.langCode = NULL;
    globalArgs.outFileName = NULL;
    globalArgs.outFile = NULL;
    globalArgs.verbosity = 0;
    globalArgs.inputFiles = NULL;
    globalArgs.numInputFiles = 0;

    /* Process the arguments with getopt(), then
     * populate globalArgs.
     */
    opt = getopt( argc, argv, optString );
    while( opt != -1 ) {
        switch( opt ) {
            case 'I':
                globalArgs.noIndex = 1;    /* true */
                break;

            case 'l':
                globalArgs.langCode = optarg;
                break;

            case 'o':
                /* This generates an "assignment from
                 * incompatible pointer type" warning that
                 * you can safely ignore.
                 */
                globalArgs.outFileName = optarg;
                break;

            case 'v':
                globalArgs.verbosity++;
                break;

            case 'h':    /* fall-through is intentional */
            case '?':
                display_usage();
                break;

            default:
                /* You won't actually get here. */
                break;
        }

        opt = getopt( argc, argv, optString );
    }

    globalArgs.inputFiles = argv + optind;
    globalArgs.numInputFiles = argc - optind;

    convert_document();

    return EXIT_SUCCESS;
}
