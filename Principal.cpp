#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#include <sstream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <chrono>

using namespace cv;
using namespace std;

int mT = 0;
Mat imagen1;
Mat imagenGris;

int nNiveles(int pixel)
{
  if (mT == 0 && pixel >= 0 && pixel <= 25)
    return 0;
  if (mT == 1 && pixel >= 26 && pixel <= 50)
    return 25;
  if (mT == 2 && pixel >= 51 && pixel <= 75)
    return 50;
  if (mT == 3 && pixel >= 76 && pixel <= 100)
    return 75;
  if (mT == 4 && pixel >= 101 && pixel <= 125)
    return 100;
  if (mT == 5 && pixel >= 126 && pixel <= 150)
    return 125;
  if (mT == 6 && pixel >= 151 && pixel <= 175)
    return 150;
  if (mT == 7 && pixel >= 176 && pixel <= 200)
    return 175;
  if (mT == 8 && pixel >= 201 && pixel <= 225)
    return 200;
  if (mT == 9 && pixel >= 226 && pixel <= 255)
    return 225;
  return pixel;
}

void eventoTrack(int v, void *data)
{
  Mat imagenGrisNiveles = imagenGris.clone();
  for (int i = 0; i < imagen1.rows; i++)
  {
    for (int j = 0; j < imagen1.cols; j++)
    {
      int pixel = imagenGrisNiveles.at<uchar>(i, j);
      imagenGrisNiveles.at<uchar>(i, j) = nNiveles(pixel);
    }
  }
  imshow("Imagen Niveles Gris", imagenGrisNiveles);
}

int main(int argc, char *argv[])
{
  imagen1 = imread("Plaza-Roja-Catedral-San-Basilio.jpg", IMREAD_COLOR);
  resize(imagen1, imagen1, Size(), 0.55, 0.55);

  cvtColor(imagen1, imagenGris, COLOR_BGR2GRAY);

  namedWindow("Imagen1 Original", WINDOW_AUTOSIZE);
  namedWindow("Imagen Gris", WINDOW_AUTOSIZE);
  namedWindow("Imagen Niveles Gris", WINDOW_AUTOSIZE);

  createTrackbar("Nivel Gris", "Imagen1 Original", &mT, 9, eventoTrack, NULL);

  imshow("Imagen1 Original", imagen1);
  imshow("Imagen Gris", imagenGris);
  imshow("Imagen Niveles Gris", imagenGris);

  waitKey(0);

  destroyAllWindows();
  return 0;
}
