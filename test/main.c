#pragma comment(copyright, " © 2018 Rocket Software, Inc. or its affiliates. All Rights Reserved. ")

#pragma runopts(FILETAG(AUTOCVT,AUTOTAG),POSIX(ON))

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <libtag.h>


#define SIZE_ARRAY    0x10
char name_new[] = "test.tag.txt";

int main (int argc,char * argv[])
{
	char * name = NULL;
	int fd = 0;
	char array[SIZE_ARRAY] = {0};
	int rc;
	init_attr_stdio();	
	printf("Begin testing : libtag-%s\n",tag_version());

	if(argc != 2){
		printf("Using test program : ./autodetect <name_file>\n");
		return 0;
	}
	name = argv[1];
	fd = open(name,O_RDONLY);
	if(fd == -1){
		printf("Can not open file \"%s\" : %s",name,strerror(errno));
		return -1;
	}
	set_tag_fd_text(fd);
		
	rc = read(fd,array,SIZE_ARRAY);
	if(rc == -1){
		printf("Can not read file \"%s\" : %s",name,strerror(errno));
		return -2;
	}

	printf("content :> %s\n",array);

	close(fd);
	printf("Create new file\n");
	unlink(name_new);

	fd = open(name_new,O_CREAT|O_RDWR,S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH);
	if(fd == -1){
		printf("Can not creat file : %\"%s\" : %s\n",name_new,strerror(errno));
		return -2;
	}
	set_tag_fd_text(fd);
	close(fd);
	printf("Done\n"); 
	return 0;
}

/*****************************************************************************/

/*
© 2018 Rocket Software, Inc. or its affiliates. All Rights Reserved.
ROCKET SOFTWARE, INC.
*/

