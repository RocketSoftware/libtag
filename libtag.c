#pragma comment(copyright, " © 2017-2018 Rocket Software, Inc. or its affiliates. All Rights Reserve. ")

#include <stdio.h>
#include <stdlib.h>
#include <sys/modes.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <_Ccsid.h>
#include <_Nascii.h>

#include <libtag.h>

/*****************************************************************************/

char VERSION[] = "0.00";

#ifdef __NATIVE_ASCII_F
char * tag_version(void)
#else
char * tag_version_e(void)
#endif
{
    sprintf(VERSION, "%01d.%02d", MAJOR_VERSION, MINOR_VERSION);
    return VERSION;
}

#ifdef __NATIVE_ASCII_F
int tag_major_version(void)
#else
int tag_major_version_e(void)
#endif
{
    return MAJOR_VERSION;
}

#ifdef __NATIVE_ASCII_F
int tag_minor_version(void)
#else
int tag_minor_version_e(void)
#endif
{
    return MINOR_VERSION;
}

/*****************************************************************************/

static __ccsid_t ccsid_new = CCSID_ISO8859_1;
static char OPTION_CCSID_NEW[] = "_ENCODE_FILE_NEW";
static __ccsid_t ccsid_all = FT_UNTAGGED;
static char OPTION_CCSID_ALL[] = "_ENCODE_FILE_EXISTING";
static __ccsid_t ccsid_pipe = CCSID_ISO8859_1;
static char OPTION_CCSID_PIPE[] = "_ENCODE_PIPE";
static __ccsid_t ccsid_sock = CCSID_ISO8859_1;
static char OPTION_CCSID_SOCK[] = "_ENCODE_SOCK";
static char NAME_UNTAGGED[] = NAME_FT_UNTAGGED;
static char NAME_BINARY[] = NAME_FT_BINARY;

#ifdef __NATIVE_ASCII_F
int query_attr(int fd, struct f_cnvrt * cvt)
#else
int query_attr_e(int fd, struct f_cnvrt * cvt)
#endif
{
    cvt->pccsid = 0;
    cvt->fccsid = 0;
    cvt->cvtcmd = QUERYCVT;

    return fcntl(fd, F_CONTROL_CVT, cvt);
}

#ifdef __NATIVE_ASCII_F
__ccsid_t query_ccsid(char * charset)
#else
__ccsid_t query_ccsid_e(char * charset)
#endif
{
    int check_binary;
    __ccsid_t ccsid = FT_UNTAGGED;

    if (charset == NULL)
        return 0;

    check_binary = strcmp(charset, NAME_BINARY);
    if (check_binary != 0)
    {
        ccsid = __toCcsid(charset);
    }
    else
    {
        ccsid = FT_BINARY;
    }
    return ccsid;
}

char NAME_CCSID[_CSNAME_LEN_MAX] = {0};

#ifdef __NATIVE_ASCII_F
char * query_ccsid_name(__ccsid_t ccsid)
#else
char * query_ccsid_name_e(__ccsid_t ccsid)
#endif
{
    int rc;
    char * name_ccsid = NAME_CCSID;
    rc = __toCSName(ccsid, name_ccsid);
    if (rc == -1)
    {
        name_ccsid = NULL;
    }
    return name_ccsid;
}
/*****************************************************************************/

static set_attr_stdio(int fd)
{
    int rc = 0;
    struct f_cnvrt cvt;

    rc = query_attr(fd, &cvt);
    if (rc == 0)
    {
        if (cvt.fccsid == FT_UNTAGGED)
        {
            cvt.pccsid = 0;
            cvt.fccsid = CCSID_IBM_1047;
            cvt.cvtcmd = SETCVTON;
            rc = fcntl(fd, F_CONTROL_CVT, &cvt);
        }
    }
    return rc;
}

#ifdef __NATIVE_ASCII_F
int init_attr_stdio(void)
#else
int init_attr_stdio_e(void)
#endif
{
    __ae_autoconvert_state(_CVTSTATE_ON);
    set_attr_stdio(STDIN_FILENO);
    set_attr_stdio(STDOUT_FILENO);
    set_attr_stdio(STDERR_FILENO);
    return 0;
}

