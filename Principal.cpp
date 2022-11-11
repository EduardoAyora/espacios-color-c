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
using namespace std::chrono;

Mat frame;
Mat gris;
Mat binaria;
Mat hsv;
Mat efecto;
Mat colorNiveles;
vector<Mat> canales;

int niveles = 0;
int nivelesAzul = 0;
int nivelesVerde = 0;
int nivelesRojo = 0;
int pixel;
int nivel = 0, hefe = 0;

int nNiveles(int pixel, int niveles)
{
  if (niveles == 0)
    return 0;
  double rango_niveles = 256 / niveles;
  int numero_nivel = (int)pixel / rango_niveles;
  int rango_inferior = numero_nivel * rango_niveles;
  return rango_inferior;
}

void eventoTrack(int v, void *data)
{
  imwrite("imagenEfecto.jpg", efecto);
}

int main(int argc, char *argv[])
{

  VideoCapture video(0);

  if (!video.isOpened())
    return 0;

  namedWindow("Video", WINDOW_AUTOSIZE);
  namedWindow("Efecto", WINDOW_AUTOSIZE);
  namedWindow("Imagen Niveles Gris", WINDOW_AUTOSIZE);
  namedWindow("Imagen Niveles Colores", WINDOW_AUTOSIZE);

  createTrackbar("Nivel gris", "Video", &niveles, 255, eventoTrack, NULL);
  createTrackbar("Nivel azul", "Video", &nivelesAzul, 255, eventoTrack, NULL);
  createTrackbar("Nivel verde", "Video", &nivelesVerde, 255, eventoTrack, NULL);
  createTrackbar("Nivel rojo", "Video", &nivelesRojo, 255, eventoTrack, NULL);
  createTrackbar("Efecto", "Video", &hefe, 3, eventoTrack, NULL);

  while (true)
  {
    video >> frame;
    resize(frame, frame, Size(), 0.5, 0.5);
    cvtColor(frame, gris, COLOR_BGR2GRAY);

    split(frame, canales);
    // Parte 1
    for (int i = 0; i < gris.rows; i++)
    {
      for (int j = 0; j < gris.cols; j++)
      {
        int pixel = gris.at<uchar>(i, j);
        gris.at<uchar>(i, j) = nNiveles(pixel, niveles);

        int pixelBlue = canales[0].at<uchar>(i, j);
        int pixelGreen = canales[1].at<uchar>(i, j);
        int pixelRed = canales[2].at<uchar>(i, j);

        canales[0].at<uchar>(i, j) = nNiveles(pixelBlue, nivelesAzul);
        canales[1].at<uchar>(i, j) = nNiveles(pixelGreen, nivelesVerde);
        canales[2].at<uchar>(i, j) = nNiveles(pixelRed, nivelesRojo);
      }
    }

    merge(canales, colorNiveles);

    // Parte 2
    if (hefe == 0)
      cvtColor(frame, efecto, COLOR_BGR2Lab);
    else if (hefe == 1)
      cvtColor(frame, efecto, COLOR_BGR2YCrCb);
    else if (hefe == 2)
      cvtColor(frame, efecto, COLOR_BGR2HSV);
    else if (hefe == 3)
      cvtColor(frame, efecto, COLOR_BGR2GRAY);

    cv::imshow("Video", frame);
    cv::imshow("Efecto", efecto);
    cv::imshow("Imagen Niveles Gris", gris);
    cv::imshow("Imagen Niveles Colores", colorNiveles);

    if (waitKey(23) == 27)
      break;
  }

  video.release();
  destroyAllWindows();

  return 0;
}