.. _lbl_dicom_series_read_modify_write:

Dicom Series Read Modify Write
==============================

Overview
--------
This example illustrates how to read a DICOM series, modify the 3D image, and then write the result as a DICOM series.

Reading the DICOM series is a three step process: first obtain the series ID, then obtain the file names associated with the series ID, and finally use the series reader to read the images. By default the DICOM meta-data dictionary for each of the slices is not read. In this example we configure the series reader to load the meta-data dictionary including all of the private tags.

Modifying the 3D image can involve changes to its physical characteristics (spacing, direction cosines) and its intensities. In our case we only modify the intensities by blurring the image.

Writing the 3D image as a DICOM series is done by configuring the meta-data dictionary for each of the slices and then writing it in DICOM format. In our case we copy some of the meta-data from the original dictionaries which are available from the series reader. We then set some additional meta-data values to indicate that this series is derived from the original acquired data. Note that we write the intensity values as is and thus do not set the rescale slope (0028|1053), rescale intercept (0028|1052) meta-data dictionary values.

Always represent DICOM tags using lower case hexadecimals. DICOM tags represent hexadecimal numbers, so 0020|000D and 0020|000d are equivalent. The ITK/SimpleITK dictionary is string based, so these are two different keys, case sensitive. When read from a DICOM file the hexadecimal string representations are in lower case. To ensure consistency, always use lower case for the tags.


See also :ref:`lbl_print_image_meta_data_dictionary`, :ref:`lbl_dicom_series_reader`.


Code
----

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/DicomSeriesReadModifyWrite/DicomSeriesReadModifySeriesWrite.cs
       :language: csharp
       :lines: 24-

  .. tab:: C++

    .. literalinclude:: ../../Examples/DicomSeriesReadModifyWrite/DicomSeriesReadModifySeriesWrite.cxx
       :language: c++
       :lines: 24-

  .. tab:: Java

    .. literalinclude:: ../../Examples/DicomSeriesReadModifyWrite/DicomSeriesReadModifySeriesWrite.java
       :language: java
       :lines: 24-

  .. tab:: Python

    .. literalinclude:: ../../Examples/DicomSeriesReadModifyWrite/DicomSeriesReadModifySeriesWrite.py
       :language: python
       :lines: 22-

  .. tab:: R

    .. literalinclude:: ../../Examples/DicomSeriesReadModifyWrite/DicomSeriesReadModifySeriesWrite.R
       :language: r
       :lines:  18-
