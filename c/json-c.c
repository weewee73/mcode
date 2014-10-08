//gcc json-c.c -I/usr/local/include/json-c/ /usr/local/lib/libjson-c.a
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <json.h>


int main(int argc, char **argv)
{
	json_object *new_obj;

	new_obj = json_tokener_parse("/* more difficult test case */ { \"glossary\": { \"title\": \"example glossary\", \"GlossDiv\": { \"title\": \"S\", \"GlossList\": [ { \"ID\": \"SGML\", \"SortAs\": \"SGML\", \"GlossTerm\": \"Standard Generalized Markup Language\", \"Acronym\": \"SGML\", \"Abbrev\": \"ISO 8879:1986\", \"GlossDef\": \"A meta-markup language, used to create markup languages such as DocBook.\", \"GlossSeeAlso\": [\"GML\", \"XML\", \"markup\"] } ] } } }");
	printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
	json_object_put(new_obj);


    json_object *my_object;

	my_object = json_object_new_object();
	json_object_object_add(my_object, "abc", json_object_new_int(12));
	json_object_object_add(my_object, "foo", json_object_new_string("bar"));
	json_object_object_add(my_object, "bool0", json_object_new_boolean(0));
	json_object_object_add(my_object, "bool1", json_object_new_boolean(1));
	json_object_object_add(my_object, "baz", json_object_new_string("bang"));



	json_object *baz_obj = json_object_new_string("fark");
	json_object_get(baz_obj);
	json_object_object_add(my_object, "baz", baz_obj);
	json_object_object_del(my_object, "baz");

	/* baz_obj should still be valid */
	printf("baz_obj.to_string()=%s\n", json_object_to_json_string(baz_obj));
	json_object_put(baz_obj);


    int i;
    json_object *my_array;
	my_array = json_object_new_array();
	json_object_array_add(my_array, json_object_new_int(3));
	json_object_array_add(my_array, json_object_new_int(1));
	json_object_array_add(my_array, json_object_new_int(2));
	json_object_array_put_idx(my_array, 4, json_object_new_int(0));

	baz_obj = json_object_new_object();
	json_object_object_add(baz_obj, "abc", json_object_new_int(12));
	json_object_object_add(baz_obj, "foo", json_object_new_string("bar"));
	json_object_get(baz_obj);
	json_object_array_add(my_array, baz_obj);

	printf("my_array=\n");
	for(i=0; i < json_object_array_length(my_array); i++)
	{
		json_object *obj = json_object_array_get_idx(my_array, i);
		printf("\t[%d]=%s\n", i, json_object_to_json_string(obj));
	}
	printf("my_array.to_string()=%s\n", json_object_to_json_string(my_array));    
	json_object_object_add(my_object, "array", my_array);



	/*json_object_object_add(my_object, "arr", my_array);*/
	printf("my_object=\n");
	json_object_object_foreach(my_object, key, val)
	{
		printf("\t%s: %s\n", key, json_object_to_json_string(val));
	}
	printf("my_object.to_string()=%s\n", json_object_to_json_string(my_object));



    json_object *test_obj;
    test_obj = json_tokener_parse(json_object_to_json_string(my_object));
	printf("test_obj.to_string()=%s\n", json_object_to_json_string(test_obj));


	json_object_put(my_array);
	json_object_put(my_object);

	return 0;
}