/*****************************************************************************/

static int check_env_ccsid(void)
{
    int rc;
    __ccsid_t ccsid;
    char * option = NULL;

    option = __getenv(OPTION_CCSID_NEW);
    if (option == NULL)
    {
        ccsid_new = CCSID_ISO8859_1;
    }
    else
    {
        ccsid = __toCcsid(option);
        if (ccsid != 0)
        {
            ccsid_new = ccsid;
        }
        else
        {
            rc = strcmp(option, NAME_UNTAGGED);
            if (rc == 0)
            {
                ccsid_new = FT_UNTAGGED;
            }
            else
            {
                rc = strcmp(option, NAME_BINARY);
                if (rc == 0)
                {
                    ccsid_new = FT_BINARY;
                }
                else
                {
                    ccsid_new = CCSID_ISO8859_1;
                }
            }
        }
    }

    option = __getenv(OPTION_CCSID_ALL);
    if (option == NULL)
    {
        ccsid_all = FT_UNTAGGED;
    }
    else
    {
        ccsid = __toCcsid(option);
        if (ccsid != 0)
        {
            ccsid_all = ccsid;
        }
        else
        {
            rc = strcmp(option, NAME_UNTAGGED);
            if (rc == 0)
            {
                ccsid_all = FT_UNTAGGED;
            }
            else
            {
                rc = strcmp(option, NAME_BINARY);
                if (rc == 0)
                {
                    ccsid_all = FT_BINARY;
                }
                else
                {
                    ccsid_all = FT_UNTAGGED;
                }
            }
        }
    }

    option = __getenv(OPTION_CCSID_PIPE);
    if (option == NULL)
    {
        ccsid_pipe = CCSID_ISO8859_1;
    }
    else
    {
        ccsid = __toCcsid(option);
        if (ccsid != 0)
        {
            ccsid_pipe = ccsid;
        }
        else
        {
            rc = strcmp(option, NAME_UNTAGGED);
            if (rc == 0)
            {
                ccsid_pipe = FT_UNTAGGED;
            }
            else
            {
                rc = strcmp(option, NAME_BINARY);
                if (rc == 0)
                {
                    ccsid_pipe = FT_BINARY;
                }
                else
                {
                    ccsid_pipe = CCSID_ISO8859_1;
                }
            }
        }
    }

    option = __getenv(OPTION_CCSID_SOCK);
    if (option == NULL)
    {
        ccsid_sock = CCSID_ISO8859_1;
    }
    else
    {
        ccsid = __toCcsid(option);
        if (ccsid != 0)
        {
            ccsid_sock = ccsid;
        }
        else
        {
            rc = strcmp(option, NAME_UNTAGGED);
            if (rc == 0)
            {
                ccsid_sock = FT_UNTAGGED;
            }
            else
            {
                rc = strcmp(option, NAME_BINARY);
                if (rc == 0)
                {
                    ccsid_sock = FT_BINARY;
                }
                else
                {
                    ccsid_sock = CCSID_ISO8859_1;
                }
            }
        }
    }

    return 0;
}

/*****************************************************************************/

#ifdef __NATIVE_ASCII_F
int disable_conversion_fd(int fd)
#else
int disable_conversion_fd_e(int fd)
#endif
{
    struct f_cnvrt cvt = { .pccsid = 0, .fccsid = 0, .cvtcmd = SETCVTOFF };
    return fcntl(fd, F_CONTROL_CVT, &cvt);
}

#ifdef __NATIVE_ASCII_F
int change_attr_fd2(int fd, __ccsid_t ccsid, int filetagchg)
#else
int change_attr_fd2_e(int fd, __ccsid_t ccsid, int filetagchg)
#endif
{
    attrib_t attrs;
    memset(&attrs, 0, sizeof(attrs));
    attrs.att_filetagchg = filetagchg;
    if ((ccsid == FT_BINARY) || (ccsid == FT_UNTAGGED))
        attrs.att_filetag.ft_txtflag = 0;
    else
        attrs.att_filetag.ft_txtflag = 1;
    attrs.att_filetag.ft_ccsid = ccsid;
    attrs.att_filetag.ft_deferred = 0; /* if 1 EDC5121I Invalid argument*/
    return __fchattr(fd, &attrs, sizeof(attrs));
}

