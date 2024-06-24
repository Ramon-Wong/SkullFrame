#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.resources"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[1157]; const double alignment; void * const ptr;}  resources_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\000\001\000\000\000\000\000\050\010\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\001\000\000\000"
  "\002\000\000\000\003\000\000\000\003\000\000\000\004\000\000\000"
  "\052\302\267\054\002\000\000\000\000\001\000\000\006\000\114\000"
  "\010\001\000\000\014\001\000\000\233\030\247\362\004\000\000\000"
  "\014\001\000\000\007\000\114\000\024\001\000\000\030\001\000\000"
  "\324\265\002\000\377\377\377\377\030\001\000\000\001\000\114\000"
  "\034\001\000\000\040\001\000\000\336\027\310\306\001\000\000\000"
  "\040\001\000\000\010\000\166\000\050\001\000\000\327\001\000\000"
  "\267\302\003\152\000\000\000\000\327\001\000\000\004\000\114\000"
  "\334\001\000\000\350\001\000\000\137\270\316\033\007\000\000\000"
  "\350\001\000\000\011\000\166\000\370\001\000\000\334\002\000\000"
  "\037\122\217\367\004\000\000\000\334\002\000\000\011\000\166\000"
  "\350\002\000\000\171\004\000\000\067\075\347\135\004\000\000\000"
  "\171\004\000\000\006\000\114\000\200\004\000\000\204\004\000\000"
  "\155\171\141\160\160\057\000\000\004\000\000\000\163\143\162\151"
  "\160\164\057\000\003\000\000\000\057\000\000\000\000\000\000\000"
  "\151\156\144\145\170\056\152\163\237\000\000\000\000\000\000\000"
  "\144\157\143\165\155\145\156\164\056\141\144\144\105\166\145\156"
  "\164\114\151\163\164\145\156\145\162\050\047\104\117\115\103\157"
  "\156\164\145\156\164\114\157\141\144\145\144\047\054\040\050\051"
  "\040\075\076\040\173\040\144\157\143\165\155\145\156\164\056\147"
  "\145\164\105\154\145\155\145\156\164\102\171\111\144\050\047\141"
  "\154\145\162\164\102\165\164\164\157\156\047\051\056\141\144\144"
  "\105\166\145\156\164\114\151\163\164\145\156\145\162\050\047\143"
  "\154\151\143\153\047\054\040\050\051\040\075\076\040\173\040\141"
  "\154\145\162\164\050\047\102\165\164\164\157\156\040\143\154\151"
  "\143\153\145\144\041\047\051\073\175\051\073\175\051\073\012\000"
  "\000\050\165\165\141\171\051\167\145\142\057\000\006\000\000\000"
  "\001\000\000\000\007\000\000\000\163\164\171\154\145\056\143\163"
  "\163\000\000\000\000\000\000\000\324\000\000\000\000\000\000\000"
  "\142\157\144\171\040\173\040\146\157\156\164\055\146\141\155\151"
  "\154\171\072\040\101\162\151\141\154\054\040\163\141\156\163\055"
  "\163\145\162\151\146\073\040\142\141\143\153\147\162\157\165\156"
  "\144\055\143\157\154\157\162\072\040\043\146\060\146\060\146\060"
  "\073\040\164\145\170\164\055\141\154\151\147\156\072\040\143\145"
  "\156\164\145\162\073\040\160\141\144\144\151\156\147\055\164\157"
  "\160\072\040\065\060\160\170\073\040\175\012\150\061\040\173\040"
  "\143\157\154\157\162\072\040\043\063\063\063\073\175\012\160\040"
  "\173\040\146\157\156\164\055\163\151\172\145\072\040\061\070\160"
  "\170\073\175\012\142\165\164\164\157\156\040\173\040\160\141\144"
  "\144\151\156\147\072\040\061\060\160\170\040\062\060\160\170\073"
  "\040\146\157\156\164\055\163\151\172\145\072\040\061\066\160\170"
  "\073\040\143\165\162\163\157\162\072\040\160\157\151\156\164\145"
  "\162\073\175\012\000\000\050\165\165\141\171\051\155\141\151\156"
  "\056\150\164\155\154\000\000\000\201\001\000\000\000\000\000\000"
  "\074\041\104\117\103\124\131\120\105\040\150\164\155\154\076\012"
  "\074\150\164\155\154\076\012\074\150\145\141\144\076\012\011\074"
  "\154\151\156\153\040\162\145\154\075\042\163\164\171\154\145\163"
  "\150\145\145\164\042\040\164\171\160\145\075\042\164\145\170\164"
  "\057\143\163\163\042\040\150\162\145\146\075\042\162\145\163\157"
  "\165\162\143\145\163\072\057\057\057\155\171\141\160\160\057\167"
  "\145\142\057\163\164\171\154\145\057\163\164\171\154\145\056\143"
  "\163\163\042\076\012\011\074\163\143\162\151\160\164\040\164\171"
  "\160\145\075\042\164\145\170\164\057\152\141\166\141\163\143\162"
  "\151\160\164\042\040\163\162\143\075\042\162\145\163\157\165\162"
  "\143\145\163\072\057\057\057\155\171\141\160\160\057\167\145\142"
  "\057\163\143\162\151\160\164\057\151\156\144\145\170\056\152\163"
  "\042\076\074\057\163\143\162\151\160\164\076\012\074\057\150\145"
  "\141\144\076\012\074\142\157\144\171\076\012\011\074\150\061\076"
  "\110\145\154\154\157\054\040\127\145\142\113\151\164\107\124\113"
  "\040\167\151\164\150\040\107\122\145\163\157\165\162\143\145\041"
  "\074\057\150\061\076\012\011\074\160\076\124\150\151\163\040\151"
  "\163\040\141\040\163\151\155\160\154\145\040\167\145\142\160\141"
  "\147\145\040\164\157\040\164\145\163\164\040\107\122\145\163\157"
  "\165\162\143\145\040\151\156\164\145\147\162\141\164\151\157\156"
  "\056\074\057\160\076\012\011\074\142\165\164\164\157\156\040\151"
  "\144\075\042\141\154\145\162\164\102\165\164\164\157\156\042\076"
  "\103\154\151\143\153\040\155\145\074\057\142\165\164\164\157\156"
  "\076\012\074\057\142\157\144\171\076\012\074\057\150\164\155\154"
  "\076\000\000\050\165\165\141\171\051\163\164\171\154\145\057\000"
  "\005\000\000\000" };

static GStaticResource static_resource = { resources_resource_data.data, sizeof (resources_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_MODULE_EXPORT
GResource *resources_get_resource (void);
GResource *resources_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_CONSTRUCTOR_H__
#define __G_CONSTRUCTOR_H__

/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

/*
 * Only try to include gslist.h if not already included via glib.h,
 * so that items using gconstructor.h outside of GLib (such as
 * GResources) continue to build properly.
 */
#ifndef __G_LIB_H__
#include "gslist.h"
#endif

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */
#endif /* __G_CONSTRUCTOR_H__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(resourcesresource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(resourcesresource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(resourcesresource_destructor)
#endif
G_DEFINE_DESTRUCTOR(resourcesresource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void resourcesresource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void resourcesresource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
