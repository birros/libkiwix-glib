project('libkiwix-glib', 'cpp', version: '1.0.1')

kiwix_version = meson.project_version()
kiwix_version_digits = kiwix_version.split('.')
kiwix_major_version = kiwix_version_digits[0].to_int()
kiwix_minor_version = kiwix_version_digits[1].to_int()
kiwix_micro_version = kiwix_version_digits[2].to_int()

kiwix_api_version = '@0@.0'.format(kiwix_major_version)

prefix = get_option('prefix')
datadir = join_paths(prefix, get_option('datadir'))
libdir = join_paths(prefix, get_option('libdir'))
includedir = join_paths(prefix, get_option('includedir'))

glib = dependency('glib-2.0')
gobject = dependency('gobject-2.0')
kiwix = dependency('kiwix', version : '>=1.0.1')

gnome = import('gnome')

enable_tests = get_option('enable-tests')

subdir('src')