#ifdef __NATIVE_ASCII_F
int change_attr_fd(int fd, __ccsid_t ccsid)     { return change_attr_fd2(fd, ccsid, 1); }
#else
int change_attr_fd_e(int fd, __ccsid_t ccsid)   { return change_attr_fd2_e(fd, ccsid, 1); }
#endif

#ifdef __NATIVE_ASCII_F
int set_attr_fd(int fd, __ccsid_t ccsid)
#else
int set_attr_fd_e(int fd, __ccsid_t ccsid)
#endif
{
    struct file_tag ft;
    ft.ft_ccsid = ccsid;
    if ((ccsid == FT_BINARY) || (ccsid == FT_UNTAGGED))
    {
        ft.ft_txtflag = 0;
    }
    else
    {
        ft.ft_txtflag = 1;
    }
    ft.ft_deferred = 1;

    return fcntl(fd, F_SETTAG, &ft);
}

#ifdef __NATIVE_ASCII_F
int control_attr_fd(int fd, __ccsid_t ccsid)
#else
int control_attr_fd_e(int fd, __ccsid_t ccsid)
#endif
{
    struct f_cnvrt cvt = { .pccsid = 0, .fccsid = ccsid, .cvtcmd = SETCVTON };
    return fcntl(fd, F_CONTROL_CVT, &cvt);
}

static int percent(int total, int part)
{
    int p = (part * 100) / total;
    return p;
}

#define SIZE_TEST_ARRAY      0x100

static __ccsid_t  autodetect_encoding(int fd)
{
    int i;
    __ccsid_t ccsid = FT_UNTAGGED;
    char test_array[SIZE_TEST_ARRAY] = {0};
    char * p_array = test_array;
    int amount = 0;
    int ascii = 0;
    int ebcdic = 0;
    int binary = 0;

    amount = pread(fd, test_array, SIZE_TEST_ARRAY, 0);
    if ((amount == -1) || (amount == 0))
    {
        return ccsid;
    }

    for (i = 0; i < amount; i++, p_array++)
    {
        char t = *p_array;
        if (t == 0x15)
        {
         /*NL in ebcdic */
            ebcdic ++;
            continue;
        }
        if (t == 0x05)
        {
         /*TAB in ebcdic */
            ebcdic ++;
            continue;
        }
        if (t == 0x0A)
        {
            /*NL in ascii*/
            ascii ++;
            continue;
        }
        if (t == 0x09)
        {
            /*TAB in ascii*/
            ascii ++;
            continue;
        }
        if (t < 0x20)
        {
            /*expect binary */
            return ccsid;
        }
        if ((t > 0x1F) && (t < 0x7F))
        {
            /*interval ASCII*/
            ascii++;
        }
        /**interval ebcdic*/
        if (t == 0x40)
        {
            ebcdic ++;
            continue;
        }
        if (t == 0xAD)
        {
            ebcdic ++;
            continue;
        }
        if (t == 0xBD)
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0x4A) && (t < 0x51))
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0x59) && (t < 0x62))
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0x69) && (t < 0x70))
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0x78) && (t < 0x80))
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0x80) && (t < 0x8C))
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0x90) && (t < 0x9A))
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0xA0) && (t < 0xAA))
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0xBF) && (t < 0xCA))
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0xCF) && (t < 0xDA))
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0xDF) && (t < 0xEA))
        {
            ebcdic ++;
            continue;
        }
        if ((t > 0xEF) && (t < 0xFA))
        {
            ebcdic ++;
            continue;
        }
    }
    ascii = percent(amount, ascii);
    ebcdic = percent(amount, ebcdic);
    if ((ascii > 70) && (ebcdic > 70))
    {
        /*expect binary*/
        return ccsid;
    }
    /*more 70%*/
    if ((ascii > 70) && (ebcdic < 50))
    {
        ccsid = CCSID_ISO8859_1;
        return ccsid;
    }
    if ((ebcdic > 70) && (ascii < 50))
    {
        ccsid = CCSID_IBM_1047;
        return ccsid;
    }
    /*expect binary*/
    return ccsid;
}

