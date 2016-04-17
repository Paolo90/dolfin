
.. _styleguides_sphinx_documenting_interface:

==================================================
Documenting the interface (Programmer's reference)
==================================================

The DOLFIN :ref:`Programmer's Reference <documentation>` is generated
for the DOLFIN C++ library and Python module from the source code
using the documentation tool `Sphinx
<http://sphinx.pocoo.org/index.html>`_. This page describes how to
generate the DOLFIN documentation locally and how to extend the
contents of the Programmer's Reference.

.. _generate_dolfin_documentation_locally:

How to locally build the DOLFIN documentation
---------------------------------------------

The DOLFIN documentation can be generated and built from the DOLFIN
source directly as follows:

* Make sure that `Sphinx <http://sphinx.pocoo.org/index.html>`_ is
  installed.

* Build DOLFIN (for instructions, see :ref:`installation_from_source`).

* Build the documentation by running:

    make doc

  in the DOLFIN build directory.

For ``make doc`` to successfully run, the DOLFIN Python module must be
installed.

How to improve and extend the DOLFIN Programmer's reference
-----------------------------------------------------------

The documentation contents are extracted from specially formatted
comments (docstring comments) in the source code, converted to
`reStructuredText <http://docutils.sourceforge.net/rst.html>`_, and
formatted using `Sphinx <http://sphinx.pocoo.org/index.html>`_. The
syntax used for these specially formatted comments is described below.

To document a feature,

#. Add appropriate docstring comments to source files (see
   :ref:`syntax_for_docstring_comments`).

