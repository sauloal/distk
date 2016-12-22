# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.8
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_kmer_set', [dirname(__file__)])
        except ImportError:
            import _kmer_set
            return _kmer_set
        if fp is not None:
            try:
                _mod = imp.load_module('_kmer_set', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _kmer_set = swig_import_helper()
    del swig_import_helper
else:
    import _kmer_set
del version_info
try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.


def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr_nondynamic(self, class_type, name, static=1):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    if (not static):
        return object.__getattr__(self, name)
    else:
        raise AttributeError(name)

def _swig_getattr(self, class_type, name):
    return _swig_getattr_nondynamic(self, class_type, name, 0)


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object:
        pass
    _newclass = 0


class SwigPyIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SwigPyIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SwigPyIterator, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _kmer_set.delete_SwigPyIterator
    __del__ = lambda self: None

    def value(self):
        return _kmer_set.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _kmer_set.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _kmer_set.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _kmer_set.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _kmer_set.SwigPyIterator_equal(self, x)

    def copy(self):
        return _kmer_set.SwigPyIterator_copy(self)

    def next(self):
        return _kmer_set.SwigPyIterator_next(self)

    def __next__(self):
        return _kmer_set.SwigPyIterator___next__(self)

    def previous(self):
        return _kmer_set.SwigPyIterator_previous(self)

    def advance(self, n):
        return _kmer_set.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _kmer_set.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _kmer_set.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _kmer_set.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _kmer_set.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _kmer_set.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _kmer_set.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self
SwigPyIterator_swigregister = _kmer_set.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)

class StringVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StringVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StringVector, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _kmer_set.StringVector_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _kmer_set.StringVector___nonzero__(self)

    def __bool__(self):
        return _kmer_set.StringVector___bool__(self)

    def __len__(self):
        return _kmer_set.StringVector___len__(self)

    def __getslice__(self, i, j):
        return _kmer_set.StringVector___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _kmer_set.StringVector___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _kmer_set.StringVector___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _kmer_set.StringVector___delitem__(self, *args)

    def __getitem__(self, *args):
        return _kmer_set.StringVector___getitem__(self, *args)

    def __setitem__(self, *args):
        return _kmer_set.StringVector___setitem__(self, *args)

    def pop(self):
        return _kmer_set.StringVector_pop(self)

    def append(self, x):
        return _kmer_set.StringVector_append(self, x)

    def empty(self):
        return _kmer_set.StringVector_empty(self)

    def size(self):
        return _kmer_set.StringVector_size(self)

    def swap(self, v):
        return _kmer_set.StringVector_swap(self, v)

    def begin(self):
        return _kmer_set.StringVector_begin(self)

    def end(self):
        return _kmer_set.StringVector_end(self)

    def rbegin(self):
        return _kmer_set.StringVector_rbegin(self)

    def rend(self):
        return _kmer_set.StringVector_rend(self)

    def clear(self):
        return _kmer_set.StringVector_clear(self)

    def get_allocator(self):
        return _kmer_set.StringVector_get_allocator(self)

    def pop_back(self):
        return _kmer_set.StringVector_pop_back(self)

    def erase(self, *args):
        return _kmer_set.StringVector_erase(self, *args)

    def __init__(self, *args):
        this = _kmer_set.new_StringVector(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def push_back(self, x):
        return _kmer_set.StringVector_push_back(self, x)

    def front(self):
        return _kmer_set.StringVector_front(self)

    def back(self):
        return _kmer_set.StringVector_back(self)

    def assign(self, n, x):
        return _kmer_set.StringVector_assign(self, n, x)

    def resize(self, *args):
        return _kmer_set.StringVector_resize(self, *args)

    def insert(self, *args):
        return _kmer_set.StringVector_insert(self, *args)

    def reserve(self, n):
        return _kmer_set.StringVector_reserve(self, n)

    def capacity(self):
        return _kmer_set.StringVector_capacity(self)
    __swig_destroy__ = _kmer_set.delete_StringVector
    __del__ = lambda self: None
StringVector_swigregister = _kmer_set.StringVector_swigregister
StringVector_swigregister(StringVector)

class ULongVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ULongVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ULongVector, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _kmer_set.ULongVector_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _kmer_set.ULongVector___nonzero__(self)

    def __bool__(self):
        return _kmer_set.ULongVector___bool__(self)

    def __len__(self):
        return _kmer_set.ULongVector___len__(self)

    def __getslice__(self, i, j):
        return _kmer_set.ULongVector___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _kmer_set.ULongVector___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _kmer_set.ULongVector___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _kmer_set.ULongVector___delitem__(self, *args)

    def __getitem__(self, *args):
        return _kmer_set.ULongVector___getitem__(self, *args)

    def __setitem__(self, *args):
        return _kmer_set.ULongVector___setitem__(self, *args)

    def pop(self):
        return _kmer_set.ULongVector_pop(self)

    def append(self, x):
        return _kmer_set.ULongVector_append(self, x)

    def empty(self):
        return _kmer_set.ULongVector_empty(self)

    def size(self):
        return _kmer_set.ULongVector_size(self)

    def swap(self, v):
        return _kmer_set.ULongVector_swap(self, v)

    def begin(self):
        return _kmer_set.ULongVector_begin(self)

    def end(self):
        return _kmer_set.ULongVector_end(self)

    def rbegin(self):
        return _kmer_set.ULongVector_rbegin(self)

    def rend(self):
        return _kmer_set.ULongVector_rend(self)

    def clear(self):
        return _kmer_set.ULongVector_clear(self)

    def get_allocator(self):
        return _kmer_set.ULongVector_get_allocator(self)

    def pop_back(self):
        return _kmer_set.ULongVector_pop_back(self)

    def erase(self, *args):
        return _kmer_set.ULongVector_erase(self, *args)

    def __init__(self, *args):
        this = _kmer_set.new_ULongVector(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def push_back(self, x):
        return _kmer_set.ULongVector_push_back(self, x)

    def front(self):
        return _kmer_set.ULongVector_front(self)

    def back(self):
        return _kmer_set.ULongVector_back(self)

    def assign(self, n, x):
        return _kmer_set.ULongVector_assign(self, n, x)

    def resize(self, *args):
        return _kmer_set.ULongVector_resize(self, *args)

    def insert(self, *args):
        return _kmer_set.ULongVector_insert(self, *args)

    def reserve(self, n):
        return _kmer_set.ULongVector_reserve(self, n)

    def capacity(self):
        return _kmer_set.ULongVector_capacity(self)
    __swig_destroy__ = _kmer_set.delete_ULongVector
    __del__ = lambda self: None
ULongVector_swigregister = _kmer_set.ULongVector_swigregister
ULongVector_swigregister(ULongVector)

class MutexType(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, MutexType, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, MutexType, name)
    __repr__ = _swig_repr

    def Lock(self):
        return _kmer_set.MutexType_Lock(self)

    def Unlock(self):
        return _kmer_set.MutexType_Unlock(self)

    def __init__(self):
        this = _kmer_set.new_MutexType()
        try:
            self.this.append(this)
        except Exception:
            self.this = this
    __swig_destroy__ = _kmer_set.delete_MutexType
    __del__ = lambda self: None
MutexType_swigregister = _kmer_set.MutexType_swigregister
MutexType_swigregister(MutexType)

class ScopedLock(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ScopedLock, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ScopedLock, name)
    __repr__ = _swig_repr

    def __init__(self, m):
        this = _kmer_set.new_ScopedLock(m)
        try:
            self.this.append(this)
        except Exception:
            self.this = this
    __swig_destroy__ = _kmer_set.delete_ScopedLock
    __del__ = lambda self: None

    def Unlock(self):
        return _kmer_set.ScopedLock_Unlock(self)

    def LockAgain(self):
        return _kmer_set.ScopedLock_LockAgain(self)
ScopedLock_swigregister = _kmer_set.ScopedLock_swigregister
ScopedLock_swigregister(ScopedLock)


def fact(n):
    return _kmer_set.fact(n)
fact = _kmer_set.fact

def version():
    return _kmer_set.version()
version = _kmer_set.version
class extract_kmers(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, extract_kmers, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, extract_kmers, name)
    __repr__ = _swig_repr

    def __init__(self, ks):
        this = _kmer_set.new_extract_kmers(ks)
        try:
            self.this.append(this)
        except Exception:
            self.this = this
    __swig_destroy__ = _kmer_set.delete_extract_kmers
    __del__ = lambda self: None

    def read_one_liner(self, infile):
        return _kmer_set.extract_kmers_read_one_liner(self, infile)

    def read_fasta(self, infile):
        return _kmer_set.extract_kmers_read_fasta(self, infile)

    def read_fastq(self, infile):
        return _kmer_set.extract_kmers_read_fastq(self, infile)

    def parse_line(self, line):
        return _kmer_set.extract_kmers_parse_line(self, line)

    def save_kmer_db(self, outfile):
        return _kmer_set.extract_kmers_save_kmer_db(self, outfile)

    def read_kmer_db(self, infile):
        return _kmer_set.extract_kmers_read_kmer_db(self, infile)

    def merge_kmers(self, *args):
        return _kmer_set.extract_kmers_merge_kmers(self, *args)

    def save_matrix(self, outfile, infiles, mat):
        return _kmer_set.extract_kmers_save_matrix(self, outfile, infiles, mat)

    def get_db_file_size(self, infile):
        return _kmer_set.extract_kmers_get_db_file_size(self, infile)

    def get_db_num_registers(self, infile):
        return _kmer_set.extract_kmers_get_db_num_registers(self, infile)

    def get_kmer_db(self):
        return _kmer_set.extract_kmers_get_kmer_db(self)

    def size(self):
        return _kmer_set.extract_kmers_size(self)

    def print_all(self):
        return _kmer_set.extract_kmers_print_all(self)
extract_kmers_swigregister = _kmer_set.extract_kmers_swigregister
extract_kmers_swigregister(extract_kmers)

# This file is compatible with both classic and new-style classes.


