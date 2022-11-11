#include <iostream>
#include <cstdlib>

#include <cstring>
#include <vector>
#include <cmath>
#include <sstream>
#include <random>

// Librerías de OpenCV
// Librería que contiene las definiciones de las estructuras básicas
// para representar imágenes a través de Matrices y sus operaciones
#include <opencv2/core/core.hpp>

// Librería para preprocesamiento y manipulación de imágenes
#include <opencv2/imgproc/imgproc.hpp>

// Librería para creación de ventanas y manejo de GUI
#include <opencv2/highgui/highgui.hpp>

// Librería para manejar los códecs de los diferentes formatos de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp>

// Librería para lectura de vídeo
#include <opencv2/video/video.hpp>

// Librería para escritura de vídeo
#include <opencv2/videoio/videoio.hpp>

#include <chrono>

// Espacio de nombres de OpenCV
using namespace cv;

using namespace std; // Funciones propias de C++

using namespace std::chrono;

Mat frame;
Mat gris;
Mat binaria;
Mat hsv;
Mat efecto;

int mT = 0;
int pixel;
int nivel = 0, hefe = 0;

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
}

int main(int argc, char *argv[])
{

  VideoCapture video(0);

  if (!video.isOpened())
    return 0;

  namedWindow("Video", WINDOW_AUTOSIZE);
  namedWindow("Efecto", WINDOW_AUTOSIZE);
  namedWindow("Imagen Niveles Gris", WINDOW_AUTOSIZE);

  createTrackbar("Nivel gris", "Video", &mT, 9, eventoTrack, NULL);
  createTrackbar("Efecto", "Video", &hefe, 4, eventoTrack, NULL);

  while (true)
  {
    video >> frame;
    resize(frame, frame, Size(), 0.5, 0.5);
    cvtColor(frame, gris, COLOR_BGR2GRAY);

    // Parte 1
    for (int i = 0; i < gris.rows; i++)
    {
      for (int j = 0; j < gris.cols; j++)
      {
        int pixel = gris.at<uchar>(i, j);
        gris.at<uchar>(i, j) = nNiveles(pixel);
      }
    }

    // Parte 2
    if (hefe == 0)
    {
      cvtColor(frame, efecto, COLOR_BGR2Lab);
      imwrite("imagenEfecto.jpg", efecto);
    }
    else if (hefe == 1)
    {
      cvtColor(frame, efecto, COLOR_BGR2YCrCb);
      imwrite("imagenEfecto.jpg", efecto);
    }
    else if (hefe == 2)
    {
      cvtColor(frame, efecto, COLOR_BGR2HSV);
      imwrite("imagenEfecto.jpg", efecto);
    }
    else if (hefe == 3)
    {
      cvtColor(frame, efecto, COLOR_BGR2GRAY);
      imwrite("imagenEfecto.jpg", efecto);
    }

    cv::imshow("Video", frame);
    cv::imshow("Efecto", efecto);
    cv::imshow("Imagen Niveles Gris", gris);

    if (waitKey(23) == 27)
      break;
  }

  video.release();
  destroyAllWindows();

  return 0;
}