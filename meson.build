project('misc-tools', 'c', 'cpp', version: '0.0.1', license: 'MIT',
	default_options: ['c_std=gnu99', 'cpp_std=gnu++17'])

executable('bin-packing', 'bin-packing.cc')
executable('bit-extract', 'bit-extract.c')
executable('bit-not', 'bit-not.c')
executable('bit-shift', 'bit-shift.c')
executable('fake-sudo', 'fake-sudo.c')
executable('page2vma', 'page2vma.c')
executable('vma2page', 'vma2page.c')

if host_machine.system() == 'darwin'
  add_languages('objc')
  foundation_dep = dependency('appleframeworks', modules: 'foundation')
  executable('notify', 'notify.m', dependencies: foundation_dep)
endif
