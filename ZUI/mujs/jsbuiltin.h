#ifndef js_builtin_h
#define js_builtin_h
#include <ZUI.h>
void jsB_init(js_State *J);
void jsB_initobject(js_State *J);
void jsB_initarray(js_State *J);
void jsB_initfunction(js_State *J);
void jsB_initboolean(js_State *J);
void jsB_initnumber(js_State *J);
void jsB_initstring(js_State *J);
void jsB_initregexp(js_State *J);
void jsB_initerror(js_State *J);
void jsB_initmath(js_State *J);
void jsB_initjson(js_State *J);
void jsB_initdate(js_State *J);

void jsB_propf(js_State *J, const wchar_t *name, js_CFunction cfun, int n);
void jsB_propn(js_State *J, const wchar_t *name, double number);
void jsB_props(js_State *J, const wchar_t *name, const wchar_t *string);

typedef struct js_Buffer { int n, m; wchar_t s[64]; } js_Buffer;

static void js_putc(js_State *J, js_Buffer **sbp, int c)
{
	js_Buffer *sb = *sbp;
	if (!sb) {
		sb = ZuiMalloc(sizeof *sb);
		sb->n = 0;
		sb->m = sizeof sb->s;
		*sbp = sb;
	} else if (sb->n == sb->m) {
		sb = ZuiRealloc(sb, (sb->m *= 2) + soffsetof(js_Buffer, s));
		*sbp = sb;
	}
	sb->s[sb->n++] = c;
}

static inline void js_puts(js_State *J, js_Buffer **sb, const wchar_t *s)
{
	while (*s)
		js_putc(J, sb, *s++);
}

static inline void js_putm(js_State *J, js_Buffer **sb, const wchar_t *s, const wchar_t *e)
{
	while (s < e)
		js_putc(J, sb, *s++);
}

#endif
