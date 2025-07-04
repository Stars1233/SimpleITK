/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/

// Get and Set Buffer of SimpleITK Image

using System;
using System.Runtime.InteropServices;

using SitkImage = itk.simple.Image;
using PixelId = itk.simple.PixelIDValueEnum;

namespace itk.simple.examples
{
    public class Program
    {
        static void Main(string[] args)
        {

            if (args.Length < 1)
            {
                Console.WriteLine("Usage: inputImage outputImage");
                return;
            }

            string inputFilename = args[0];
            string outputFilename = args[1];

            // Read input image
            SitkImage input = SimpleITK.ReadImage(inputFilename);

            // Cast so we know the the pixel type
            input = SimpleITK.Cast(input, PixelId.sitkFloat32);

            // calculate the number of pixels
            VectorUInt32 size = input.GetSize();
            int len = 1;
            for (int dim = 0; dim < input.GetDimension(); dim++)
            {
                len *= (int)size[dim];
            }
            IntPtr buffer = input.GetBufferAsFloat();

            // There are two ways to access the buffer:

            // (1) Access the underlying buffer as a pointer in an "unsafe" block
            // (note that in C# "unsafe" simply means that the compiler can not
            // perform full type checking), and requires the -unsafe compiler flag
            // unsafe {
            //   float* bufferPtr = (float*)buffer.ToPointer();

            //   // Now the byte pointer can be accessed as per Brad's email
            //   // (of course this example is only a 2d single channel image):
            //   // This is a 1-D array but can be access as a 3-D. Given an
            //   // image of size [xS,yS,zS], you can access the image at
            //   // index [x,y,z] as you wish by image[x+y*xS+z*xS*yS],
            //   // so x is the fastest axis and z is the slowest.
            //   for (int j = 0; j < size[1]; j++) {
            //     for (int i = 0; i < size[0]; i++) {
            //       float pixel = bufferPtr[i + j*size[1]];
            //       // Do something with pixel here
            //     }
            //   }
            // }

            // (2) Copy the buffer to a "safe" array (i.e. a fully typed array)
            // (note that this means memory is duplicated)
            float[] bufferAsArray = new float[len]; // Allocates new memory the size of input
            Marshal.Copy(buffer, bufferAsArray, 0, len);
            double total = 0.0;
            for (int j = 0; j < size[1]; j++)
            {
                for (int i = 0; i < size[0]; i++)
                {
                    float pixel = bufferAsArray[i + j * size[1]];
                    total += pixel;
                }
            }
            Console.WriteLine("Pixel value total: {0}", total);

            // Set buffer of new SimpleITK Image from managed array.
            // bufferAsArray could also have come from a BMP,PNG,etc...

            uint width = input.GetWidth();
            uint height = input.GetHeight();

            SitkImage outImage = new SitkImage(width, height, PixelId.sitkFloat32);
            IntPtr outImageBuffer = outImage.GetBufferAsFloat();

            Marshal.Copy(bufferAsArray, 0, outImageBuffer, (int)(size[0] * size[1]));

            //
            // Write out the resulting file
            //
            outImage = SimpleITK.RescaleIntensity(outImage, 0, 255);
            outImage = SimpleITK.Cast(outImage, PixelId.sitkUInt8);

            SimpleITK.WriteImage(outImage, outputFilename);


        }
    }
}
