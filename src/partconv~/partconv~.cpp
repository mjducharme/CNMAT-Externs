/*
 Copyright (c) 2008.  The Regents of the University of California (Regents).
 All Rights Reserved.
 
 Permission to use, copy, modify, distribute, and distribute modified versions
 of this software and its documentation without fee and without a signed
 licensing agreement, is hereby granted, provided that the above copyright
 notice, this paragraph and the following two paragraphs appear in all copies,
 modifications, and distributions.

 Written by Andy Schmeder <andy@cnmat.berkeley.edu>, The Center for New Music and Audio Technologies,
 University of California, Berkeley.
 
 IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
 SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
 OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
 BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
 HEREUNDER IS PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE
 MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 
 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 NAME: partconv~
 DESCRIPTION: Non-uniform partitioned FFT convolution, multiple in/out and parallel multithreaded
 AUTHORS: Andy Schmeder, Eric Battenberg, Rama Gottfried
 COPYRIGHT_YEARS: 2011-14
 VERSION 0.1: Initial port of partconv code
 VERSION 0.2: Ported to max 64 bit, and to pd (currently only 32bit)
 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 
 notes: need to seriously think about how we're doing buffer managment here, Pd has only 1D arrays for tables, and Max has interleaved buffers when multichannel, but a limit on how many channels you can use -- Max has polybuffer to facilitate a large number of buffers, and we could script something like that in Pd (or make a new external). PartConv expects concatenated buffers, so eventually I think the best thing to do will be to combine approaches around the polybuffer style. However, the question at some point is where to make the change, and how deep? We might want to tweak how Eric's PartConv routine handles buffers (see partconv.c).
 
 */

// stdlib
#include <math.h>

#ifdef CNMAT_PD_VERSION
#include "unistd.h"
#include "stdlib.h"
#include "m_pd.h"
#include "max2pd.h"
#else
// maxmsp
#include "ext.h"
#include "ext_obex.h"
#include "ext_obex_util.h"
//#include "ext_critical.h"
#include "ext_atomic.h"
#include "z_dsp.h"
#include "buffer.h"
#endif

// cnmat versioning
//#include "version.h"
//#include "version.c"

// fftw 3
#include "fftw3.h"

#include "buffers.h"
#include "partconv.h"

typedef struct _partconv
{
    
    // header
	t_pxobject x_obj;
    
    // buffer
    t_symbol* buffer;
#ifdef CNMAT_PD_VERSION
    float *ir_vec;
    int ir_size;
    t_float x_f;
#else
    t_buffer_ref *l_buffer_reference;
#endif
    // number of signals in
    long n;
    
    // number of signals out
    long m;
    
    // number of filters
    long k;
    
    // length of filters in bank (must all be same length)
    long v;

    // v internal
    int v0;
    
    // planing mode
    int plan;

    // max num of threads per level
    long max_threads_per_level;
    
    // max num of threads at level 0
    int max_threads_per_level0;
        
    // wisdom file
    t_symbol* wisdom;

    int scheme_32[256];
    int nparts_32;
    int scheme_64[256];
    int nparts_64;
    int scheme_128[256];
    int nparts_128;
    int scheme_256[256];
    int nparts_256;
    int scheme_512[256];
    int nparts_512;
    int scheme_1024[256];
    int nparts_1024;
    int scheme_2048[256];
    int nparts_2048;
    int scheme_4096[256];
    int nparts_4096;
    
    // dsp state, buffers
    t_int** w;
    float** input;
    float** output;
    
    PartConvMax *pc;
    
} t_partconv;

static t_class *partconv_class;

// symbols
t_symbol *ps_buffer_tilde;


#ifdef CNMAT_PD_VERSION

t_int* partconv_perform(t_int *w) {
    
    t_int** wp;
    int i, j, s;
	t_partconv *x;
    
    wp = (t_int**)w;
    
    x = (t_partconv*)(wp[1]);
    s = (t_int)(wp[2]);
    
    if(s < 32 || s > 4096) {
        // not supported vector size
        return w + 3 + x->n + x->m;
    }
    
    for(i = 0; i < x->n; i++) {
        x->input[i] = (float*)(wp[3 + i]);
    }
    
    for(i = 0; i < x->m; i++) {
        x->output[i] = (float*)(wp[3 + i + x->n]);
    }
    
    if(x->pc != NULL) {
        x->pc->run(x->output, x->input);
    } else {
        // pass-thru outputs all zeros
        for(i = 0; i < x->m; i++) {
            for(j = 0; j < s; j++) {
                x->output[i][j] = 0.f;
            }
        }
    }
    
    return w + 3 + x->n + x->m;
    
}

