.. _lbl_print_image_meta_data_dictionary:

Read Image Meta-Data Dictionary and Print
=========================================

Overview
--------

This example illustrates how to read only an image's information and meta-data dictionary without loading the pixel content via the `ImageFileReader <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageFileReader.html>`_.

Reading an entire image potentially is memory and time intensive operation when the image is large or many files must be read. The image information and meta-data dictionary can be read without the bulk data by using the ImageFilerReader's object oriented interface, with use of the ImageFileReader::ReadImageInformation method.

While all file formats support loading image information such as size, pixel type, origin, and spacing many image types do not have a meta-data dictionary. The most common case for images with a dictionary is DICOM, but also the fields from TIFF, NIFTI, MetaIO and other file formats maybe loaded into the meta-data dictionary.

For efficiency, the default DICOM reader settings will only load public tags (even group numbers). In the example we explicitly set the reader to also load private tags (odd group numbers). For further information on DICOM data elements see the standard part 5, `Data Structures and Encoding <http://dicom.nema.org/medical/dicom/current/output/pdf/part05.pdf>`_.

See also :ref:`lbl_dicom_series_read_modify_write`, :ref:`lbl_dicom_series_reader`.

Sample Output
-------------
Running the above Python script with the image  "docs/images/Image0075.dcm" produces the following output:

.. collapse:: DICOM Output (click triangle to collapse)
    :open:

    .. exec_code::

        # --- hide: start ---
        from example_utils import run_example
        args = ['../images/Image0075.dcm']
        run_example('DicomImagePrintTags', 'main', args)
        # --- hide: stop ---

Code
----

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/DicomImagePrintTags/DicomImagePrintTags.cs
       :language: csharp
       :lines: 22-

  .. tab:: C++

    .. literalinclude:: ../../Examples/DicomImagePrintTags/DicomImagePrintTags.cxx
       :language: c++
       :lines: 22-

  .. tab:: Java

    .. literalinclude:: ../../Examples/DicomImagePrintTags/DicomImagePrintTags.java
       :language: java
       :lines: 23-

  .. tab:: Python

    .. literalinclude:: ../../Examples/DicomImagePrintTags/DicomImagePrintTags.py
       :language: python
       :lines: 22-44

  .. tab:: R

    .. literalinclude:: ../../Examples/DicomImagePrintTags/DicomImagePrintTags.R
       :language: r
       :lines: 18-
