/* Trabalho de Segurança Usando Opencv + c++ para deteccao de Faces
 *
 * Usaremos para contruir uma deteccao facial:
 *
 * 1 - A classe CascadeClassifier para detectar objetos em um fluxo de vídeo. Particularmente, vamos usar as funções de:
 * 2 - LOAD para carregar um arquivo .xml classificador. Ele pode ser qualquer um de Haar ou um classifer LBP
 * 3 - DetectMultiScale para efectuar a detecção.
 * 4 - Copiar para a pasta do projeto os arquivos haarcascade_frontalface_alt.xml, haarcascade_eye_tree_eyeglasses.xml que esta localizado na pasta do OpenCV
 *
 *
 * Tutorial como contruir uma deteccao de faces
 *
 * http://docs.opencv.org/2.4/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
 *
 */

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "time.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;
using namespace cv;

//Funcoes
void detectAndDisplay(Mat frame);

//variaveis Globais

String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
string window_name = "Video - Deteccao de Faces";
RNG rng(12345);

//metodo main
int main(int argc, const char** argv) {
	CvCapture* capture;
	Mat frame;

	//carregando o cascades
	if (!face_cascade.load(face_cascade_name)) {
		printf("--(!)Erro ao Abrir\n");
		return -1;
	};
	if (!eyes_cascade.load(eyes_cascade_name)) {
		printf("--(!)Erro ao Abrir\n");
		return -1;
	};

	//Carregando live do video
	capture = cvCaptureFromCAM(-1);
	if (capture) {
		while (true) {
			frame = cvQueryFrame(capture);

			//Aplicando o classifier para frame
			if (!frame.empty()) {
				detectAndDisplay(frame);
			} else {
				printf(" --(!) Nao capturado frame -- Break!");
				break;
			}

			int c = waitKey(10);
			if ((char) c == 'c') {
				break;
			}
		}
	}
	return 0;
}

// Funcao que detecta e mostra
void detectAndDisplay(Mat frame) {
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//Detecção de Faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2,
			0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++) {
		Point center(faces[i].x + faces[i].width * 0.5,
				faces[i].y + faces[i].height * 0.5);

		//mostra o desenho no rosto em ellipse
		//ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 0, 255, 0 ), 4, 8, 0 );

		//mostra desenho do rosto em retangulo
		rectangle(frame, faces[i], CV_RGB(0, 255, 0), 2);

		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes;

		//Em cada face, Detectar os olho
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2,
				0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++) {

			Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5,
					faces[i].y + eyes[j].y + eyes[j].height * 0.5);
			int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
			circle(frame, center, radius, Scalar(0, 255, 0), 1, 1, 0);
		}

		//Escreve um cima do Retangulo
		string box_text;
		box_text = "Face Detectada!";

		int pos_x = std::max(faces[i].tl().x - 10, 0);
		int pos_y = std::max(faces[i].tl().y - 10, 0);
		putText(frame, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0,
				CV_RGB(255, 0, 0), 2.0);

	}
	//Mostrar resultado
	imshow(window_name, frame);
}