// PD dsp setup
void partconv_dsp(t_partconv *x, t_signal **sp, short *connect) {
    
    int i;
    
    t_garray *ir_array;
    t_word *ir_data;
    int arraysize;
    
    int bstride;
    
    int *nparts = NULL;
    int *scheme = NULL;
    
    int fs;
    int bs;
    
    FILE* fp;
    
    //post("partconv~.dsp: n=%d, m=%d, k=%d, v=%d", x->n, x->m, x->k, x->v);
    
    if(sp[0]->s_n < 32) {
        object_error((t_object*)x, "partconv~: vector size less than 32 is not supported");
    }
    
    if(sp[0]->s_n > 4096) {
        object_error((t_object*)x, "partconv~: vector size greater than 4096 is not supported");
    }
    
    // setup args
    x->w[0] = (t_int*)x;
    x->w[1] = (t_int*)(sp[0]->s_n);
    
    for(i = 0; i < (x->n + x->m); i++) {
        x->w[i+2] = (t_int*)(sp[i]->s_vec);
    }
    
    // @todo check for buffer validity
    
    float *bdata = NULL;
    bstride = 0;
    
    if(x->buffer == NULL) {
        object_error((t_object*)x, "partconv~: no buffer defined");
    } else {
        
        ir_array = (t_garray *)pd_findbyclass(x->buffer, garray_class);
        if(!ir_array)
        {
            error("partconv~: could not find array name");
            return;
        }
        
        if(!garray_getfloatwords(ir_array, &arraysize, &ir_data))
        {
            error("partconv~: could not load array");
            bdata = NULL;
        }
        
        if(arraysize)
        {
        
            if(x->ir_vec == NULL)
                x->ir_vec = (float *)getbytes(sizeof(float) * arraysize );
            else
            {
                x->ir_vec = (float *)resizebytes(x->ir_vec, sizeof(float) * x->ir_size, sizeof(float) * arraysize);
            }
            x->ir_size = arraysize;
            
            for(i=0; i<arraysize; i++)
            {
                x->ir_vec[i] = ir_data[i].w_float;
            }

            bdata = x->ir_vec;
            bstride = 1;
            
            // auto-guess the number of samples
            if(x->v == 0) {
                if((arraysize % x->k) != 0) {
                    object_error((t_object*)x, "partconv~: k does not divide into buffer length; could not automatically determine v");
                    bdata = NULL;
                } else {
                    x->v0 = arraysize / x->k;
                }
            } else {
                x->v0 = x->v;
            }
            
            
            if(arraysize < (x->k * x->v0)) {
                object_error((t_object*)x, "partconv~: frames in buffer is less than k*v (b: %u, k: %u, v: %u",arraysize,x->k,x->v0);
                bdata = NULL;
            }
        } else {
            object_error((t_object*)x, "partconv~: invalid buffer");
            bdata = NULL;
        }
    }

    fs = sp[0]->s_sr;
    bs = sp[0]->s_n;
    
    switch (bs) {
        case 32:
            nparts = &(x->nparts_32);
            scheme = &(x->scheme_32[0]);
            break;
        case 64:
            nparts = &(x->nparts_64);
            scheme = &(x->scheme_64[0]);
            break;
        case 128:
            nparts = &(x->nparts_128);
            scheme = &(x->scheme_128[0]);
            break;
        case 256:
            nparts = &(x->nparts_256);
            scheme = &(x->scheme_256[0]);
            break;
        case 512:
            nparts = &(x->nparts_512);
            scheme = &(x->scheme_512[0]);
            break;
        case 1024:
            nparts = &(x->nparts_1024);
            scheme = &(x->scheme_1024[0]);
            break;
        case 2048:
            nparts = &(x->nparts_2048);
            scheme = &(x->scheme_2048[0]);
            break;
        case 4096:
            nparts = &(x->nparts_4096);
            scheme = &(x->scheme_4096[0]);
            break;
    }
    
    // cleanup if already running
    if(x->pc != NULL) {
        x->pc->cleanup();
        delete x->pc;
        x->pc = NULL;
    }
    
    if(!
       (((x->n == x->m) && (x->n == x->k)) ||
        ((x->n == x->m) && (x->k == 1)) ||
        (x->m == x->n * x->k)
        ))
    {
        object_error((t_object*)x, "partconv~: invalid channel configuration n=%d, m=%d, k=%d", x->n, x->m, x->k);
    } else {
        
        // check wisdom file...
        if(x->wisdom != NULL && strlen(x->wisdom->s_name)) {
            if(access(x->wisdom->s_name, F_OK) < 0) {
                if(x->plan == 2) {
                    post("partconv~: creating new wisdom file in patient mode; be patient now!");
                }
                else {
                    post("partconv~: creating new wisdom file");
                }
                fp = fopen(x->wisdom->s_name, "w+");
                if(! fp) {
                    object_error((t_object*)x, "partconv~: error creating wisdom file");
                    bdata = NULL;
                } else {
                    fclose(fp);
                    unlink(x->wisdom->s_name);
                }
            } else if(access(x->wisdom->s_name, R_OK) < 0) {
                object_error((t_object*)x, "partconv~: error reading wisdom file");
                bdata = NULL;
            }
        } else {
            object_error((t_object*)x, "partconv~: wisdom file is not configured");
            bdata = NULL;
        }
        
        if(bdata != NULL && sp[0]->s_sr != 0) {
            
            // allocate new partconv with scheme
            x->pc = new PartConvMax();
            //post("partconv~: setup(FS=%d, blocksize=%d, n=%d, m=%d, k=%d, v=%d, stride=%d, scheme=%d, levels=%d, plan=%d, wisdom=%s, max_per_level=%d, max_level0=%d)",
            //      fs, bs, x->n, x->m, x->k, x->v, bstride, scheme, *nparts, x->plan, x->wisdom->s_name, x->max_threads_per_level, x->max_threads_per_level0);
            if(x->pc->setup(sp[0]->s_sr, x->n, x->m, x->k, bdata, x->v0, bstride, scheme, *nparts, x->plan, x->wisdom->s_name, x->max_threads_per_level, x->max_threads_per_level0) != 0) {
                object_error((t_object*)x, "partconv~: setup error detected");
                x->pc = NULL;
            }
        } else {
            if(bdata == NULL) {
                object_error((t_object*)x, "partconv~: buffer is invalid or not defined");
            } else {
                object_error((t_object*)x, "partconv~: sample rate is not set");
            }
        }
    }
	dsp_addv(partconv_perform, 2 + x->n + x->m, (t_int *)(x->w));
}
#else

// msp arcana to extract t_buffer* from a t_symbol*
t_buffer* _sym_to_buffer(t_symbol* s) {
    
    t_buffer *b;
    if ((b = (t_buffer *)(s->s_thing)) && ob_sym(b) == ps_buffer_tilde) {
		return b;
    } else {
        return 0;
    }
    
}


void partconv_perform64(t_partconv *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    
    long i, j, s;
	//t_partconv *x;
    
    //   wp = (t_int**)w;
    
    //    x = (t_partconv *)(wp[1]);
    s = sampleframes;//(t_int)(wp[2]);
    
    if(s < 32 || s > 4096) {
        // not supported vector size
        return;
    }
    
    
    for (j = 0; j < sampleframes; j++) {
        
        for(i = 0; i < x->n; i++)
            x->input[i][j] = (float)ins[i][j];//(float *)(wp[3 + i]);
    }
    
    if(x->pc != NULL) {
        x->pc->run(x->output, x->input);
    } else {
        // pass-thru outputs all zeros
        for(i = 0; i < x->m; i++) {
            for(j = 0; j < s; j++) {
                x->output[i][j] = 0.;
            }
        }
    }
    
    for (j = 0; j < sampleframes; j++){
        for(i = 0; i < x->m; i++){
            outs[i][j] = (double)x->output[i][j];
        }
    }
    
}