#ifdef __NATIVE_ASCII_F
int set_tag_fd_text(int fd)     { return set_tag_fd_text2(fd, 1); }
#else
int set_tag_fd_text_e(int fd)   { return set_tag_fd_text2_e(fd, 1); }
#endif

#ifdef __NATIVE_ASCII_F
int set_tag_fd_text2(int fd, int filetagchg)
#else
int set_tag_fd_text2_e(int fd, int filetagchg)
#endif
{
    int rc;
    __ccsid_t ccsid_rc;
    struct stat st;
    struct file_tag * tag = &st.st_tag;

    rc = fstat(fd, &st);
    if (rc == -1)
    {
        return rc;
    }

    /*tag set OK*/
    if (tag->ft_ccsid != FT_UNTAGGED)
    {
        return 0;
    }
    /*block special files*/
    if (S_ISBLK(st.st_mode))
    {
        return 0;
    }
    /*character special files*/
    if (S_ISCHR(st.st_mode))
    {
        return 0;
    }
    /*directories*/
    if (S_ISDIR(st.st_mode))
    {
        return 0;
    }
    /*external links*/
    if (S_ISEXTL(st.st_mode, st.st_genvalue))
    {
        return 0;
    }
    /*symbolic links*/
    if (S_ISLNK(st.st_mode))
    {
        return 0;
    }

    check_env_ccsid();

    if (S_ISFIFO(st.st_mode))
    {
        if (filetagchg)
        {
            rc = change_attr_fd(fd, ccsid_pipe);
            if (rc != -1)
            {
                return rc;
            }
        }
        return control_attr_fd(fd, ccsid_pipe);
    }

    if (S_ISSOCK(st.st_mode))
    {
        if (filetagchg)
        {
            rc = change_attr_fd2(fd, ccsid_sock, filetagchg);
            if (rc != -1)
            {
                return rc;
            }
        }
        return control_attr_fd(fd, ccsid_sock);
    }

    if ((S_ISREG(st.st_mode)))
    {
        if (st.st_size == 0){
            /*suppose new file */
            if (filetagchg)
            {
                rc = change_attr_fd2(fd, ccsid_new, filetagchg);
                if (rc != -1)
                {
                    return rc;
                }
            }
            return control_attr_fd(fd, ccsid_new);
        }
    }

    /*try detect encoding*/
    printf("autodetecting encoding\n");
    ccsid_rc = autodetect_encoding(fd);
    printf("ccsid_rc: %d\n", ccsid_rc);
    if (ccsid_rc != FT_UNTAGGED)
    {
        ccsid_all = ccsid_rc;
    }
    printf("ccsid_all: %d\n", ccsid_all);
    /*set defualt attribute IBM-1047*/
    if (ccsid_all == FT_UNTAGGED)
    {
        printf("1\n");
        /*set attribute only stream*/
        return control_attr_fd(fd, CCSID_IBM_1047);
    }
    printf("2\n");
    if (filetagchg)
    {
        /*set attribute file*/
        rc = change_attr_fd2(fd, ccsid_all, filetagchg);
        if (rc != -1)
        {
            return rc;
        }
    }
    return control_attr_fd(fd, ccsid_all);
}

#ifdef __NATIVE_ASCII_F
int set_tag_fd_binary(int fd)
#else
int set_tag_fd_binary_e(int fd)
#endif
{
    int rc;
    struct stat st;
    struct file_tag * tag = &st.st_tag;

    rc = fstat(fd, &st);
    if (rc == -1)
    {
        return -rc;
    }

    /*tag set OK*/
    if (tag->ft_ccsid != FT_UNTAGGED)
    {
        return 0;
    }

    rc = change_attr_fd(fd, FT_BINARY);
    if (rc == -1)
    {
        return control_attr_fd(fd, FT_BINARY);
    }
    return rc;
}

#ifdef __NATIVE_ASCII_F
int set_tag_fd(int fd, char * name_ccsid)   { return set_tag_fd2(fd, name_ccsid, 1); }
#else
int set_tag_fd_e(int fd, char * name_ccsid) { return set_tag_fd2_e(fd, name_ccsid, 1); }
#endif

