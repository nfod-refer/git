#ifndef USERDIFF_H
#define USERDIFF_H

#include "notes-cache.h"

struct index_state;
struct repository;

struct userdiff_funcname {
	const char *pattern;
	int cflags;
};

struct userdiff_driver {
	const char *name;
	const char *external;
	int binary;
	struct userdiff_funcname funcname;
	const char *word_regex;
	const char *textconv;
	struct notes_cache *textconv_cache;
	int textconv_want_cache;
};
enum userdiff_driver_type {
	USERDIFF_DRIVER_TYPE_UNSPECIFIED = 1<<0,
	USERDIFF_DRIVER_TYPE_BUILTIN = 1<<1,
	USERDIFF_DRIVER_TYPE_CUSTOM = 1<<2,
};
typedef int (*each_userdiff_driver_fn)(struct userdiff_driver *,
				       enum userdiff_driver_type, void *);

int userdiff_config(const char *k, const char *v);
struct userdiff_driver *userdiff_find_by_name(const char *name);
struct userdiff_driver *userdiff_find_by_path(struct index_state *istate,
					      const char *path);

/*
 * Initialize any textconv-related fields in the driver and return it, or NULL
 * if it does not have textconv enabled at all.
 */
struct userdiff_driver *userdiff_get_textconv(struct repository *r,
					      struct userdiff_driver *driver);

/*
 * Iterate over each driver of type userdiff_driver_type, or
 * USERDIFF_DRIVER_TYPE_UNSPECIFIED for all of them. Return non-zero
 * to exit from the loop.
 */
int for_each_userdiff_driver(each_userdiff_driver_fn,
			     enum userdiff_driver_type, void *);

#endif /* USERDIFF */