void partconv_dsp64(t_partconv *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    /*
     x->v = sys_getblksize();
     
     if(x->v != x->framesize / 2) {
     object_post((t_object *)x, "firbank~: vector size (%d) is not equal to framesize / 2 (%d)", x->v, x->framesize / 2);
     }
     
     
     if(count[0]){
     object_method(dsp64, gensym("dsp_add64"), x, firbank_perform64, 0, NULL);
     }
     */
    
    //// ***********************************
    int i;
    
    
    float* bdata;
    int bstride;
    
    int *nparts = NULL;
    int *scheme = NULL;
    
    //    int fs;
    //    int bs;
    
    FILE* fp;
    
    //post("partconv~.dsp: n=%d, m=%d, k=%d, v=%d", x->n, x->m, x->k, x->v);
    int bs = sys_getblksize();
    int fs = (int)samplerate;
    
    if(bs < 32) {
        object_error((t_object*)x, "partconv~: vector size less than 32 is not supported");
    }
    
    if(bs > 4096) {
        object_error((t_object*)x, "partconv~: vector size greater than 4096 is not supported");
    }
    
    // setup args
    //    x->w[0] = (t_int*)x;
    //    x->w[1] = (t_int*)(sp[0]->s_n);
    /*
     for(i = 0; i < (x->n + x->m); i++) {
     x->w[i+2] = (t_int*)(sp[i]->s_vec);
     }
     */
    // @todo check for buffer validity
    
    bdata = NULL;
    bstride = 0;
    
    if(x->buffer == NULL) {
        object_error((t_object*)x, "partconv~: no buffer defined");
    } else {
        
        t_buffer *b = _sym_to_buffer(x->buffer);
        
        if(b && (b->b_valid)) {
            bdata = b->b_samples;
            bstride = b->b_nchans;
            
            post("v = %d frames %d channels %d", x->v, b->b_frames, b->b_nchans);
            
            // auto-guess the number of samples
            if(x->v == 0) {
                if((b->b_frames % x->k) != 0) {
                    object_error((t_object*)x, "partconv~: k does not divide into buffer length; could not automatically determine v");
                    bdata = NULL;
                } else {
                    x->v0 = b->b_frames / x->k;
                    post("b_frames % k == 0 && x->v0 = %d", x->v0);
                }
            } else {
                x->v0 = x->v;
            }
            
            
            if(b->b_frames < (x->k * x->v0)) {
                object_error((t_object*)x, "partconv~: frames in buffer is less than k*v (b: %u, k: %u, v: %u",b->b_frames,x->k,x->v0);
                bdata = NULL;
            }
        } else {
            object_error((t_object*)x, "partconv~: invalid buffer");
            bdata = NULL;
        }
    }
    
    
    //    bs = sp[0]->s_n;
    
    switch (bs) {
        case 32:
            nparts = &(x->nparts_32);
            scheme = &(x->scheme_32[0]);
            break;
        case 64:
            nparts = &(x->nparts_64);
            scheme = &(x->scheme_64[0]);
            break;
        case 128:
            nparts = &(x->nparts_128);
            scheme = &(x->scheme_128[0]);
            break;
        case 256:
            nparts = &(x->nparts_256);
            scheme = &(x->scheme_256[0]);
            break;
        case 512:
            nparts = &(x->nparts_512);
            scheme = &(x->scheme_512[0]);
            break;
        case 1024:
            nparts = &(x->nparts_1024);
            scheme = &(x->scheme_1024[0]);
            break;
        case 2048:
            nparts = &(x->nparts_2048);
            scheme = &(x->scheme_2048[0]);
            break;
        case 4096:
            nparts = &(x->nparts_4096);
            scheme = &(x->scheme_4096[0]);
            break;
    }
    
    // cleanup if already running
    if(x->pc != NULL) {
        x->pc->cleanup();
        delete x->pc;
        x->pc = NULL;
    }
    
    if(!
       (((x->n == x->m) && (x->n == x->k)) ||
        ((x->n == x->m) && (x->k == 1)) ||
        (x->m == x->n * x->k)
        ))
    {
        object_error((t_object*)x, "partconv~: invalid channel configuration n=%d, m=%d, k=%d", x->n, x->m, x->k);
    } else {
        
        // check wisdom file...
        if(x->wisdom != NULL && strlen(x->wisdom->s_name)) {
            if(access(x->wisdom->s_name, F_OK) < 0) {
                if(x->plan == 2) {
                    post("partconv~: creating new wisdom file in patient mode; be patient now!");
                }
                else {
                    post("partconv~: creating new wisdom file");
                }
                fp = fopen(x->wisdom->s_name, "w+");
                if(! fp) {
                    object_error((t_object*)x, "partconv~: error creating wisdom file");
                    bdata = NULL;
                } else {
                    fclose(fp);
                    unlink(x->wisdom->s_name);
                }
            } else if(access(x->wisdom->s_name, R_OK) < 0) {
                object_error((t_object*)x, "partconv~: error reading wisdom file");
                bdata = NULL;
            }
        } else {
            object_error((t_object*)x, "partconv~: wisdom file is not configured");
            bdata = NULL;
        }
        
        if(bdata != NULL && fs != 0) {
            
            // allocate new partconv with scheme
            x->pc = new PartConvMax();
            post("partconv~: setup(FS=%d, blocksize=%d, n=%d, m=%d, k=%d, v0=%d, stride=%d, scheme=%d, levels=%d, plan=%d, wisdom=%s, max_per_level=%d, max_level0=%d)",
                 fs, bs, x->n, x->m, x->k, x->v0, bstride, *scheme, *nparts, x->plan, x->wisdom->s_name, x->max_threads_per_level, x->max_threads_per_level0);
            if(x->pc->setup(fs, x->n, x->m, x->k, bdata, x->v0, bstride, scheme, *nparts, x->plan, x->wisdom->s_name, x->max_threads_per_level, x->max_threads_per_level0) != 0) {
                object_error((t_object*)x, "partconv~: setup error detected");
                x->pc = NULL;
            }
        } else {
            if(bdata == NULL) {
                object_error((t_object*)x, "partconv~: buffer is invalid or not defined");
            } else {
                object_error((t_object*)x, "partconv~: sample rate is not set");
            }
        }
    }
    
    if(count[0]){
		object_method(dsp64, gensym("dsp_add64"), x, partconv_perform64, 0, NULL);
	}
    
    
}

#endif



#ifdef CNMAT_PD_VERSION

