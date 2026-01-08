project(
  'test_xsimd_dynamic_dispatch',
  'cpp',
  meson_version: '>= 1.0.0',
  version : '0.1.0', 
  default_options : ['warning_level=3', 'cpp_std=c++20', 'default_library=static', 'buildtype=release'],
  license : 'GPL3'
)

xsimd_dep = dependency('xsimd')

simd_deps = []

cpp = meson.get_compiler('cpp')

if target_machine.cpu_family() == 'x86_64'
    x86_vectorized_libs = []
    x86_vectorized_defs = []
    xsimd_arch_list = []
    if cpp.get_id() == 'msvc'
        archs = [
            {
                'name':'avx512bw',
                'flags':['/arch:AVX10.1'],
                'xsimd_name':'avx512bw'
            },
            {
                'name':'avx512',
                'flags':['/arch:AVX512'],
                'xsimd_name':'avx512f'
            },
            {
                'name':'avx2',
                'flags':['/arch:AVX2'],
                'xsimd_name':'avx2'
            },
            {
                'name':'sse2',
                'flags':['/arch:SSE2'],
                'xsimd_name':'sse2'
            }
            ]
    else
        archs = [
            {
                'name':'avx512bw',
                'flags':['-mavx512f', '-mavx512bw', '-mavx512dq', '-mavx512cd'],
                'xsimd_name':'avx512bw'
            },
            {
                'name':'avx512',
                'flags':['-mavx512f'],
                'xsimd_name':'avx512f'
            },
            {
                'name':'avx2',
                'flags':['-mavx2'],
                'xsimd_name':'avx2'
            },
            {
                'name':'sse2',
                'flags':['-msse2'],
                'xsimd_name':'sse2'
            }
            ]
    endif
    foreach arch : archs
        enable_arch_def = '-DTEST_XSIMD_ENABLE_'+arch['name'].to_upper()+'_ARCH'
        x86_vectorized_libs += [
            static_library('test_xsimd_x86_vectorized_'+arch['name'],
                'src/simd_arch.cpp',
                include_directories : 'include',
                cpp_args : arch['flags'] + [enable_arch_def, '-DTEST_XSIMD_ARCH='+arch['xsimd_name']],
                dependencies : [xsimd_dep],
                )
        ]
        x86_vectorized_defs += [enable_arch_def]
        xsimd_arch_list += ['xsimd::'+arch['xsimd_name']]
    endforeach
    
    xsimd_arch_list = 'xsimd::arch_list<' + ', '.join(xsimd_arch_list) + '>'

    x86_vectorized_dep = declare_dependency(
        sources : 'src/simd_dispatch.cpp',
        link_with : x86_vectorized_libs,
        compile_args : x86_vectorized_defs + ['-DTEST_XSIMD_ARCH_LIST=@0@'.format(xsimd_arch_list)],
        dependencies : [xsimd_dep]
    )
    simd_deps += [x86_vectorized_dep]
endif

exe = executable('test_xsimd_dynamic_dispatch',
    'src/test_xsimd_dynamic_dispatch.cpp',
    include_directories : 'include',
    dependencies : simd_deps,
)

test('run_test_xsimd_dynamic_dispatch', exe)

summary({'C++': meson.get_compiler('cpp').cmd_array()
        }, section: 'Compilers')
