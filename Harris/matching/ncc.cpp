std::pair<int,float> ncc (cv::Mat ROI , std::Vector<cv::Mat> Target){
    int corr_id =0;
    float corr_val =0;
    for(int k=0;k<Target.size();k++){
        if(ROI.size() != Target[k].size())
            // error
            break;
        int mul_sum =0 , sum_roi=0,sum_target=0;
        for(int i =0;i<ROI.rows;i++)
            for(int j=0;j<ROI.cols;j++){
                mul_sum += ROI.at<uchar>(i,j)*Targer[k].at<uchar>(i,j);
                sum_roi += pow(ROI.at<uchar>(i,j),2);
                sum_target += pow(Targer[k].at<uchar>(i,j),2);
            }
        sum_roi = sqrt(sum_roi);
        sum_target = sqrt(sum_target);
        float corr = float(mul_sum)/(sum_roi*sum_target);
        if(corr > corr_val){
            corr_val = corr;
            corr_id = k;
        }
    }
    return (std::make_pair(corr_id,corr_val));
}