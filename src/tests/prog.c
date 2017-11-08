#include <stdio.h>
#include "reader.h"

#define STYLE_BOLD    "\033[1m"
#define STYLE_NO_BOLD "\033[22m"

int
main (int argc, char *argv[])
{
    // filename argument
    char *filename;
    if (argc == 2) {
        filename = argv [1];
    } else {
        fprintf (stderr, "missing zim file argument, see README.md\n");
        return 1;
    }


    // init reader
    GError* err = NULL;
    KiwixReader *reader = kiwix_reader_new (filename, &err);
    if (err != NULL)
    {
        fprintf (stderr, "%s\n", err->message);
        g_error_free (err);
        return 1;
    }


    // infos
    printf ("==INFOS==\n");

    const gchar *title = kiwix_reader_get_title (reader);
    const gchar *date = kiwix_reader_get_date (reader);
    const gchar *language = kiwix_reader_get_language (reader);
    int file_size = kiwix_reader_get_file_size (reader);
    const gchar *tags = kiwix_reader_get_tags (reader);
    const gchar *id = kiwix_reader_get_id (reader);
    const gchar *name = kiwix_reader_get_name (reader);
    const gchar *description = kiwix_reader_get_description (reader);
    const gchar *random_page_url = kiwix_reader_get_random_page_url (reader);
    unsigned int article_count = kiwix_reader_get_article_count (reader);
    unsigned int media_count = kiwix_reader_get_media_count (reader);
    unsigned int global_count = kiwix_reader_get_global_count (reader);
    const gchar *creator = kiwix_reader_get_creator (reader);
    const gchar *publisher = kiwix_reader_get_publisher (reader);

    //g_assert_cmpstr (title, ==, "Wikipédia");

    printf (STYLE_BOLD "Archive path:    " STYLE_NO_BOLD "%s\n", filename);
    printf (STYLE_BOLD "Title:           " STYLE_NO_BOLD "%s\n", title);
    printf (STYLE_BOLD "Date:            " STYLE_NO_BOLD "%s\n", date);
    printf (STYLE_BOLD "Language:        " STYLE_NO_BOLD "%s\n", language);
    printf (STYLE_BOLD "File size:       " STYLE_NO_BOLD "%d\n", file_size);
    printf (STYLE_BOLD "Tags:            " STYLE_NO_BOLD "%s\n", tags);
    printf (STYLE_BOLD "ID:              " STYLE_NO_BOLD "%s\n", id);
    printf (STYLE_BOLD "Name:            " STYLE_NO_BOLD "%s\n", name);
    printf (STYLE_BOLD "Description:     " STYLE_NO_BOLD "%s\n", description);
    printf (STYLE_BOLD "Random page url: " STYLE_NO_BOLD "%s\n", random_page_url);
    printf (STYLE_BOLD "Article count:   " STYLE_NO_BOLD "%u\n", article_count);
    printf (STYLE_BOLD "Media count:     " STYLE_NO_BOLD "%u\n", media_count);
    printf (STYLE_BOLD "Global count:    " STYLE_NO_BOLD "%u\n", global_count);
    printf (STYLE_BOLD "Creator:         " STYLE_NO_BOLD "%s\n", creator);
    printf (STYLE_BOLD "Publisher:       " STYLE_NO_BOLD "%s\n", publisher);


    // suggestions
    printf ("==SUGGESTIONS==\n");

    kiwix_reader_search_suggestions_smart (reader, "ab", 20);

    char *suggestion;
    char *suggestion_url;
    while (kiwix_reader_get_next_suggestion (reader, &suggestion, &suggestion_url))
    {
        printf (STYLE_BOLD "Suggestion: " STYLE_NO_BOLD "%s, ", suggestion);
        printf (STYLE_BOLD "Suggestion url: " STYLE_NO_BOLD "%s\n", suggestion_url);
        g_free (suggestion);
        g_free (suggestion_url);
    }


    // favicon
    printf ("==FAVICON==\n");

    gsize size;
    char* data = NULL;
    char* mime_type = NULL;
    kiwix_reader_get_faveicon (reader, &data, &size, &mime_type);

    printf (STYLE_BOLD "Faveicon size     : " STYLE_NO_BOLD "%lu\n", size);
    printf (STYLE_BOLD "Faveicon mime type: " STYLE_NO_BOLD "%s\n", mime_type);

    // write faveicon to file
    FILE *f;
    f = fopen("faveicon-from-c.png", "wb");
    fwrite (data, size, 1, f);
    fclose (f);

    return 0;
}
