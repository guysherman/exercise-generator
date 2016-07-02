#! /usr/bin/env python
# encoding: utf-8
# Guy Sherman, 2015

import subprocess
import waftools

PROJ_VERSION			=	'0.0.1'
PROJ_MAJOR_VERSION 	=	'0'


VERSION = PROJ_VERSION
APPNAME = 'my_proj'

top = '.'
out = 'build'
libs = ['pthread', 'boost_system', 'gtkmm-3.0']

defines = ''


SUBFOLDERS = ['dep']

def options(opt):
	opt.recurse(SUBFOLDERS)

	opt.load('compiler_cxx')
	opt.load('cppcheck', tooldir=waftools.location)
	opt.add_option("--prefix", action="store", help="the install prefix for the application")
#	opt.add_option("--shared", action="store_true", help="build shared library")
#	opt.add_option("--static", action="store_true", help="build static library")


def configure(conf):
	env = conf.env
	conf.recurse(SUBFOLDERS)
	conf.setenv('main', env)
	conf.load('compiler_cxx')
	conf.load('cppcheck')
	conf.env.CXXFLAGS = ['-Wall', '-ansi', '-g', '-std=c++11']
	conf.env.LIBPATH_JDKSMIDI = ['../dep/jdksmidi/lib']
	conf.env.INCLUDES_JDKSMIDI = ['./dep/jdksmidi/include']
	conf.env.LIB_JDKSMIDI = ['jdksmidi']
	conf.check_cfg(package='gtkmm-3.0', uselib_store='GTKMM', args=['--cflags', '--libs'])
	if conf.options.prefix:
		conf.define('RES_PREFIX', conf.options.prefix + 'share/exercise-generator/res')
	else:
		conf.define('RES_PREFIX', '/usr/local/share/exercise-generator/res')
	conf.write_config_header('config.h')


def build(bld):
	bld.recurse(SUBFOLDERS)
	bld.env = bld.all_envs['main']
	#resources = bld.path.ant_glob('res/**/*')
	#for r in resources:
	#	print("Copying", r.abspath())
	#	bld(rule="mkdir -p res && cp -R  ${SRC} res/", source=r)
	bld.program(source = bld.path.ant_glob('src/**/*.cxx'),
				includes = ['./include', './dep/buffer/include'],
				cxxflags=['-Werror', '-pedantic-errors'],
				lib = libs,
				target = 'myproj',
				install_path = '${BINDIR}',
				defines = defines,
				use=['JDKSMIDI', 'GTKMM'],
				features=['cxx', 'cxxprogram'])

	bld.program(source = bld.path.ant_glob('tests/**/*.cxx'),
				includes = ['./include', './src', './dep/wq/include', './dep/buffer/include'],
				cxxflags=['-w'],
				lib = ['pthread', 'boost_system'],
				target = 'tests/all',
				install_path = '${BINDIR}',
				defines = defines,
				use=['wq', 'gtest', 'gtest_main'],
				cppcheck_skip=True,
				features="cxx cxxprogram")


def test(bld):
	subprocess.check_call("./run_tests.sh")


def verify(bld):
	subprocess.check_call("./grind_tests.sh")
