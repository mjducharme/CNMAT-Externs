/* Copyright (c) 1990-2006.  The Regents of the University of California (Regents).
All Rights Reserved.

Permission to use, copy, modify, and distribute this software and its
documentation for educational, research, and not-for-profit purposes, without
fee and without a signed licensing agreement, is hereby granted, provided that
the above copyright notice, this paragraph and the following two paragraphs
appear in all copies, modifications, and distributions.  Contact The Office of
Technology Licensing, UC Berkeley, 2150 Shattuck Avenue, Suite 510, Berkeley,
CA 94720-1620, (510) 643-7201, for commercial licensing opportunities.

Written by Mike Lee, The Center for New Music and Audio Technologies,
University of California, Berkeley.

     IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
     SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
     ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
     REGENTS HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

     REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
     LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
     FOR A PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING
     DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS".
     REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
     ENHANCEMENTS, OR MODIFICATIONS.
*/

#define	SCOPE	extern
#include "NNInclude.h"

static char *PtoCstr(unsigned char* src);


#ifndef MAXObject
/* ------------------------- nn_error_stats ------------------------ */

void	*nn_error_stats(x,set,index)
NeuralNetPtr	x;
patternSetPtr	set;	
int				index;
{
	int	i,j;
	FILE	*file_ptr;
	char	fileName[256],prefix[256];

	strcpy(prefix,set->fileName);
#ifdef NEVER
	PtoCstr((unsigned char*)prefix);
#endif
	sprintf(fileName,"%s.err",prefix);
		
	file_ptr = fopen(fileName,"a+");
	if (!file_ptr){
		post("Cannot open %s.",fileName);
		return(0);
	}
		
	fprintf(file_ptr,"epochs: %d\n",index);
	
	for (i=0;i<set->patterns;i++) {
		for (j=0;j<x->nn_net->numOUT;j++) 
			fprintf(file_ptr,"%lf\t",*((set->outz)+i*x->nn_net->numOUT+j));
		fprintf(file_ptr,"\t%lf\n",*((set->errz)+i));
	}
	
	fprintf(file_ptr,"pss: %lf\n",set->pss);
	fprintf(file_ptr,"tss: %lf\n",set->tss);
	fprintf(file_ptr,"maxError: %lf\n",set->maxError);
	
	fclose(file_ptr);
}
#else
/* ------------------------- nn_error_stats ------------------------ */
   
void	*nn_error_stats(x,set,index)
NeuralNetPtr	x;
patternSetPtr	set;	
int				index;
{
	short	i,j,file;
	long	count;
	char	buf[512];
	char	fileName[256],prefix[256];
	short result;
	FILE_REF fileref;

	strcpy(prefix,set->fileName);
	PtoCstr((unsigned char*)prefix);
	sprintf(fileName, "%s.err", prefix);
	
	result = path_createfile(fileName, path_getdefault(), 'TEXT', &fileref);

	if (result) {
		error("Error %d creating xValidation file %s.err", prefix);
		return;
	}
	
	post("xValidation file %s.err created" ,prefix);

	/* On July 1, 2003, A max "FILE_REF" is precisely the short that should be passed to 
	   FSWrite, etc. */
	file = fileref;

	sprintf(buf,"epochs: %d\r",index);
	count = strlen(buf);
	FSWrite(file,&count,buf);
	
	for (i=0;i<set->patterns;i++) {
		for (j=0;j<x->nn_net->numOUT;j++) {
			sprintf(buf,"%lf\t",*((set->outz)+i*x->nn_net->numOUT+j));
			count = strlen(buf);
			FSWrite(file,&count,buf);
		}
		sprintf(buf,"\t%lf\r",*((set->errz)+i));
		count = strlen(buf);
		FSWrite(file,&count,buf);
	}
	
	sprintf(buf,"pss: %lf\r",set->pss);
	count = strlen(buf);
	FSWrite(file,&count,buf);
	sprintf(buf,"tss: %lf\r",set->tss);
	count = strlen(buf);
	FSWrite(file,&count,buf);
	sprintf(buf,"maxError: %lf\r",set->maxError);
	count = strlen(buf);
	FSWrite(file,&count,buf);
	
	FSClose(file);
}
#endif

/* ------------------------- nn_xValidate ------------------------ */

double	nn_xValidate(x,set,index)
NeuralNetPtr	x;
patternSetPtr	set;
int				index;
{
	int i;
	double	sum;
	double	maxError;

	sum = 0.0;
	if (set->patterns) {
		maxError = 0.0;
		for (i=0;i<set->patterns;i++) {
			bpLearn(x->nn_net,(set->input+i*x->nn_net->numIN),
					(set->target+i*x->nn_net->numOUT),
					(set->target+(i-1)*x->nn_net->numOUT),
					(set->outz+i*x->nn_net->numOUT),
					(set->errz+i),x->nn_error_tolerance,false);

			sum += *(set->errz+i);
			maxError = MAX(maxError,*(set->errz+i));
		}
			
		set->pss = sum/set->patterns;
		set->tss = sum;
		set->maxError = maxError;
		
		post("PSS: %lf",sum/set->patterns);
		post("TSS: %lf",sum);
		post("maxError: %lf",maxError);
		nn_error_stats(x,set,index);
	}
	return sum;
}

