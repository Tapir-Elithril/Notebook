# Data shapley  
2025.11  
## Background
data values:a score for each training point reflecting their contribution to the downstream performance  
utility functions:maps any subset of training set N to a score;validation acc for classfication tasks  
data shapley definition in data selection:find the optimal subset of size K that maximize the utility function  (inpractical)->find the top K data points with highest values  
## Rethinking Data Shapley for Data Selection Tasks: Misleads and Merits
data selection:choosing the optimal training sets to maximize final model performance
[goal] theoretical explaination for data shapley’s application(misleads and merits) in data selection
[results] assumptions are needed,only using shapley is not enough(may not be better than random)
[theory] a strong correlation between the effectiveness of Data Shapley in data selection and the fitting residual of the MTM approximation  
comparing the utility of two datasets by hypothesis testing（假设检验）  
no better than random sampling because P(第一类错误) + P(第二类错误)<=1  
relying solely on shapley value is not enough because different utility function may map two datasets to the same Shapley vector   

add constraints can help:Data Shapley can effectively prioritize all clean data points over the problematic ones
Monotonically Transformed Modular Function (MTM)(a sufficient but not necessary condition for utility functions to be effective)  
$v$ is monotonical if $v(S)=f(\omega_0+\sum_{i\in S}\omega_i)$

evaluate the utility functions:fitting quality based on fitting residual  

## LESS: Selecting Influential Data for Targeted Instruction Tuning
LESS:Low-rank gradiEnt Similarity Search:identify the most relevant data for specific capabilities development,targeted instruction tuning  
the problem of gradient of LLM:LLM traditionally fine-tuned on Adam optimizer instead of SGD;variable length causes complicate gradient calculation and gradient mismatch(**natural language data evaluation!**);resource-intensive for storing gradients  
[preliminary] influence formulations[4]:model $\theta^t$,batch size$=1$,loss function $l$,optimizier$=SGD$，learning rate$=\eta_t$  
$$
l(z';\theta^{t+1})-l(z';\theta^t)=-\eta_t<\nabla l(z;\theta^t),\nabla l(z';\theta^t)>
$$
The influence of a data point $z$(trajectory influence) with epoches$=N$:  
$$
Inf_{SGD}(z,z')=\sum_{i=1}^N\overline{\eta_i}<\nabla l(z;\theta_i),\nabla l(z';\theta_i)>
$$
data selection:selecting $z$ to maximize $<\nabla l(z;\theta_i),\nabla l(z';\theta_i)>$ at a warmup training dataset and small number of epoches  
[Entension] Adam influence:
$$
Inf_{Adam}(z,z')=\sum_{i=1}^N\overline{\eta_i}cos(\nabla l(z';\theta_i),\Gamma(z,\theta_i))
$$
cos(A,B):cosine similarity  
**Efficient gradient computation**:LoRA & random projections  
LoRA:freezes the pre-trained weights and adds a low-rank
adaptor to linear layers throughout the network  
Random projections(preserve inner products,JL引理):  
$$
\tilde{\nabla}l(z';\theta_i)=\Pi^T\hat{\nabla}l(z';\theta_i),\Pi\in\mathbb{R}^{P\times d},\Pi_{ij}\sim U(\left\{-1,1\right\})
$$

[result] selects a small subset of the data (5%) that outperforms training on the full dataset

## Data Selection for Fine-tuning Large Language Models Using Transferred Shapley Values
reduce computational cost of Shapley-based data valuation:efficient sampling;a value transfer method(first train a classifer using representations from the target model and then leverage the info extracted from the classifer)  
1)model constraint:retraining->compute Shapley value using a linear model trained on learned representation from the target  
2)dataset constraint:time-complexity\size->sampling method(use only 2% of original training data)  
TS-DSHAPLEY(Transferred Sampling Data Shapley):use a linear classifier as the proxy of the target classifer(**what if the downstream model is not just a classifer**) and use multi-chain Monte Carlo sampling  
representation extraction using the penultimate(倒数第二) layer of pretrained LM and then perform PCA  
Monte Carlo sampling on **subsets** of data(sampling chains) & parallel computing the multiple chains  
Selection:removal  

## “WHAT DATA BENEFITS MY CLASSIFIER?” ENHANCING MODEL PERFORMANCE AND INTERPRETABILITY THROUGH INFLUENCE-BASED DATA SELECTION
[Goal] not to get a value for data but analyze what **type**/features of data can be utilized to enhance performance  
Tree-based influence estimation models  

## DsDm: Model-Aware Dataset Selection with Datamodels
[Problem] selecting data based on human notion,namely the similarity with "high quality" data sources may not increase,or even hurt performance campared to randomly selecting data  
[Solution] framing dataset selection as an optimization problem for find the subset that maximizes the performance  
low quality text data:spam,poor writing,nonsense text,documents with fewer than 5 sentences...  
[Problem] training model for each subset to find the best is computationally infeasible  
[Solution] datamodels:estimate the loss based on a general prediction function(linear in DsDm)  
method:a supervised regression task  
TRAK:transform the original problem to a convex learning problem  

||Influence function|Data Shapley|Datamodel|
|----|----|----|----|
|Definition|how prediction changes if a datapoint is removed|the average of performance boost if a certain point is added to a subset|predicting predictions from training data|
|Method|mariginal benefit|credit allocation|prediction model based on influence function|
|Time complexity|$O=(np)\\$Inverse Hessian matrix|$O(2^n)$|$O=(np)\\$|
|Advantage|efficient|fairness|prediction framework|
|Application|big data|small data|online|  
  
