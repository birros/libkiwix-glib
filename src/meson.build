public_headers = [
    'reader.h'
]

sources = [
    'reader.cpp'
]

libkiwix = shared_library(
    'kiwix-glib-@0@'.format(kiwix_api_version),
    sources,
    version : kiwix_version,
    soversion : '0',
    dependencies : [
        glib,
        gobject,
        kiwix
    ],
    install: true
)

install_headers(
    public_headers,
    subdir: 'kiwix-glib-@0@'.format(kiwix_api_version)
)

kiwix_gir = gnome.generate_gir(
    libkiwix,
    sources: [
        public_headers,
        sources
    ],
    namespace: 'Kiwix',
    nsversion: kiwix_api_version,
    identifier_prefix: 'Kiwix',
    symbol_prefix: 'kiwix',
    export_packages: 'kiwix-glib-@0@'.format(kiwix_api_version),
    includes: ['GLib-2.0', 'GObject-2.0'],
    install: true
)

cp = find_program('cp')
kiwix_metadata = custom_target(
    'kiwix-metadata',
    input: 'Kiwix.metadata',
    output: 'Kiwix-@0@.metadata'.format(kiwix_api_version),
    install: false,
    command: [cp, '@INPUT@', '@OUTPUT@']
)

# the move command and metadatadir's src argument are for fixing the destination
# path of the output file
vapigen = find_program('vapigen')
kiwix_vapi = custom_target(
    'kiwix-vapi',
    depends: kiwix_metadata,
    input: kiwix_gir,
    output: 'kiwix-glib-@0@.vapi'.format(kiwix_api_version),
    command: [
        vapigen,
            '--library', 'kiwix-glib-@0@'.format(kiwix_api_version),
            '--metadatadir', './src',
            '@INPUT@',
        '&&',
        'mv',
            'kiwix-glib-@0@.vapi'.format(kiwix_api_version),
            '@OUTPUT@'
    ],
    install: true,
    install_dir: join_paths(datadir, 'vala/vapi')
)

pkg = import('pkgconfig')
pkg.generate(
    filebase : 'kiwix-glib-@0@'.format(kiwix_api_version),
    name : 'Kiwix',
    description : 'GObject Bindings of Kiwix library',
    version : kiwix_version,
    libraries : [
        libkiwix
    ],
    subdirs : ['kiwix-glib-@0@'.format(kiwix_api_version)],
    requires: ['glib-2.0', 'gobject-2.0']
)

if enable_tests
    libkiwix_private = static_library(
        'kiwix-glib-private',
        sources: sources,
        dependencies : [
            glib,
            gobject,
            kiwix
        ],
        install: false
    )
    libkiwix_private_inc = include_directories('.')
    libkiwix_private_dep = declare_dependency(
        include_directories: libkiwix_private_inc,
        link_with : libkiwix_private,
        sources: kiwix_vapi
    )

    subdir('tests')
endif
