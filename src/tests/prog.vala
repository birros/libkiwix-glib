const string STYLE_BOLD    = "\033[1m";
const string STYLE_NO_BOLD = "\033[22m";

static int main (string[] argv) {
    // filename argument
    string filename;
    if (argv.length == 2) {
        filename = argv [1];
    } else {
        error ("missing zim file argument, see README.md");
    }


    // init reader
    Kiwix.Reader reader;
    try {
        reader = new Kiwix.Reader(filename);
    } catch (Error e) {
        error ("%s\n", e.message);
    }


    // infos
    stdout.printf ("==INFOS==\n");

    string title = reader.get_title ();
    string date = reader.get_date ();
    string language = reader.get_language ();
    uint file_size = reader.get_file_size ();
    string tags = reader.get_tags ();
    string id = reader.get_id ();
    string name = reader.get_name ();
    string description = reader.get_description ();
    string random_page_url = reader.get_random_page_url ();
    uint article_count = reader.get_article_count ();
    uint media_count = reader.get_media_count ();
    uint global_count = reader.get_global_count ();
    string creator = reader.get_creator ();
    string publisher = reader.get_publisher ();

    //assert(title == "Wikipédia");

    stdout.printf (STYLE_BOLD + "Archive path:    " + STYLE_NO_BOLD + "%s\n", filename);
    stdout.printf (STYLE_BOLD + "Title:           " + STYLE_NO_BOLD + "%s\n", title);
    stdout.printf (STYLE_BOLD + "Date:            " + STYLE_NO_BOLD + "%s\n", date);
    stdout.printf (STYLE_BOLD + "Language:        " + STYLE_NO_BOLD + "%s\n", language);
    stdout.printf (STYLE_BOLD + "File size:       " + STYLE_NO_BOLD + "%d\n", file_size);
    stdout.printf (STYLE_BOLD + "Tags:            " + STYLE_NO_BOLD + "%s\n", tags);
    stdout.printf (STYLE_BOLD + "ID:              " + STYLE_NO_BOLD + "%s\n", id);
    stdout.printf (STYLE_BOLD + "Name:            " + STYLE_NO_BOLD + "%s\n", name);
    stdout.printf (STYLE_BOLD + "Description:     " + STYLE_NO_BOLD + "%s\n", description);
    stdout.printf (STYLE_BOLD + "Random page url: " + STYLE_NO_BOLD + "%s\n", random_page_url);
    stdout.printf (STYLE_BOLD + "Article count:   " + STYLE_NO_BOLD + "%u\n", article_count);
    stdout.printf (STYLE_BOLD + "Media count:     " + STYLE_NO_BOLD + "%u\n", media_count);
    stdout.printf (STYLE_BOLD + "Global count:    " + STYLE_NO_BOLD + "%u\n", global_count);
    stdout.printf (STYLE_BOLD + "Creator:         " + STYLE_NO_BOLD + "%s\n", creator);
    stdout.printf (STYLE_BOLD + "Publisher:       " + STYLE_NO_BOLD + "%s\n", publisher);


    // suggestions
    stdout.printf ("==SUGGESTIONS==\n");

    reader.search_suggestions_smart ("ab", 20);

    string suggestion;
    string suggestion_url;
    while (reader.get_next_suggestion (out suggestion, out suggestion_url)) {
        stdout.printf (STYLE_BOLD + "Suggestion: " + STYLE_NO_BOLD + "%s, ", suggestion);
        stdout.printf (STYLE_BOLD + "Suggestion url: " + STYLE_NO_BOLD + "%s\n", suggestion_url);
    }


    // favicon
    stdout.printf ("==FAVICON==\n");

    uint8[]? data;
    string mime_type;
    reader.get_faveicon (out data, out mime_type);
    uint size = data.length;

    stdout.printf (STYLE_BOLD + "Faveicon size     : " + STYLE_NO_BOLD + "%lu\n", size);
    stdout.printf (STYLE_BOLD + "Faveicon mime type: " + STYLE_NO_BOLD + "%s\n", mime_type);

    // write faveicon to file
    FileStream f = FileStream.open ("faveicon-from-vala.png", "wb");
    f.write (data);

    return 0;
}
