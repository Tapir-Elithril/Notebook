
## 目标
低质量数据靶点：什么是低质量的，有哪些（类别），如何识别，如何增强  
  
调研方向：数值类型数据  
数值类型的数据集（结构化的表格类型）：质量是如何评估的（传统数据评估的算法，缺失值，错误值）；传感器/分类器：目前数据修正的方法  
传感器数据做预测/regression，kaggle上找一些数据集（天然有缺陷）  

## Quality Evaluation
### Scaling and assessment of data quality

### Data Quality Evaluation of Numeric Data for Classification Tasks

### A review on evaluation metrics for data classification evaluations

### The challenges of data quality and data quality assessment in the big data era

### A Ardeshir Goshtasby. 2012. Similarity and Dissimilarity Measures. In Image Registration. Springer, 7–66.

### Tabular Data: Deep Learning is Not All You Need
对比树模型与深度学习

## Data cleaning(detection & repairment)
### Data Cleaning: Overview and Emerging Challenges

### Automatic Data Repair: Are We Ready to Deploy?

### Activeclean: Interactive data cleaning for statistical modeling

### Transformers for Tabular Data
Transformer架构处理综述
tabtransformer处理表格数据：数据靶点的识别与处理是否介入llm（llm在数据处理的应用）  
## Datasets
数值类型的有缺陷数据集
(from kaggle)  
[Cafe Sales - Dirty Data for Cleaning Training](https://www.kaggle.com/datasets/ahmedmohamed2003/cafe-sales-dirty-data-for-cleaning-training)  
[Retail Store Sales: Dirty for Data Cleaning](https://www.kaggle.com/datasets/ahmedmohamed2003/retail-store-sales-dirty-for-data-cleaning)  
[World Development Indicators](https://www.kaggle.com/datasets/kaggle/world-development-indicators/data)缺失值，数据对齐问题  
[FIFA 21 messy, raw dataset for cleaning/ exploring](https://www.kaggle.com/datasets/yagunnersya/fifa-21-messy-raw-dataset-for-cleaning-exploring)

(from UCL)  
[Air Quality](https://archive.ics.uci.edu/dataset/360/air+quality)多传感器冲突值、负值异常  

## Comments
因子暴露中性化（量化投资）  
通过统计方法调整投资组合隔离因子影响（回归法、分组标准化）  
文本数据（情感中性化，角色特征，作者人格）  
  
**标注错误**  
Cleanlab
**异常值**   
Isolation forest  
过滤（Z-score，IQR），ai编辑  
**缺失值**  
Missingno矩阵
统计填充，模型填充KNN，生成填充GAN   
**重复**  
特征哈希+Jaccard相似度  
**不一致**  
scaling,normalization  
**偏差数据** 
SMOTE算法 MOLRL框架 对抗网络  
标准化去偏  
平均模型预测率：动态测试集
**噪声**  

研究应着重在噪声并兼顾其他种类缺陷？  

### 关于数据靶点对象（低质量数据）的思考
对抗验证→特征联合分布优化验证机制  
数据靶点→？样本质量  
删去异常点导致测试集表现更差  
误区：数据偏移不意味着质量差（新的有效信息）  
误区：低质量数据是低性能数据  
低性能数据：影响预测准确率  
**低质量数据：明确为异常值、噪声、缺失、标注错误等**  
注意偏移与噪声的区别  
本质还是数据清洗  
低性能数据包含特殊情况，是提高泛化能力的重要保障，不是治疗的对象  
进一步思考，需要治疗的只是数据，还是特征构建，训练，验证的整个过程  
如果只是数据清洗，可能能写的东西不多→重点上下游性能表现的整体提升（不仅是治病，还要康复，健壮）  

## Other
数据质量评估维度  
- 完整性：缺失值比例、数据覆盖度  
- 准确性：值域检查、业务规则验证  
- 一致性：跨系统一致性、时间序列一致性  
- 时效性：数据新鲜度、更新频率  
- 唯一性：重复数据检测  
  
常见缺陷类型及修正方法  
- 缺失值处理：  
  删除法  
  均值/中位数/众数填补  
  模型预测填补(如KNN、回归)  
  多重插补法  
- 异常值处理：  
  统计方法(3σ原则、IQR)  
  基于距离的方法  
  基于密度的方法(LOF)  
  基于聚类的方法  
  基于机器学习的方法(隔离森林、One-Class SVM)  
- 不一致数据：  
  数据标准化(归一化、标准化)  
  单位统一化  
  业务规则验证与修正  
- 噪声数据：  
  平滑技术(移动平均、指数平滑)  
  分箱技术  
  回归分析  
