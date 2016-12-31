#ifndef RPMPYTHON_HEADER
#define RPMPYTHON_HEADER

/** \ingroup python
 * \file python/header-py.h
 */

/** \ingroup python
 */
typedef struct hdrObject_s hdrObject;
extern PyTypeObject hdrType;

/** \ingroup python
 */
PyObject * pyrpmError;

hdrObject * createHeaderObject(Header h);
Header hdrGetHeader(hdrObject * h);
PyObject * labelCompare (PyObject * self, PyObject * args);
PyObject * versionCompare (PyObject * self, PyObject * args);
PyObject * rpmMergeHeadersFromFD(PyObject * self, PyObject * args);
int rpmMergeHeaders(PyObject * list, FD_t fd, int matchTag);
PyObject * rpmHeaderFromFile(PyObject * self, PyObject * args);
PyObject * rpmHeaderFromFD(PyObject * self, PyObject * args);
PyObject * rpmReadHeaders (FD_t fd);
PyObject * rhnLoad(PyObject * self, PyObject * args);
PyObject * hdrLoad(PyObject * self, PyObject * args);
PyObject * rpmHeaderFromPackage(PyObject * self, PyObject * args);
long tagNumFromPyObject (PyObject *item);

#endif
