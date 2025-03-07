.. Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
.. Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
.. other details. No copyright assignment is required to contribute to Conduit.

================================
Releases
================================

Source distributions for Conduit releases are hosted on github:

https://github.com/LLNL/conduit/releases

.. note:: Conduit uses `BLT <https://github.com/LLNL/blt>`__ as its core CMake build system. We leverage BLT as a git submodule, however github does not include submodule contents in its automatically created source tarballs. To avoid confusion, starting with v0.3.0 we provide our own source tarballs that include BLT. 

v0.9.3
---------------------------------

* Released 2025-01-27
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.9.3/conduit-v0.9.3-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~

* **Conduit**

 * Added ``conduit_yaml`` and ``conduit_base64_yaml`` protocol support.
 * Added support to detect ``.yml`` files as ``yaml`` protocol.

* **Blueprint**

 * Added ``conduit::blueprint::mesh::examples:generate`` driver functions that supports creating any blueprint example mesh with options.
 * Added ``conduit::blueprint::mesh::examples:generate_default_options`` functions that provide default options values for ``conduit::blueprint::mesh::examples:generate``.
 * Added python API support for ``conduit::blueprint::mesh::examples:generate`` and ``conduit::blueprint::mesh::examples:generate_default_options``.
 * Added ``gyre`` example mesh, which provides a simple velocity vector field.
 * Added ``bent_multi_grid`` example mesh, which provides a multi-grid that can contain enhanced and reduced connectivity.  ``bent_multi_grid`` can produce meshes like the example at http://visitusers.org/index.php?title=Representing_ghost_data#Enhanced_and_Reduced_Connectivity_Zones .
 * Added new utilities for material sets: ``conduit::blueprint::mesh::matset::count_zones_from_matset()``, ``conduit::blueprint::mesh::matset::is_material_in_zone()``, and ``conduit::blueprint::mesh::matset::create_reverse_material_map()``.
 * Added a new example, ``conduit::blueprint::mesh::examples::venn_specsets()``, which covers the breadth of species set representations.

* **Relay**

 * Added limited support for species sets for Silo/Overlink I/O. Multi-buffer element-dominant species sets can be written to Silo and the same can be read from Silo. Additional species set flavors will come online in a later release.
 * Added support for ``conduit_yaml`` and ``conduit_base64_yaml`` I/O cases.
 * Standardized the way that Relay Silo Save handles name collisions and non-idiomatic Silo names.

Changed
~~~~~~~


* **Conduit**

 * Changed the MPI CMake target used by conduit from ``MPI:MPI_CXX`` to ``MPI:MPI_C`` to provide better compatibility with downstream tools.
 * Added vendored yyjson v0.10.0 as new and default JSON parser. yyjson has an MIT license that is compatible with Debian's Free Software Guidelines, where RapidJSON is not  (https://wiki.debian.org/qa.debian.org/jsonevil). You can still use RapidJSON by setting the new CMake option ``ENABLE_YYJSON`` to ``FALSE``.
 * The ``DataType::equals()`` method now correctly takes striding into account.

* **Blueprint**

 * Certain algorithms that use MPI tags had their tag values lowered since some MPI implementations do not support large values.
 * Changed the name of ``conduit::blueprint::mesh::matset::to_sparse_by_element()`` to ``conduit::blueprint::mesh::matset::to_uni_buffer_by_element()`` to be more consistent with similar function names.
 * Expanded the ways species sets can be represented in Blueprint to include sparse by element and sparse by material representations, much like material sets.
 * Updated ``conduit.relay.io.blueprint.{load_mesh|read_mesh}`` to support reading and writing Silo files when Conduit is built with Silo support.
 * Updated ``conduit.relay.io.blueprint.{load_mesh|read_mesh}`` to use improved logic to auto detect the format (hdf5 , silo, yaml, or json) of mesh blueprint root files. Added silo logic, and fixed prior logic that could confuse yaml as json files due to format specifiers in partition pattern strings.

* **Relay**

 * User-supplied warning and error handlers are suspended during ``conduit::relay::communicate_using_schema::execute()`` so exceptions will be thrown properly when there is an MPI error. The handlers are restored before the execute method returns.
 * ``conduit::relay::communicate_using_schema::execute()`` flushes logs as they are generated, in case of error. This is mostly to facilitate internal debugging.
 * Changes were made to how Relay queries the upper limit for MPI tags to work around problems on some systems.
 * Rewrote ``conduit::blueprint::mesh::specset::to_silo()`` to allow it to support specsets that do not use all the materials in the associated matset.


v0.9.2
---------------------------------

* Released 2024-05-21
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.9.2/conduit-v0.9.2-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **Relay**

 * Added support for Blueprint + Silo round trip for axis units and labels.
 * Added support for reading Silo column major data as strided structured Blueprint data.
 * Added support for reading a much wider set of Silo meshes, beyond multimeshes, multivars, etc.

Changed
~~~~~~~


* **Conduit**

 * Removed cmake use of distutils for python introspection.

* **Blueprint**

 * Fixed partitioner so it reverses vertex order as needed in polyhedral face definitions when extracting mesh elements.
 * Changed ``conduit::blueprint::mesh::partition_map_back()`` function so it will attempt to reuse existing field memory when mapping fields back. This permits ``partition_map_back()`` to send data from a partitioned mesh into the original mesh where fields were provided from a host code using ``Node::set_external()``.
 * Changed ``generate_sides`` to be robust to the case where no fields exist.

* **Relay**

 * Changed ``conduit::relay::mpi::communicate_using_schema`` to avoid an invalid tag MPI error message on some MPI distributions.

Fixed
~~~~~


* **Relay**

 * Fixed Relay I/O HDF5 DataSpace handle leak.

v0.9.1
---------------------------------

* Released 2024-02-09
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.9.1/conduit-v0.9.1-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Changed
~~~~~~~


* **Conduit**

 * Relaxed strict header check for C++14 back to C++11. A downstream consumer of Conduit has C++11 hardcoded into their build system and patching for related deployments is intractable.
 * Restore logic to avoid fused mpi c++ and fortran flags that can undermine blt's mpi smoke test.

* **Blueprint**

 * Fixed missing build dependency relationship with the python conduit blueprint table examples module.
 * Fixed partitioner so it does not duplicate faces when combining polyhedral meshes.

Added
~~~~~


* **Relay**

 * Added polygonal support to Blueprint Silo I/O.


v0.9.0
---------------------------------

* Released 2024-02-04
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.9.0/conduit-v0.9.0-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **General**

 * Added ``conduit_json_external`` protocol. Creates a json schema representation of a node that includes all addresses that the node is pointing to. Parsing this schema will create a node equivalent to ``set_external()``.
 * Added a ``conduit_generate_data`` executable that can generate datasets using the ``tiled()`` and ``braid()`` functions and save the datasets to files.
 * Added helpers that support enhanced debugging of Conduit Node objects in several debuggers.
 * Added the ability to set values via a DataAccessor and DataAccessor to string methods.
 * Added explicit set methods to DataArray, and the ability to set DataArray values from a DataAccessor.

* **Relay**

 * Added extensive Mesh Blueprint Silo I/O support including, including options for Overlink Silo conventions. This capability allows Silo files to be used as a close peer to the Blueprint HDF5 I/O options.
 * Added ability to read N-dimensional hyperslabs from HDF5 leaf arrays into linear memory arrays.
 * Added ``conduit.relay.io.silo`` to the Python interface.

