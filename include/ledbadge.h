#pragma once

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
enum {
	LEDTAG_DEV_NONE, LEDTAG_DEV_M1_8, LEDTAG_NDEV
};

enum {
	LEDTAG_ERR_NOINIT = 16700, /* initialization failed/missing initialization  */
	LEDTAG_ERR_INVALID, /* invalid argument */
	LEDTAG_ERR_OPEN, /* device could not be opened */
	LEDTAG_ERR_IO, /* io error */
	LEDTAG_ERR_MSGSPAN, /* invalid message span */
};

typedef struct ledbadge_info ledbadge_info_t;
typedef struct ledbadge ledbadge_t;

struct ledbadge_info {
	const char *name;
	unsigned height;
	unsigned max_width;
	unsigned char_width; /* width of each message must be a multiple of char_width */
	unsigned display_chars; /* width of physical display in characters */
	unsigned max_chars; /* equals max_width / char_width */
	unsigned max_messages;
	unsigned max_speed;
	unsigned max_brightness;
	unsigned n_mode;
	const char **mode_name;
	unsigned n_option;
	const char **option_name;
};

int ledbadge_init();
void ledbadge_exit();

/* opens first device which has been found. */
ledbadge_t *ledbadge_open(
		const wchar_t *serial);

void ledbadge_close(
		ledbadge_t *self);

const ledbadge_info_t *ledbadge_info(
		ledbadge_t *self);

int ledbadge_setup(
		ledbadge_t *self,
		unsigned brightness);

int ledbadge_setup_message(
		ledbadge_t *self,
		unsigned msg,
		unsigned bchar, /* begin character */
		unsigned nchar, /* end character */
		unsigned mode,
		unsigned speed,
		unsigned options); /* for each option to enable: 1 << option_id */

void ledbadge_invert(
		ledbadge_t *self);

void ledbadge_clear(
		ledbadge_t *self);

void ledbadge_fill(
		ledbadge_t *self);

int ledbadge_set(
		ledbadge_t *self,
		unsigned x, /* coords in pixels */
		unsigned y);

int ledbadge_unset(
		ledbadge_t *self,
		unsigned x,
		unsigned y);

/* check, whether messages are setup correctly */
int ledbadge_validate(
		const ledbadge_t *self);

int ledbadge_flash(
		ledbadge_t *self);
#ifdef __cplusplus
}
#endif

