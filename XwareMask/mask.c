/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Choldrim <choldrim@foxmail.com>
* Maintainer: Choldrim <choldrim@foxmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

char * file = "/proc/mounts";
char * mFile = "/.PointConfig/XwarePlugin/mounts/mounts";
char redirectFile[PATH_MAX] = {0};
FILE * (*real_fopen64)(const char *filename, const char *type) = NULL;

void f(void) __attribute__ ((constructor));

void f(void)
{
    // get plugin dir
    char plugin[PATH_MAX] = {0};
    struct passwd* pw = getpwuid(getuid());
    if (pw == NULL)
    {
        perror("err: getpwuid");
        exit(EXIT_FAILURE);
    }
    strcpy(plugin, pw->pw_dir);
    strcat(plugin, mFile);
    strcpy(redirectFile, plugin);


    // get the real fopen64
    void * dl = dlopen("libc.so.6", RTLD_LAZY);
    if(dl)
    {
        real_fopen64 = dlsym(dl, "fopen64");
    }
    else
    {
        printf("error, fopen64 can't be found in libc.so \n");
    }

}

FILE * fopen64(const char *filename, const char *type)
{
    if(strcmp(filename, file))
    {
        printf("Point: normal open! \n");
        return real_fopen64(filename,type);
    }

    printf("  Point: redirect mount path! \n");

    return real_fopen64(redirectFile, type);
}
