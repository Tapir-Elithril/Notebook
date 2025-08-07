current major focus:numeric data & ML model  

### Quality Evaluation
**Error Types.** The types of data errors(a.k.a low-quality data) in a dataset can be classifies mainly into two categories:quantitative error,which describes the abnormal behaviours and errors(missing values,duplicates,obsolete or irrelevant,inconsistencies,mislabels,miscodings,outliers,noise,representation bias) and qualitative error,which describes the constraints,rules and patterns(domain value violations,violations of integrity constraints,syntactic and semantic constraint violations).[1]  

**Data Quality Evaluation Metrics.** How we evaluate the quality of data is based on both subjective(whether the data is timeliness and trust) and objective(how accurate the prediction is and the validity of the data based on context dependence) view.Commly used data evaluation metrics including acc,err,sn,sp,p,r,FM,GM,...MSE,AUC and hybrid evaluation.[2]Despite the variety of data evaluation metrics,no unified quality stardards exist,which is a serious challenge especially in the big data era.Other factors affecting the data quality involves diversity of sources,tremendous volumes of data and fast data change(short timeliness).[3]  

### Data Cleaning
Data cleaning is a method for improving the quality of data so as to achieve the benefitted overall (downstream) performance.For Machine Learning(ML),it can be trained to help boost the effieciency and accuracy of improving.For database,statistical analysis based on database queries give an insight into the effect evaluation. [4]  

**Cleaning Algorithm.** There're four aspects of data cleaning:new abstractions,interfaces,approaches of scalability, and crowdsourcing techniques(like active learning). [4]  
Data cleaning algorithm are classified into three categories:constraint(cstr)-driven,data-driven and hybrid-driven,corresponding to the two categories of error types.[5]  
cstr-driven data repair algorithms includes:  


data-driven data repair algorithms includes:  


hybird-driven data repair algorithms includes:  

However,data cleaning also face challenges including the difficulty in scalability,possible user engagement,semi-structured and unstructured data,new applications for streaming data and privacy & security concerns.[4]  

### Transformers for Tabular Data


### Reference
[1] Data Quality Evaluation of Numeric Data for Classification Tasks  
[2] A review on evaluation metrics for data classification evaluations  
[3] The challenges of data quality and data quality assessment in the big data era  
[4] Data Cleaning: Overview and Emerging Challenges  
[5] Automatic Data Repair: Are We Ready to Deploy?  