#include "reader.h"
#include <kiwix/reader.h>

/**
 * SECTION: kiwix-reader
 * @Title: KiwixReader
 * @short_description: A kiwix reader
 *
 * #KiwixReader is a class that permit to get informations from a zim file.
 * It can be also used to get search suggetions and favicon file.
 */

#define KIWIX_READER_GET_PRIVATE(obj) \
    ((KiwixReaderPrivate *) kiwix_reader_get_instance_private ((KiwixReader *) (obj)))

typedef struct _KiwixReaderPrivate KiwixReaderPrivate;
struct _KiwixReaderPrivate
{
    kiwix::Reader *reader;
};

G_DEFINE_TYPE_WITH_PRIVATE (KiwixReader, kiwix_reader, G_TYPE_OBJECT)

static void
kiwix_reader_finalize (GObject *gobject)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (gobject);

    delete priv->reader;

    G_OBJECT_CLASS (kiwix_reader_parent_class)->dispose (gobject);
}

static void
kiwix_reader_class_init (KiwixReaderClass *klass)
{
    G_OBJECT_CLASS (klass)->finalize = kiwix_reader_finalize;
}

static void
kiwix_reader_init (KiwixReader *object)
{
}

/**
 * kiwix_reader_new:
 * @zimpath: the path to the zim file
 * @error: a #GError object
 *
 * Allocates a new #KiwixReader.
 *
 * Returns: (transfer full): the newly created #KiwixReader instance
 */
KiwixReader *
kiwix_reader_new (const char *zimpath, GError **error)
{
    KiwixReader *reader;
    reader = (KiwixReader *) g_object_new (KIWIX_TYPE_READER, NULL);

    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    try
    {
        priv->reader = new kiwix::Reader (zimpath);
    }
    catch (const std::exception &err)
    {
        *error = g_error_new_literal (1, 0, err.what ());
    }

    return reader;
}

/**
 * kiwix_reader_get_title:
 * @reader: A #KiwixReader
 *
 * Get the title of the zim file.
 *
 * Returns: (transfer full): the title of the zim file
 */
const char *
kiwix_reader_get_title (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    std::string title = priv->reader->getTitle ();
    return g_strdup (title.c_str ());
}

/**
 * kiwix_reader_get_date:
 * @reader: A #KiwixReader
 *
 * Get the creation date of the zim file.
 *
 * Returns: (transfer full): the date of the zim file
 */
const char *
kiwix_reader_get_date (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    std::string date = priv->reader->getDate ();
    return g_strdup (date.c_str ());
}

/**
 * kiwix_reader_get_language:
 * @reader: A #KiwixReader
 *
 * Get the languages used in the zim file.
 * If there are multiple languages those are separated by a comma.
 *
 * Returns: (transfer full): a string containing the list of languages
 */
const char *
kiwix_reader_get_language (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    std::string language = priv->reader->getLanguage ();
    return g_strdup (language.c_str ());
}

/**
 * kiwix_reader_get_file_size:
 * @reader: A #KiwixReader
 *
 * Get the zim file size.
 *
 * Returns: the zim file size
 */
unsigned int
kiwix_reader_get_file_size (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    return priv->reader->getFileSize ();
}

/**
 * kiwix_reader_get_tags:
 * @reader: A #KiwixReader
 *
 * Get the list of tags of the zim file separated by semilicon.
 *
 * Returns: (transfer full): the list of tags of the zim file
 */
const char *
kiwix_reader_get_tags (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    std::string tags = priv->reader->getTags();
    return g_strdup (tags.c_str ());
}

/**
 * kiwix_reader_get_id:
 * @reader: A #KiwixReader
 *
 * Get the unique id of the zim file.
 *
 * Returns: (transfer full): the unique id of the zim file
 */
const char *
kiwix_reader_get_id (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    std::string id = priv->reader->getId ();
    return g_strdup (id.c_str ());
}

/**
 * kiwix_reader_get_name:
 * @reader: A #KiwixReader
 *
 * Get the zim file name, that is stable across content versionning.
 * Usefull for inter-version references sharing (history, bookmarks, search).
 *
 * Returns: (transfer full): the name of the zim file
 */
const char *
kiwix_reader_get_name (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    std::string name = priv->reader->getName ();
    return g_strdup (name.c_str ());
}

/**
 * kiwix_reader_get_description:
 * @reader: A #KiwixReader
 *
 * Get the description of the zim file.
 *
 * Returns: (transfer full): the description of the zim file
 */
