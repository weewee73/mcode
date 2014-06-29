#include <stdio.h>
#include <getopt.h>
#include <locale.h>
#include <stdlib.h>

#define PACKAGE_BUGREPORT "zero.flyfire@gmail.com"
#define PACKAGE "FlyFire"
#define VERSION "0.0.1"


/* String containing name the program is called with. */
const char *program_name;

static const struct option longopts[] =
{
    { "greeting", required_argument, NULL, 'g' },
    { "help", no_argument, NULL, 'h' },
    { "next-generation", no_argument, NULL, 'n' },
    { "traditional", no_argument, NULL, 't' },
    { "version", no_argument, NULL, 'v' },
    { NULL, 0, NULL, 0 }
};

static void print_help(void);
static void print_version(void);

int main(int argc, char *argv[])
{
    int optc;
    int t = 0, n = 0, lose = 0;
    const char *greeting = NULL;

    program_name = argv[0];

    /* Set locale via LC_ALL. */
    setlocale(LC_ALL, "");

    while ((optc = getopt_long(argc, argv, "g:hntv", longopts, NULL)) != -1)
    {
        switch (optc) {
            /* One goal here is having --help and --version exit immediately,
             * per GNU coding standards.  */
            case 'v':
                print_version();
                exit(EXIT_SUCCESS);
                break;
            case 'g':
                greeting = optarg;
                break;
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
                break;
            case 'n':
                n = 1;
                break;
            case 't':
                t = 1;
                break;
            default:
                lose = 1;
                break;
        }
    }

    if (lose || optind < argc)
    {
        /* Print error message and exit. */
        if (optind < argc)
            fprintf(stderr, ("%s: extra operand: %s\n"), program_name, argv[optind]);

        fprintf(stderr, ("Try `%s --help' for more information.\n"), program_name);
        exit(EXIT_FAILURE);
    }

    /* Print greeting message and exit. */
    if (t)
    {
        printf("hello, world\n");
    }
    else if (n)
    {
        /* TRANSLATORS: Use box drawing characters or other fancy stuff
           if your encoding (e.g., UTF-8) allows it.
           If done so add the following note, please:

           [Note: For best viewing results use a UTF-8 locale, please.]
           */
        printf("\
                +---------------+\n\
                | Hello, world! |\n\
                +---------------+\n");
    }
   else
   {
       if (!greeting)
           greeting = "Hello, world!";
       puts(greeting);
   }

    exit (EXIT_SUCCESS);
}


/* Print help info.
   This long message is split into several pieces to help translators be able to align different
   blocks and identify the various pieces.  */

static void print_help(void)
{
    /* TRANSLATORS: --help output 1 (synopsis) no-wrap */
    printf(("\
        Usage: %s [OPTION]...\n"), program_name);

    /* TRANSLATORS: --help output 2 (brief description) no-wrap */
    fputs(("\
        Print a friendly, customizable greeting.\n"), stdout);

    puts ("");
    /* TRANSLATORS: --help output 3: options 1/2 no-wrap */
    fputs(("\
        -h, --help          display this help and exit\n\
        -v, --version       display version information and exit\n"), stdout);

    puts("");
    /* TRANSLATORS: --help output 4: options 2/2 no-wrap */
    fputs(("\
        -t, --traditional       use traditional greeting format\n\
        -n, --next-generation   use next-generation greeting format\n\
        -g, --greeting=TEXT     use TEXT as the greeting message\n"), stdout);

    printf("\n");
    /* TRANSLATORS: --help output 5 (end)
       TRANSLATORS: the placeholder indicates the bug-reporting address for this application.
                    Please add _another line_ with the address for translation bugs.  no-wrap */
    printf(("\
        Report bugs to <%s>.\n"), PACKAGE_BUGREPORT);
}


/* Print version and copyright information. */

static void print_version(void)
{
    printf("\
        hello (%s) %s (Built %s %s)\n", PACKAGE, VERSION, __DATE__, __TIME__);
    /* xgettext: no-wrap */
    puts("");

    /* It is important to separate the year from the rest of the message, as done here,
       to avoid having to retranslate the message when a new year comes around.  */
    printf(("\
        Copyright (C) %s Free Software Foundation, Inc.\n\
        This is free software: you are free to change and redistribute it.\n\
        There is NO WARRANTY, to the extent permitted by law.\n"),
        "2014");
}
