#include <iostream>
#include "itkImageFileReader.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkImageFileWriter.h"

int main(int, char*[])
{
	typedef itk::Image< float, 3 > ImageType;
	typedef itk::ImageFileReader<ImageType> ReadType;
	ReadType::Pointer reader = ReadType::New();
	reader->SetFileName("WXK_PCA.mhd");
	reader->Update();//读图

	typedef itk::BinaryThresholdImageFilter<ImageType, ImageType> FilterType;
	FilterType::Pointer filter = FilterType::New();
	filter->SetInput(reader->GetOutput());
	filter->SetOutsideValue(0);
	filter->SetInsideValue(255);
	filter->SetLowerThreshold(40);
	filter->SetUpperThreshold(255);
	filter->Update();//门限分割 下限40 上限255

	ImageType::Pointer image = filter->GetOutput();
	ImageType::IndexType PixIndex;
	int x = image->GetLargestPossibleRegion().GetSize()[0];
    int y = image->GetLargestPossibleRegion().GetSize()[1];
    int z = image->GetLargestPossibleRegion().GetSize()[2];
	typedef itk::Image< unsigned char, 2> ImageFinalType;
	ImageFinalType::Pointer imagetotal = ImageFinalType::New();
	const ImageFinalType::SizeType size = { { 400, 330 } };
	const ImageFinalType::IndexType start = { { 0, 0 } };
	ImageFinalType::RegionType region;
	region.SetSize(size);
	region.SetIndex(start);
	imagetotal->SetRegions(region);
	imagetotal->Allocate(true);
	ImageFinalType::IndexType Index;
	for (PixIndex[0] = 0, Index[0] = 0;PixIndex[0] < x;PixIndex[0]++, Index[0]++)
	{
		for (PixIndex[2] = 0, Index[1] = 0;PixIndex[2] < z;PixIndex[2]++, Index[1]++)
		{
			ImageFinalType::PixelType  Value = imagetotal->GetPixel(Index);
			for (PixIndex[1] = 0;PixIndex[1] < y;PixIndex[1]++)
			{
				ImageType::PixelType pixelValue = image->GetPixel(PixIndex);
				if (pixelValue > Value)
				{
					imagetotal->SetPixel(Index, pixelValue);
				}

			}

		}
	}//MIP

	typedef itk::ImageFileWriter<ImageFinalType> WriteType;
	WriteType::Pointer writer = WriteType::New();
	writer->SetInput(imagetotal);
	writer->SetFileName("ITK.jpg");
	writer->Update();
	return 0;
}