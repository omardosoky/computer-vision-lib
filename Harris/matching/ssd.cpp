std::pair<int,float> ncc (cv::Mat ROI , std::Vector<cv::Mat> Target){
    int ssd_id =0;
    float ssd_val =2147483647;
    for(int k=0;k<Target.size();k++){
        if(ROI.size() != Target[k].size())
            // error
            break;
        int sum_df =0;
        for(int i =0;i<ROI.rows;i++)
            for(int j=0;j<ROI.cols;j++){
                sumdf += ROI.at<uchar>(i,j)-Targer[k].at<uchar>(i,j);
                sumdf = pow(sumdf,2);
            }
        if(sumdf <= ssd_val){
            ssd_val = sumdf;
            ssd_id =k;
        }
        
    }
    return (std::make_pair(ssd_id,ssd_val));
}