#ifdef __NATIVE_ASCII_F
int set_tag_fd2(int fd, char * name_ccsid, int filetagchg)
#else
int set_tag_fd2_e(int fd, char * name_ccsid, int filetagchg)
#endif
{
    int rc;
    __ccsid_t ccsid = query_ccsid(name_ccsid);

    rc = change_attr_fd2(fd, ccsid, filetagchg);
    if (rc == -1)
    {
        return control_attr_fd(fd, ccsid);
    }
    return rc;
}

#ifdef __NATIVE_ASCII_F
int copy_tag(int fdsrc, int fddst)
#else
int copy_tag_e(int fdsrc, int fddst)
#endif
{
    int rc;
    struct f_cnvrt cvt = { .pccsid = 0, .fccsid = 0, .cvtcmd = 0 };
    __ccsid_t ccsid;
    query_attr(fdsrc, &cvt);
    ccsid = cvt.fccsid;

    rc = change_attr_fd(fddst, ccsid);
    if (rc == -1)
    {
        return control_attr_fd(fddst, ccsid);
    }
    return rc;
#if 0
    attrib_t attrs;
    struct stat st;
    struct file_tag * tag = &st.st_tag;

    memset(&attrs, 0, sizeof(attrs));

    fstat(fdsrc, &st);

    attrs.att_filetagchg = 1;
    attrs.att_filetag.ft_txtflag = tag->ft_txtflag;
    attrs.att_filetag.ft_ccsid = tag->ft_ccsid;
    attrs.att_filetag.ft_deferred = tag->ft_deferred;

    return __fchattr(fddst, &attrs, sizeof(attrs));
#endif
}

/*****************************************************************************/

#ifdef __NATIVE_ASCII_F
int change_attr_name(char * name, __ccsid_t ccsid)
#else
int change_attr_name_e(char * name, __ccsid_t ccsid)
#endif
{
    attrib_t attrs;
    memset(&attrs, 0, sizeof(attrs));
    attrs.att_filetagchg = 1;
    if (ccsid == FT_BINARY)
        attrs.att_filetag.ft_txtflag = 0;
    else
        attrs.att_filetag.ft_txtflag = 1;
    attrs.att_filetag.ft_ccsid = ccsid;
    return __chattr(name, &attrs, sizeof(attrs));
}

#ifdef __NATIVE_ASCII_F
int set_tag_name_text(char * name)
#else
int set_tag_name_text_e(char * name)
#endif
{
    int rc;
    struct stat st;
    struct file_tag * tag = &st.st_tag;
    mode_t * st_mode = &st.st_mode;
    off_t * st_size = &st.st_size;

    rc = stat(name, &st);
    if (rc == -1)
    {
        return rc;
    }

    /*tag set OK*/
    if (tag->ft_ccsid != FT_UNTAGGED)
    {
        return 0;
    }

    check_env_ccsid();

    if ((S_ISREG(st.st_mode)))
    {
        if ( st.st_size == 0)
        {
            /*suppose new file */
            return change_attr_name(name, ccsid_new);
        }
    }

    return change_attr_name(name, ccsid_all);
}

#ifdef __NATIVE_ASCII_F
int set_tag_name_binary(char * name)
#else
int set_tag_name_binary_e(char * name)
#endif
{
    int rc;
    struct stat st;
    struct file_tag * tag = &st.st_tag;

    rc = stat(name, &st);
    if (rc == -1)
    {
        return -rc;
    }

    /*tag set OK*/
    if (tag->ft_ccsid != FT_UNTAGGED)
    {
        return 0;
    }

    return change_attr_name(name, FT_BINARY);
}

#ifdef __NATIVE_ASCII_F
int set_tag_name(char * name, char * name_ccsid)
#else
int set_tag_name_e(char * name, char * name_ccsid)
#endif
{
    int rc;
    __ccsid_t ccsid = query_ccsid(name_ccsid);
    return change_attr_name(name, ccsid);
}
/*****************************************************************************/

/*
© 2017-2018 Rocket Software, Inc. or its affiliates. All Rights Reserved.
ROCKET SOFTWARE, INC.
*/