* **Blueprint**

 * Added a ``conduit::blueprint::mesh::examples::tiled()`` function that can generate meshes by repeating a tiled pattern.
 * Added a ``conduit::blueprint::mpi::mesh::utils::adjset::compare_pointwise()`` function that can compare adjsets for multi-domain meshes in parallel. The function is used to diagnose adjsets with points that are out of order on either side of the boundary. The comparison is done point by point within each group and it checks to ensure that the points reference the same spatial location.
 * Added a ``conduit::blueprint::mesh::utils::reorder()`` function that can accept a vector of element ids and create a reordered topology. The points and coordinates are re-ordered according to their first use in the new element ordering.
 * Added a ``conduit::blueprint::mesh::utils::topology::spatial_ordering()`` function that takes a topology and computes centroids for each element, passes them through a kdtree, and returns the new element ordering. The new ordering can be used with the ``reorder()`` function.
 * Added a ``conduit::blueprint::mesh::utils::topology::hilbert_ordering()`` function that computes a new order for a topology's elements based on their centroids and a Hilbert curve. The new ordering can be used with the ``reorder()`` function.
 * Added a ``conduit::blueprint::mesh::utils::slice_array()`` function that can slice Conduit nodes that contain arrays. A new node with the same type is created but it contains only the selected indices.
 * Added a ``conduit::blueprint::mesh::utils::slice_field()`` function. It is like ``slice_array()`` but it can handle the mcarray protocol. This functionality was generalized from the partitioner.
 * Added a ``conduit::blueprint::mesh::utils::topology::unstructured::rewrite_connectivity()`` function that will rewrite a topology's connectivity in terms of a different coordset. The PointQuery is used internally to search for equivalent coordinates in the new coordset.
 * Added a ``conduit::blueprint::mesh::utils::copy_fields()`` function that helps copy fields from one fields node to another.
 * Added a ``conduit::blueprint::mesh::utils::convert()`` function that converts a list of nodes to a desired data type.
 * Added a ``conduit::blueprint::mesh::generate_boundary_partition_field()`` function that can take a topology and a partition field and generate a field for a related boundary topology. This is helpful when partitioning a boundary topology in the same manner as its parent topology.
 * Added ``blueprint.mesh.examples.strided_structured`` to the blueprint python module.
 * Added ``conduit::blueprint::mesh::utils::adjset::to_topo()`` function to make new point mesh topologies for each group of an adjacency set. This permits each group to be visualized as a set of points in VisIt. The groups for each side of the domain interface can be compared since they are separate point meshes.
 * Added ``conduit::blueprint::mesh::utils::adjset::is_canonical()`` function to check whether the group names in an adjacency set are canonical.
 * Added more Mesh Blueprint docs.

Changed
~~~~~~~


* **General**

 * Conduit now requires C++14 and CMake 3.21 or newer.
 * Improved the efficiency of json parsing logic.
 * The ``conduit_relay_io_convert`` program was enhanced so it can read/write Blueprint root files by passing _"blueprint"_ for the read or write protocols.
 * The ``conduit_adjset_validate`` program now writes a point mesh for each adjset groups if the `-output` argument is supplied.
 * Updated to BLT 0.6.1
 * Updated Python logic hybrid module build logic to use pip and setuptools. Removed use of distutils.

* **Blueprint**

 * The ``conduit::blueprint::mpi::mesh::partition_map_back()`` function was enhanced so it accepts a "field_prefix" value in its options. The prefix is used when looking for the ``global_vertex_ids`` field, which could have been created with a prefix by the same option in the ``conduit::blueprint::mpi::mesh::generate_partition_field()`` function.
 * The ``conduit::blueprint::mesh::utils::ShapeType`` class was enhanced so it can take topologies other than unstructured.
 * The ``conduit::blueprint::mesh::utils::topology::unstructured::points()`` function was changed so it takes an optional argument that can turn off point uniqueness and sorting so the method can return points for an element as they appear in the connectivity, for non-polyhedral shapes.
 * Removed deprecated use of ``npts_z !=0`` for 2D shape types in ``conduit::blueprint::mesh::examples::{braid,basic,grid}``. These cases now issue a ``CONDUIT_ERROR``.
 * Removed ``volume_dependent`` entry in ``specsets``. Species ratios and mass fractions are innately volume independent.

* **Relay**

 * Relay Mesh Blueprint I/O methods (``conduit::relay::io::blueprint::{save,write}_mesh()````) now default to ``hdf5`` protocol if Conduit is built with ``hdf5`` support.

Fixed
~~~~~


* **General**

 * The Fortran ``node`` procedures for fetching integer pointers are now associated with the correct routines.

* **Blueprint**

 * The ``conduit::blueprint::mesh::partition()`` function no longer issues an error when it receives a "maxshare" adjset.
 * The partitioner is better about outputting a "material_map" node for matsets. The "material_map" node is optional for some varieties of matset but they can also help the ``conduit::blueprint::mesh::matset::to_silo()`` function generate the right material numbers when a domain does not contain all materials.
 * The ``conduit::Node::swap()`` and ``conduit::Node::move()`` functions no longer cause node names to disappear.
 * The ``conduit::blueprint::mesh::utils::kdtree`` could erroneously return that points were not found when one of the coordset dimensions had a very narrow range of values. This could happen with planar 2D geometries embedded in 3D, such as inside a ``MatchQuery`` during adjacency set creation.
 * The ``conduit::blueprint::mpi::mesh::generate_partition_field()`` function was not treating polyhedral topologies correctly, leading to unusable partitioning fields.
 * The point merging algorithm in the Blueprint partitioner was corrected so it should no longer produce occasional duplicate points when merging coordsets.


v0.8.8
---------------------------------

* Released 2023-05-18
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.8.8/conduit-v0.8.8-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


* **General**

 * Added Python 3 Stable ABI compatibility (Py_LIMITED_API) build support. Enabled by default when building against Python 3.11 or newer.
 * Added ``conduit_adjset_validate`` tool which can read root files for a multiple domain dataset and check whether the adjsets (vertex or element associations) in it are correct. Any errors are printed to the console.

* **Blueprint**

 * Added ``PointQuery`` class that can query points in a topology and return whether the query points hit a point in that topology's coordset. There are serial and parallel versions of this class. In parallel, the query domain may exist on a different MPI rank and the result will be communicated to the calling rank.
 * Added ``MatchQuery`` class that can be used to ask remote domains whether they contain an entity given using a set of point ids in the current rank's topology. The query builds up a query topology that it sends to the neighboring rank (if the query domain is not owned by the current MPI rank) and the topology is matched against the remote topology by matching points in the remote coordset. The results are returned to the calling MPI rank and can be retrieved using the query.
 * Added ``TopologyBuilder`` class that can be used to build up a new topology subset from a source topology. The new topology shape does not have to match the original topology shape. A new coordset is created based on the points that are referenced from the original topology.
 * Added ``topology::search`` function that allows one topology to be searched for in another topology. The topologies must have the same shape type and their respective coordsets can have points in different orders. The shapes are matched using coordinate matching.
 * Added ``adjset::validate`` function which tests adjacency sets for correctness and flags any errors in a Conduit node. There are serial and parallel versions of the function. The functions apply PointQuery for vertex association adjsets and MatchQuery for element association adjsets. Each domain's adjset will make queries to its neighboring domains as to whether the vertex or element of interest exists in the neighbor's topology.
 * Added ``utils::kdtree`` class that can be used to accelerate point lookups for coordsets.
 * Field selections for the ``conduit::blueprint::mesh::partition()`` function support a new ``destination_ranks`` property that contains a list of integers that map domain numbers to MPI ranks. This property tells the partitioner the ranks where it should place each domain. If the property is not supplied, the partitioner is free to place domains as before.

