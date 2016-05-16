/* getopt_long_demo - demonstrate getopt_long() usage
 *
 * This application shows you one way of using getopt_long()
 * to process your command-line options and store them in a
 * global structure for easy access.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

/* doc2html supports the following command-line arguments:
 *
 * -I - don't produce a keyword index
 * -l lang - produce output in the specified language, lang
 * -o outfile - write output to outfile instead of stdout
 * -v - be verbose; more -v means more diagnostics
 * additional file names are used as input files
 *
 * In addition to the standard 'short' options, this
 * version also supports these 'long' options:
 *
 * --no-index
 * --language=lang
 * --output=outfile
 * --verbose
 *
 * The optString global tells getopt_long() which options we
 * support, and which options have arguments.
 *
 * The longOpts global tells getopt_long() which long options
 * we support, and which long options have arguments.
 */

struct globalArgs_t {
    int noIndex;                /* -I option */
    char *langCode;             /* -l option */
    const char *outFileName;    /* -o option */
    FILE *outFile;
    int verbosity;              /* -v option */
    char **inputFiles;          /* input files */
    int numInputFiles;          /* # of input files */
    int randomized;             /* --randomize option */
} globalArgs;

static const char *optString = "Il:o:vh?";

static const struct option longOpts[] = {
    { "no-index", no_argument, NULL, 'I' },
    { "language", required_argument, NULL, 'l' },
    { "output", required_argument, NULL, 'o' },
    { "verbose", no_argument, NULL, 'v' },
    { "randomize", no_argument, NULL, 0 },
    { "help", no_argument, NULL, 'h' },
    { NULL, no_argument, NULL, 0 }
};

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
    printf( "no-index: %d\n", globalArgs.noIndex );
    printf( "language: %s\n", globalArgs.langCode );
    printf( "output: %s\n", globalArgs.outFileName );
    printf( "verbosity: %d\n", globalArgs.verbosity );
    printf( "randomized: %d\n", globalArgs.randomized );
}

int main( int argc, char *argv[] )
{
    int opt = 0;
    int longIndex = 0;

    /* Initialize globalArgs before we get to work. */
    globalArgs.noIndex = 0;        /* false */
    globalArgs.langCode = NULL;
    globalArgs.outFileName = NULL;
    globalArgs.outFile = NULL;
    globalArgs.verbosity = 0;
    globalArgs.inputFiles = NULL;
    globalArgs.numInputFiles = 0;
    globalArgs.randomized = 0;

    /* Process the arguments with getopt_long(), then
     * populate globalArgs.
     */
    opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    while( opt != -1 ) {
        switch( opt ) {
            case 'I':
                globalArgs.noIndex = 1;    /* true */
                break;

            case 'l':
                globalArgs.langCode = optarg;
                break;

            case 'o':
                globalArgs.outFileName = optarg;
                break;

            case 'v':
                globalArgs.verbosity++;
                break;

            case 'h':    /* fall-through is intentional */
            case '?':
                display_usage();
                break;

            case 0:        /* long option without a short arg */
                if( strcmp( "randomize", longOpts[longIndex].name ) == 0 ) {
                    globalArgs.randomized = 1;
                }
                break;

            default:
                /* You won't actually get here. */
                break;
        }

        opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    }

    globalArgs.inputFiles = argv + optind;
    globalArgs.numInputFiles = argc - optind;

    convert_document();

    return EXIT_SUCCESS;
}
