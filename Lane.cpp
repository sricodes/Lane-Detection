#include <unistd.h> 
// dats the time library #include <math.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <highgui.h> 
#include <cv.h> 
#include <cxcore.h>
using namespace cv;
int n_dil,n_ero; 
int a =100; 
int b=50; 
int c=10; 
int i=0; 
int min_c=35;
int max_c=60;
int n_smo=3; 
void setup(){ 
  cvNamedWindow("control_1"); 
  cvCreateTrackbar("smoothing","control_1",&n_smo,30, NULL); 
  cvCreateTrackbar("dilation", "control_1", &n_dil,300, NULL); 
  cvCreateTrackbar("errosion", "control_1", &n_ero,100, NULL); 
  cvNamedWindow("canny"); cvCreateTrackbar("min","canny",&min_c,300, NULL);
  cvCreateTrackbar("max", "canny", &max_c,300, NULL); 
  cvNamedWindow("PHough line"); 
  cvCreateTrackbar("Var_1","PHough line",&a,300, NULL); 
  cvCreateTrackbar("var_2", "PHough line", &b,300, NULL); 
  cvCreateTrackbar("vaar_3", "PHough line", &c,300, NULL);
  }
  
  
  int main(int argc, char** argv) {
    Mat src, dst, color_dst,blu,out; 
    Mat less; CvCapture* capture = cvCaptureFromCAM(0); 
    do{ 
      setup(); // src=cvQueryFrame(capture); 
      Mat pic; 
      pic=imread(argv[1], CV_LOAD_IMAGE_COLOR); 
      src=pic; imshow("main", src);
      int x=225; 
      int y=450; 
      int width=600;
      int height=200; 
      Rect roi(x, y, width, height);
      Mat image_roi = src(roi); 
      // line( image_roi, Point(x, y), Point(x+width, y+height), Scalar(0,0,255), 3, 8 );
      imshow("fullltooo",image_roi);
      Mat median; src=image_roi; 
      int l=41; 
      // medianBlur(InputArray src, OutputArray dst, int ksize) medianBlur( src, median,l) ; 
      imshow("med" ,median); int i=41; bilateralFilter ( src, blu, i, i*2, i/2 ); 
      // blur( src, blu, Size( n_smo,n_smo ), Point(-1,-1)); src=median; imshow(" new", blu); 
      if(cvWaitKey(33)==27)break; 
      Canny( src, dst,min_c, max_c, 3 ); 
      imshow("not_filtered" ,dst);
      const Scalar& borderValue=morphologyDefaultBorderValue(); 
      int borderType=BORDER_CONSTANT; int iterations=1;
      Point anchor=Point(-1,-1); Mat kernel = Mat::ones(Size(4, 4), CV_8U); 
      // erode(dst, dst, kernel,anchor,n_ero ,borderType,borderValue);
      // imshow("filtered" ,dst);
      // imshow("can",dst); 
      // Point anchor=Point(-1,-1);
      // int borderType=BORDER_CONSTANT; 
      // const Scalar& borderValue=morphologyDefaultBorderValue(); 
      // erode(dst, dst, 3, anchor, n_ero, borderType,borderValue);
      imshow("morpho",dst); cvtColor( dst, color_dst, CV_GRAY2BGR ); 
      erode(color_dst, color_dst, kernel,anchor,n_ero ,borderType,borderValue);
      dilate(color_dst, color_dst, kernel,anchor,n_dil,borderType,borderValue); 
      imshow("filters" , color_dst); vector<Vec4i> lines; 
      // array of 4 dimension with integer HoughLinesP( dst, lines, 1, CV_PI/180, a, b, c );
      for( size_t i = 0; i < lines.size(); i++ ) 
      { 
        line( color_dst, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
      } 
      imshow("find",color_dst); if(cvWaitKey(33)==27)break; 
      }while(1); // cvReleaseImage(&src); 
      cvDestroyWindow("CV"); 
      return 0 ;
      }





