Fixed
~~~~~


* **General**

 * Added explicit control for OpenMP Features with CMake ``ENABLE_OPENMP`` option (default = OFF). Adds ``CONDUIT_USE_OPENMP`` define to ``conduit_config.h``. Guards all use of OpenMP with ``CONDUIT_USE_OPENMP``. Prior to these guards, downstream users could enable OpenMP and macros could evaluate inconsistently with how Conduit was built causing OpenMP related linking errors.

* **Blueprint**

 * Functions such as ``generate_corners`` or ``generate_faces`` that accept adjsets now include a filtering stage to improve adjset quality. This filtering stage uses ``PointQuery`` and ``MatchQuery`` to ensure that entities referenced in a remote domain actually exist in the neighboring domain.


v0.8.7
---------------------------------

* Released 2023-03-23
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.8.7/conduit-v0.8.7-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **General**

 * Added public default and copy constructor to DataAccessor. Enables more flexibility with initializing DataAccessors from Nodes.
 * Added Node.name(), Node.path(), Schema.name(), and Schema.path() to Python API.
 * Added Node.as_index_t_ptr()
 * Added ``conduit::execution`` namespace, which contains ``for_all()`` and ``sort()`` functions.
 * Added DataType support to the Fortran API

* **Blueprint**

 * Added ``conduit::blueprint::mpi::mesh::distribute``, which enables sending mesh domains to arbitrary MPI ranks (suppo
 * Added ``conduit::blueprint::mesh::utils::NDIndex`` class.  Instantiate with shape, offset, and stride in array or conduit::Node.  Get flatindex for N-D coordinates.
 * Added ``conduit::blueprint::o2mrelation::O2MIndex`` class.  Instantiate with O2M relation Node; get flatindex for a given one_index and many_index.  Alternative to Java-style iterator.
 * Added ``conduit::blueprint::examples::mesh::rz_cylinder`` function that generates example 2D cylindrical (RZ) meshes.

Fixed
~~~~~


* **General**

 * Fixed a logic issue undermining C++ type mapping when using CMake 3.26.

* **Blueprint**

 * Performance improvements to Mesh Blueprint topology metadata, used by ``generate_points``, ``generate_sides``, etc. The class was rewritten and the old one was moved to ``conduit::blueprint::mesh::utils::reference::TopologyMetadata``. The new implementation is faster, often about 6-20x depending on options.
 * Performance improvements to O2M Iterators.
 * Performance improvements to functions that underpin centroid generation.

* **Relay**

 * Fixed MPI baton logic error in ``conduit::relay::io::blueprint::save_mesh()`` that caused MPI tasks to serialize writes to files in the N domains to M files case. Fix restores parallel write performance. This bug did not impact cases where where N domains were written to N files (N to N) or N domains were written to a single file (N to 1).

Changed
~~~~~~~


* **General**

 * Changed diff of string types to respect null terminated strings instead of described length
 * Improved diff_compatible of string types to look for substring match, to implement expected compatible semantics.

* **Blueprint**

 * Changed the recommended axis order for 2D cylindrical meshes to be ``Z`` as the first axis, and ``R`` as the second. This choice aligns with expected visualization cases where ``Z`` varies with the horizontal axis and ``R`` varies with the vertical axis.

v0.8.6
---------------------------------

* Released 2023-01-11
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.8.6/conduit-v0.8.6-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **General**

 * Added C++ ``int DataType::sizeof_index_t()`` and C ``int conduit_datatype_sizeof_index_t()`` methods to provide a stable ABI to determine configured size (number of bytes) of Conduit's index_t type.

Fixed
~~~~~


* **General**

 * Build fixes for Conda Forge (mpi -fallow-argument-mismatch clang protection)

* **Relay**

 * Fixed a directory creation bug in ``relay::io::blueprint::{save_mesh|write_mesh}`` that occurred with sparse topologies with no domains on rank 0.
 * Fixed a bug in ``relay::io::blueprint::{save_mesh|write_mesh}`` with the ``suffix=cycle`` option that could cause int max to erroneously be used as the cycle number in the output directory.



v0.8.5
---------------------------------

* Released 2022-12-22
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.8.5/conduit-v0.8.5-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **General**

 * Added Node::move and Node::swap methods, which provide efficient ways to help build Node trees by consuming other Nodes.
 * Added Node::reset methods to C and Fortran interfaces.
 * Added initial optional support for Caliper performance annotations.
 * Added Python support for ``Node.set`` and ``Node.set_external`` with a schema and external buffer.

* **Blueprint**

 * Added support for Wedges and Pyramids.
 * Added helper function ``blueprint::mesh::generate_strip`` to generate a 2D "strip mesh" topology, and dependent other Blueprint mesh parts, from a 1D mesh.

Changed
~~~~~~~


* **General**

 * Changed ``Schema::has_path()`` (and transitively ``Node::has_path()`` ) to ignore leading ``/`` s.
 * Updated to BLT v0.5.2

* **Relay**

 * When using HDF5 1.10 or newer, default to use libver 1.8 when creating HDF5 files for wider read compatibly. This setting can be controlled via the hdf5 relay option ``libver``, accepted values: ``default``, ``none``, ``latest``, ``v108``, and ``v110``.

* **Relay**

 * Updated C++ and Python tutorial docs for Compatible Schemas with a new example to outline the most common use case.

Fixed
~~~~~


* **Blueprint**

 * Fixed bug with ``blueprint::mesh::examples::strided_structured`` so it correctly generates a coordset with padding
 * Fixes (correctness and performance) to ``topology::unstructured::generate_offsets``
 * Updated ``conduit.relay.io.blueprint.{load_mesh|read_mesh}`` to use improved logic to auto detect the format (hdf5 ,yaml, or json) of mesh blueprint root files.
 * Leading ``/`` s in mesh tree paths no longer undermine ``conduit.relay.io.blueprint.{load_mesh|read_mesh}`` reading json and yaml flavored files.
 * Fixed indexing and offsets in blueprint mixed element topology examples.

* **Relay**

 * Leading ``/`` s in tree paths no longer undermine io::IOHandle reads for conduit_bin, json, conduit_json, conduit_base64_json, and yaml flavored files.
 * Updated ``conduit.relay.io.blueprint.{load_mesh|read_mesh}`` to only the read the necessary subset of root file entries. Updated MPI version to only read root file entries on rank 0 and broadcast them to other ranks.
 * Fixed write compatibly check in ``relay::mpi::gather``, ``relay::mpi::all_gather``, and ``relay::mpi::broadcast_using_schema``. Node compatible check is not commutative and checks in leaf zero-copy logic were reversed.




v0.8.4
---------------------------------

* Released 2022-08-22
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.8.4/conduit-v0.8.4-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **General**

 * Added variants of ``Node::to_json``, ``Node::to_yaml``, and ``Node::to_string`` that take formatting options via a Conduit Node.
 * Added C API methods ``conduit_node_to_json``, ``conduit_node_to_yaml``, ``conduit_node_to_string``, and ``conduit_node_to_summary_string``.
 * Added ``DataArray::count`` method.
 * Added ``DataAccessor::{min,max,sum,mean,count}`` methods.
 * Added Schema and Python Buffer variants to Python ``Node.set()`` and ``Node.set_external()``.

* **Blueprint**

 * Added ``blueprint::mesh::paint_adjset``, which paints fields that encode adjacency set counts and ordering details.
 * Added ``blueprint::mesh::examples::strided_structured`` which creates a structured mesh with arbitrarily strided vertex and element fields.
 * Added support for mixed element topologies to the mesh blueprint.
 * Added ``blueprint::mesh::examples::braid`` examples with mixed element topologies (``mesh_type={"mixed", "mixed_2d"}``)
 * Added 1D mesh example support to ``blueprint::mesh::examples::basic()``.
 * Added adjacency set aware generate functions (``genearte_points()``, etc) to the non-mpi blueprint library.

* **Relay**

 * Added any source, any tag variants of mpi receive functions: ``recv``, ``recv_using_schema``, and ``irecv``.
 * Added subpath support for ``relay::io::{save,load,save_merged,load_merged}`` for basic protocols (json, yaml, etc).

Changed
~~~~~~~


* **Relay**

 * Changed HDF5 CMake sanity checks to issue ``WARNING`` instead of ``FATAL_ERROR``, since Cray system HDF5 installs do not always present the info we use for sanity checks.
 * Changed HDF5 version guards to also check requested HDF5 API.

Fixed
~~~~~


* **General**

 * Fixed bug with ``to_json()`` where leaf arrays of size 0 lead to malformed json.
 * Fixed parsing issue with ``conduit_json`` protocol for leaf arrays of size 0.
 * Fixed roundtrip parsing of numeric arrays with nan, infs, etc for JSON cases (``Node::to_json()`` followed by ``Node::parse(...,"json")``).

* **Blueprint**

 * Fixed a bug with ``blueprint::mesh::index::generate``, where a uniform grid with no origin would lead to invalid coordinate system name ``logical`` in the resulting index. This case now defaults to ``cartesian``.
 * Improved ``relay::io::blueprint::{save_mesh|write_mesh}`` blueprint index generation for cases where fields do not exist on all domains.
 * Fixed a bug that labeled internal faces as shared in generated adjsets.

* **Relay**

 * Fixed a bug with blueprint root file creation, where the ``file_pattern`` was not relative to the root file location
 * Fixed missing header include for relay io csv support.
 * Fixed a bug with relay mpi all reduce.



v0.8.3
---------------------------------

* Released 2022-04-14
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.8.3/conduit-v0.8.3-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **General**

 * Added C/C++ version macros ``CONDUIT_VERSION_MAJOR``, ``CONDUIT_VERSION_MINOR``, ``CONDUIT_VERSION_PATCH`` and these values as separate entries in ``conduit::about()`` to provide more support for compile time and runtime conduit version detection.

* **Blueprint**

 * Added ``blueprint::mesh::examples::polystar``, which creates a mesh with a polyhedral star pattern that demonstrates hanging vertices in a topology, along with its representations from ``generate_sides`` and ``generate_corners``.
 * Added ``blueprint::mesh::examples::related_boundary``, which creates a multi-domain mesh with a related boundary topology and several fileds that encode relationships between the main topology and the boundary.
 * Expanded ``blueprint::mpi::mesh::generate_partition_field`` to support all topology types.

Fixed
~~~~~


* **Blueprint**

 * Fixed a bug with ``conduit::blueprint::mesh::examples::braid``, where 2D cases for points and structured examples would create coordsets with all entries being zero.

Changed
~~~~~~~


* **General**

 * Improved pip install logic

* **Relay**

 * Added szip and zlib linking fix for older version of HDF5 (1.8.14)
 * Fixed a bug with ``relay::io::blueprint::write_mesh`` and ``relay::io::blueprint::save_mesh`` for the multi domain case, removing unintended ``:mesh`` file name suffix for json and yaml domain files.


v0.8.2
---------------------------------

* Released 2022-02-01
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.8.2/conduit-v0.8.2-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Fixed
~~~~~

* **Blueprint**

 * Fixed missing C++ include used by Blueprint Parmetis support.


v0.8.1
---------------------------------

* Released 2022-01-25
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.8.1/conduit-v0.8.1-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **General**

 * Added ``CONDUIT_DLL_DIR`` env var support on windows, for cases where Conduit DLLs are not installed directly inside the Python Module.

* **Blueprint**

 * Allow adjsets to be used in ``blueprint::mesh::partition`` to determine global vertex ids.
 * Added partial matset support to ``blueprint::mesh::partition`` and ``blueprint::mesh::combine``.

Fixed
~~~~~


* **General**

 * Fixed CMake bug with ``ENABLE_RELAY_WEBSERVER`` option.
 * Fixed build and test issues with Python >= 3.8  on Windows.

* **Blueprint**

 * Fixed a bug in ``blueprint::mesh::partition`` where adjsets could be missing in new domains.
 * Fixed a bug with ``blueprint::mesh::matset::to_silo`` and uni-buffer matsets.




v0.8.0
---------------------------------

* Released 2021-12-20
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.8.0/conduit-v0.8.0-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **General**

 * Added ``setup.py`` for building and installing Conduit and its Python module via pip
 * Added DataAccessor class that helps write generic algorithms that consume data arrays using expected types.
 * Added support to register custom memory allocators and a custom data movement handler. This allows conduit to move trees of data between heterogenous memory spaces (e.g. CPU and GPU memory). See conduit_utils.hpp for API details.

* **Blueprint**

 * Added ``conduit::blueprint::{mpi}::partition`` function that provides a general N-to-M partition capability for Blueprint Meshes. This helps with load balancing and other use cases, including fusing multi-domain data to simplifying post processing. This capability supports several options, see (https://llnl-conduit.readthedocs.io/en/latest/blueprint_mesh_partition.html) for more details.
 * Added a ``Table`` blueprint used to represent tables of numeric data. See (https://llnl-conduit.readthedocs.io/en/latest/blueprint_table.html) more details.
 * Added ``conduit::blueprint::{mpi}::flatten`` which transforms Blueprint Meshes into Blueprint Tables. This transforms Mesh Blueprint data into a form that is more easily digestible in machine learning applications.
 * Added ``conduit::blueprint::mpi::generate_partition_field``, which uses Parmetis to create a field that identifies how to load balance an input mesh elements.  This field can be used as a Field selection input to ``conduit::blueprint::mpi::partition`` function.
 * Added the``blueprint::mesh::examples::polychain`` example. It is an example of a polyhedral mesh. See Mesh Blueprint Examples docs (https://llnl-conduit.readthedocs.io/en/latest/blueprint_mesh.html#polychain) for more details.
 * Added a new function signature for ``blueprint::mesh::topology::unstructured::generate_sides``, which performs the same task as the original and also takes fields from the original topology and maps them onto the new topology.
 * Added ``blueprint::mpi::mesh::to_polygonal``, which provides a MPI aware conversion Blueprint Structured AMR meshes to a Blueprint Polyhedral meshes.
 * Added a host of ``conduit::blueprint::mpi::mesh::generate_*`` methods, which are the MPI parallel equivalents of the ``conduit::blueprint::mesh::topology::unstructured::generate_*`` functions.
 * Added the ``conduit::blueprint::mpi::mesh::find_delegate_domain`` function, which returns a single delegate domain for the given mesh across MPI ranks (useful when all ranks need mesh information and some ranks can have empty meshes).
 * Added check and transform functions for the newly-designated ``pairwise`` and ``maxshare`` variants of ``adjsets``. For more information, see the ``conduit::blueprint::mesh::adjset`` namespace.
 * Added ``mesh::topology::unstructured::to_polytopal`` as an alias to ``mesh::topology::unstructured::to_polygonal``, to reflect that both polygonal and polyhedral are supported.
 * Added ``conduit::blueprint::mpi::mesh::to_polytopal`` as an alias to ``conduit::blueprint::mpi::mesh::to_polygonal`` and ``conduit::blueprint::mpi::mesh::to_polyhedral``.

* **Relay**

 * Added ``conduit::relay::io::hdf5_identifier_report`` methods, which create conduit nodes that describes active hdf5 resource handles.

Changed
~~~~~~~


* **General**

 * Updated CMake logic to provide more robust Python detection and better support for HDF5 installs that were built with CMake.
 * Improved Node::diff and Node::diff_compatible to show string values when strings differ.
 * ``conduit::Node::print()`` and in Python Node ``repr`` and ``str`` now use ``to_summary_string()``. This reduces the output for large Nodes. Full output is still supported via ``to_string()``, ``to_yaml()``, etc methods.

* **Blueprint**

 * The ``blueprint::mesh::examples::polytess`` function now takes a new argument, called ``nz``, which allows it to be extended into 3 dimensions. See Mesh Blueprint Examples docs (https://llnl-conduit.readthedocs.io/en/latest/blueprint_mesh.html#polytess) for more details.
 * Added support for both ``const`` and non-``const`` inputs to the ``conduit::blueprint::mesh::domains`` function.
 * Improved mesh blueprint index generation logic (local and MPI) to support domains with different topos, fields, etc.
 * Deprecated accepting ``npts_z !=0`` for 2D shape types in ``conduit::blueprint::mesh::examples::{braid,basic,grid}``. They issue a ``CONDUIT_INFO`` message when this detected and future versions will issue a ``CONDUIT_ERROR``.
 * An empty Conduit Node is now considered a valid multi-domain mesh. This change was made to make serial uses cases better match sparse MPI multi-domain use cases. Existing code that relied ``mesh::verify`` to exclude empty Nodes will now need an extra check to see if an input mesh has data.
 * Added MPI communicator argument to ``conduit::blueprint::mpi::mesh::to_polygonal`` and ``conduit::blueprint::mpi::mesh::to_polyhedral``.

* **Relay**

 * Added CMake option (``ENABLE_RELAY_WEBSERVER``, default = ``ON``) to control if Conduit's Relay Web Server support is built. Down stream codes can check for support via header ifdef ``CONDUIT_RELAY_WEBSERVER_ENABLED`` or at runtime in ``conduit::relay::about``.
 * Added support to compile against HDF5 1.12.

Fixed
~~~~~


* **General**

 * Avoid compile issue with using ``_Pragma()`` with Python 3.8 on Windows
 * ``conduit_node`` and ``conduit_datatype`` in the C API are no longer aliases to ``void`` so that callers cannot pass just any pointer to the APIs.
 * Fixed memory over read issue with Fortran API due to int vs bool binding error. Fortran API still provides logical returns for methods like conduit_node_has_path() however the binding implementation now properly translates C_INT return codes into logical values.
 * Fixed a subtle bug with Node fetch and Object role initialization.

* **Blueprint**

 * Fixed a bug that was causing the ``conduit::blueprint::mesh::topology::unstructured::generate_*`` functions to produce bad results for polyhedral input topologies with heterogeneous elements (e.g. tets and hexs).
 * Fixed a bug with ``conduit::relay::io::blueprint::write_mesh`` that undermined ``truncate=true`` option for root-only style output.
 * Fixed options parsing bugs and improved error messages for the ``conduit_blueprint_verify`` exe.

* **Relay**

 * Changed HDF5 offset support to use 64-bit unsigned integers for offsets, strides, and sizes.
 * Fixed a bug with ``conduit::relay::mpi::io::blueprint::save_mesh`` where ``file_style=root_only`` could crash or truncate output files.
 * Fixed a bug with inconsistent HDF5 handles being used in some cases when converting existing HDF5 Datasets from fixed to extendable.


v0.7.2
---------------------------------

* Released 2021-05-19
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.7.2/conduit-v0.7.2-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **General**

 * Added the ``cpp_fort_and_py`` standalone example. It demos passing Conduit Nodes between C++, Fortran, and Python. See the related tutorial docs (https://llnl-conduit.readthedocs.io/en/latest/tutorial_cpp_fort_and_py.html) for more details.
 * Added  ``conduit::utils::info_handler()``, ``conduit::utils::warning_handler()``, and ``conduit::utils::error_handler()``  methods, which provide access to the currently registered info, warning, and error handlers.
 * Added DataType::index_t method. Creates a DataType instance that describes an ``index_t``, which is an alias to either ``int32``, or ``int 64`` controlled by the ``CONDUIT_INDEX_32`` compile time option.
 * Added several more methods to Python DataType interface
 * Removed duplicate install of CMake exported target files that served as a bridge for clients using old style paths.

Changed
~~~~~~~


* **General**

 * Updated to newer version of uberenv and changed to track spack fork https://github.com/alpine-dav/spack (branch: conduit/develop).
 * Updated to newer version of BLT to leverage CMake's FindMPI defined targets when using CMake 3.15 or newer.
 * Changed ``rapidjson`` namespace to ``conduit_rapidjson`` to avoid symbol collisions with other libraries using RapidJSON.

* **Blueprint**

 * The semantics of ``conduit::blueprint::mesh::verify`` changed. An empty conduit Node is now considered a valid multi-domain mesh with zero domains. If you always expect mesh data, you can add an additional check for empty to craft code that works for both the old and new verify semantics.

* **Relay**

 * Added Relay HDF5 support for reading and writing to an HDF5 dataset with offset.
 * Added ``conduit::relay::io::hdf5::read_info`` which allows you to obtain metadata from an HDF5 file.
 * Added configure error when conduit lacks MPI support and HDF5 has MPI support

Fixed
~~~~~


* **General**

 * Fixed missing implementation of DataType::is_index_t
 * Fixed issue with compiling t_h5z_zfp_smoke.cpp against an MPI-enabled HDF5.

* **Blueprint**

 * Fixed a bug that caused HDF5 reference paths to appear twice in Relay HDF5 Error messages.

* **Blueprint**

 * ``conduit::relay::io::blueprint.read_mesh`` now uses read only I/O handles.

v0.7.1
---------------------------------

* Released 2021-02-11
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.7.1/conduit-v0.7.1-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Fixed
~~~~~


* **General**

 * Fixed a bug with Conduit's C interface including C++ headers.

* **Blueprint**

 * Fixed a bug with ``blueprint::mesh::matset::to_silo`` and ``blueprint::mesh::field::to_silo`` that could modify input values.
 

v0.7.0
---------------------------------

* Released 2021-02-08
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.7.0/conduit-v0.7.0-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Changed
~~~~~~~


* **General**

 * Conduit now requires C++11 support.
 * Python Node repr string construction now uses ``Node.to_summary_string()``

Added
~~~~~

 * CMake: Added extra check for include dir vs fully resolved hdf5 path.

* **General**

 * Added a builtin sandboxed header-only version of fmt. The namespace and directory paths were changed to ``conduit_fmt`` to avoid potential symbol collisions with other codes using fmt. Downstream software can use by including ``conduit_fmt/conduit_fmt.h``.
 * Added support for using C++11 initializer lists to set Node and DataArray values from numeric arrays. See C++ tutorial docs (https://llnl-conduit.readthedocs.io/en/latest/tutorial_cpp_numeric.html#c-11-initializer-lists) for more details.
 * Added a Node::describe() method. This method creates a new node that mirrors the current Node, however each leaf is replaced by summary stats and a truncated display of the values. For use cases with large leaves, printing the describe() output Node is much more helpful for debugging and understanding vs wall of text from other to_string() methods.
 * Added conduit::utils::format methods. These methods use fmt to format strings that include fmt style patterns. The formatting arguments are passed as a conduit::Node tree. The ``args`` case allows named arguments (args passed as object) or ordered args (args passed as list). The ``maps`` case also supports named or ordered args and works in conjunction with a ``map_index``. The ``map_index`` is used to fetch a value from an array, or list of strings, which is then passed to fmt. The ``maps`` style of indexed indirection supports generating path strings for non-trivial domain partition mappings in Blueprint. This functionality is also available in Python, via the  ``conduit.utils.format`` method.
 * Added ``DataArray::fill`` method, which set all elements of a DataArray to a given value.
 * Added ``Node::to_summary_string`` methods, which allow you to create truncated strings that describe a node tree, control the max number of children and max number of elements shown.
 * Added python support for ``Node.to_summary_string``

* **Relay**

 * Added Relay IO Handle mode support for ``a`` (append) and ``t`` (truncate).  Truncate allows you to overwrite files when the handle is opened. The default is append, which preserves prior IO Handle behavior.
 * Added ``conduit::relay::io::blueprint::save_mesh`` variants, these overwrite existing files (providing relay save semantics) instead of adding mesh data to existing files. We recommend using  ``save_mesh`` for most uses cases, b/c in many cases ``write_mesh`` to an existing HDF5 file set can fail due to conflicts with the current HDF5 tree.
 * Added ``conduit::relay::io::blueprint::load_mesh`` variants, these reset the passed node before reading mesh data (providing relay load semantics). We recommend using  ``load_mesh`` for most uses cases.
 * Added ``truncate`` option to ``conduit::relay::io::blueprint::write_mesh``, this is used by ``save_mesh``.
 * Improve capture and reporting of I/O errors in ``conduit::relay::[mpi::]io::blueprint::{save_mesh|write_mesh}``. Now in the MPI case, If any rank fails to open or write to a file all ranks will throw an exception.
 * Added yaml detection support to ``conduit::relay::io:identify_file_type``.

* **Blueprint**

 * Added ``conduit::blueprint::mesh::matset::to_silo()`` which converts a valid blueprint matset to a node that contains arrays that follow Silo's sparse mix slot volume fraction representation.
 * Added ``conduit::blueprint::mesh::field::to_silo()`` which converts a valid blueprint field and matset to a node that contains arrays that follow Silo's sparse mix slot volume fraction representation.
 * Added ``material_map`` to ``conduit::blueprint::mesh:matset::index``, to provide an explicit material name to id mapping.
 * Added ``mat_check`` field to ``blueprint::mesh::examples::venn``. This field encodes the material info in a scalar field and in the ``matset_values`` in a way that can be used to easily compare and verify proper construction in other tools.

Fixed
~~~~~


* **Relay**

 * Fixed bug in the Relay IOHandle Basic that would create unnecessary "_json" schema files to be written to disk upon open().

Removed
~~~~~~~


* **General**

 * Removed ``Node::fetch_child`` and ``Schema::fetch_child`` methods for v0.7.0. (Deprecated in v0.6.0 -- prefer ``fetch_existing``)
 * Removed ``Schema::to_json`` method variants with ``detailed`` for v0.7.0. (Deprecated in v0.6.0 -- prefer standard ``to_json``)
 * Removed ``Schema::save`` method variant with ``detailed`` for v0.7.0. (Deprecated in v0.6.0 -- prefer standard ``save``)
 * The ``master`` branch was removed from GitHub (Deprecated in v0.6.0 -- replaced by the ``develop`` branch)

* **Relay**

 * Removed ``conduit::relay::io_blueprint::save`` methods for v0.7.0. (Deprecated in v0.6.0 -- prefer ``conduit::relay::io::blueprint::save_mesh``)


v0.6.0
---------------------------------

* Released 2020-11-02
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.6.0/conduit-v0.6.0-src-with-blt.tar.gz>`__

Highlights
++++++++++++++++++++++++++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)


Added
~~~~~


* **General**

 * Added support for children with names that include ``/``. Since slashes are part of Conduit's hierarchical path mechanism, you must use explicit methods (add_child(), child(), etc) to create and access children with these types of names. These names are also supported in all basic i/o cases (JSON, YAML, Conduit Binary).
 * Added Node::child and Schema::child methods, which provide access to existing children by name.
 * Added Node::fetch_existing and Schema::fetch_existing methods, which provide access to existing paths or error when given a bad path.
 * Added Node::add_child() and Node::remove_child() to support direct operations and cases where names have ``/`` s.
 * Added a set of conduit::utils::log::remove_* filtering functions, which process conduit log/info nodes and strip out the requested information (useful for focusing the often verbose output in log/info nodes).
 * Added to_string() and to_string_default() methods to Node, Schema, DataType, and DataArray. These methods alias either to_yaml() or to_json(). Long term yaml will be preferred over json.
 * Added helper script (scripts/regen_docs_outputs.py) that regenerates all example outputs used Conduit's Sphinx docs.
 * Added to_yaml() and to_yaml_stream methods() to Schema, DataType, and DataArray.
 * Added support for C++-style iterators on node children. You can now do ``for (Node &node : node.children()) {}``. You can also do ``node.children.begin()`` and ``node.children.end()`` to work with the iterators directly.

* **Relay**

 * Added an open mode option to Relay IOHandle. See Relay IOHandle docs (https://llnl-conduit.readthedocs.io/en/latest/relay_io.html#relay-i-o-handle-interface) for more details.
 * Added the conduit.relay.mpi Python module to support Relay MPI in Python.
 * Added support to write and read Conduit lists to HDF5 files. Since HDF5 Groups do not support unnamed indexed children, each list child is written using a string name that represents its index and a special attribute is written to the HDF5 group to mark the list case. On read, the special attribute is used to detect and read this style of group back into a Conduit list.
 * Added preliminary support to read Sidre Datastore-style HDF5 using Relay IOHandle,  those grouped with a root file.
 * Added ``conduit::relay::io::blueprint::read_mesh`` functions, were pulled in from Ascent's Blueprint import logic.
 * Added ``conduit::relay::mpi::wait`` and ``conduit::relay::mpi::wait_all`` functions. These functions consolidate the logic supporting both ``isend`` and ``irecv`` requests. ``wait_all`` supports cases where both sends and receives were posted, which is a common for non-trivial point-to-point communication use cases.

* **Blueprint**

 * Added support for sparse one-to-many relationships with the new ``blueprint::o2mrelation`` protocol. See the ``blueprint::o2mrelation::examples::uniform`` example for details.
 * Added sparse one-to-many, uni-buffer, and material-dominant specification support to Material sets. See the Material sets documentation
 * Added support for Adjacency sets for Structured Mesh Topologies. See the ``blueprint::mesh::examples::adjset_uniform`` example.
 * Added ``blueprint::mesh::examples::julia_nestsets_simple`` and ``blueprint::mesh::examples::julia_nestsets_complex`` examples represent Julia set fractals using patch-based AMR meshes and the Mesh Blueprint Nesting Set protocol. See the Julia AMR Blueprint docs
 * Added ``blueprint::mesh::examples::venn`` example that demonstrates different ways to encode volume fraction based multi-material fields.  See the Venn Blueprint docs
 * Added ``blueprint::mesh::number_of_domains`` property method for trees that conform to the mesh blueprint.
 * Added MPI mesh blueprint methods, ``blueprint::mpi::mesh::verify`` and  ``blueprint::mpi::mesh::number_of_domains`` (available in the ``conduit_blueprint_mpi`` library)
 * Added ``blueprint::mpi::mesh::examples::braid_uniform_multi_domain`` and ``blueprint::mpi::mesh::examples::spiral_round_robin`` distributed-memory mesh examples to the ``conduit_blueprint_mpi`` library.
 * Added ``state/path`` to the Mesh Blueprint index, needed for consumers to know the proper path to read extended state info (such as ``domain_id``)

Fixed
~~~~~


* **General**

 * Updated to newer BLT to resolve BLT/FindMPI issues with rpath linking commands when using OpenMPI.
 * Fixed internal object name string for the Python Iterator object. It used to report ``Schema``, which triggered both puzzling and concerned emotions.
 * Fixed a bug with ``Node.set`` in the Python API that undermined setting NumPy arrays with sliced views and complex striding. General slices should now work with ``set``. No changes to the ``set_external`` case, which requires 1-D effective striding and throws an exception when more complex strides are presented.
 * Fixed a bug with auto detect of protocol for Node.load
 * Fixed bugs with auto detect of protocol for Node.load and Node.save in the Python interface

* **Relay**

 * Use H5F_ACC_RDONLY in relay::io::is_hdf5_file to avoid errors when checking files that already have open HDF5 handles.
 * Fixed compatibility check for empty Nodes against HDF5 files with existing paths

Changed
~~~~~~~


* **General**

 * Conduit's main git branch was renamed from ``master`` to ``develop``. To allow time for folks to migrate, the ``master`` branch is active but frozen and will be removed during the ``0.7.0`` release.
 * We recommend a C++11 (or newer) compiler, support for older C++ standards is deprecated and will be removed in a future release.
 * Node::fetch_child and Schema::fetch_child are deprecated in favor of the more clearly named Node::fetch_existing and Schema::fetch_existing. fetch_child variants still exist, but will be removed in a future release.
 * Python str() methods for Node, Schema, and DataType now use their new to_string() methods.
 * DataArray<T>::to_json(std::ostring &) is deprecated in favor DataArray<T>::to_json_stream. to_json(std::ostring &) will be removed in a future release.
 * Schema::to_json and Schema::save variants with detailed (bool) arg are deprecated. The detailed arg was never used. These methods will be removed in a future release.
 * Node::print() now prints yaml instead of json.
 * The string return variants of ``about`` methods now return yaml strings instead of json strings.
 * Sphinx Docs code examples and outputs are now included using start-after and end-before style includes.
 * Schema to_json() and to_json_stream() methods were expanded to support indent, depth, pad and end-of-element args.
 * In Python, conduit.Node() repr now returns the YAML string representation of the Node. Perviously verbose ``conduit_json`` was used, which was overwhelming.
 * conduit.about() now reports the git tag if found, and ``version`` was changed to add git sha and status (dirty) info to avoid confusion between release and development installs.

* **Relay**

 * Provide more context when a Conduit Node cannot be written to a HDF5 file because it is incompatible with the existing HDF5 tree. Error messages now provide the full path and details about the incompatibility.
 * ``conduit::relay::io_blueprint::save`` functions are deprecated in favor of ``conduit::relay::io::blueprint::write_mesh``
 * ``conduit::relay::io::blueprint::write_mesh`` functions were pulled in from Ascent's Blueprint export logic.
 * ``conduit_relay_io_mpi`` lib now depends on ``conduit_relay_io``. Due to this change, a single build supports either ADIOS serial (no-mpi) or ADIOS with MPI support, but not both. If conduit is configured with MPI support, ADIOS MPI is used.
 * The functions ``conduit::relay::mpi::wait_send`` and ``conduit::relay::mpi::wait_recv`` now use ``conduit::relay::mpi::wait``. The functions ``wait_send`` and ``wait_recv`` exist to preserve the old API, there is no benefit to use them over ``wait``.
 * The functions ``conduit::relay::mpi::wait_all_send`` and ``conduit::relay::mpi::wait_all_recv`` now use ``conduit::relay::mpi::wait_all``. The functions ``wait_all_send`` and ``wait_all_recv`` exist to preserve the old API, there is no benefit to use them over ``wait_all``.

* **Blueprint**

 * Refactored the Polygonal and Polyhedral mesh blueprint specification to leverage one-to-many concepts and to allow more zero-copy use cases.
 * The ``conduit_blueprint_mpi`` library now depends on ``conduit_relay_mpi``.
 * The optional Mesh Blueprint structured topology logical element origin is now specified using ``{i,j,k}`` instead of ``{i0,j0,k0}``.


v0.5.1
-----------------

* Released 2020-01-18
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.5.1/conduit-v0.5.1-src-with-blt.tar.gz>`__

Highlights
+++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)

Added
~~~~~~~~~

* **General**

 * Added Node::parse() method, (C++, Python and Fortran) which supports common json and yaml parsing use cases without creating a generator instance.
 * Use FOLDER target property to group targets for Visual Studio
 * Added Node load(), and save() support to the C and Fortran APIs

Changed
~~~~~~~~~

* **General**

 * Node::load() and Node::save() now auto detect which protocol to use when protocol argument is an empty string
 * Changed Node::load() and Node::save() default protocol value to empty (default now is to auto detect)
 * Changed Python linking strategy to defer linking for our compiler modules
 * Conduit Error Exception message strings now print cleaner (avoiding nesting doll string escaping headaches)
 * Build system improvements to support conda-forge builds for Linux, macOS, and Windows

Fixed
~~~~~~~~~

* **General**

 * Fixed install paths for CMake exported target files to follow standard CMake find_package() search conventions. Also perserved duplicate files to support old import path structure for this release.
 * python: Fixed Node.set_external() to accept conduit nodes as well as numpy arrays
 * Fixed dll install locations for Windows


v0.5.0
-----------------

* Released 2019-10-25
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.5.0/conduit-v0.5.0-src-with-blt.tar.gz>`__

Highlights
+++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)

Added
~~~~~~~~~

* **General**

 *  Added support to parse YAML into Conduit Nodes and to create YAML from Conduit Nodes. Support closely follows the "json" protocol, making similar choices related to promoting YAML string leaves to concrete data types.
 * Added several more Conduit Node methods to the C and Fortran APIs. Additions are enumerated here:  https://github.com/LLNL/conduit/pull/426
 * Added Node set support for Python Tuples and Lists with numeric and string entires
 * Added Node set support for Numpy String Arrays. String Arrays become Conduit lists with child char8_str arrays


* **Blueprint**

 * Added support for a "zfparray" blueprint that holds ZFP compressed array data. 
 * Added the the "specsets" top-level section to the Blueprint schema, which can be used to represent multi-dimensional per-material quantities (most commonly per-material atomic composition fractions).
 * Added explicit topological data generation functions for points, lines, and faces
 * Added derived topology generation functions for element centroids, sides, and corners
 * Added the basic example function to the conduit.mesh.blueprint.examples module

* **Relay**

 * Added optional ZFP support to relay, that enables wrapping and unwraping zfp arrays into conduit Nodes. 
 * Extended relay HDF5 I/O support to read a wider range of HDF5 string representations including H5T_VARIABLE strings.

Changed
~~~~~~~~~

* **General**

 * Conduit's automatic build process (uberenv + spack) now defaults to using Python 3
 * Improved CMake export logic to make it easier to find and use Conduit install in a CMake-based build system. (See using-with-cmake example for new recipe)

* **Relay**

 * Added is_open() method to IOHandle in the C++ and Python interfaces
 * Added file name information to Relay HDF5 error messages


Fixed
~~~~~~~~~

* **General**

 * Fixed bug that caused memory access after free during Node destruction

* **Relay**

 * Fixed crash with mpi broadcast_using_schema() when receiving tasks pass a non empty Node.
 * Fixed a few Windows API export issues for relay io


v0.4.0
-----------------

* Released 2019-03-01
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.4.0/conduit-v0.4.0-src-with-blt.tar.gz>`__

Highlights
+++++++++++++

(Extracted from Conduit's :download:`Changelog <../../../CHANGELOG.md>`)

Added
~~~~~~~~~~~~~~~

* **General**

 * Added Generic IO Handle class (relay::io::IOHandle) with C++ and Python APIs, tests, and docs.
 * Added ``rename_child`` method to Schema and Node 
 * Added generation and install of conduit_config.mk for using-with-make example
 * Added datatype helpers for long long and long double
 * Added error for empty path fetch
 * Added C functions for setting error, warning, info handlers. 
 * Added limited set of C bindings for DataType
 * Added C bindings for relay IO
 * Added several more functions to conduit node python interfaces

* **Blueprint**

 * Added implicit point topology docs and example
 * Added julia and spiral mesh bp examples
 * Added mesh topology transformations to blueprint
 * Added polygonal mesh support to mesh blueprint
 * Added verify method for mesh blueprint nestset

* **Relay**

 * Added ADIOS Support, enabling ADIOS read and write of Node objects.
 * Added a relay::mpi::io library that mirrors the API of relay::io, except  that all functions take an MPI communicator. The functions are implemented in parallel for the ADIOS protocol. For other protocols, they will behave the same as the serial functions in relay::io. For the ADIOS protocol, the save() and save_merged() functions operate collectively within a communicator to enable multiple MPI ranks to save data to a single file as separate "domains".
 * Added an add_time_step() function to that lets the caller append data collectively to an existing  ADIOS file
 * Added a function to query the number of time steps and the number of domains in a  ADIOS file.
 * Added versions of save and save_merged that take an options node. 
 * Added C API for new save, save_merged functions.
 * Added method to list an HDF5 group's child names
 * Added save and append methods to the HDF5 I/O interface
 * Added docs and examples for relay io


Changed
~~~~~~~~~~~~~

* **General**

 * Changed mapping of c types to bit-width style to be compatible with C++11 std bit-width types when C++11 is enabled
 * Several improvements to uberenv, our automated build process, and building directions
 * Upgraded the type system with more explicit signed support


* **Relay**

 * Improvements to the Silo mesh writer
 * Refactor to support both relay::io and relay::mpi::io namespaces. 
 * Refactor to add support for steps and domains to I/O interfaces
 * Changed to only use ``libver latest`` setting for for hdf5 1.8 to minimize compatibility issues 

Fixed
~~~~~~~~~~~~~

* **General**

 * Fixed bugs with std::vector gap methods
 * Fixed A few C function names in conduit_node.h 
 * Fixed bug in python that was requesting unsigned array for signed cases
 * Fixed issue with Node::diff failing for string data with offsets
 * Fixes for building on BlueOS with the xl compiler

* **Blueprint**

 * Fixed validity status for blueprint functions
 * Fixed improper error reporting for Blueprint references


* **Relay**

 * Relay I/O exceptions are now forwarded to python  
 * Fixed MPI send_with_schema bug when data was compact but not contiguous  
 * Switched to use MPI bit-width style data type enums in ``relay::mpi``

 
v0.3.1
-----------------

* Released 2018-02-26
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.3.1/conduit-v0.3.1-src-with-blt.tar.gz>`__


Highlights
+++++++++++++

* **General**
 
 * Added new ``Node::diff`` and ``Node::diff_compatible`` methods
 * Updated uberenv to use a newer spack and removed several custom packages
 * C++ ``Node::set`` methods now take const pointers for data
 * Added Python version of basic tutorial
 * Expanded the Node Python Capsule API
 * Added Python API bug fixes
 * Fixed API exports for static libs on Windows

* **Blueprint**
 
 * Mesh Protocol
 
   * Removed unnecessary state member in the braid example
 
 * Added Multi-level Array Protocol (conduit::blueprint::mlarray)

* **Relay**
 
 * Added bug fixes for Relay HDF5 support on Windows
 

v0.3.0
-----------------

* Released 2017-08-21
* `Source Tarball <https://github.com/LLNL/conduit/releases/download/v0.3.0/conduit-v0.3.0-src-with-blt.tar.gz>`__

Highlights
+++++++++++++

* **General**

 * Moved to use BLT (https://github.com/llnl/blt) as our core CMake-based build system
 * Bug fixes to support building on Visual Studio 2013
 * Bug fixes for ``conduit::Node`` in the List Role
 * Expose more of the Conduit API in Python
 * Use ints instead of bools in the Conduit C-APIs for wider compiler compatibility   
 * Fixed memory leaks in *conduit* and *conduit_relay*
 

* **Blueprint**

 * Mesh Protocol
 
   * Added support for multi-material fields via *matsets* (volume fractions and per-material values)
   * Added initial support for domain boundary info via *adjsets* for distributed-memory unstructured meshes  
  

* **Relay**

 * Major improvements *conduit_relay* I/O HDF5 support 
 
   * Add heuristics with knobs for controlling use of HDF5 compact datasets and compression support
   * Improved error checking and error messages 
   
 * Major improvements to *conduit_relay_mpi* support 
 
   * Add support for reductions and broadcast
   * Add support zero-copy pass to MPI for a wide set of calls
   * Harden notion of `known schema` vs `generic` MPI support
 

v0.2.1
-----------------

* Released 2017-01-06
* `Source Tarball <https://github.com/LLNL/conduit/archive/v0.2.1.tar.gz>`__


Highlights
+++++++++++++

* **General**

 * Added fixes to support static builds on BGQ using xlc and gcc
 * Fixed missing install of fortran module files
 * Eliminated separate fortran libs by moving fortran symbols into their associated main libs
 * Changed ``Node::set_external`` to support const Node references
 * Refactored path and file systems utils functions for clarity.

* **Blueprint**

 * Fixed bug with verify of mesh/coords for rectilinear case
 * Added support to the blueprint python module for the mesh and mcarray protocol methods 
 * Added stand alone blueprint verify executable

* **Relay**

 * Updated the version of civetweb used to avoid dlopen issues with SSL for static builds


v0.2.0
-----------------

* Released 2016-11-03
* `Source Tarball <https://github.com/LLNL/conduit/archive/v0.2.0.tar.gz>`__
    
Highlights 
+++++++++++++
* **General**

 * Changes to clarify concepts in the ``conduit::Node`` API
 * Added const access to ``conduit::Node`` children and a new ``NodeConstIterator``
 * Added support for building on Windows
 * Added more Python, C, and Fortran API support
 * Resolved several bugs across libraries
 * Resolved compiler warnings and memory leaks
 * Improved unit test coverage
 * Renamed source and header files for clarity and to avoid potential conflicts with other projects

* **Blueprint**
    
 * Added verify support for the mcarray and mesh protocols
 * Added functions that create examples instances of mcarrays and meshes
 * Added memory layout transform helpers for mcarrays
 * Added a helper that creates a mesh blueprint index from a valid mesh

* **Relay**

 * Added extensive HDF5 I/O support for reading and writing between HDF5 files and conduit Node trees
 * Changed I/O protocol string names for clarity
 * Refactored the ``relay::WebServer`` and the Conduit Node Viewer application
 * Added entangle, a python script ssh tunneling solution

v0.1.0
-----------------

* Released 2016-03-30
* Initial Open Source Release on GitHub
* `Source Tarball <https://github.com/LLNL/conduit/archive/v0.1.0.tar.gz>`__


