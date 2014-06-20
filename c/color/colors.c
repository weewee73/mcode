#include <assert.h>
#include <errno.h>
#include <err.h>
#include <stdlib.h>   //EXIT_SUCCESSGN EXIT——FAILURE 
#include <strings.h>

#include "colors.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

static int ul_color_term_ok;

int colors_init(int mode)
{
	switch (mode) {
	case UL_COLORMODE_AUTO:
		ul_color_term_ok = isatty(STDOUT_FILENO);
		break;
	case UL_COLORMODE_ALWAYS:
		ul_color_term_ok = 1;
		break;
	case UL_COLORMODE_NEVER:
	default:
		ul_color_term_ok = 0;
	}
	return ul_color_term_ok;
}

int colors_wanted(void)
{
	return ul_color_term_ok;
}

void color_fenable(const char *color_scheme, FILE *f)
{
	if (ul_color_term_ok && color_scheme)
		fputs(color_scheme, f);
}

void color_fdisable(FILE *f)
{
	if (ul_color_term_ok)
		fputs(UL_COLOR_RESET, f);
}

int colormode_from_string(const char *str)
{
	size_t i;
	static const char *modes[] = {
		[UL_COLORMODE_AUTO]   = "auto",
		[UL_COLORMODE_NEVER]  = "never",
		[UL_COLORMODE_ALWAYS] = "always"
	};

	if (!str || !*str)
		return -EINVAL;

	assert(ARRAY_SIZE(modes) == __UL_NCOLORMODES);

	for (i = 0; i < ARRAY_SIZE(modes); i++) {
		if (strcasecmp(str, modes[i]) == 0)
			return i;
	}

	return -EINVAL;
}

int colormode_or_err(const char *str, const char *errmsg)
{
	const char *p = str && *str == '=' ? str + 1 : str;
	int colormode;

	colormode = colormode_from_string(p);
	if (colormode < 0)
		errx(EXIT_FAILURE, "%s: '%s'", errmsg, p);

	return colormode;
}

#define TEST_PROGRAM

#ifdef TEST_PROGRAM
# include <getopt.h>
int main(int argc, char *argv[])
{
	static const struct option longopts[] = {
		{ "colors", optional_argument, 0, 'c' },
		{ NULL, 0, 0, 0 }
	};
	int c, mode = UL_COLORMODE_NEVER;	/* default */

	while ((c = getopt_long(argc, argv, "c::", longopts, NULL)) != -1) {
		switch (c) {
		case 'c':
			mode = UL_COLORMODE_AUTO;
			if (optarg)
            {
				mode = colormode_or_err(optarg, "unsupported color mode");
                printf("%d\n", mode);
            }
            printf("%s\n", optarg);
			break;
		}
	}

	colors_init(mode);

	color_enable(UL_COLOR_RED);
	printf("Hello World!\n");
	color_disable();


	color_enable(UL_COLOR_GREEN);
	printf("Hello World!\n");
	color_disable();

	return EXIT_SUCCESS;
}
#endif