t_max_err partconv_scheme_set(t_partconv *x, void *attr, long argc, t_atom *argv)
{
    post("partconv~: manual scheme setup not ported to pd yet");
/*
    int i;
    int part1;
    int partn;
    int* nparts = NULL;
    int* scheme = NULL;
    
    // make sure the length of the list is ok
    if (argc >= 1 && argc <= 255) {
        // ok
    } else {
        object_error((t_object*)x, "partconv~: partitioning scheme is too long, or too short");
        return MAX_ERR_GENERIC;
    }
    
    // check that all elements are integers
    for(i = 0; i < argc; i++) {
        if(argv[i].a_type != A_LONG) {
            object_error((t_object*)x, "partconv~: partitioning scheme must be a list of integers", i);
            return MAX_ERR_GENERIC;
        }
    }
    
    partn = 0;
    
    for(i = 0; i < argc; i++) {
        if(argv[i].a_w.w_long <= partn) {
            object_error((t_object*)x, "partconv~: partitioning scheme must be monotonically increasing");
            return MAX_ERR_GENERIC;
        } else {
            partn = argv[i].a_w.w_long;
        }
    }
    
    for(i = 0; i < argc; i++) {
        partn = argv[i].a_w.w_long;
        
        if (((partn | (partn - 1)) + 1) / 2 != partn) {
            object_error((t_object*)x, "partconv~: %d at position %d is not a power of two", partn, i);
            return MAX_ERR_GENERIC;
        }
    }
    
    // check that the first element is equal to the corresponding scheme start-vector size
    
    if (object_attr_get(x, gensym("scheme_32")) == attr) {
        part1 = 32;
        nparts = &(x->nparts_32);
        scheme = &(x->scheme_32[0]);
    }
    else if (object_attr_get(x, gensym("scheme_64")) == attr) {
        part1 = 64;
        nparts = &(x->nparts_64);
        scheme = &(x->scheme_64[0]);
    }
    else if (object_attr_get(x, gensym("scheme_128")) == attr) {
        part1 = 128;
        nparts = &(x->nparts_128);
        scheme = &(x->scheme_128[0]);
    }
    else if (object_attr_get(x, gensym("scheme_256")) == attr) {
        part1 = 256;
        nparts = &(x->nparts_256);
        scheme = &(x->scheme_256[0]);
    }
    else if (object_attr_get(x, gensym("scheme_512")) == attr) {
        part1 = 512;
        nparts = &(x->nparts_512);
        scheme = &(x->scheme_512[0]);
    }
    else if (object_attr_get(x, gensym("scheme_1024")) == attr) {
        part1 = 1024;
        nparts = &(x->nparts_1024);
        scheme = &(x->scheme_1024[0]);
    }
    else if (object_attr_get(x, gensym("scheme_2048")) == attr) {
        part1 = 2048;
        nparts = &(x->nparts_2048);
        scheme = &(x->scheme_2048[0]);
    }
    else if (object_attr_get(x, gensym("scheme_4096")) == attr) {
        part1 = 4096;
        nparts = &(x->nparts_4096);
        scheme = &(x->scheme_4096[0]);
    }
    else {
        object_error((t_object*)x, "partconv~: unknown attribute");
        return MAX_ERR_GENERIC;
    }
    
    *nparts = argc;
    
    for(i = 0; i < argc; i++) {
        scheme[i] = argv[i].a_w.w_long;
    }
    
    for(i = argc; i < 256; i++) {
        scheme[i] = 0;
    }
 
    */
    // all okay
    return MAX_ERR_NONE;
    
}

/*
void partconv_buffer_set(t_partconv *x, t_symbol *s)
{
    //move set routine here from dsp function
    // although, I can see why andy keeps you from changing with the dsp on
}
*/
// free
void partconv_free(t_partconv *x) {
	
    
    // cleanup if already running
    if(x->pc != NULL) {
        x->pc->cleanup();
        delete x->pc;
        x->pc = NULL;
    }
    
    free(x->input);
    free(x->output);
    
    free(x->w);
    
    if(x->ir_vec)
        freebytes(x->ir_vec, x->ir_size);
    
}

