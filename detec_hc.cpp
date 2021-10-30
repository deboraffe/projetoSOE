#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <vector>


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



using namespace cv;
using namespace std;
int modo=0;
int i=0;

int main(int argc, char** argv) {

	CascadeClassifier faceDetector("haarcascade_frontalface_alt.xml");

	VideoCapture cap(0);

	if(!cap.isOpened())
		return -1;

	//cap.open(0 + CAP_ANY);

	double scale = 0.8;

	while(i<100)
	{
		Mat frame;
		cap>>frame;

		Mat grayscale;
		cvtColor (frame, grayscale, COLOR_BGR2GRAY);
		resize (grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

		vector<Rect> faces;
		faceDetector.detectMultiScale(grayscale, faces, 1.2, 4.5, 0, Size(40,40));
         
        //delay(500); // 300 ms
		for (Rect area:faces)
		{
			Scalar drawColor = Scalar(255,0,0);
			rectangle (frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)), Point(cvRound((area.x + area.width -1)*scale), cvRound((area.y + area.height -1)*scale)), drawColor);
			putText(frame,"Sem mascara", Point(30,30),FONT_HERSHEY_SIMPLEX,1 ,(255,255,255),2,LINE_AA);
			printf("sem mascara\n");
			//system("raspistill -q 100 -o testimage_q100.jpg");
			//delay(1); // 300 ms 
			//return 1; // retorna 1 quando n	
			modo=1;
		}
		if(modo==1)
		{
		 return 1; // retorna 1 quando n	
	    }
		printf("com mascara\n");

		imshow("webcam frame", frame);

		if(waitKey(30) >= 0)
			break;
		i++;
	 //return 2; // retorna 1 quando n
	}

	return 0;
	
}
