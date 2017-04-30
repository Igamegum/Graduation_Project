////////////////////////////KALMANFLITER///////////////////////////////////////////

void KalManFliter()
{
	const int winHeight=480;  
	const int winWidth=640;

	cv::RNG rng;
	const int stateNum=4;                                      //状态值4×1向量(x,y,△x,△y)  
	const int measureNum=2;                                    //测量值2×1向量(x,y)    
	cv::KalmanFilter KF(stateNum, measureNum, 0);     

	KF.transitionMatrix *= (Mat_<float>(4, 4) <<1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1);  //转移矩阵A  
	setIdentity(KF.measurementMatrix);                                             //测量矩阵H  
	setIdentity(KF.processNoiseCov, Scalar::all(1e-5));                            //系统噪声方差矩阵Q  
	setIdentity(KF.measurementNoiseCov, Scalar::all(1e-8));                        //测量噪声方差矩阵R  
	setIdentity(KF.errorCovPost, Scalar::all(1));                                  //后验错误估计协方差矩阵P  
	rng.fill(KF.statePost,RNG::UNIFORM,0,winHeight>winWidth?winWidth:winHeight);   //初始状态值x(0)  
	Mat measurement = Mat::zeros(measureNum, 1, CV_32F);                          //初始测量值x'(0)，因为后面要更新这个值，所以必须先定义  



	float origin_x = (result.hand_area[0][1] + result.hand_area[0][3])/2;                                                                                               
	float origin_y = result.hand_area[0][2];                                                                                                                            
	std::cout<<"Origin Point "<< origin_x << "   "<<origin_y<<std::endl;                                                                                                

	CvScalar _color({130,0,75});                                                                                                                                        
	cv::circle(src_img,cv::Point(origin_x,origin_y),15,_color,3);                                                                                                       

	measurement.at<float>(0) = origin_x;                                                                                                                                
	measurement.at<float>(1) = origin_y;                                                                                                                                
	KF.correct(measurement);                                                                                                                                            

	Mat prediction = KF.predict();                                                                                                                                      
	float predict_x = prediction.at<float>(0);                                                                                                                          
	float predict_y = prediction.at<float>(1);                                                                                                                          
	std::cout<<"Predict Point"<< predict_x << "   "<<predict_y<<std::endl<<std::endl; 
}