/*
 class_dspinit(c);
 
 CLASS_ATTR_SYM(c, "buffer", 0, t_partconv, buffer);
 CLASS_ATTR_LABEL(c, "n", 0, "Impulse response buffer");
 //CLASS_ATTR_SAVE(c, "buffer", 0);
 
 CLASS_ATTR_SYM(c, "wisdom", 0, t_partconv, wisdom);
 CLASS_ATTR_LABEL(c, "wisdom", 0, "FFTW plan wisdom cache file");
 CLASS_ATTR_STYLE(c, "wisdom", 0, "file");
 //CLASS_ATTR_SAVE(c, "wisdom", 0);
 
 CLASS_ATTR_LONG(c, "plan", 0, t_partconv, plan);
 CLASS_ATTR_LABEL(c, "plan", 0, "FFTW plan mode");
 CLASS_ATTR_ENUMINDEX(c, "plan", 0, "estimate measure patient");
 //CLASS_ATTR_SAVE(c, "plan", 0);
 
 CLASS_ATTR_LONG(c, "max_threads_per_level", 0, t_partconv, max_threads_per_level);
 CLASS_ATTR_LABEL(c, "max_threads_per_level", 0, "Maximum number of threads per partition level");
 CLASS_ATTR_FILTER_MIN(c, "max_threads_per_level", 1);
 
 CLASS_ATTR_LONG(c, "max_threads_per_level0", 0, t_partconv, max_threads_per_level0);
 CLASS_ATTR_LABEL(c, "max_threads_per_level0", 0, "Maximum number of threads at first partition level");
 CLASS_ATTR_FILTER_MIN(c, "max_threads_per_level0", 0);
 
 CLASS_ATTR_LONG(c, "plan", 0, t_partconv, plan);
 CLASS_ATTR_LABEL(c, "plan", 0, "FFTW plan mode");
 CLASS_ATTR_ENUMINDEX(c, "plan", 0, "estimate measure patient");
 //CLASS_ATTR_SAVE(c, "plan", 0);
 
 CLASS_ATTR_LONG(c, "n", 0, t_partconv, n);
 CLASS_ATTR_FILTER_MIN(c, "n", 1);
 CLASS_ATTR_LABEL(c, "n", 0, "Number of inputs");
 
 CLASS_ATTR_LONG(c, "m", 0, t_partconv, m);
 CLASS_ATTR_FILTER_MIN(c, "m", 1);
 CLASS_ATTR_LABEL(c, "m", 0, "Number of outputs");
 
 CLASS_ATTR_LONG(c, "k", 0, t_partconv, k);
 CLASS_ATTR_FILTER_MIN(c, "k", 1);
 CLASS_ATTR_LABEL(c, "k", 0, "Number of impulse responses");
 
 CLASS_ATTR_LONG(c, "v", 0, t_partconv, v);
 CLASS_ATTR_FILTER_MIN(c, "v", 0);
 CLASS_ATTR_DEFAULT(c, "v", 0, 0);
 CLASS_ATTR_LABEL(c, "v", 0, "Impulse response length, 0 = automatic");
 
 CLASS_ATTR_LONG_VARSIZE(c, "scheme_32", 0, t_partconv, scheme_32, nparts_32, 256);
 CLASS_ATTR_ACCESSORS(c, "scheme_32", NULL, partconv_scheme_set);
 CLASS_ATTR_LABEL(c, "scheme_32", 0, "Partioning scheme for 32 sample block");
 //CLASS_ATTR_SAVE(c, "scheme_32", 0);
 
 CLASS_ATTR_LONG_VARSIZE(c, "scheme_64", 0, t_partconv, scheme_64, nparts_64, 256);
 CLASS_ATTR_ACCESSORS(c, "scheme_64", NULL, partconv_scheme_set);
 CLASS_ATTR_LABEL(c, "scheme_64", 0, "Partioning scheme for 64 sample block");
 //CLASS_ATTR_SAVE(c, "scheme_64", 0);
 
 CLASS_ATTR_LONG_VARSIZE(c, "scheme_128", 0, t_partconv, scheme_128, nparts_128, 256);
 CLASS_ATTR_ACCESSORS(c, "scheme_128", NULL, partconv_scheme_set);
 CLASS_ATTR_LABEL(c, "scheme_128", 0, "Partioning scheme for 128 sample block");
 //CLASS_ATTR_SAVE(c, "scheme_128", 0);
 
 CLASS_ATTR_LONG_VARSIZE(c, "scheme_256", 0, t_partconv, scheme_256, nparts_256, 256);
 CLASS_ATTR_ACCESSORS(c, "scheme_256", NULL, partconv_scheme_set);
 CLASS_ATTR_LABEL(c, "scheme_256", 0, "Partioning scheme for 256 sample block");
 //CLASS_ATTR_SAVE(c, "scheme_256", 0);
 
 CLASS_ATTR_LONG_VARSIZE(c, "scheme_512", 0, t_partconv, scheme_512, nparts_512, 256);
 CLASS_ATTR_ACCESSORS(c, "scheme_512", NULL, partconv_scheme_set);
 CLASS_ATTR_LABEL(c, "scheme_512", 0, "Partioning scheme for 512 sample block");
 //CLASS_ATTR_SAVE(c, "scheme_512", 0);
 
 CLASS_ATTR_LONG_VARSIZE(c, "scheme_1024", 0, t_partconv, scheme_1024, nparts_1024, 256);
 CLASS_ATTR_ACCESSORS(c, "scheme_1024", NULL, partconv_scheme_set);
 CLASS_ATTR_LABEL(c, "scheme_1024", 0, "Partioning scheme for 1024 sample block");
 //CLASS_ATTR_SAVE(c, "scheme_1024", 0);
 
 CLASS_ATTR_LONG_VARSIZE(c, "scheme_2048", 0, t_partconv, scheme_2048, nparts_2048, 256);
 CLASS_ATTR_ACCESSORS(c, "scheme_2048", NULL, partconv_scheme_set);
 CLASS_ATTR_LABEL(c, "scheme_2048", 0, "Partioning scheme for 2048 sample block");
 //CLASS_ATTR_SAVE(c, "scheme_2048", 0);
 
 CLASS_ATTR_LONG_VARSIZE(c, "scheme_4096", 0, t_partconv, scheme_4096, nparts_4096, 256);
 CLASS_ATTR_ACCESSORS(c, "scheme_4096", NULL, partconv_scheme_set);
 CLASS_ATTR_LABEL(c, "scheme_4096", 0, "Partioning scheme for 4096 sample block");
 //CLASS_ATTR_SAVE(c, "scheme_4096", 0);
 */

void partconv_process_args(t_partconv *x, short argc, t_atom *argv)
{
    if(argc)
    {
        int i;
        for( i=0; i<argc; i++)
        {
            if(atom_gettype(argv+i) == A_SYMBOL)
            {
                char *s = atom_getsym(argv+i)->s_name;
                
                if(++i < argc)
                {
                    if(!strcmp(s, "@buffer"))
                    {
                        if(atom_gettype(argv+i)==A_SYM)
                            x->buffer = atom_getsym(argv+i);
                    }
                    else if (!strcmp(s, "@n"))
                    {
                        if(atom_gettype(argv+i)==A_FLOAT)
                            x->n = (int)atom_getfloat(argv+i);
                    }
                    else if (!strcmp(s, "@m"))
                    {
                        if(atom_gettype(argv+i)==A_FLOAT)
                            x->m = (int)atom_getfloat(argv+i);
                    }
                    else if (!strcmp(s, "@k"))
                    {
                        if(atom_gettype(argv+i)==A_FLOAT)
                            x->k = (int)atom_getfloat(argv+i);
                    }
                    else if (!strcmp(s, "@v"))
                    {
                        if(atom_gettype(argv+i)==A_FLOAT)
                            x->v = (int)atom_getfloat(argv+i);
                    }
                    else
                    {
                        post("unknown argument");
                    }
                }
            }
        }
    }
}

