{
  'targets': [
    {
      'target_name': 'pHashBinding',
      'defines': [
        'HAVE_IMAGE_HASH',
        'cimg_verbosity=0',
        'cimg_use_png',
        'cimg_use_jpeg',
      ],
      'include_dirs': [
        'deps/pHash',
        'deps/libpng',
        'deps/libjpeg',
        "<!(node -e \"require('nan')\")"
       ],
      'sources': [
        'src/Helper.cpp',
        'src/ImageHash.cpp',
        'src/VideoHash.cpp',
        'src/phash.cpp'
      ],
      'libraries': [
        '-ljpeg',
        '-lpng',
        '-lavformat',
        '-lavcodec',
        '-lswscale',
        '-lswresample'
      ],
      'cflags': ['-fexceptions'],
      'cflags_cc': ['-fexceptions'],
      'dependencies': [
        'deps/pHash/pHash.gyp:phash'
      ]
    }
  ]
}
