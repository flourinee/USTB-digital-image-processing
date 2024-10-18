#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void proc(string* path,string* out_path,int laplace_size,int bulrsize,float coredata[]){
	Mat img=imread(*path);
	imshow("src",img);
	Mat dest,tmp;
	tmp = Mat::ones( bulrsize, bulrsize, CV_32F )/ (float)(bulrsize*bulrsize);
	Mat kernel(laplace_size,laplace_size,CV_32F,coredata);
	filter2D(img,img,-1,tmp);
	filter2D(img,dest,-1,kernel);
	
	imshow("dest",dest);
	imwrite(*out_path,dest);
	waitKey(0);
}
int main(){
	float core[9]={0,-1,0,-1,5,-1,0,-1,0};
    string img1_path="./img/img1.jfif"; 
    string img2_path="./img/img2.jfif"; 
    string img1_out_path="./img/imgout1.jpg"; 
    string img2_out_path="./img/imgout2.jpg"; 
    proc(&img1_path,&img1_out_path,3,2,core);
    proc(&img2_path,&img2_out_path,3,2,core);
    return 0;
}