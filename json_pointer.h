/*
 * Copyright (c) 2016 Alexadru Ardelean.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#ifndef _json_pointer_h_
#define _json_pointer_h_

#include "json_object.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Retrieves a JSON sub-object from inside another JSON object
 * using the JSON pointer notation as defined in RFC 6901
 *   https://tools.ietf.org/html/rfc6901
 *
 * The returned JSON sub-object is equivalent to parsing manually the
 * 'obj' JSON tree ; i.e. it's not a new object that is created, but rather
 * a pointer inside the JSON tree.
 *
 * Internally, this is equivalent to doing a series of 'json_object_object_get()'
 * and 'json_object_array_get_idx()' along the given 'path'.
 *
 * @param obj the json_object instance/tree from where to retrieve sub-objects
 * @param path a (RFC6901) string notation for the sub-object to retrieve
 * @param res a pointer where to store a reference to the json_object
 *              associated with the given path
 *
 * @return negative if an error (or not found), or 0 if succeeded
 */
int json_pointer_get(struct json_object *obj, const char *path, struct json_object **res);

/**
 * Sets JSON object 'value' in the 'obj' tree at the location specified
 * by the 'path'. 'path' is JSON pointer notation as defined in RFC 6901
 *   https://tools.ietf.org/html/rfc6901
 *
 * Note that 'obj' is a double pointer, mostly for the "" (empty string)
 * case, where the entire JSON object would be replaced by 'value'.
 * In the case of the "" path, the object at '*obj' will have it's refcount
 * decremented with 'json_object_put()' and the 'value' object will be assigned to it.
 *
 * For other cases (JSON sub-objects) ownership of 'value' will be transferred into
 * '*obj' via 'json_object_object_add()' & 'json_object_array_put_idx()', so the
 * only time the refcount should be decremented for 'value' is when the return value of
 * 'json_pointer_set()' is negative (meaning the 'value' object did not get set into '*obj').
 *
 * That also implies that 'json_pointer_set()' does not do any refcount incrementing.
 * (Just that single decrement that was mentioned above).
 *
 * @param obj the json_object instance/tree to which to add a sub-object
 * @param path a (RFC6901) string notation for the sub-object to set in the tree
 * @param value object to set at path
 *
 * @return negative if an error (or not found), or 0 if succeeded
 */
int json_pointer_set(struct json_object **obj, const char *path, struct json_object *value);

#ifdef __cplusplus
}
#endif

#endif
