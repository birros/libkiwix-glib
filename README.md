# Libkiwix-GLib

**Partial GObject/C bindings for the libkiwix.**
This bindings was primarly done to permit [libkiwix] usage for [WebArchives].

## Dependencies and environnement

See flatpak manifest and adapt your system in consequence.

## Building

```
mkdir build && cd build
meson ..
ninja
```

## Tests

Enable tests by passing `enable-tests=true` argument during meson configuration.

```
cd build
meson -Denable-tests=true ..
```

**Disclaimer**
Tests are not truely unit tests, just try to use the library to get informations
from an archive.
Those are useful to quickly show result of bindings use.

### All tests

```
meson test --test-args=<archive-path>
```

**Notice**
Don't forget to:
1. give *absolute path* of the archive.
2. *double quote* the path.
3. *escape space character* with backslash.


### Test and print output of a specific test

```
meson test --test-args=<archive-path> prog-c -v
```

**Notice**
Same requirements as previous notice.

### TODO

1. Write true unit tests.
2. Make doc.

## License

GPLv3 or later, see COPYING for more details.

<!-- Links references -->

[libkiwix]: https://github.com/kiwix/kiwix-lib
[WebArchives]: https://github.com/birros/web-archives
