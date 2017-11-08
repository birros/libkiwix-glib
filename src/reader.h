#ifndef KIWIX_GLIB_READER_H
#define KIWIX_GLIB_READER_H

#include <glib-object.h>

G_BEGIN_DECLS

#define KIWIX_TYPE_READER \
    (kiwix_reader_get_type())
#define KIWIX_READER(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), KIWIX_TYPE_READER, KiwixReader))
#define KIWIX_READER_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), KIWIX_TYPE_READER, KiwixReaderClass))
#define KIWIX_IS_READER(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), KIWIX_TYPE_READER))
#define KIWIX_IS_READER_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), KIWIX_TYPE_READER))
#define KIWIX_READER_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), KIWIX_TYPE_READER, KiwixReaderClass))

typedef struct _KiwixReader      KiwixReader;
typedef struct _KiwixReaderClass KiwixReaderClass;

struct _KiwixReader
{
    GObject parent_instance;
};

struct _KiwixReaderClass
{
    GObjectClass parent_class;
};

GType         kiwix_reader_get_type (void) G_GNUC_CONST;
KiwixReader * kiwix_reader_new (const char *zimpath, GError **error);
const char *  kiwix_reader_get_title (KiwixReader *reader);
const char *  kiwix_reader_get_date (KiwixReader *reader);
const char *  kiwix_reader_get_language (KiwixReader *reader);
unsigned int  kiwix_reader_get_file_size (KiwixReader *reader);
const char *  kiwix_reader_get_tags (KiwixReader *reader);
const char *  kiwix_reader_get_id (KiwixReader *reader);
const char *  kiwix_reader_get_name (KiwixReader *reader);
const char *  kiwix_reader_get_description (KiwixReader *reader);
unsigned int  kiwix_reader_get_article_count (KiwixReader *reader);
unsigned int  kiwix_reader_get_media_count (KiwixReader *reader);
unsigned int  kiwix_reader_get_global_count (KiwixReader *reader);
const char *  kiwix_reader_get_creator (KiwixReader *reader);
const char *  kiwix_reader_get_publisher (KiwixReader *reader);
const char *  kiwix_reader_get_random_page_url (KiwixReader *reader);
void          kiwix_reader_search_suggestions_smart (KiwixReader *reader, char *text, unsigned int limit);
gboolean      kiwix_reader_get_next_suggestion (KiwixReader *reader, char **suggestion, char** suggestion_url);
gboolean      kiwix_reader_get_faveicon (KiwixReader *reader, char **content, gsize *size, char** mime_type);

G_END_DECLS

#endif
