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
Mat binaria;
Mat hsv;
Mat efecto;
int pixel;
int nivel = 0, hefe = 0;

void eventoTrack(int v, void *data)
{
    for (int i = 0; i < binaria.rows; i++)
    {
        for (int j = 0; j < binaria.cols; j++)
        {
            pixel = binaria.at<uchar>(i, j);
            if (pixel >= 0 && pixel <= 25)
            {
                binaria.at<uchar>(i, j) = 0;
            }
            if (pixel >= 26 && pixel <= 50)
            {
                binaria.at<uchar>(i, j) = 25;
            }
            if (pixel >= 51 && pixel <= 75)
            {
                binaria.at<uchar>(i, j) = 50;
            }
            if (pixel >= 76 && pixel <= 100)
            {
                binaria.at<uchar>(i, j) = 75;
            }
            if (pixel >= 101 && pixel <= 125)
            {
                binaria.at<uchar>(i, j) = 100;
            }
            if (pixel >= 126 && pixel <= 150)
            {
                binaria.at<uchar>(i, j) = 125;
            }
            if (pixel >= 151 && pixel <= 175)
            {
                binaria.at<uchar>(i, j) = 150;
            }
            if (pixel >= 176 && pixel <= 200)
            {
                binaria.at<uchar>(i, j) = 175;
            }
            if (pixel >= 201 && pixel <= 225)
            {
                binaria.at<uchar>(i, j) = 200;
            }
            if (pixel >= 226 && pixel <= 255)
            {
                binaria.at<uchar>(i, j) = 255;
            }
        }
    }
    cout << "imagen mod" << endl;
}

int main(int argc, char *argv[])
{

    VideoCapture video(0);

    if (video.isOpened())
    {
        namedWindow("Video", WINDOW_AUTOSIZE);
        namedWindow("Ecualizada", WINDOW_AUTOSIZE);
        namedWindow("Efecto", WINDOW_AUTOSIZE);

        createTrackbar("Ecualizador", "Video", &nivel, 255, eventoTrack, NULL);
        createTrackbar("Efecto", "Video", &hefe, 4, eventoTrack, NULL);

        while (3 == 3)
        {

            video >> frame;
            resize(frame, frame, Size(), 0.5, 0.5);
            cvtColor(frame, hsv, COLOR_BGR2GRAY);

            // inRange(hsv, Scalar(nivel), Scalar(255), binaria);
            threshold(hsv, binaria, nivel, 255, 3);

            if (hefe == 0)
            {
                cvtColor(frame, efecto, COLOR_BGR2Lab);
                imwrite("imagenEfecto.jpg",efecto);
            }
            else if (hefe == 1)
            {
                cvtColor(frame, efecto, COLOR_BGR2YCrCb);
                imwrite("imagenEfecto.jpg",efecto);
            }
            else if (hefe == 2)
            {
                cvtColor(frame, efecto, COLOR_BGR2HSV);
                imwrite("imagenEfecto.jpg",efecto);
            }
            else if (hefe == 3)
            {
                cvtColor(frame, efecto, COLOR_BGR2GRAY);
                imwrite("imagenEfecto.jpg",efecto);
            }

            cv::imshow("Efecto", efecto);

            cv::imshow("Video", frame);
            cv::imshow("Ecualizada", binaria);

            if (waitKey(23) == 27)
            {
                break;
            }
        }
        video.release();
        destroyAllWindows();
    }
    destroyAllWindows();

    return 0;
}