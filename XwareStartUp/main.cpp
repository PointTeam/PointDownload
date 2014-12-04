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

/*
 * this file is refered to the chmns writed by xinkai who is the author of XwareDesktop,
 *  thank xinkai very much!
 */
/*
 *  此源码参考了XwareDesktop的原作者Xinkai写的chmns
 * 所以在部分代码上会有相似之处
 * 在此先谢谢原作者给我的各种启示和灵感
 */

//#define _GNU_SOURCE
#include <sched.h> // unshare
#include <sys/mount.h> // mount
#include <unistd.h> // execvp, getuid
#include <stdio.h> // stderr
#include <stdlib.h> // getenv, EXIT_FAILURE
#include <limits.h> // PATH_MAX
#include <pwd.h> // getpwuid
#include <string.h> // strcpy
#include <errno.h> // errno

#include <iostream>
using namespace std;

char** cmd = NULL;
char* home = NULL;
char* defaultDownloadDir = NULL;

char profileDir[PATH_MAX] = {0};
char pointMntHome[PATH_MAX] = {0};

void prepare()
{
    int ret;

    // get home
    struct passwd* pw = getpwuid(getuid());
    if (pw == NULL)
    {
        // error
        perror("err: getpwuid");
        exit(EXIT_FAILURE);
    }

    // plugin dir
    home = pw->pw_dir;
    strcpy(profileDir, home);
    strcat(profileDir, "/.PointConfig/XwarePlugin");

    // Separate the mount namespace
    ret = unshare(CLONE_NEWNS);
    if (ret < 0) {
        perror("err: unshare");
        exit(EXIT_FAILURE);
    }

    // mount independent mount namespace
    ret = mount("", "/", "Doesntmatter", MS_PRIVATE|MS_REC|MS_NODEV, NULL);
    if (ret < 0) {
        perror("err: mount (making sure subtree '/' is private)");
        exit(EXIT_FAILURE);
    }
}

// mount the tmp dir
void mountDirs()
{
    int ret;
    char tmpDir[PATH_MAX];

    strcpy(tmpDir, profileDir);
    strcat(tmpDir, "/tmp");

    // mount the /tmp independently for xware configure profile
    ret = mount(tmpDir, "/tmp", "Doesntmatter", MS_BIND|MS_NOEXEC, NULL);
    if (ret < 0) {
        perror("err: mount (bind:/tmp)");
        exit(EXIT_FAILURE);
    }

    ret = chdir(tmpDir);
    if (ret < 0) {
        perror("err: chdir");
        exit(EXIT_FAILURE);
    }
}

void mountDownloadDir()
{
    int ret;

    // mount default download directory
    cout<<"defaultDownloadDir: "<<defaultDownloadDir<<endl;
    cout<<"pointMntHome: "<<pointMntHome<<endl;
    ret = mount(defaultDownloadDir, pointMntHome, "Doesntmatter", MS_BIND|MS_NOEXEC, NULL);
    if (ret < 0)
    {
        perror("err: mount Download Dirs: ");
        exit(EXIT_FAILURE);
    }
}

void run()
{
    int ret;

    // set the LD_PRELOAD env
    ret = setenv("LD_PRELOAD", getenv("POINT-SO-PATH"), 1);
    if (ret < 0)
    {
        perror("err: set env (PRE_LOAD)");
        exit(EXIT_FAILURE);
    }

    // start up xware(ETM)
    ret = execvp(cmd[0], cmd);

    if (ret < 0)
    {
        perror("err: execvp");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char** argv)
{
    (void)argc;
    // move the pointer of agrc
    ++argv;
    int ret = setenv("POINT-SO-PATH", argv[0], 1);
    if (ret < 0)
    {
        perror("err: setenv(POINT-SO-PATH) ");
        exit(EXIT_FAILURE);
    }

    // get the excute cmd
    cmd = ++argv;

    prepare();
    mountDirs();
    run();
    return 0;
}