## Superfiltering: Weak-to-Strong Data Filtering for Fast Instruction-Tuning
[Problem] data filtering cost much due to the involvement of LLMs  
[Solution] use a easier model and try to achieve the close performance with much faster speed and lower expenses  

## MODERATE CORESET: A UNIVERSAL METHOD OF DATA SELECTION FOR REAL-WORLD DATA-EFFICIENT DEEP LEARNING
[Problem] the existing method(first count the scores for each data point and select the points whose score is in a certain range) is not robust to the changes of the scenarios  
[Solution] a moderate coreset built based on score median(as proxy)  

## Data agent for feature engineering
critic agent -> potential error data  
generator/repair agent -> repair data semantically  
[problem] the critic agent may need to read the whole dataset and it is rather difficult to find the **critical** error data  
[possible solution] A combination of pre-selection and query,a partition of input data and a quantitatively criticality evaluation metric  

## To be considered 
1.Which one is better? 
data selection -> critical data -> find errors -> repair  
find errors -> data selection -> critical error data -> repair  
a brand new definition for data shapley in repairment task:how much improvement we can get if we repair an error correctly(seems not pracitical)  
[Answer] the first is better based on the theorem made in [1],the top-k data must be the dirty data  

2.In the big data era,training two or three epoches in the process of deep learning can be extremely time-consuming,so even we apply Monta Carlo sampling,it can still be too slow for us to get the result  
Also,it can be so time-consuming to train many models(see the (6) below)  
[Answer] Influence score using LoRA and random projection[3]  
Or Transferred Sampling Data Shapley[5]  
Or Datamodelling using TRAK[14]  

3.**the process may be as follows**:  
(0) initialize
kth iteration:
    (1)know the shapley value/influence(gradient) score of each data point after training
    (2)find the top-k data points with the lowest(may be negative) shapley value or the points with value below a specific threshold    
    (3)query a pre-trained expert model for correction,the expert model should be taught about the common mistakes happen in database and fine-tuned for the specific dataset  
    (4)get the repaired data  
    (5)substitute the original dataset for the repaired data  
    (6)train the model again to see whether acc improved  
stop iteration when the model's performance begin to decrease or the acc increase below a threshold  

The problems/challenges are:  
Use shapley or influence score(gradient) or other ways(like Banzhaf index=voting[12] or reinforcement learning[13])?**Why we choose this metric**?
[Answer] Similarity-based may not be effective enough[14].Therefore,we'd better not *detect* erronous data manually or even using LM.Our LM is only used for repairment  
Shapley value is transferable and fair  
TMC-Shapley requires the model to be retrained and evaluated multiple times  
KNN-Shapley:model-agnostic(not tailored to a specific use),cannot guarantee downstream classifier  
influence score for its ease in computing  
reinforcement learning:complex design & poor convergence[11]  

The expert model should be pretrained on what and how to fine-tune it on our target model?or we just use the similarity to few-shot examples embodying a specific error and how to repair(like [3])  
[Answer] Using a fine-tuned expert model by representation extraction in [5]  

The HALLUCINATION problem:how to ensure the model's repair is correct(especially for those with infinite repair region)  
The model may try to repair all the data provided even if the provided data is correct,but this can be strongly avoided in the process of selection[1]  

4.If the target model is a language model(the data type is in natural language),more investigation on the error of natural language data(especially the semantic understanding error) is needed  

## Reference
[1]Rethinking Data Shapley for Data Selection Tasks: Misleads and Merits  
[2]Opendataval:a unified benchmark for data valuation(data shapley can be effective for mislabelled or noisy data detection)  
[3]LESS: Selecting Influential Data for Targeted Instruction Tuning  
[4]Estimating training data influence by tracing gradient descent  
[5]Data Selection for Fine-tuning Large Language Models Using Transferred Shapley Values  
Data Shapley for mislabeled:  
[6]Understanding black-box predictions via influence functions  
[7]Dataset cartography: Mapping and diagnosing datasets with training dynamics  
[8]Data shapley: Equitable valuation of data for machine learning  
Data Shapley for spelling mistakes or grammatical errors:  
[9]Adv-bert: Bert is not robust on misspellings! generating nature adversarial samples on bert  
[10]Noisy text data: Achilles’ heel of bert  
[11]“WHAT DATA BENEFITS MY CLASSIFIER?” ENHANCING MODEL PERFORMANCE AND INTERPRETABILITY THROUGH INFLUENCE-BASED DATA SELECTION  
[12]Data Banzhaf: A Robust Data Valuation Framework for Machine Learning  
[13]Data valuation using reinforcement learning  
[14]DsDm: Model-Aware Dataset Selection with Datamodels  
[15]Superfiltering: Weak-to-Strong Data Filtering for Fast Instruction-Tuning
[16]MODERATE CORESET: A UNIVERSAL METHOD OF DATA SELECTION FOR REAL-WORLD DATA-EFFICIENT DEEP LEARNING  

[Insight]
Recently,most data repairing methods base on the database constraints or the data themselves,which may not improve the downstream performance and can be exhausting in repairing.Actually,while there are many erroneous data,the number of data that greatly affect model performance(we call these data the data target) may not be such large.In this paper,we combine the process of data selection for erroneous data and data repairing by leveraging the effect caused by the dirty data.We mainly take advantage of data shapley and influence score for data error detection{generate text summary} and use a pretrained expert model for efficient and exquisite repairment.Finally,we implement a complete,intelligent self-improving database system which can process various kinds of data types including numerics,vectors,texts,...Our system {test_result...}