#. If you made changes to C++ header files or docstrings in
   ``dolfin_dir/dolfin/swig/*.i`` you should update the
   ``dolfin_dir/dolfin/swig/codeexamples.py`` file with an example
   snippet if applicable and run the script
   ``dolfin_dir/dolfin/swig/generate.py`` to update the
   ``dolfin_dir/dolfin/swig/docstrings.i`` file.

#. Build the documentation as described in
   :ref:`generate_dolfin_documentation_locally` to check the result.

.. _syntax_for_docstring_comments:

Syntax for docstring comments
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

As Sphinx does not allow sections in the markup for class/function
documentation, we use *italics* (``*italics*``) and definition lists
to group information.  This is to keep the markup as simple as
possible since the reST source for the Python documentation of classes
and functions will be used 'as is' in the docstrings of the DOLFIN
module.

Most information can be put in the three sections:

* *Arguments*, which are formatted using definition lists following this
  structure::

    *Arguments*
        <name> (<type>)
            <description>
        <name2> (<type>)
            <description>

  For example:

  .. code-block:: rest

      *Arguments*
          dim (int)
              some dimension.
          d (double)
              some value.

* *Returns*, which is formatted in a similar fashion::

    *Returns*
        <return type>
            <description>

  For example:

  .. code-block:: rest

      *Returns*
          int
              Some random integer.

* *Example*, a very small code snippet that shows how the
  class/function works. It does not necessarily have to be a
  stand-alone program.

.. Links to demos that use the feature being documented should be put in
.. a ``seealso`` directive.


An example of how to document a feature
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To make matters more concrete let's consider the case of writing
documentation for the member function ``closest_cell`` of the DOLFIN
``Mesh`` class.  The Python interface to this class is generated by
Swig and it is not extended in the Python layer.  Writing
documentation for other classes and functions in DOLFIN which are not
extended or added in the Python layer follow a similar procedure.

The ``Mesh::closest_cell`` function is defined in the file
``dolfin_dir/dolfin/mesh/Mesh.h``, and the comment lines and function
definition look as follows:

.. code-block:: c++

    /// Computes the index of the cell in the mesh which is closest to the
    /// point query.
    ///
    /// *Arguments*
    ///     point (_Point_)
    ///         A _Point_ object.
    ///
    /// *Returns*
    ///     uint
    ///         The index of the cell in the mesh which is closest to point.
    ///
    /// *Example*
    ///     .. code-block:: c++
    ///
    ///         UnitSquare mesh(1, 1);
    ///         Point point(0.0, 2.0);
    ///         info("%d", mesh.closest_cell(point));
    ///
    ///     output::
    ///
    ///         1
    dolfin::uint closest_cell(const Point& point) const;

Note that the documentation of a function or class is placed above the
definition in the source code.
The structure and content follow the guidelines in the previous section.

The Point object is a class like Mesh and it is defined in the FEniCS
interface.  To insert a link to the documentation of this class use
leading and trailing underscore i.e., ``_Point_``.  When parsing the
comment lines this string will be substituted with either
``:cpp:class:`Point``` or ``:py:class:`Point``` depending on whether
documentation for the C++ or Python interface is being generated.  The
return type, in this case ``dolfin::uint``, will automatically be
mapped to the correct Python type when generating the documentation
for the Python interface. Note that if you are writing documentation
for one of the functions/classes which are added to the Python layer
manually you have to add manually the correct links and types.

The example code uses C++ syntax because it is located in the C++
header file.  Translating this code to a correct Python equivalent is
rather difficult.  It is therefore necessary to add example code using
the Python syntax manually.  This code should be put in the
``dolfin_dir/dolfin/swig/codeexamples.py`` which contains a simple
dictionary of example code.  The dictionary containing only the
example code for the example above should look as follows:

.. code-block:: python

    codesnippets = {
    "Mesh":{
    "dolfin::uint closest_cell(const Point& point) const":
    """
    .. code-block:: python

        >>> mesh = dolfin.UnitSquare(1, 1)
        >>> point = dolfin.Point(0.0, 2.0)
        >>> mesh.closest_cell(point)
        1
    """}
    }

The first dictionary contains dictionaries for all classes with code
examples for each function. Note that the full C++ function signature
has been used to identify the function to which the code example
belongs.

After adding the documentation to the ``Mesh.h`` file and Python code example
to the ``codeexamples.py`` file, you have to run the script
``dolfin/dolfin/swig/generate.py`` to generate the
``dolfin/dolfin/swig/docstrings.i`` file and then build DOLFIN to update the
docstrings in the ``dolfin`` Python module.

Why is the documentation procedure so elaborate?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The procedure for writing documentation might seem cumbersome so let's have a
look at the design considerations which have led to this ostensible case of
overengineering.

The Python interface is (partially) generated automatically using
`Swig <http://www.swig.org/>`_ from the C++ implementation of DOLFIN.
Some classes are extended when building (see the ``dolfin/dolfin/swig/*post.i``
files) while others are added or extended manually in the Python layer defined
in ``dolfin/site-packages/dolfin``.
While this approach saves a lot of work when implementing the Python interface
it puts some constraints on the way the documentation can be handled.
In addition we have the following design goals for writing and maintaining the
documentation:

Avoid duplicate text
    In many cases the documentation of a feature will be virtually identical
    for the C++ and Python interfaces, and since the Python interface is
    generated from the C++ code, the documentation should be in the C++ source
    code.
    To avoid that the documentation on these pages and the comments in the
    source code (and the implementation itself) diverge, the documentation
    should be automatically generated from the C++ source code.
    Therefore the comments should be written using Sphinx markup.

Help in the Python interpreter
    The documentation of a class/function when running ``help(dolfin.foo)``
    in the Python interpreter should be identical to what can be found online.
    In practice this means that we have to generate the
    ``dolfin/dolfin/swig/docstrings.i`` file using the comments extracted from
    the C++ source before building the Python interface with Swig.

Simple markup
    Since the documentation is written directly in the C++ source code, we want
    markup to be simple such that we have 'code with comments' rather than
    'comments with code'.
    Another reason for preferring simple markup is that it is the raw docstring
    which will be available from the Python interpreter.