#!/usr/bin/env python3

import sys
import gi
gi.require_version('Kiwix', '1.0')
from gi.repository import Kiwix
from gi.repository import GLib

STYLE_BOLD    = "\033[1m"
STYLE_NO_BOLD = "\033[22m"

def main (argc, argv):
    # filename argument
    if argc == 2:
        filename = argv[1]
    else:
        print ("missing zim file argument, see README.md", file=sys.stderr)
        exit (1)


    # init reader
    try:
        reader = Kiwix.Reader.new (filename)
    except GLib.Error as e:
        print (e, file=sys.stderr)
        exit(1)


    # infos
    print ("==INFOS==");

    title = reader.get_title ()
    date = reader.get_date ()
    language = reader.get_language ()
    file_size = reader.get_file_size ()
    tags = reader.get_tags ()
    id = reader.get_id ()
    name = reader.get_name ()
    description = reader.get_description ()
    random_page_url = reader.get_random_page_url ()
    article_count = reader.get_article_count ()
    media_count = reader.get_media_count ()
    global_count = reader.get_global_count ()
    creator = reader.get_creator ()
    publisher = reader.get_publisher ()

    #assert( title == "Wikipédia" )

    print (STYLE_BOLD + "Archive path:    " + STYLE_NO_BOLD + filename);
    print (STYLE_BOLD + "Title:           " + STYLE_NO_BOLD + title);
    print (STYLE_BOLD + "Date:            " + STYLE_NO_BOLD + date);
    print (STYLE_BOLD + "Language:        " + STYLE_NO_BOLD + language);
    print (STYLE_BOLD + "File size:       " + STYLE_NO_BOLD + str(file_size));
    print (STYLE_BOLD + "Tags:            " + STYLE_NO_BOLD + tags);
    print (STYLE_BOLD + "ID:              " + STYLE_NO_BOLD + id);
    print (STYLE_BOLD + "Name:            " + STYLE_NO_BOLD + name);
    print (STYLE_BOLD + "Description:     " + STYLE_NO_BOLD + description);
    print (STYLE_BOLD + "Random page url: " + STYLE_NO_BOLD + random_page_url);
    print (STYLE_BOLD + "Article count:   " + STYLE_NO_BOLD + str(article_count));
    print (STYLE_BOLD + "Media count:     " + STYLE_NO_BOLD + str(media_count));
    print (STYLE_BOLD + "Global count:    " + STYLE_NO_BOLD + str(global_count));
    print (STYLE_BOLD + "Creator:         " + STYLE_NO_BOLD + creator);
    print (STYLE_BOLD + "Publisher:       " + STYLE_NO_BOLD + publisher);


    # suggestions
    print ("==SUGGESTIONS==");

    reader.search_suggestions_smart ("ab", 20)

    next = True
    while next:
        next, suggestion, suggestion_url = reader.get_next_suggestion ()
        if next:
            print (STYLE_BOLD + "Suggestion: " + STYLE_NO_BOLD + suggestion + ", ", end='')
            print (STYLE_BOLD + "Suggestion url: " + STYLE_NO_BOLD + suggestion_url)


    # favicon
    print ("==FAVICON==")

    result, data, mime_type = reader.get_faveicon ()
    size = len(data)

    print (STYLE_BOLD + "Favicon size:      " + STYLE_NO_BOLD + str(size))
    print (STYLE_BOLD + "Favicon mime type: " + STYLE_NO_BOLD + mime_type)

    # write faveicon to file
    f = open ('faveicon-from-python.png', 'wb')
    f.write (data)
    f.close ()


if __name__ == "__main__":
    main (len(sys.argv), sys.argv)