void *partconv_new(t_symbol *s, short argc, t_atom *argv) {
    
    int i;
    
    // scope vars
    t_partconv *x;
    
    // instantiate
    x = (t_partconv *)object_alloc(partconv_class);
    
    if(! x) {
        return NULL;
    }
    
    x->n = 1;
    x->m = 1;
    x->k = 1;
    x->v = 0;
    x->v0 = 0;
    
    // "measure" mode default
    x->plan = 1;
    x->wisdom = gensym("/tmp/partconv~.fftwf-wisdom");
    
    x->max_threads_per_level = 1;
    x->max_threads_per_level0 = 0;
    
    x->input = NULL;
    x->output = NULL;
    x->w = NULL;
    
    // default partitioning schemes
    // modified by eric 5-19-2011
    x->scheme_32[0] = 32;
    x->scheme_32[1] = 256;
    x->scheme_32[2] = 1024;
    x->scheme_32[3] = 4096;
    x->scheme_32[4] = 16384;
    x->scheme_32[5] = 65536;
    x->nparts_32 = 6;
    
    x->scheme_64[0] = 64;
    x->scheme_64[1] = 256;
    x->scheme_64[2] = 2048;
    x->scheme_64[3] = 8192;
    x->scheme_64[4] = 65536;
    x->nparts_64 = 5;
    
    x->scheme_128[0] = 128;
    x->scheme_128[1] = 512;
    x->scheme_128[2] = 4096;
    x->scheme_128[3] = 16384;
    x->scheme_128[4] = 65536;
    x->nparts_128 = 5;
    
    x->scheme_256[0] = 256;
    x->scheme_256[1] = 1024;
    x->scheme_256[2] = 4096;
    x->scheme_256[3] = 16384;
    x->scheme_256[4] = 65536;
    x->nparts_256 = 5;
    
    x->scheme_512[0] = 512;
    x->scheme_512[1] = 2048;
    x->scheme_512[2] = 8192;
    x->scheme_512[3] = 65536;
    x->nparts_512 = 4;
    
    x->scheme_1024[0] = 1024;
    x->scheme_1024[1] = 4096;
    x->scheme_1024[2] = 16384;
    x->scheme_1024[3] = 65536;
    x->nparts_1024 = 4;
    
    x->scheme_2048[0] = 2048;
    x->scheme_2048[1] = 8192;
    x->scheme_2048[2] = 65536;
    x->nparts_2048 = 3;
    
    x->scheme_4096[0] = 4096;
    x->scheme_4096[1] = 16384;
    x->scheme_4096[2] = 65536;
    x->nparts_4096 = 3;
    
    // pass attrs...
    partconv_process_args(x, argc, argv);
    
    x->w = (t_int**)malloc(sizeof(t_int*) * (x->n + x->m + 2));
    x->input = (float**)malloc(sizeof(float*) * x->n);
    x->output = (float**)malloc(sizeof(float*) * x->m);
    
    x->ir_vec = NULL;

    // allocate inlets
    for(i = 0; i < x->n-1; i++) {
        inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    }
    
    // allocate outlets
    for(i = 0; i < x->m; i++) {
        outlet_new((t_object *)x, &s_signal);	// type of outlet: "signal"
    }
    
    x->pc = NULL;
    
    post("partconv~.new: n=%d, m=%d, k=%d, v=%d", x->n, x->m, x->k, x->v);
    
    return (x);
    
}

extern "C" int partconv_tilde_setup(void) {
    
    t_class *c = class_new(gensym("partconv~"), (t_newmethod)partconv_new, (t_method)partconv_free, sizeof(t_partconv), 0L, A_GIMME, 0);
    
    class_addmethod(c, (t_method)partconv_dsp, gensym("dsp"), A_CANT, 0);
//    class_addmethod(c, (t_method)partconv_buffer_set, gensym("setIR"), A_SYM, 0);
    
    CLASS_MAINSIGNALIN(c, t_partconv, x_f);

	partconv_class = c;
    
    return 0;
    
}

#else

t_max_err partconv_scheme_set(t_partconv *x, void *attr, long argc, t_atom *argv)
{
    
    int i;
    int part1;
    int partn;
    int* nparts = NULL;
    int* scheme = NULL;
    
    // make sure the length of the list is ok
    if (argc >= 1 && argc <= 255) {
        // ok
    } else {
        object_error((t_object*)x, "partconv~: partitioning scheme is too long, or too short");
        return MAX_ERR_GENERIC;
    }
    
    // check that all elements are integers
    for(i = 0; i < argc; i++) {
        if(argv[i].a_type != A_LONG) {
            object_error((t_object*)x, "partconv~: partitioning scheme must be a list of integers", i);
            return MAX_ERR_GENERIC;
        }
    }
    
    partn = 0;
    
    for(i = 0; i < argc; i++) {
        if(argv[i].a_w.w_long <= partn) {
            object_error((t_object*)x, "partconv~: partitioning scheme must be monotonically increasing");
            return MAX_ERR_GENERIC;
        } else {
            partn = argv[i].a_w.w_long;
        }
    }
    
    for(i = 0; i < argc; i++) {
        partn = argv[i].a_w.w_long;
        
        if (((partn | (partn - 1)) + 1) / 2 != partn) {
            object_error((t_object*)x, "partconv~: %d at position %d is not a power of two", partn, i);
            return MAX_ERR_GENERIC;
        }
    }
    
    // check that the first element is equal to the corresponding scheme start-vector size
    
    if (object_attr_get(x, gensym("scheme_32")) == attr) {
        part1 = 32;
        nparts = &(x->nparts_32);
        scheme = &(x->scheme_32[0]);
    }
    else if (object_attr_get(x, gensym("scheme_64")) == attr) {
        part1 = 64;
        nparts = &(x->nparts_64);
        scheme = &(x->scheme_64[0]);
    }
    else if (object_attr_get(x, gensym("scheme_128")) == attr) {
        part1 = 128;
        nparts = &(x->nparts_128);
        scheme = &(x->scheme_128[0]);
    }
    else if (object_attr_get(x, gensym("scheme_256")) == attr) {
        part1 = 256;
        nparts = &(x->nparts_256);
        scheme = &(x->scheme_256[0]);
    }
    else if (object_attr_get(x, gensym("scheme_512")) == attr) {
        part1 = 512;
        nparts = &(x->nparts_512);
        scheme = &(x->scheme_512[0]);
    }
    else if (object_attr_get(x, gensym("scheme_1024")) == attr) {
        part1 = 1024;
        nparts = &(x->nparts_1024);
        scheme = &(x->scheme_1024[0]);
    }
    else if (object_attr_get(x, gensym("scheme_2048")) == attr) {
        part1 = 2048;
        nparts = &(x->nparts_2048);
        scheme = &(x->scheme_2048[0]);
    }
    else if (object_attr_get(x, gensym("scheme_4096")) == attr) {
        part1 = 4096;
        nparts = &(x->nparts_4096);
        scheme = &(x->scheme_4096[0]);
    }
    else {
        object_error((t_object*)x, "partconv~: unknown attribute");
        return MAX_ERR_GENERIC;
    }
    
    *nparts = argc;
    
    for(i = 0; i < argc; i++) {
        scheme[i] = argv[i].a_w.w_long;
    }
    
    for(i = argc; i < 256; i++) {
        scheme[i] = 0;
    }
    
    // all okay
    return MAX_ERR_NONE;
    
}

