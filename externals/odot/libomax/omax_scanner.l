%{
#include <Carbon.h>
#include <CoreServices.h>
#include "ext.h"
#include "ext_obex.h"
#include "ext_obex_util.h"
#include "osc.h"
void omax_scanner_scan_atom_array(int argc, t_atom *argv, int *argc_out, t_atom **argv_out);
%}

%option reentrant
%option extra-type="t_atom **"
%option prefix="omax_scanner_"
%option noyywrap

dseq      ([[:digit:]]+)
dseq_opt  ([[:digit:]]*)
frac      (({dseq_opt}"."{dseq})|{dseq}".")
exp       ([eE][+-]?{dseq})
exp_opt   ({exp}?)
fsuff     [flFL]
fsuff_opt ({fsuff}?)
hpref     (0[xX])
hdseq     ([[:xdigit:]]+)
hdseq_opt ([[:xdigit:]]*)
hfrac     (({hdseq_opt}"."{hdseq})|({hdseq}"."))
bexp      ([pP][+-]?{dseq})
dfc       (({frac}{exp_opt}{fsuff_opt})|({dseq}{exp}{fsuff_opt}))
hfc       (({hpref}{hfrac}{bexp}{fsuff_opt})|({hpref}{hdseq}{bexp}{fsuff_opt}))
c99_floating_point_constant  ({dfc}|{hfc})

%%

\(					{
						atom_setsym(*yyextra, gensym("("));
						(*yyextra)++;
						//printf("open paren\n");
					}

\)					{
						atom_setsym(*yyextra, gensym(")"));
						(*yyextra)++;
						//printf("open paren\n");
					}

([[:digit:]]{-}[0])[[:digit:]]* 	{
						char *endptr = NULL;
						atom_setlong(*yyextra, strtol(yytext, &endptr, 0));
						(*yyextra)++;
						//printf("int: %ld\n", l);
					}
{c99_floating_point_constant}		{
						//printf("%s: buf = %p\n", __func__, yyextra);
						char *endptr = NULL;
						atom_setfloat(*yyextra, strtod(yytext, &endptr));
						(*yyextra)++;
						//printf("float: %f\n", f);
					}

[^0-9\(\) \t\n]+[^\(\) \t\n]*		{
						atom_setsym(*yyextra, gensym(yytext));
						(*yyextra)++;
						//printf("string: %s\n", yytext);
					}
[ \t\n]+	/* eat up whitespace */

%%
/*
int main(int argc, char **argv){
	++argv, --argc;
	yyin = stdin;
	yylex();
}
*/

void omax_scanner_scan_atom_array(int argc, t_atom *argv, int *argc_out, t_atom **argv_out){
	yyscan_t scanner;
	t_atom buf[512];
	t_atom *bufptr = buf;
	int i;
	for(i = 0; i < argc; i++){
		if(atom_gettype(argv + i) == A_SYM){
			yylex_init_extra(&bufptr, &scanner);
			YY_BUFFER_STATE myybuf = yy_scan_string(atom_getsym(argv + i)->s_name, scanner);
			yylex(scanner);
			yy_delete_buffer(myybuf, scanner);
			yylex_destroy(scanner);
		}else{
			*bufptr++ = *(argv + i);
		}
	}
	if(*argv_out){
		if(bufptr - buf > *argc_out){
			memcpy(*argv_out, buf, *argc_out * sizeof(t_atom));
		}else{
			memcpy(*argv_out, buf, (bufptr - buf) * sizeof(t_atom));
		}
	}else{
		t_atom *tmp = (t_atom *)osc_mem_alloc((bufptr - buf) * sizeof(t_atom));
		memcpy(tmp, buf, (bufptr - buf) * sizeof(t_atom));
		*argv_out = tmp;
	}
	*argc_out = bufptr - buf;
}