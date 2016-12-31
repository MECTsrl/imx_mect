/** \ingroup rpmbuild
 * \file build/myftw.c
 * Modified ftw() -- uses Lstat() instead of stat().
 */

/* Copyright (C) 1992, 1994, 1995 Free Software Foundation, Inc.
This file is part of the GNU C Library.
Contributed by Ian Lance Taylor (ian@airs.com).

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA.  */

#include "system.h"

#include <rpmio.h>

#ifndef NAMLEN
#define NAMLEN(a) strlen((a)->d_name)
#endif

#if !defined(__LCLINT__)
#ifndef PATH_MAX
#ifdef _POSIX_VERSION
#define PATH_MAX _POSIX_PATH_MAX
#else
#ifdef MAXPATHLEN
#define PATH_MAX MAXPATHLEN
#else
#define PATH_MAX 1024
#endif
#endif
#endif
#endif	/* !__LCLINT */

#include "myftw.h"
#include "debug.h"

/* Traverse one level of a directory tree.  */

/**
 */
/*@-nullstate@*/
static int
myftw_dir (DIR **dirs, int level, int descriptors,
	   char *dir, size_t len, 
	   myftwFunc func,
	   void *fl)
	/*@globals errno, fileSystem @*/
	/*@modifies *dirs, *dir, errno, fileSystem @*/
{
  int got;
  struct dirent *entry;
  int d_namlen;

  got = 0;

  errno = 0;

  while ((entry = Readdir (dirs[level])) != NULL)
    {
      struct stat s;
      int flag, retval, newlev = 0;

      ++got;

      if (entry->d_name[0] == '.'
	  && (entry->d_name [1] == '\0' ||
	      (entry->d_name [2] == '\0' && entry->d_name[1] == '.')))
	{
	  errno = 0;
	  continue;
	}

      d_namlen = NAMLEN(entry) + 1;
      if (d_namlen + len > PATH_MAX)
	{
#ifdef ENAMETOOLONG
	  errno = ENAMETOOLONG;
#else
	  errno = ENOMEM;
#endif
	  return -1;
	}

      dir[len] = '/';
      memcpy ((void *) (dir + len + 1), (void *) entry->d_name, d_namlen);

      if (Lstat (dir, &s) < 0)
	{
	  /* Following POSIX.1 2.4 ENOENT is returned if the file cannot
	   * be stat'ed.  This can happen for a file returned by Readdir
	   * if it's an unresolved symbolic link.  This should be regarded
	   * as an forgivable error.  -- Uli.  */
	  if (errno != EACCES && errno != ENOENT)
	    return -1;
	  flag = MYFTW_NS;
	}
      else if (S_ISDIR (s.st_mode))
	{
	  newlev = (level + 1) % descriptors;

	  /*@-unqualifiedtrans@*/
	  if (dirs[newlev] != NULL)
	    (void) Closedir (dirs[newlev]);
	  /*@=unqualifiedtrans@*/

	  dirs[newlev] = Opendir (dir);
	  if (dirs[newlev] != NULL)
	    flag = MYFTW_D;
	  else
	    {
	      if (errno != EACCES)
		return -1;
	      flag = MYFTW_DNR;
	    }
	}
      else
	flag = MYFTW_F;

      retval = (*func) (fl, dir, &s);

      if (flag == MYFTW_D)
	{
	  if (retval == 0)
	    retval = myftw_dir (dirs, newlev, descriptors, dir,
				d_namlen + len, func, fl);
	  if (dirs[newlev] != NULL)
	    {
	      int save;

	      save = errno;
	      (void) Closedir (dirs[newlev]);
	      errno = save;
	      dirs[newlev] = NULL;
	    }
	}

      if (retval != 0)
	return retval;

      if (dirs[level] == NULL)
	{
	  int skip;

	  dir[len] = '\0';
	  dirs[level] = Opendir (dir);
	  if (dirs[level] == NULL)
	    return -1;
	  skip = got;
	  while (skip-- != 0)
	    {
	      errno = 0;
	      if (Readdir (dirs[level]) == NULL)
		return errno == 0 ? 0 : -1;
	    }
	}

      errno = 0;
    }

  return errno == 0 ? 0 : -1;
}
/*@=nullstate@*/

/* Call a function on every element in a directory tree.  */

int myftw (const char *dir,
	   int descriptors,
	   myftwFunc func,
	   void *fl)
{
  DIR **dirs;
  size_t len;
  char buf[PATH_MAX + 1];
  struct stat s;
  int flag, retval;
  int i;

  if (descriptors <= 0)
    descriptors = 1;

  /*@access DIR@*/
  dirs = (DIR **) alloca (descriptors * sizeof (*dirs));
  i = descriptors;
  while (i-- > 0)
    dirs[i] = NULL;

  if (Lstat (dir, &s) < 0)
    {
      /* Following POSIX.1 2.4 ENOENT is returned if the file cannot
       * be stat'ed.  This can happen for a file returned by Readdir
       * if it's an unresolved symbolic link.  This should be regarded
       * as an forgivable error.  -- Uli.  */
      if (errno != EACCES && errno != ENOENT)
	return -1;
      flag = MYFTW_NS;
    }
  else if (S_ISDIR (s.st_mode))
    {
      dirs[0] = Opendir (dir);
      if (dirs[0] != NULL)
	flag = MYFTW_D;
      else
	{
	  if (errno != EACCES)
	    return -1;
	  flag = MYFTW_DNR;
	}
    }
  else
    flag = MYFTW_F;

  len = strlen (dir);
  memcpy ((void *) buf, (void *) dir, len + 1);

  retval = (*func) (fl, buf, &s);

  if (flag == MYFTW_D)
    {
      if (retval == 0)
	retval = myftw_dir (dirs, 0, descriptors, buf, len, func, fl);
      if (dirs[0] != NULL)
	{
	  int save;

	  save = errno;
	  (void) Closedir (dirs[0]);
	  /*@-mods@*/
	  errno = save;
	  /*@=mods@*/
	}
    }

  return retval;
}