void partconv_assist(t_partconv *x, void *b, long io, long index, char *s) {
    
	switch(io){
        case 1:
            switch(index){
                case 0:
                    sprintf(s, "input %ld", index);
                    break;
            }
            break;
        case 2:
            switch(index){
                case 0:
                    sprintf(s, "output %ld", index);
                    break;
            }
            break;
	}
    
}

void partconv_buffer_set(t_partconv *x, t_symbol *s)
{
	if (!x->l_buffer_reference)
		x->l_buffer_reference = buffer_ref_new((t_object*)x, s);
	else
		buffer_ref_set(x->l_buffer_reference, s);
    
    
    t_buffer_obj *buf = buffer_ref_getobject(x->l_buffer_reference);
    
}

t_max_err partconv_buffer_notify(t_partconv *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	return buffer_ref_notify(x->l_buffer_reference, s, msg, sender, data);
}

// free
void partconv_free(t_partconv *x) {
	
    dsp_free(&(x->x_obj));

    // cleanup if already running
    if(x->pc != NULL) {
        x->pc->cleanup();
        delete x->pc;
        x->pc = NULL;
    }
    
    int i ;
    for( i = 0; i < x->n; i++)
    {
        if(x->input[i])
            free(x->input[i]);
    }
    for( i = 0; i < x->m; i++)
    {
        if(x->output[i])
            free(x->output[i]);
    }
    
    free(x->input);
    free(x->output);
    
    free(x->w);
    
    // @todo cleanup of partconv threads if they are still running
    
    object_free(x->l_buffer_reference);
    
}

// new
void *partconv_new(t_symbol *s, short argc, t_atom *argv) {
    
    int i;
    
    // scope vars
    t_partconv *x;
    
    // instantiate
    x = (t_partconv *)object_alloc(partconv_class);
    
    if(! x) {
        return NULL;
    }
    
    x->n = 1;
    x->m = 1;
    x->k = 1;
    x->v = 0;
    x->v0 = 0;
    
    // "measure" mode default
    x->plan = 1;
    x->wisdom = gensym("/tmp/partconv~.fftwf-wisdom");
    
    x->max_threads_per_level = 1;
    x->max_threads_per_level0 = 0;
    
    x->input = NULL;
    x->output = NULL;
    x->w = NULL;
    
    // default partitioning schemes
    // modified by eric 5-19-2011
    x->scheme_32[0] = 32;
    x->scheme_32[1] = 256;
    x->scheme_32[2] = 1024;
    x->scheme_32[3] = 4096;
    x->scheme_32[4] = 16384;
    x->scheme_32[5] = 65536;
    x->nparts_32 = 6;
    
    x->scheme_64[0] = 64;
    x->scheme_64[1] = 256;
    x->scheme_64[2] = 2048;
    x->scheme_64[3] = 8192;
    x->scheme_64[4] = 65536;
    x->nparts_64 = 5;
    
    x->scheme_128[0] = 128;
    x->scheme_128[1] = 512;
    x->scheme_128[2] = 4096;
    x->scheme_128[3] = 16384;
    x->scheme_128[4] = 65536;
    x->nparts_128 = 5;
    
    x->scheme_256[0] = 256;
    x->scheme_256[1] = 1024;
    x->scheme_256[2] = 4096;
    x->scheme_256[3] = 16384;
    x->scheme_256[4] = 65536;
    x->nparts_256 = 5;
    
    x->scheme_512[0] = 512;
    x->scheme_512[1] = 2048;
    x->scheme_512[2] = 8192;
    x->scheme_512[3] = 65536;
    x->nparts_512 = 4;
    
    x->scheme_1024[0] = 1024;
    x->scheme_1024[1] = 4096;
    x->scheme_1024[2] = 16384;
    x->scheme_1024[3] = 65536;
    x->nparts_1024 = 4;
    
    x->scheme_2048[0] = 2048;
    x->scheme_2048[1] = 8192;
    x->scheme_2048[2] = 65536;
    x->nparts_2048 = 3;
    
    x->scheme_4096[0] = 4096;
    x->scheme_4096[1] = 16384;
    x->scheme_4096[2] = 65536;
    x->nparts_4096 = 3;
    
    // pass attrs...
    attr_args_process(x, argc, argv);
    
    x->w = (t_int**)malloc(sizeof(t_int*) * (x->n + x->m + 2));
    x->input = (float**)malloc(sizeof(float*) * x->n);
    x->output = (float**)malloc(sizeof(float*) * x->m);
    
    for(i = 0; i < x->n; i++)
        x->input[i] = (float *)malloc(sizeof(float) * 4096); //<< temp max vector size
    
    for(i = 0; i < x->m; i++)
        x->output[i] = (float *)malloc(sizeof(float) * 4096); //<< temp max vector size
    
#ifdef CNMAT_PD_VERSION
    x->ir_vec = NULL;
#endif
    // allocate inlets
    dsp_setup((t_pxobject *)x, x->n);
    
    // allocate outlets
    for(i = 0; i < x->m; i++) {
        outlet_new((t_object *)x, "signal");	// type of outlet: "signal"
    }
    
    x->pc = NULL;
    
    post("partconv~.new: n=%d, m=%d, k=%d, v=%d", x->n, x->m, x->k, x->v);
    
    return (x);
    
}

