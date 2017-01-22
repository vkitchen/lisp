#
# CMAKELISTS.TXT
# --------------
#
# Copyright (c) 2017 Vaughan Kitchen
#
# Released under the MIT license (https://opensource.org/licenses/MIT)
#

cmake_minimum_required(VERSION 2.6)
project(Lisp)

set(LISP_FILES
		source/builtin.c
		source/dynarray.c
		source/eval.c
		source/memory.c
		source/parser.c
		)

add_library(LISPlib ${LISP_FILES})

#
# Build any external dependencies
#
include_directories(external/linenoise)
add_subdirectory(external)

add_executable(lisp source/lisp.c)
target_link_libraries(lisp linenoise LISPlib)
