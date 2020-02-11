#ifndef LIBTAG_H
#define LIBTAG_H

#define MAJOR_VERSION     0
#define MINOR_VERSION     9

#include <_Ccsid.h>

#define CCSID_ISO8859_1       (__ccsid_t) 819
#define CCSID_IBM_1047        (__ccsid_t) 1047
#define CCSID_DEFAULT         CCSID_ISO8859_1
#define NAME_CCSID_ISO8859_1  "ISO8859-1"
#define NAME_CCSID_IBM_1047   "IBM-1047"
#define NAME_CCSID_DEFAULT    NAME_CCSID_ISO8859_1
#define NAME_FT_BINARY        "BINARY"
#define NAME_FT_UNTAGGED      "UNTAGGED"

char * tag_version(void);
int tag_major_version(void);
int tag_minor_version(void); 

int init_attr_stdio(void);

int query_attr(int fd, struct f_cnvrt * cvt);
__ccsid_t query_ccsid(char * charset);
char * query_ccsid_name(__ccsid_t ccsid);

int disable_conversion_fd(int fd);
int change_attr_fd(int fd, __ccsid_t ccsid);
int change_attr_fd2(int fd, __ccsid_t ccsid, int filetagchg);
int set_attr_fd(int fd, __ccsid_t ccsid);
int control_attr_fd(int fd, __ccsid_t ccsid);
int set_tag_fd_text(int fd);
int set_tag_fd_text2(int fd, int filetagchg);
int set_tag_fd_binary(int fd);
int set_tag_fd(int fd, char * name_ccsid);
int set_tag_fd2(int fd, char * name_ccsid, int filetagchg);
int copy_tag(int fdsrc, int fddst);

int change_attr_name(char * name, __ccsid_t ccsid);
int set_tag_name_text(char * name);
int set_tag_name_binary(char * name);
int set_tag_name(char * name, char * name_ccsid);

#ifndef __NATIVE_ASCII_F
/*EBCDIC mode*/

#pragma map(tag_version           , "tag_version_e")
#pragma map(tag_major_version     , "tag_major_version_e")
#pragma map(tag_minor_version     , "tag_minor_version_e")
#pragma map(init_attr_stdio       , "init_attr_stdio_e")
#pragma map(query_attr            , "query_attr_e")
#pragma map(query_ccsid           , "query_ccsid_e")
#pragma map(query_ccsid_name      , "query_ccsid_name_e")
#pragma map(disable_conversion_fd , "disable_conversion_fd_e")
#pragma map(change_attr_fd        , "change_attr_fd_e")
#pragma map(change_attr_fd2       , "change_attr_fd2_e")
#pragma map(set_attr_fd           , "set_attr_fd_e")
#pragma map(control_attr_fd       , "control_attr_fd_e")
#pragma map(set_tag_fd_text       , "set_tag_fd_text_e")
#pragma map(set_tag_fd_text2      , "set_tag_fd_text2_e")
#pragma map(set_tag_fd_binary     , "set_tag_fd_binary_e")
#pragma map(set_tag_fd            , "set_tag_fd_e")
#pragma map(set_tag_fd2           , "set_tag_fd2_e")
#pragma map(copy_tag              , "copy_tag_e")
#pragma map(change_attr_name      , "change_attr_name_e")
#pragma map(set_tag_name_text     , "set_tag_name_text_e")
#pragma map(set_tag_name_binary   , "set_tag_name_binary_e")
#pragma map(set_tag_name          , "set_tag_name_e")

#endif

#endif /*#ifndef LIBTAG_H*/

/*
© 2017-2018 Rocket Software, Inc. or its affiliates. All Rights Reserved.
ROCKET SOFTWARE, INC.
*/