int main(void) {
    
    t_class *c = class_new("partconv~", (method)partconv_new, (method)partconv_free, sizeof(t_partconv), 0L, A_GIMME, 0);
    
    class_dspinit(c);
    
    CLASS_ATTR_SYM(c, "buffer", 0, t_partconv, buffer);
    CLASS_ATTR_LABEL(c, "buffer", 0, "Impulse response buffer");
    //CLASS_ATTR_SAVE(c, "buffer", 0);
    
    CLASS_ATTR_SYM(c, "wisdom", 0, t_partconv, wisdom);
    CLASS_ATTR_LABEL(c, "wisdom", 0, "FFTW plan wisdom cache file");
    CLASS_ATTR_STYLE(c, "wisdom", 0, "file");
    //CLASS_ATTR_SAVE(c, "wisdom", 0);
    
    CLASS_ATTR_LONG(c, "plan", 0, t_partconv, plan);
    CLASS_ATTR_LABEL(c, "plan", 0, "FFTW plan mode");
    CLASS_ATTR_ENUMINDEX(c, "plan", 0, "estimate measure patient");
    //CLASS_ATTR_SAVE(c, "plan", 0);
    
    CLASS_ATTR_LONG(c, "max_threads_per_level", 0, t_partconv, max_threads_per_level);
    CLASS_ATTR_LABEL(c, "max_threads_per_level", 0, "Maximum number of threads per partition level");
    CLASS_ATTR_FILTER_MIN(c, "max_threads_per_level", 1);
    
    CLASS_ATTR_LONG(c, "max_threads_per_level0", 0, t_partconv, max_threads_per_level0);
    CLASS_ATTR_LABEL(c, "max_threads_per_level0", 0, "Maximum number of threads at first partition level");
    CLASS_ATTR_FILTER_MIN(c, "max_threads_per_level0", 0);
    
    CLASS_ATTR_LONG(c, "plan", 0, t_partconv, plan);
    CLASS_ATTR_LABEL(c, "plan", 0, "FFTW plan mode");
    CLASS_ATTR_ENUMINDEX(c, "plan", 0, "estimate measure patient");
    //CLASS_ATTR_SAVE(c, "plan", 0);
    
    CLASS_ATTR_LONG(c, "n", 0, t_partconv, n);
    CLASS_ATTR_FILTER_MIN(c, "n", 1);
    CLASS_ATTR_LABEL(c, "n", 0, "Number of inputs");
    
    CLASS_ATTR_LONG(c, "m", 0, t_partconv, m);
    CLASS_ATTR_FILTER_MIN(c, "m", 1);
    CLASS_ATTR_LABEL(c, "m", 0, "Number of outputs");
    
    CLASS_ATTR_LONG(c, "k", 0, t_partconv, k);
    CLASS_ATTR_FILTER_MIN(c, "k", 1);
    CLASS_ATTR_LABEL(c, "k", 0, "Number of impulse responses");
    
    CLASS_ATTR_LONG(c, "v", 0, t_partconv, v);
    CLASS_ATTR_FILTER_MIN(c, "v", 0);
    CLASS_ATTR_DEFAULT(c, "v", 0, 0);
    CLASS_ATTR_LABEL(c, "v", 0, "Impulse response length, 0 = automatic");
    /*
    CLASS_ATTR_LONG_VARSIZE(c, "scheme_32", 0, t_partconv, scheme_32, nparts_32, 256);
    CLASS_ATTR_ACCESSORS(c, "scheme_32", NULL, partconv_scheme_set);
    CLASS_ATTR_LABEL(c, "scheme_32", 0, "Partioning scheme for 32 sample block");
    //CLASS_ATTR_SAVE(c, "scheme_32", 0);
    
    CLASS_ATTR_LONG_VARSIZE(c, "scheme_64", 0, t_partconv, scheme_64, nparts_64, 256);
    CLASS_ATTR_ACCESSORS(c, "scheme_64", NULL, partconv_scheme_set);
    CLASS_ATTR_LABEL(c, "scheme_64", 0, "Partioning scheme for 64 sample block");
    //CLASS_ATTR_SAVE(c, "scheme_64", 0);
    
    CLASS_ATTR_LONG_VARSIZE(c, "scheme_128", 0, t_partconv, scheme_128, nparts_128, 256);
    CLASS_ATTR_ACCESSORS(c, "scheme_128", NULL, partconv_scheme_set);
    CLASS_ATTR_LABEL(c, "scheme_128", 0, "Partioning scheme for 128 sample block");
    //CLASS_ATTR_SAVE(c, "scheme_128", 0);
    
    CLASS_ATTR_LONG_VARSIZE(c, "scheme_256", 0, t_partconv, scheme_256, nparts_256, 256);
    CLASS_ATTR_ACCESSORS(c, "scheme_256", NULL, partconv_scheme_set);
    CLASS_ATTR_LABEL(c, "scheme_256", 0, "Partioning scheme for 256 sample block");
    //CLASS_ATTR_SAVE(c, "scheme_256", 0);
    
    CLASS_ATTR_LONG_VARSIZE(c, "scheme_512", 0, t_partconv, scheme_512, nparts_512, 256);
    CLASS_ATTR_ACCESSORS(c, "scheme_512", NULL, partconv_scheme_set);
    CLASS_ATTR_LABEL(c, "scheme_512", 0, "Partioning scheme for 512 sample block");
    //CLASS_ATTR_SAVE(c, "scheme_512", 0);
    
    CLASS_ATTR_LONG_VARSIZE(c, "scheme_1024", 0, t_partconv, scheme_1024, nparts_1024, 256);
    CLASS_ATTR_ACCESSORS(c, "scheme_1024", NULL, partconv_scheme_set);
    CLASS_ATTR_LABEL(c, "scheme_1024", 0, "Partioning scheme for 1024 sample block");
    //CLASS_ATTR_SAVE(c, "scheme_1024", 0);
    
    CLASS_ATTR_LONG_VARSIZE(c, "scheme_2048", 0, t_partconv, scheme_2048, nparts_2048, 256);
    CLASS_ATTR_ACCESSORS(c, "scheme_2048", NULL, partconv_scheme_set);
    CLASS_ATTR_LABEL(c, "scheme_2048", 0, "Partioning scheme for 2048 sample block");
    //CLASS_ATTR_SAVE(c, "scheme_2048", 0);
    
    CLASS_ATTR_LONG_VARSIZE(c, "scheme_4096", 0, t_partconv, scheme_4096, nparts_4096, 256);
    CLASS_ATTR_ACCESSORS(c, "scheme_4096", NULL, partconv_scheme_set);
    CLASS_ATTR_LABEL(c, "scheme_4096", 0, "Partioning scheme for 4096 sample block");
    //CLASS_ATTR_SAVE(c, "scheme_4096", 0);
    */
//    class_addmethod(c, (method)partconv_dsp, "dsp", A_CANT, 0);
    class_addmethod(c, (method)partconv_dsp64, "dsp64", A_CANT, 0);
	class_addmethod(c, (method)partconv_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)partconv_buffer_notify, "notify", A_CANT, 0);
    class_addmethod(c, (method)partconv_buffer_set, "set", A_SYM, 0);
    
	class_register(CLASS_BOX, c);
    
	partconv_class = c;
    
    ps_buffer_tilde = gensym("buffer~");
    
    //    version(0);
    
    return 0;
    
}
#endif