#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
	char infile[1024];
	FILE *fpout=stdout;
	if(argc < 2) {
		fprintf(stderr,"Purpose: infinitepipe continuously opens and reads from the source pipe,\n");
		fprintf(stderr,"         closing and reopening it whenever EOF or error occurs.  As it\n");
		fprintf(stderr,"         reads, it copies the data to stdout, NOT closing stdout when\n");
		fprintf(stderr,"         it closes the source pipe.  Optionally, a destination pipe or\n");
		fprintf(stderr,"         file may be specified as the second argument.\n");
		fprintf(stderr,"Usage: %s [source fifo] {[target fifo/file]}\n",argv[0]);
		exit(-1);
	}
	strncpy(infile,argv[1],sizeof(infile)-1);
	if(argc > 2) {
		fpout=fopen(argv[2],"wb");
		if(!fpout) { fprintf(stderr,"Error opening output '%s': %s\n",argv[2],strerror(errno)); exit(1); }
	}
	while(true) {
		FILE *fpin=fopen(infile,"rb");
		size_t olen;
		while(!feof(fpin) && !ferror(fpin)) {
			unsigned char buf[4000];
			size_t ilen=fread(buf, sizeof(buf), 1, fpin);
			if(ilen<=0) { break; }
			size_t rem=ilen,ofs=0;
			do {
				olen=fwrite(&buf[ofs], rem, 1, fpout); fflush(fpout);
				if(olen<rem || ferror(fpout)) {
					fprintf(stderr,"Short write: %ld < %ld\n",olen,rem);
					clearerr(fpout);
				}
				rem-=olen; ofs+=olen;
			} while(rem>0);
		}
		fclose(fpin);
	}	
}