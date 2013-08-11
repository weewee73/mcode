#include <ruby.h>

static VALUE hola_bonjour(VALUE self)
{
	return rb_str_new2("bonjour!");
}

void Init_hola(void)
{
	VALUE klass = rb_define_class("Hola", rb_cObject);

	rb_define_singleton_method(Klass, "bonjour", hola_bonjour, 0);
}
