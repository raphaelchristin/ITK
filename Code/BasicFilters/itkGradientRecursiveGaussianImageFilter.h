/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkGradientRecursiveGaussianImageFilter.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkGradientRecursiveGaussianImageFilter_h
#define __itkGradientRecursiveGaussianImageFilter_h

#include "itkRecursiveGaussianImageFilter.h"
#include "itkNthElementImageAdaptor.h"
#include "itkImage.h"

namespace itk
{

/** \class GradientRecursiveGaussianImageFilter
 * \brief Computes the gradient of an image by convolution
 *        with the first derivative of a Gaussian.
 * 
 * This filter is implemented using the recursive gaussian
 * filters
 *
 * 
 * \ingroup GradientFilters   
 * \ingroup Singlethreaded
 */
template <typename TInputImage, 
          typename TOutputImage=
              Image< CovariantVector< 
                      typename NumericTraits<typename TInputImage::PixelType>::RealType,
                      ExtractImageDimension<TInputImage>::ImageDimension >,
                          ExtractImageDimension<TInputImage>::ImageDimension > >
class ITK_EXPORT GradientRecursiveGaussianImageFilter:
  public ImageToImageFilter<TInputImage,TOutputImage>
{
public:
  /** Standard class typedefs. */
  typedef GradientRecursiveGaussianImageFilter  Self;
  typedef ImageToImageFilter<TInputImage,TOutputImage> Superclass;
  typedef SmartPointer<Self>                   Pointer;
  typedef SmartPointer<const Self>        ConstPointer;
  
  
  /**  Output Image Nth Element Adaptor
   *  This adaptor allows to use conventional scalar 
   *  smoothing filters to compute each one of the 
   *  components of the gradient image pixels. */
  typedef NthElementImageAdaptor< TOutputImage,
                                  typename TInputImage::PixelType >  
                                                OutputImageAdaptorType;
  typedef typename OutputImageAdaptorType::Pointer OutputImageAdaptorPointer;

  /**  Smoothing filter type */
  typedef RecursiveGaussianImageFilter<
                                  TInputImage,
                                  TInputImage
                                  >    GaussianFilterType;

  /**  Pointer to a gaussian filter.  */
  typedef typename GaussianFilterType::Pointer   GaussianFilterPointer;
  /**  Pointer to the Output Image */
  typedef typename TOutputImage::Pointer          OutputImagePointer;                                  
  /** Image dimension. */
  enum { ImageDimension = TInputImage::ImageDimension };

  /** Pixel Type of the input image */
  typedef typename TInputImage::PixelType                PixelType;
  typedef typename NumericTraits<PixelType>::RealType    RealType;

  /** Type of the output Image */
  typedef TOutputImage      OutputImageType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Set Sigma value */
  void SetSigma( RealType sigma );

protected:
  GradientRecursiveGaussianImageFilter();
  virtual ~GradientRecursiveGaussianImageFilter() {};
  
  /** Generate Data */
  void GenerateData( void );

private:
  GradientRecursiveGaussianImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  
  GaussianFilterPointer         m_SmoothingFilters[ImageDimension-1];
  GaussianFilterPointer         m_DerivativeFilter;
  OutputImageAdaptorPointer     m_ImageAdaptor;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkGradientRecursiveGaussianImageFilter.txx"
#endif

#endif