const char *
kiwix_reader_get_description (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    std::string description = priv->reader->getDescription ();
    return g_strdup (description.c_str ());
}

/**
 * kiwix_reader_get_article_count:
 * @reader: A #KiwixReader
 *
 * Get the count of articles inside the zim file.
 *
 * Returns: the count of articles
 */
unsigned int
kiwix_reader_get_article_count (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    return priv->reader->getArticleCount ();
}

/**
 * kiwix_reader_get_media_count:
 * @reader: A #KiwixReader
 *
 * Get the count of media files inside the zim file.
 *
 * Returns: the count of media files
 */
unsigned int
kiwix_reader_get_media_count (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    return priv->reader->getMediaCount ();
}

/**
 * kiwix_reader_get_global_count:
 * @reader: A #KiwixReader
 *
 * Get the global count of files inside the zim file.
 *
 * Returns: the total of files inside the zim file.
 */
unsigned int
kiwix_reader_get_global_count (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    return priv->reader->getGlobalCount ();
}

/**
 * kiwix_reader_get_creator:
 * @reader: A #KiwixReader
 *
 * Get the creator's name of the content of the zim file.
 *
 * Returns: (transfer full): the creator of the content
 */
const char *
kiwix_reader_get_creator (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    std::string creator = priv->reader->getCreator ();
    return g_strdup (creator.c_str ());
}

/**
 * kiwix_reader_get_publisher:
 * @reader: A #KiwixReader
 *
 * Get the creator's name of the zim file, not the content.
 *
 * Returns: (transfer full): the creator of the zim file
 */
const char *
kiwix_reader_get_publisher (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    std::string publisher = priv->reader->getPublisher ();
    return g_strdup (publisher.c_str ());
}

/**
 * kiwix_reader_get_random_page_url:
 * @reader: A #KiwixReader
 *
 * Get the url of a random page from the zim file.
 *
 * Returns: (transfer full): a random page url
 */
const char *
kiwix_reader_get_random_page_url (KiwixReader *reader)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);
    std::string random_page_url = priv->reader->getRandomPageUrl ();
    return g_strdup (random_page_url.c_str ());
}

/**
 * kiwix_reader_search_suggestions_smart:
 * @reader: A #KiwixReader
 * @text: text to search
 * @limit: limit of the search results
 *
 * Start search suggestions task.
 */
void
kiwix_reader_search_suggestions_smart (KiwixReader *reader, char *text, unsigned int limit)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);

    priv->reader->searchSuggestionsSmart (text, limit);
}

/**
 * kiwix_reader_get_next_suggestion:
 * @reader: A #KiwixReader
 * @suggestion: (out) (transfer full): suggestion title
 * @suggestion_url: (out) (transfer full): suggestion url
 *
 * Get the next search suggestion.
 *
 * Returns: TRUE if there is a next suggestion, FALSE otherwise
 */
gboolean
kiwix_reader_get_next_suggestion (KiwixReader *reader, char **suggestion, char **suggestion_url)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);

    std::string suggestion_cpp;
    std::string suggestion_url_cpp;

    bool next = priv->reader->getNextSuggestion (suggestion_cpp, suggestion_url_cpp);

    *suggestion = g_strdup (suggestion_cpp.c_str ());
    *suggestion_url = g_strdup (suggestion_url_cpp.c_str ());

    return next;
}

/**
 * kiwix_reader_get_faveicon:
 * @reader: A #KiwixReader
 * @content: (out) (array length=size) (element-type guint8) (transfer full): favicon data
 * @size: (out) (optional): length of favicon data
 * @mime_type: (out) (transfer full): mime_type of favicon data
 *
 * Get favicon data of the zim file.
 *
 * Returns: TRUE if favicon is found, FALSE otherwise
 */
gboolean
kiwix_reader_get_faveicon (KiwixReader *reader, char **content, gsize *size, char **mime_type)
{
    KiwixReaderPrivate *priv = KIWIX_READER_GET_PRIVATE (reader);

    std::string image;
    std::string type;

    priv->reader->getFavicon (image, type);

    *size = image.size ();

    // copy the favicon data
    *content = (char*) malloc (image.size () * sizeof (char));
    memcpy(*content, image.data (), image.size ());

    *mime_type = g_strdup (type.c_str ());

    return image.size () > 0;
}
