{
  'targets': [
    {
      'target_name': 'phash',
      'type': 'static_library',
      'defines': [
        'HAVE_IMAGE_HASH',
        'cimg_verbosity=0',
        'cimg_use_png',
        'cimg_use_jpeg',
      ],
      'include_dirs': [
        '.'
      ],
      'cflags': ['-fexceptions'],
      'cflags_cc': ['-fexceptions'],
      'sources': [
        './ph_fft.c',
        './cimgffmpeg.cpp',
        './pHash.cpp'
      ]
    },
  ],
}
